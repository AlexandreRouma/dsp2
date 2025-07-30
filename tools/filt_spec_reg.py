import numpy as np
import scipy.fft as fft
import scipy.interpolate as spi
import matplotlib.pyplot as plt
import scipy.optimize as opt

def sincFIR(b, N, win):
    lim = b * (N-1) * 0.5
    x = np.linspace(-lim, lim, N)
    taps = np.sinc(x) * win(N)
    taps *= 1 / np.sum(taps)
    return taps

def response(taps, points = 65536):
    # Zero pad
    ztaps = np.concatenate([taps, np.zeros(points - len(taps))])

    # Compute FFT
    ff = fft.fft(ztaps)
    ff = ff[:len(ff)//2]

    # Compite the frequency of each bin
    freqs = np.array(range(points))/points
    freqs = freqs[:len(freqs)//2]*2
    
    # Return the amplitude and phase
    return np.array(freqs), 20*np.log10(np.abs(ff)), np.angle(ff)*180/np.pi

def getSpecs(taps, att = None):
    # Get the response
    freqs,amp,_ = response(taps)
    
    # Find the inflection point
    searchIdx = -1
    mid = len(amp)//2
    last = amp[mid-1]
    for i in range(mid, len(amp)):
        diff = amp[i]-last
        last = amp[i]
        if diff > 0.0:
            searchIdx = i
            break
    searchFreq = freqs[searchIdx-1]
    
    # Find the stop band attenuation if none given
    if att == None:
        maxIdx = np.argmax(amp[searchIdx:]) + searchIdx
        att = amp[maxIdx]

    # Find the transition point
    interp = spi.interp1d(freqs, amp)
    res = opt.root_scalar(lambda x : interp(x)-att, bracket=[0.5, searchFreq])
    return att, res.root - 0.5

def bnuttallw(n, N):
    return 0.3635819 - 0.4891775*np.cos(2*np.pi*n/N) + 0.13659955*np.cos(4*np.pi*n/N) - 0.0106411*np.cos(6*np.pi*n/N)

# def lolw(n, N):
#     return 0.35881115 - 0.48845026*np.cos(2*np.pi*n/N) + 0.14118885*np.cos(4*np.pi*n/N) - 0.01154974*np.cos(6*np.pi*n/N)

def nuttallw(n, N):
    return 0.355768 - 0.487396*np.cos(2*np.pi*n/N) + 0.144232*np.cos(4*np.pi*n/N) - 0.012604*np.cos(6*np.pi*n/N)

def lol2w(n, N):
    return 0.3560283 - 0.48748693*np.cos(2*np.pi*n/N) + 0.1439717*np.cos(4*np.pi*n/N) - 0.01251307*np.cos(6*np.pi*n/N)

def nuttall(N):
    return bnuttallw(np.array(range(N+1)), N+1)[1:]

# def lol(N):
#     return lolw(np.array(range(N+1)), N+1)[1:]

def lol2(N):
    return lol2w(np.array(range(N+1)), N+1)[1:]

def nuttallT(N):
    return nuttallw(np.array(range(N)), N-1)

# Previous prediction                   1824
# nuttall =  [ 7.74932575 -0.99720463]  1859
# nuttallT = [ 7.749348    1.00079625]  1861
# np.blackman = [5.58715521 0.98759599] 1341
# np.hanning = [3.12375105 1.02086163]  751
# bnuttal =  [ 7.79530085 -2.42566429]  1867

def charactWindow(win, minTaps = 32, maxTaps = 1024):
    ii = []
    att = []
    tw = []
    for i in range(minTaps, maxTaps+1):
        taps = sincFIR(0.5, i, win)
        a,t = getSpecs(taps)
        ii.append(i)
        att.append(a)
        tw.append(t)
    res = np.polyfit(1/np.array(tw), ii, 1)
    return res[0], res[1], np.mean(att)

# print(charactWindow(lol2))
# exit(0)

freqs, amps, phases = response(sincFIR(0.5, 101, lol2))
plt.plot(freqs, amps)
freqs, amps, phases = response(sincFIR(0.5, 101, nuttall))
plt.plot(freqs, amps)
plt.show()

# params = []
# alphas = []
# atts = []
# for i in range(1000):
#     p = np.random.uniform(0.0, 1.0, 3)
#     p = np.concatenate([ [p[0] - p[1] + p[2]], p ])
    
#     def winw(n, N):
#         return p[0] - p[1]*np.cos(2*np.pi*n/N) + p[2]*np.cos(4*np.pi*n/N) - p[3]*np.cos(6*np.pi*n/N)
    
#     def win(N):
#         return winw(np.array(range(N+1)), N+1)[1:]

#     try:
#         alpha, beta, att = charactWindow(win, 1000, 1024)
#         params.append(p)
#         alphas.append(alpha)
#         atts.append(-att)
#         print(p, alpha, beta, att)
#     except:
#         pass
    

# best = np.argmax(atts)
# print(alphas[best], atts[best], params[best])

# plt.scatter(atts, alphas)
# plt.show()

# (5.587154476193536, 0.9876436878253441, -75.28786662414193)
# (5.587618976822818, 0.9168073377669025, -75.28843748397959)

# 7.4081533102937565 75.34448596788963 [0.35417698 0.95739698 0.78534742 0.18212743]

p = [0.35417698, 0.95739698, 0.78534742, 0.18212743]

def customWin(N, p):
    def winw(n, N):
        return p[0] - p[1]*np.cos(2*np.pi*n/N) + p[2]*np.cos(4*np.pi*n/N) - p[3]*np.cos(6*np.pi*n/N)
    return winw(np.array(range(N+1)), N+1)[1:]

def optfunc(x):
    x = [ np.power(10, x[0]), np.power(10, x[1]), np.power(10, x[2]) ]
    p = np.concatenate([ [x[0] - x[1] + x[2]], x ])
    test = customWin(301, p)
    test *= 1/np.sum(test)

    p *= 1/np.sum(p)
    print(p)
    plt.plot(test)
    plt.show()

    freqs, amps, _ = response(test)

    # Find the inflection point
    searchIdx = -1
    last = amps[0]
    for i in range(1, len(amps)):
        diff = amps[i]-last
        last = amps[i]
        if diff > 0.0:
            searchIdx = i
            break

    # Find stop band attenuation
    att = np.max(amps[searchIdx:])

    # Optimise for attenuation
    return att

optfunc([-0.57685987, -1.10654573, -2.16745906])

# best = 0
# bestCoeffs = None
# for i in range(1000):
#     res = opt.minimize(optfunc, np.random.uniform(-10, 0, 3))
#     if res.fun < best:
#         best = res.fun
#         bestCoeffs = res.x
#     print('Result:', i, res.fun, best)
# print('Best:', best, bestCoeffs)

# # Cool window: [0.38373144 0.49571507 0.11626856 0.00428493]

