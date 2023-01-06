import matplotlib.pyplot as plt

alpha = .1
beta = 1-alpha

def parallel_time(p):
    return alpha+beta/p

nprocs = 100
times = [ parallel_time(p) for p in range(1,nprocs) ]
speedup = [ 1/t for t in times ]
s_is_p = [ 1 for p in range(1,nprocs) ]

plt.plot( speedup )
plt.plot( s_is_p )
plt.xlabel( "number of processors" )
plt.ylabel( "speedup" )
plt.show()
