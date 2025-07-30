import numpy as np
import scipy.fft as fft
import scipy.interpolate as spi
import matplotlib.pyplot as plt
import scipy.optimize as opt

data = np.loadtxt('nuttall.txt')

atts = data[0]
alphas = data[1]
betas = data[2]

# def sqerr(xs, ys, f):
#     err = 0
#     for i in range(len(xs)):
#         x = xs[i]
#         dy = ys[i]
#         fy = f(x)
#         err += (fy - dy)**2
#     return err

# def compErr(d):
#     p = np.polyfit(atts, alphas, d)
#     return sqerr(atts, alphas, lambda x : np.polyval(p, x))

# p = np.polyfit(atts, alphas, 2)

# plt.plot(atts, alphas)
# x = np.linspace(atts[0], atts[-1], 1000)
# plt.plot(x, np.polyval(p, x))
# plt.show()
plt.plot(atts, alphas)
plt.show()