import math
import matplotlib.pyplot as plt

alpha = 0.0001
beta = 1-alpha

def communication(p):
    return .01*math.log(p,2)

def parallel_time(p):
    return alpha+beta/float(p)+communication(p)

nprocs = 100
times = [ parallel_time(p) for p in range(1,nprocs) ]
speedup = [ 1./t for t in times ]
s_is_p = [ p for p in range(1,nprocs) ]

plt.plot( speedup, 'r' )
plt.plot( s_is_p, 'b' )
plt.xlabel( "number of processors" )
plt.ylabel( "speedup" )
plt.show()
