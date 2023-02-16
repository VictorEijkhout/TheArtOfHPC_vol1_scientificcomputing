####
#### python bit manipulation
####

print
print("Representation")
five = int('101',2)
twentyfive = five*five
print("twenty five in hex: %x" % twentyfive)
five = 0b101
print("five binary as int: {}".format(five))
print("five as binary: {}".format( bin(five) ))
print

print("Bit shift")
ten  = five \
    <<1 
two = five \
YOUR CODE HERE
print("Ten: {}, two: {}".format(ten,two))
print

print("And or")
six = 4 | 2
five_odd = five & 1
print("Six: {}, five odd: {}".format(six,five_odd))
print

print("Flip all bits")
five_flip = ~ five
print("flip five: {}".format(five_flip))

maxint = int('0xffffffff',16)
five_flip = five ^ maxint
print("flip five hex: {}".format(five_flip))
print

print("Xor")
# what does ^ do?
c = five ^ 3
print("five ^ three: {}".format(c+1))
print

print("bit lengths")
short = 128
print("Short int length: {}".format(short.bit_length()))
bigint = maxint * maxint
print("big int {} has length {}".format(bigint,bigint.bit_length()))
enormous_int = bigint * bigint
print("enormous int {} has length {}".format(enormous_int,enormous_int.bit_length()))
