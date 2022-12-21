""" Python wrapper for the C shared library mylib"""
import sys, platform
import ctypes, ctypes.util

# Find the library and load it
mylib_path = ctypes.util.find_library("./mylib")
if not mylib_path:
    print("Unable to find the specified library.")
    sys.exit()

try:
    mylib = ctypes.CDLL(mylib_path)
except OSError:
    print("Unable to load the system C library")
    sys.exit()

# Make the function names visible at the module level and add types
test_empty = mylib.test_empty

test_add = mylib.test_add
test_add.argtypes = [ctypes.c_float, ctypes.c_float]
test_add.restype = ctypes.c_float

test_passing_array = mylib.test_passing_array
test_passing_array.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
test_passing_array.restype = None
