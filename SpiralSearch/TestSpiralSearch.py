from ctypes import *
import os
import math


spiral_search = cdll.LoadLibrary("./SpiralSearch.dll")

spiral_search.initialize.argtypes = [c_int, c_int, c_int, c_int, POINTER(c_int)]
spiral_search.pop.argtypes = [POINTER(c_int)]


char_arr = [
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '@', '#', '.', '.', '.', '.', 
         '.', '.', '.', '#', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.']
         
startX = -1;
startY = -1;
width = 8;
height = 10;

def print_arr(arr):
   outStr = ""
   for y in range(height):
      for x in range(width):
         outStr = outStr + arr[x + (y * width)]
      outStr = outStr + "\n"
   print(outStr + "\n")

def cartesian_to_index(x, y):
   return x + (y * width)
      

print_arr(char_arr);

cArr2d = (c_int * (height * width))()
cLoc = (c_int * 2)()

for i in range(len(char_arr)):
   if(char_arr[i] == '#'):
      cArr2d[i] = 0
   elif(char_arr[i] == '@'):
      startX = i % width
      startY = i // width
   else:
      cArr2d[i] = 1

print(f"Origin is {startX}, {startY}")

spiral_search.initialize(startX, startY, width, height, cArr2d)

for i in range(0, 26):
   spiral_search.pop(cLoc)
#    print(f"Popped {cLoc[0]}, {cLoc[1]}")
   newChar = chr(ord('a') + i)
   index = cartesian_to_index(cLoc[0], cLoc[1])
   char_arr[index] = newChar

print_arr(char_arr)