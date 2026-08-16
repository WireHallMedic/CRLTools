#include<stdlib.h>

#define FALSE 0

struct SearchStep
{
   int x;         
   int y;         
   struct SearchStep *next;    
};
typedef struct SearchStep SearchStep;

void push(int x, int y);
void addNeighbors(int x, int y);
int isInBounds(int x, int y);
int cartesianToIndex(int x, int y);
void freeAll();

// export functions
void initialize(long seed, int x, int y, int w, int h, int* map);
void pop(int* returnVals);
