#ifndef ASTARDEFS_H
   #include "AStarDefs.h"
#endif

struct StepStats
{
   int x;         
   int y;         
   double cost;     
};
typedef struct StepStats StepStats;

void _findPath(double* passMap, int mapWidth, int startX, int startY, int endX, int endY, short* returnArr);

int isInBounds(int x, int y, int mapWidth);

int cartesianToIndex(int x, int y, int mapWidth);

// export function for DLL
void findPath(double* passMap, int mapWidth, int startX, int startY, int endX, int endY, short* returnArr);