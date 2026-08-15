
#include <math.h>
#include "Noise.h"
#define PI 3.14159265358979323846

double primaryArray[FIELD_SIZE][FIELD_SIZE];
double secondaryArray[FIELD_SIZE][FIELD_SIZE];
double tertiaryArray[FIELD_SIZE][FIELD_SIZE];

// returns the value of a point between two values.  For example, if the passed values are 2 and 4, and the xOffset
// is .5 (halfway between the two), this will return 3.
double interpolateLinear(double p1, double p2, double xOff)
{
   return p1 + ((p2 - p1) * xOff);
}


// returns a value similar to interpolateLinear(), but on an s-curve so that results are more heavily weighted towards
// the closer of the two points.
double interpolateCosine(double p1, double p2, double xOff)
{
   xOff = ((-1.0 * (float)cos(PI * xOff)) *.5) + .5;
   return interpolateLinear(p1, p2, xOff);
}

double sanatizeIndex(double val)
{
   // negative
   if(val < 0)
   {
      val = -1.0 * val;
      if(val > (double)FIELD_SIZE)
      {
         val = reduceInput(val);
      }
      val = (double)FIELD_SIZE - val;
   }
   // positive
   else
   if(val > (double)FIELD_SIZE)
      val = reduceInput(val);
   return val;
}

// input must be positive
double reduceInput(double val)
{
   if(val > (double)FIELD_SIZE)
   {
      int val_int = (int)val % FIELD_SIZE;
      double val_double = val - (double)((int)val);
      val = val_int + val_double;
   }
   return val;
}