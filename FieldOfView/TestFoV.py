from ctypes import *
import os
import math

OPAQUE = 0;
TRANSPARENT = 1;

fov = cdll.LoadLibrary("./FieldOfView.dll")

def getX(index, width):
   return index % width;

def getY(index, width):
   return index // width;

def getIndex(x, y, width):
   return x + (y * width)

def print_char_list(char_list, width):
   for y in range(width):
      for x in range(width):
         print("" + char_list[getIndex(x, y, width)], end = "");
      print()

char_list = [
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '#', '.', '.', '@', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
list_len = len(char_list)
width = int(math.sqrt(len(char_list)))
int_list = [TRANSPARENT] * list_len

for i in range(list_len):
   if char_list[i] == '#':
      int_list[i] = OPAQUE

in_arr = (c_int * list_len)(*int_list)
out_arr = (c_int * list_len)()

fov.calcFoV.argtypes = [POINTER(c_int), POINTER(c_int), c_int, c_int]

fov.calcFoV(in_arr, out_arr, width, 7)

print_char_list(char_list, width)

for i in range(list_len):
   if out_arr[i] == OPAQUE:
      char_list[i] = ' '

print_char_list(char_list, width)