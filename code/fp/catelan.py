def c(ls):
    if len(ls)==1:
        x = ls[0]
        return [('L',x)]
    else: 
        r = range(1,len(ls))
        return [('I',x,y) for i in r for x in c(ls[i:]) for y in c(ls[:i])]

def interm(ls):
    r = range(1,len(ls))
    return [(ls[:i], ls[i:]) for i in r]

# for i in range(15):
#     clist = c(range(i))
#     print( f"{i}: {len(clist)}" )
print( c( range(3) ) )
