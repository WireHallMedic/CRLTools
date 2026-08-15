#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979323846
#define FIELD_SIZE 23 // just need a reasonably-sized prime number to limit repetition

double interpolateLinear(double p1, double p2, double xOff);
double interpolateCosine(double p1, double p2, double xOff);
double sanatizeIndex(double val);
double reduceInput(double val);
void initialize(long seed);