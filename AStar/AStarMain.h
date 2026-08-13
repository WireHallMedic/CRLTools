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

void test();

int getXTowards(short directionEnum);

int getYTowards(short directionEnum);

void printCharMap(char* charMap, int width);

// export function for DLL
void findPath(double* passMap, int mapWidth, int startX, int startY, int endX, int endY, short* returnArr);