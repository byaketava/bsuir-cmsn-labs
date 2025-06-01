import matplotlib.pyplot as plt
import numpy as np
import soundfile as sf
import time


def dft(x):
    x = np.asarray(x, dtype=complex)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)


def idft(X):
    X = np.asarray(X, dtype=complex)
    N = X.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(2j * np.pi * k * n / N)
    return (np.dot(M, X) / N).real


# Прямая свертка
def convolve_direct(signal1, signal2):
    N = len(signal1)
    M = len(signal2)
    y_len = N + M - 1
    y = np.zeros(y_len)
    for n in range(y_len):
        for k in range(N):
            if 0 <= n - k < M:
                y[n] += signal1[k] * signal2[n - k]
    return y


# Свертка через FFT
def convolve_fft(signal1, signal2):
    N = len(signal1) + len(signal2) - 1
    X = dft(np.pad(signal1, (0, N - len(signal1))))
    H = dft(np.pad(signal2, (0, N - len(signal2))))
    return np.real(idft(X * H))


# Прямая корреляция
def correlate_direct(signal1, signal2):
    N = len(signal1)
    M = len(signal2)
    corr_len = N + M - 1
    corr = np.zeros(corr_len)
    for lag in range(-M + 1, N):
        sum_val = 0
        for n in range(N):
            if 0 <= n - lag < M:
                sum_val += signal1[n] * signal2[n - lag]
        corr[lag + M - 1] = sum_val
    return corr


# Корреляция через FFT
def correlate_fft(signal1, signal2):
    N = len(signal1) + len(signal2) - 1
    X = dft(np.pad(signal1, (0, N - len(signal1))))
    Y = dft(np.pad(signal2[::-1], (0, N - len(signal2))))
    result = np.real(idft(X * Y))
    if np.allclose(signal1, signal2):
        start = (len(result) - len(signal1)) // 2
        return result[start : start + len(signal1)]
    return result


def plot_signal(ax, t, signal, title, xlabel="Время, с", ylabel="Амплитуда"):
    ax.set_title(title, fontsize=8)
    ax.plot(t, signal)
    ax.set_xlabel(xlabel, fontsize=8)
    ax.set_ylabel(ylabel, fontsize=8)
    ax.grid(True)
    ax.legend()


def save_wav(signal, filename, fs):
    """Сохранение сигнала в WAV-файл с нормализацией."""
    scaled = signal / np.max(np.abs(signal)) * 0.99
    sf.write(filename, scaled, fs)


def benchmark(func, *args):
    start = time.time()
    result = func(*args)
    duration = time.time() - start
    return duration, result


def main():
    # Параметры
    fs = 200  # Частота дискретизации
    T = 16  # Длительность
    N = fs * T  # Количество отсчетов

    t = np.linspace(0, T, N, endpoint=False)

    # Генерация сигналов
    f = 2 * np.sin(878 * t)
    g = 3 * np.cos(2 * t)

    # Настройка сетки для графиков
    gridsize = (7, 4)
    plt.figure(figsize=(15, 8))
    ax1 = plt.subplot2grid(gridsize, (0, 0), colspan=2, rowspan=2)
    ax2 = plt.subplot2grid(gridsize, (0, 2), colspan=2, rowspan=2)
    ax3 = plt.subplot2grid(gridsize, (2, 0), colspan=2, rowspan=2)
    ax4 = plt.subplot2grid(gridsize, (2, 2), colspan=2, rowspan=2)
    ax5 = plt.subplot2grid(gridsize, (4, 0), colspan=2, rowspan=2)
    ax6 = plt.subplot2grid(gridsize, (4, 2), colspan=2, rowspan=2)

    # 2.1 Прямая свертка и корреляция
    conv_direct = convolve_direct(f, g)
    corr_direct = correlate_direct(f, g)

    # 2.2 Свертка и корреляция через FFT
    conv_fft = convolve_fft(f, g)
    corr_fft = correlate_fft(f, g)

    t_conv = np.linspace(0, 2 * T - 1 / fs, len(conv_direct))
    t_corr = np.linspace(-T + 1 / fs, T - 1 / fs, len(corr_direct))

    # Графики
    plot_signal(ax1, t, f, "Сигнал f(t) = 2sin(878t)")
    plot_signal(ax2, t, g, "Сигнал g(t) = 3cos(2t)")
    plot_signal(ax3, t_conv, conv_direct, "Прямая свертка f * g")
    plot_signal(ax4, t_corr, corr_direct, "Прямая корреляция f ⋆ g")
    plot_signal(ax5, t_conv, conv_fft, "Свертка через DFT f * g")
    plot_signal(ax6, t_corr, corr_fft, "Корреляция через DFT f ⋆ g")

    t1, _ = benchmark(convolve_direct, f, g)
    t2, _ = benchmark(convolve_fft, f, g)

    print(f"Сложность прямой свертки (время): {t1:.4f} сек")
    print(f"Сложность свертки через DFT (время): {t2:.4f} сек")

    # Настройка layout
    plt.tight_layout()
    plt.show()

    # Сохранение
    save_wav(conv_direct, "conv_direct.wav", fs)
    save_wav(conv_fft, "conv_fft.wav", fs)

    # Вывод файлов
    print("Сохранены файлы:")
    print("- conv_direct.wav")
    print("- conv_fft.wav")


if __name__ == "__main__":
    main()
