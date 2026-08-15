#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979323846
#define FIELD_SIZE 23 // just need a reasonably-sized prime number to limit repetition

double interpolateLinear(double p1, double p2, double xOff);
double interpolateCosine(double p1, double p2, double xOff);
double normalizeIndex(double val);
double reduceIndex(double val);
double getSpecificNoiseValue(double xOff, double yOff, double arr[FIELD_SIZE][FIELD_SIZE]);

// export functions
void initialize(long seed);
__declspec(dllexport) double getNoiseValue(double xOff, double yOff);
__declspec(dllexport) double getChoirValue(double xOff, double yOff);