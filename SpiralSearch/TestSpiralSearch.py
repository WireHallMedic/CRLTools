from ctypes import *
import os
import math


spiral_search = cdll.LoadLibrary("./SpiralSearch.dll")


def print_char_list(char_list):
   for y in range(width):
      for x in range(width):
         print("" + char_arr[x][y])
      print()

char_arr = [
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '@', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '#', '.', '.', '.', '.'], 
         ['.', '.', '.', '.', '.', '.', '.', '.']]
         
startX = -1;
startY = -1;
width = len(char_arr);
height = len(char_arr[1]);

# in_arr = (c_double * list_len)(*double_list)
# out_arr = (c_short * 64)()
# 
# a_star.findPath.argtypes = [POINTER(c_double), c_int, c_int, c_int, c_int, c_int, POINTER(c_short)]
# 
# a_star.findPath(in_arr, width, startX, startY, endX, endY, out_arr)
# 
# xLoc = startX
# yLoc = startY
# 
# i = 0
# while(out_arr[i] != 0):
#    xLoc += getXStep(out_arr[i])
#    yLoc += getYStep(out_arr[i])
#    char_list[getIndex(xLoc, yLoc, width)] = 'X'
#    i += 1
# 
# print_char_list(char_list, width)