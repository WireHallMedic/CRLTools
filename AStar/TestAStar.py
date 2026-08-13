from ctypes import *
import os
import math

ORIGIN = 0
NORTH = 1
NORTH_EAST = 2
EAST = 3
SOUTH_EAST = 4
SOUTH = 5
SOUTH_WEST = 6
WEST = 7
NORTH_WEST = 8

a_star = cdll.LoadLibrary("./AStar.dll")

def getX(index, width):
   return index % width;

def getY(index, width):
   return index // width;

def getIndex(x, y, width):
   return x + (y * width)

def getXStep(dir):
   if dir == NORTH_EAST or dir == EAST or dir == SOUTH_EAST:
      return 1
   if dir == NORTH_WEST or dir == WEST or dir == SOUTH_WEST:
      return -1
   return 0

def getYStep(dir):
   if dir == NORTH_EAST or dir == NORTH or dir == NORTH_WEST:
      return -1
   if dir == SOUTH_EAST or dir == SOUTH or dir == SOUTH_WEST:
      return 1
   return 0

def print_char_list(char_list, width):
   for y in range(width):
      for x in range(width):
         print("" + char_list[getIndex(x, y, width)], end = "");
      print()

char_list = [
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', ',', ',', ',', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '@', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', '.', '.', ',', ',', ',', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '.', '.', '#', ',', '.', '.', '!', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.']
list_len = len(char_list)
width = int(math.sqrt(len(char_list)))
double_list = [1.0] * list_len
return_list = [0] * 64
startX = -1;
startY = -1;
endX = -1;
endY = -1;
for i in range(list_len):
   if char_list[i] == '@':
      startX = getX(i, width)
      startY = getY(i, width)
   if char_list[i] == '!':
      endX = getX(i, width)
      endY = getY(i, width)
   if char_list[i] == '#':
      double_list[i] = -1.0
   if char_list[i] == ',':
      double_list[i] = 2.0

in_arr = (c_double * list_len)(*double_list)
out_arr = (c_short * 64)()

a_star.findPath.argtypes = [POINTER(c_double), c_int, c_int, c_int, c_int, c_int, POINTER(c_short)]

a_star.findPath(in_arr, width, startX, startY, endX, endY, out_arr)

xLoc = startX
yLoc = startY

i = 0
while(out_arr[i] != 0):
   xLoc += getXStep(out_arr[i])
   yLoc += getYStep(out_arr[i])
   char_list[getIndex(xLoc, yLoc, width)] = 'X'
   i += 1

print_char_list(char_list, width)