from math import pow

for k in range(1,20):
    n = pow(10,k)
    e = pow( 1+1/n,n )
    print("%d: %e" % (k,e) )
print
    
e = float(1)
while True:
    print(e)
    if float(1)+float(e)==float(1):
        break
    e /= float(2)
    
