#include "SpiralSearch.h"

int **searchableArr = NULL;
int width;
int height;
SearchStep *head;

__declspec(dllexport) void initialize(long seed, int x, int y, int w, int h, int* map)
{
   if(searchableArr != NULL)
      freeAll();
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
   for(int i = 0; i < 4; i++)
   {
      int localX = 0;
      int localY = 0;
      switch(i)
      {
         case 0 : localY = 1; break;
         case 1 : localY = -1; break;
         case 2 : localX = 1; break;
         case 3 : localX = -1; break;
      }
      if(isInBounds(localX, localY) && searchableArr[localX][localY])
      {
         push(localX, localY);
         searchableArr[localX][localY] = FALSE;
      }
   }
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

__declspec(dllexport) void pop(int* returnVals)
{
   // increment list
   SearchStep* curStep = head;
   head = head->next;
   
   // add neighbors to list
   addNeighbors(curStep->x, curStep->y);
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
   
   free(searchableArr);
}
