"""Simple example of loading and using the system C library from Python"""
import sys, platform
import ctypes, ctypes.util

# Get the path to the system C library
if platform.system() == "Windows":
    path_libc = ctypes.util.find_library("msvcrt")
else:
    path_libc = ctypes.util.find_library("c")

# Get a handle to the sytem C library
try:
    libc = ctypes.CDLL(path_libc)
except OSError:
    print("Unable to load the system C library")
    sys.exit()
    
print("Succesfully loaded the system C library from {}".format(path_libc))

libc.puts(b"Hello from Python to C")
libc.printf(b"%s\n", b"Using the C printf function from Python ... ")
