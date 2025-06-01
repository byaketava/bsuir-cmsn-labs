import matplotlib.pyplot as plt
import numpy as np
import soundfile as sf

def fft(x):
    x = np.asarray(x, dtype=complex)
    N = len(x)
    if N == 1:
        return x
    
    # Дополняем нулями до ближайшей степени двойки
    if N % 2 != 0 or (N & (N - 1)) != 0:  # Проверяем, не степень ли двойки
        next_pow2 = 2 ** ((N - 1).bit_length())
        x = np.pad(x, (0, next_pow2 - N), mode='constant')
        N = next_pow2

    X_even = fft(x[::2])
    X_odd = fft(x[1::2])
    factor = np.exp(-2j * np.pi * np.arange(N) / N)
    X = np.zeros(N, dtype=complex)
    X[:N//2] = X_even + factor[:N//2] * X_odd
    X[N//2:] = X_even + factor[N//2:] * X_odd
    return X

def ifft(X):
    X = np.asarray(X, dtype=complex)
    N = len(X)
    if N == 1:
        return X
    
    # Дополняем нулями до ближайшей степени двойки
    if N % 2 != 0 or (N & (N - 1)) != 0:  # Проверяем, не степень ли двойки
        next_pow2 = 2 ** ((N - 1).bit_length())
        X = np.pad(X, (0, next_pow2 - N), mode='constant')
        N = next_pow2

    # Вычисляем IFFT через FFT
    x = fft(np.conj(X))
    return np.conj(x) / N

def plot_signal(ax, t, signal, title, xlabel="Время, с", ylabel="Амплитуда", xlim=None):
    ax.set_title(title, fontsize=12)
    ax.plot(t, signal, label=title.split()[0])
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.grid(True)
    if xlim:
        ax.set_xlim(xlim)
    ax.legend()

def plot_spectrum(ax, freq, mag, title, xlabel="Частота, Гц", ylabel="Амплитуда", xlim=None):
    ax.set_title(title, fontsize=12)
    ax.stem(freq, mag, label=title.split()[0])
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.grid(True)
    if xlim:
        ax.set_xlim(xlim)
    ax.legend()

def save_wav(signal, filename, fs):
    """Сохранение сигнала в WAV-файл с нормализацией."""
    scaled = signal / np.max(np.abs(signal)) * 0.99
    sf.write(filename, scaled, fs)

def main():
    # Параметры сигнала
    fs = 10     # частота дискретизации (Гц)
    T = 10      # длительность сигнала (с)
    N = fs * T  # длина сигнала

    # Генерация сигнала
    t = np.linspace(0, T, fs * T, endpoint=False)
    y = np.cos(2*t) + 2 * np.sin(t)

    # Настройка сетки для графиков
    gridsize = (9, 4)
    fig = plt.figure(figsize=(15, 8))
    fig.suptitle("Анализ сигнала y(t) = cos(2t) + 2sin(t)", fontfamily="serif", fontsize=16)
    ax1 = plt.subplot2grid(gridsize, (0, 0), colspan=2, rowspan=2)
    ax2 = plt.subplot2grid(gridsize, (0, 2), colspan=2, rowspan=2)
    ax3 = plt.subplot2grid(gridsize, (2, 0), colspan=2, rowspan=2)
    ax4 = plt.subplot2grid(gridsize, (2, 2), colspan=2, rowspan=2)
    ax5 = plt.subplot2grid(gridsize, (4, 0), colspan=2, rowspan=2)
    ax6 = plt.subplot2grid(gridsize, (4, 2), colspan=2, rowspan=2)
    ax7 = plt.subplot2grid(gridsize, (6, 1), colspan=2, rowspan=2)

    # График исходного сигнала
    plot_signal(ax1, t, y, "Исходный сигнал", xlim=(0, 10))

    # Вычисление FFT и построение спектра
    Y = fft(y)
    N_fft = len(Y)
    freq = np.linspace(0, fs/2, N_fft//2)
    mag = np.abs(Y[:N_fft//2])
    print("FFT проверка:", np.allclose(Y, np.fft.fft(y, n=N_fft)))

    plot_spectrum(ax2, freq, mag, "Амплитудный спектр", xlim=(0, 5))

    # Восстановление исходного сигнала
    y_original_reconstructed = ifft(Y).real[:N]  # Обрезаем до исходной длины N
    print("IFFT проверка:", np.allclose(y_original_reconstructed, np.fft.ifft(Y, n=N_fft).real[:N]))
    print("Сигнал проверка:", np.allclose(y, y_original_reconstructed, atol=1e-10))

    plot_signal(ax3, t, y_original_reconstructed, "Восстановленный исходный сигнал", xlim=(0, 10))

    # Модификации в частотной области
    # Первая модификация - уменьшение амплитуды
    scale_factor = 0.5
    Y_mod1 = Y * scale_factor
    plot_spectrum(ax4, freq, np.abs(Y_mod1[:N_fft//2]), f"Спектр с уменьшенной амплитудой ({scale_factor})", xlim=(0, 5))

    y_reconstructed1 = ifft(Y_mod1).real[:N]
    plot_signal(ax5, t, y_reconstructed1, "Сигнал с уменьшенной амплитудой", xlim=(0, 10))

    # Вторая модификация - обнуление низких частот с учетом симметрии
    f_cutoff = 1  # Пороговая частота (Гц), чтобы повлиять на sin(t)
    k_cutoff = int(f_cutoff * N_fft / fs)  # Используем N_fft для точности
    Y_mod2 = Y.copy()
    Y_mod2[:k_cutoff] = 0
    Y_mod2[-k_cutoff:] = 0  # Учет симметрии спектра

    plot_spectrum(ax6, freq, np.abs(Y_mod2[:N_fft//2]), f"Спектр с обнулёнными низкими частотами (< {f_cutoff} Гц)", xlim=(0, 5))

    y_reconstructed2 = ifft(Y_mod2).real[:N]
    plot_signal(ax7, t, y_reconstructed2, "Сигнал без низких частот", xlim=(0, 10))

    # Настройка layout
    plt.tight_layout()
    plt.show()

    # Сохранение сигналов в файлы
    for signal, filename in [
        (y, "original.wav"),
        (y_original_reconstructed, "original_reconstructed.wav"),
        (y_reconstructed1, "amplitude_modified.wav"),
        (y_reconstructed2, "frequency_filtered.wav")
    ]:
        save_wav(signal, filename, fs)

    print("Сигналы сохранены в файлы:")
    print("- original.wav")
    print("- original_reconstructed.wav")
    print("- amplitude_modified.wav")
    print("- frequency_filtered.wav")

if __name__ == "__main__":
    main()