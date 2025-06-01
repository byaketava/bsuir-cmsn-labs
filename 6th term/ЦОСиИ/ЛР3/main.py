import matplotlib

matplotlib.use("TkAgg")
import numpy as np
import matplotlib.pyplot as plt


def plot_signal(ax, t, signal, title, xlabel="Время, с", ylabel="Амплитуда"):
    ax.set_title(title, fontsize=8)
    ax.plot(t, signal)
    ax.grid(True)
    ax.legend()


# Настройка сетки для графиков
gridsize = (11, 4)
plt.figure(figsize=(20, 10))
ax1 = plt.subplot2grid(gridsize, (0, 0), colspan=2, rowspan=2)
ax2 = plt.subplot2grid(gridsize, (0, 2), colspan=2, rowspan=2)
ax3 = plt.subplot2grid(gridsize, (2, 0), colspan=2, rowspan=2)
ax4 = plt.subplot2grid(gridsize, (2, 2), colspan=2, rowspan=2)
ax5 = plt.subplot2grid(gridsize, (4, 0), colspan=2, rowspan=2)
ax6 = plt.subplot2grid(gridsize, (4, 2), colspan=2, rowspan=2)
ax7 = plt.subplot2grid(gridsize, (6, 0), colspan=2, rowspan=2)
ax8 = plt.subplot2grid(gridsize, (6, 2), colspan=2, rowspan=2)
ax9 = plt.subplot2grid(gridsize, (8, 1), colspan=2, rowspan=2)

K1 = 1  # D1 без изменений
K2 = 0  # Обнуление D2
K3 = 0  # Обнуление D3

# 1. Дискретизация сигнала y(t) = 2sin(t) + 3cos(t)
N = 1024
x = np.linspace(0, 2 * np.pi, N)
y = 2 * np.sin(5 * x) + np.cos(3 * x)

# Визуализация исходного сигнала
plot_signal(ax1, x, y, "Сигнал f(t) = 2sin(5x)+cos(3x)")

# 2. Добавление шума
noise = np.random.uniform(-1, 1, N)
y_noisy = y + noise

# Визуализация зашумленного сигнала
plot_signal(ax2, x, y_noisy, "Зашумленный сигнал")

# 3. DWT с вейвлетом Добеши D4
h_analysis = np.array(
    [
        -0.010597401784997278,
        0.0328830116668852,
        0.03084138183556076,
        -0.18703481171888114,
        -0.027983769416859854,
        0.6308807679298587,
        0.7148465705529154,
        0.23037781330885523,
    ]
)
g_analysis = h_analysis[::-1].copy()
g_analysis[::2] *= -1  # Чередуем знаки

h_synthesis = h_analysis[::-1]
g_synthesis = g_analysis[::-1]


def convolve_circular(x, filter):
    N = len(x)
    filter_padded = np.pad(filter, (0, N - len(filter)), mode="constant")
    x_fft = np.fft.fft(x, N)
    filter_fft = np.fft.fft(filter_padded, N)
    return np.real(np.fft.ifft(x_fft * filter_fft))


def downsample(x):
    return x[::2] * np.sqrt(2)


def dwt_level(x, h, g):
    N = len(x)
    if N % 2 != 0:
        x = np.pad(x, (0, 1))
    y_low = convolve_circular(x, h)
    y_high = convolve_circular(x, g)
    return downsample(y_low), downsample(y_high)


def dwt_full(x, h, g, L):
    coeffs = []
    current = x.copy()
    for _ in range(L):
        a, d = dwt_level(current, h, g)
        coeffs.append((a, d))
        current = a.copy()
    return coeffs


L = 3
coefficients = dwt_full(y_noisy, h_analysis, g_analysis, L)

# Визуализация компонент DWT
for l in range(L):
    if l == 0:
        t_A = np.linspace(x[0], x[-1], len(coefficients[l][0]))
        t_D = np.linspace(x[0], x[-1], len(coefficients[l][1]))

        plot_signal(ax3, t_A, coefficients[l][0], title=f"Аппроксимация A{l + 1}")
        plot_signal(ax4, t_D, coefficients[l][1], title=f"Детали D{l + 1}")

    if l == 1:
        t_A = np.linspace(x[0], x[-1], len(coefficients[l][0]))
        t_D = np.linspace(x[0], x[-1], len(coefficients[l][1]))

        plot_signal(ax5, t_A, coefficients[l][0], title=f"Аппроксимация A{l + 1}")
        plot_signal(ax6, t_D, coefficients[l][1], title=f"Детали D{l + 1}")
    if l == 2:
        t_A = np.linspace(x[0], x[-1], len(coefficients[l][0]))
        t_D = np.linspace(x[0], x[-1], len(coefficients[l][1]))

        plot_signal(ax7, t_A, coefficients[l][0], title=f"Аппроксимация A{l + 1}")
        plot_signal(ax8, t_D, coefficients[l][1], title=f"Детали D{l + 1}")


# 4. Обратное DWT
def upsample(x):
    res = np.zeros(len(x) * 2)
    res[::2] = x / np.sqrt(2)
    return res


def idwt_level(a, d, h_s, g_s):
    a_up = upsample(a)
    d_up = upsample(d)
    rec_a = convolve_circular(a_up, h_s)
    rec_d = convolve_circular(d_up, g_s)
    return rec_a + rec_d


def idwt_full(coeffs, h_s, g_s):
    current = coeffs[-1][0].copy()
    for i in reversed(range(len(coeffs))):
        current = idwt_level(current, coeffs[i][1], h_s, g_s)
    return current


# 5. Коррекция компонент
coefficients[0] = (coefficients[0][0], coefficients[0][1] * K1)
coefficients[1] = (coefficients[1][0], coefficients[1][1] * K2)
coefficients[2] = (coefficients[2][0], coefficients[2][1] * K3)

y_corrected = idwt_full(coefficients, h_synthesis, g_synthesis)

# Визуализация сигнала после коррекции

plot_signal(ax9, x, y_corrected, "Восстановленный")

# Настройка layout
plt.tight_layout()
plt.show()

# Оценка ошибки
mse = np.mean((y - y_corrected) ** 2)
print(f"MSE between original and corrected signal: {mse:.6f}")
