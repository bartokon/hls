#!/usr/bin/python3
#based on https://youtu.be/O0Y8FChBaFU
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    print("Generating sinewave.")
    fs = 2000
    tstep = 1 / fs
    f0 = 200 #signal freq

    N = 10 * int(fs / f0)
    N = 1024

    t = np.linspace(0, (N-1) * tstep, N)
    fstep = fs / N
    f = np.linspace(0, (N-1) * fstep, N)

    y = 0.25 * np.sin(2 * np.pi * f0 * t)

    # FFT
    x = np.fft.fft(y)
    x_mag = np.abs(x) / N

    f_plot = f[0: int(N/2 + 1)]
    x_mag_plot = 2 * x_mag[0:int(N/2 + 1)]
    x_mag_plot[0] = x_mag_plot[0] / 2 # Note: DC component doest not need to multiply by 2

    # plot
    #fig, [ax0, ax1] = plt.subplots(2)
    #ax0.plot(t, y, '.-')
    #ax1.plot(f_plot, x_mag_plot, '.-')
    #plt.show()

    np.savetxt('data_samples_x.txt', t, fmt="%.16f")
    np.savetxt('data_samples_y.txt', y, fmt="%.16f")
    np.savetxt('fft_output_re.txt', x.real, fmt="%.16f")
    np.savetxt('fft_output_im.txt', x.imag, fmt="%.16f")
    print("Done.")
    exit(0)
