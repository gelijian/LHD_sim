import os
import numpy as np
import matplotlib.pyplot as plt

bintof = np.arange(0, 200, 1)
bintofplot = 0.5 * (bintof[1:] + bintof[:-1])

filename = "TOF_csv"
data = np.loadtxt(filename)
toflist = data[:, 0]
ntof, bins = np.histogram(toflist, bins = bintof)

fig =  plg.figure()
plt.plot(bintofplot, ntof, label = "origin")
plt.legend()
plt.show()
