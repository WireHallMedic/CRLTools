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
   SearchStep* newStep = (SearchStep *)malloc(sizeof(SearchStep));
   newStep->x = x;
   newStep->y = y;
   newStep->next = NULL;
   
   if(head == NULL)
      head = newStep;
   else
   {
      SearchStep *last = head;
      while(last->next != NULL)
         last = last->next;
      last->next = newStep;
   }
}

void addNeighbors(int x, int y)
{
   // North
   if(isInBounds(x, y - 1) && searchableArr[x][y - 1])
      push(x, y - 1);
   // South
   if(isInBounds(x, y + 1) && searchableArr[x][y + 1])
      push(x, y + 1);
   // East
   if(isInBounds(x + 1, y) && searchableArr[x + 1][y])
      push(x + 1, y);
   // West
   if(isInBounds(x - 1, y) && searchableArr[x - 1][y])
      push(x - 1, y);
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
