#include "Noise.h"

double valArray[OCTAVES][FIELD_SIZE][FIELD_SIZE];
double weight[OCTAVES];
double persistenceSum = 0.0;

__declspec(dllexport) void initialize(long seed)
{
   if(seed == 0)
      srand(time(NULL));
   else
      srand(seed);
   for(int i = 0; i < OCTAVES; i++)
   for(int x = 0; x < FIELD_SIZE; x++)
   for(int y = 0; y < FIELD_SIZE; y++)
   {
      valArray[i][x][y] = (double)rand() / (double)RAND_MAX;      
   }
   weight[0] = 1.0;
   double persistenceSum = 1.0;
   
   // weight each octave
   for(int i = 1; i < OCTAVES; i++)
   {
      weight[i] = weight[i - 1] * PERSISTENCE;
      persistenceSum += weight[i];
   }
   for(int i = 0; i < OCTAVES; i++)
   {
      weight[i] = weight[i] / persistenceSum;
   }
}

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

// bind input to the size of the array
double normalizeIndex(double val)
{
   // negative
   if(val < 0)
   {
      val = -1.0 * val;
      if(val > (double)FIELD_SIZE)
      {
         val = reduceIndex(val);
      }
      val = (double)FIELD_SIZE - val;
   }
   // positive
   else
   if(val > (double)FIELD_SIZE)
      val = reduceIndex(val);
   return val;
}

// input must be positive
double reduceIndex(double val)
{
   if(val > (double)FIELD_SIZE)
   {
      int val_int = ((int)val) % FIELD_SIZE;
      double val_double = val - (double)((int)val);
      val = val_int + val_double;
   }
   return val;
}


// determine the value at a point in one field
double getSpecificNoiseValue(double xOff, double yOff, double arr[FIELD_SIZE][FIELD_SIZE])
{
   // normalize within bounds
   xOff = normalizeIndex(xOff);
   yOff = normalizeIndex(yOff);
   
   // set vertex points
   int vx = (int)xOff;
   int vy = (int)yOff;
   int vx2 = (vx + 1) % FIELD_SIZE;
   int vy2 = (vy + 1) % FIELD_SIZE;
   double p1 = arr[vx][vy];
   double p2 = arr[vx2][vy];
   double p3 = arr[vx][vy2];
   double p4 = arr[vx2][vy2];
   
   double px1 = 0.0;
   double px2 = 0.0;
   
   double xInset = xOff - (double)((int)xOff);
   double yInset = yOff - (double)((int)yOff);
   
   px1 = interpolateCosine(p1, p2, xInset);
   px2 = interpolateCosine(p3, p4, xInset);
   return interpolateCosine(px1, px2, yInset);
}

// determine the value at a point in primary array
__declspec(dllexport) double getNoiseValue(double xOff, double yOff)
{
   return getSpecificNoiseValue(xOff, yOff, valArray[0]);
}

// determine the value at a point in stacked array
__declspec(dllexport) double getChoirValue(double xOff, double yOff)
{
   double val = 0.0;
   double frequency = 1.0;
   for(int i = 0; i < OCTAVES; i++)
   {
      val += getSpecificNoiseValue(xOff / frequency, yOff / frequency, valArray[i]) * weight[i];
      frequency *= FREQUENCY_MULTIPLIER;
   }
   return val;
}