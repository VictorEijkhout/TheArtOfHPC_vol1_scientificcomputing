import mylib
import ctypes

print("Try test_empty:")
mylib.test_empty()

print("\nTry test_add:")
print(mylib.test_add(34.55, 23))

print("\nTry passing an array of 25 integers to C:")
numel = 25
data = (ctypes.c_int * numel)(*[x for x in range(numel)])

mylib.test_passing_array(data, numel)

print("data from Python after returning from C:")
for indx in range(numel):
    #print(data[indx], end=" ")
    print(data[indx])
print("")
