import numpy as np
import matplotlib.pyplot as plt

def mergeThreads (outputfilename):
    """ Function doc """
    
    data = np.zeros((1, 6))
    for threadID in xrange(0, 4):
        filename = "TOF_nt_TOF_t%d.csv"%(threadID)
        dataThread = np.loadtxt(filename, delimiter = ",", skiprows = 9)
        print filename
        data = np.vstack((data, dataThread))
    savefmt = ["%.5g", "%.5g", "%.5g", "%d", "%d", "%d"]
    np.savetxt(outputfilename, data[1:, :], fmt = savefmt)

mergeThreads("TOF_csv")

