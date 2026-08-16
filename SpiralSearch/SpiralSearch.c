#include "SpiralSearch.h"

int **searchableArr;
int width;
int height;
SearchStep *head;

__declspec(dllexport) void initialize(long seed, int x, int y, int w, int h, int* map)
{

}

void push(int x, int y)
{

}

void addNeighbors(int x, int y)
{

}

int isInBounds(int x, int y)
{
   return x >= 0 &&
          y >= 0 &&
          x < width &&
          y < height;
}

int cartesianToIndex(int x, int y)
{
   return x + (y * width);
}

__declspec(dllexport) void pop(int x, int y, int* returnVals)
{

}

void freeAll()
{
   SearchStep *curStep = head;
   SearchStep *nextStep = NULL;
   head = NULL;
   
   while(curStep != NULL)
   {
      nextStep = curStep->next;
      free(curStep);
      curStep = nextStep;
   }
   
   searchableArr = NULL;
}
