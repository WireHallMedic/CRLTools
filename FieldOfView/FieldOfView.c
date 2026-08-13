/*
A module for determining field of view using shadowcasting.
Expects a 1D array of ints representing the 2D area to be calculate,
and a parallel array into which to put the results.

1D array is treated as a square 2D array of width and height sqrt(array.length).
Vision range and center point are calculated on this; for example, if given
an array of 25 elements, it will be calculated as a 5x5 area, vision range 2, 
vision calculated from 2, 2.

Elements of the array indicate transparency; a tile with value 0 is opaque, any other 
value is transparent.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FieldOfView.h"

/* some inline functions */
#define getX(index, width) (index % width)
#define getY(index, width) (index / width)
#define getIndex(x, y, width) (x + (y * width))

static const int MULTIPLIERS[4][8] = 
{
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

static const int OPAQUE = 0;
static const int TRANSPARENT = 1;
static const int TRUE = 1;
static const int FALSE = 0;

int isInBounds(int index, int width)
{
   if(getX(index, width) < 0 ||
      getX(index, width) >= width ||
      getY(index, width) < 0 ||
      getY(index, width) >= width)
      return 0;
   return 1;
}


__declspec(dllexport) void calcFoV(int* inputMap, int* outputMap, int width, int radius)
{
   int xOrigin = width / 2;
   int yOrigin = xOrigin;
   
   if(radius > (width / 2))
   {
      fprintf(stderr, "FoV radius %d too large for map diameter %d", radius, width);
      exit(1);
   }
   radius++; // increment because origin counts

   for(int oct = 0; oct < 8; oct += 1)
   {
      castLightInOctant(inputMap, outputMap, width, xOrigin, yOrigin, oct, radius);
   }
   outputMap[getIndex(xOrigin, yOrigin, width)] = TRUE;
}

void castLightInOctant(int* inputMap, int* outputMap, int width, int xLoc, int yLoc, 
                        int oct, int radius)
{
   castLight(inputMap, outputMap, width, // map stuff
             xLoc, yLoc,         // starting coordinates
             1,                  // row number
             1.0, 0.0, radius,   // bounding slopes and radius
             MULTIPLIERS[0][oct], MULTIPLIERS[1][oct], MULTIPLIERS[2][oct], MULTIPLIERS[3][oct]); // octant multipliers
}

void castLight(int* inputMap, int* outputMap, int width, // map stuff
                  int cx, int cy,                       // starting coordinates
                  int row,                              // row number
                  double start, double end, int radius, // terminal slopes, and max light radius
                  int xx, int xy, int yx, int yy)       // multipliers for octant
   {
      if(start < end)
         return;
      
      int RADIUS_SQUARED = radius * radius; // avoid sqrt() calcs
      
      // main loop; iterates out from observer
      for(int j = row; j < radius; j += 1)
      {
         int dx = -j - 1;
         int dy = -j;
         int blocked = FALSE;
         double newStart = 0.0;
         
         while(dx <= 0)
         {
            dx += 1;
            
            // translate the dx, dy coordinates into map coordinates
            int x = cx + dx * xx + dy * xy;
            int y = cy + dx * yx + dy * yy;
            
            // calculate the left and right slopes of the square under consideration
            double leftSlope = (dx - .5) / (dy + .5);
            double rightSlope = (dx + .5) / (dy - .5);
            
            if(start < rightSlope) // not in beam yet
               continue;
            else if (end > leftSlope) // beyond beam
               break;
            else
            {
               // observer has LoS to the square; mark accordingly
               if(dx * dx + dy * dy < RADIUS_SQUARED)
               {
                  outputMap[getIndex(x, y, width)] = TRUE;
               }
               if(blocked) // we're scanning a row of blocked squares
               {
                  if(inputMap[getIndex(x, y, width)] == OPAQUE)
                  {
                     newStart = rightSlope;
                     continue;
                  }
                  else
                  {
                     blocked = FALSE;
                     start = newStart;
                  }
               }
               else    // have been scanning transparent squares
               {
                  if((inputMap[getIndex(x, y, width)] == OPAQUE) && j < radius) // start a child
                  {
                     blocked = TRUE;
                     castLight(inputMap, outputMap, width, cx, cy, j + 1, start, leftSlope, 
                        radius, xx, xy, yx, yy);
                     newStart = rightSlope;
                  }
               }
            }
         } // end while loop
         if(blocked)
            break;
      }
   }  // end castLight()

