#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979323846
#define FIELD_SIZE 23 // just need a reasonably-sized prime number to limit repetition
#define OCTAVES 6
#define PERSISTENCE 0.5
#define FREQUENCY_MULTIPLIER 0.5

double interpolateLinear(double p1, double p2, double xOff);
double interpolateCosine(double p1, double p2, double xOff);
double normalizeIndex(double val);
double reduceIndex(double val);
double getSpecificNoiseValue(double xOff, double yOff, double arr[FIELD_SIZE][FIELD_SIZE]);

// export functions
double getNoiseValue(double xOff, double yOff);
double getChoirValue(double xOff, double yOff);