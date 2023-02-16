##
## evalute difference of successive square roots two different ways
## this is the frontpage example of "herbie", but I'm not getting it to do anything.
##

from bigfloat import *

def sqrtinv(y):
    if y==0:
        return 0
    else:
        n = y*y-1; n *= n
        d = 4*y*y
        return n/d
xrange = range(16)
prange = [40,60,100]
for e in xrange:
    n = pow(10,e)
    print("%%%%%%%%%%%%%%%%")
    for p in prange:
        with precision(p):
            # naive difference
            d = sqrt(n+1)-sqrt(n)
            # herbie difference
            h = 1/(sqrt(n+1)+sqrt(n))
            # relative error
            d = float(d); h = float(h); r = (d-h)/h
            # inverse of naive
            dx = sqrtinv(d); hx = sqrtinv(h)
            print(f"""\
e={e:2}, p={p:5}: diff={d}, herbie says: {h};
    d inv={dx}, h inv={hx}
    relative error: {r}\
""")
