import re
import sys

if len(sys.argv)<2:
    print("Needs filename argument"); sys.exit(1)

filename = sys.argv[1]
if not re.search("\.runout$",filename):
    print("Only runout files"); sys.exit(1)

namebase = re.match(r'^(.*)\.runout$',filename).groups()[0]
nout = 0
doing = False
outfile = None
with open( filename ) as runout:
    for line in runout:
        line = line.strip()
        if doing and re.match("%%",line):
            ## we encounter a new block
            ## 1. close existing out file
            if nout>0:
                outfile.close()
            ## up the number and open new file
            nout += 1
            outfile = open(f"{namebase}.runout{nout}","w")
            doing = 0
        ## write this line if not preamble, and reset state
        if outfile:
            if not re.match("%%",line) and not re.match("hint:",line) :
                outfile.write(line+"\n")
        doing = not re.match("%%",line)
outfile.close()

        
