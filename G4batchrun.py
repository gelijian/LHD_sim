import os
import time
import numpy as np

def createTOFin(flightangle):
    """
    generate the input file(TOF.in) for the G4 simulation 
    """
    ftemplate = open("TOFtemplate.in", "r")
    lines = ftemplate.readlines()
    ftofin = open("TOF.in", "w")   
    line = lines[7].split()
    lines[7] = "%s %g %s\n"%(line[0], flightangle, line[2])
    ftofin.writelines(lines)
    ftemplate.close()
    ftofin.close()

def mergeThreads ():
    """ Function doc """
    
    data = np.zeros((1, 6))
    for threadID in xrange(0, 4):
        filename = "TOF_nt_TOF_t%d.csv"%(threadID)
        dataThread = np.loadtxt(filename, delimiter = ",", skiprows = 9)
        print filename
        data = np.vstack((data, dataThread))
    savefmt = ["%.5g", "%.5g", "%.5g", "%d", "%d", "%d"]
    np.savetxt("TOFfile.dat", data[1:, :], fmt = savefmt)
# create the directory 

directory = "test_flightangle"
energy = "2500keV"
elementdir = os.path.join(directory, energy)

if (not os.path.exists(elementdir)):
    os.mkdir(os.path.join(elementdir))
    print "%s has been created!" % (elementdir)
    
# set the neutron energy list

flightangle_list = np.arange(10, 45, 5)
#np.savetxt(os.path.join(directory, "Enlist"), Enlist, fmt = "%g")

for i in xrange(len(flightangle_list)):
    start = time.time()
    flightangle = flightangle_list[i]    
    createTOFin(flightangle)
    
    print "TOFED G4 Simulation for %g degree starts..." % (flightangle)
    os.system("./TOF TOF.in > TOF.out")
    mergeThreads()
    filename = "flightangle_%ddeg" % (flightangle)
    os.system("mv TOFfile.dat %s" % (os.path.join(elementdir, filename)))
    stop = time.time()
    runtime = stop - start
    print "TOFED G4 Simulation finished, run time: %g" % (runtime)
    print ""
  
