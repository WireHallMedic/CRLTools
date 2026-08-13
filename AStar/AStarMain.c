#include <stdlib.h>
#include <stdio.h>
#ifndef ASTARDEFS_H
   #include "AStarDefs.h"
#endif
#include "AStarNode.h"
#include "AStarList.h"
#include "AStarMain.h"

int main(int argNum, char* args[])
{
   test();
}

__declspec(dllexport) void findPath(double* passMap, int mapWidth, int startX, int startY, int endX, int endY, short* returnArr)
{
    _findPath(passMap, mapWidth, startX, startY, endX, endY, returnArr);
}


void _findPath(double* passMap, int mapWidth, int startX, int startY, int endX, int endY, short* returnArr)
{
   // early exit if origin or target not in area
   if(!isInBounds(startX, startY, mapWidth) || !isInBounds(endX, endY, mapWidth))
   {
      returnArr[0] = 0;
      return;
   }
   
   // search structure: [x, y, stepDist]
   struct StepStats adjVals[8][3] = {
      {1, 0, ORTHO_STEP},
      {-1, 0, ORTHO_STEP},
      {0, 1, ORTHO_STEP},
      {0, -1, ORTHO_STEP},
      {1, 1, DIAG_STEP},
      {-1, 1, DIAG_STEP},
      {1, -1, DIAG_STEP},
      {-1, -1, DIAG_STEP}};
   int pathExists = FALSE;
   int loops = 0;
                    
   // create map and list
   struct AStarNode nodeMap[mapWidth * mapWidth];
   
   // populate map
   for(int x = 0; x < mapWidth; x++)
   for(int y = 0; y < mapWidth; y++)
   {
      int curIndex = cartesianToIndex(x, y, mapWidth);
      AStarNode* newNode = &(nodeMap[curIndex]);
      initializeNode(newNode, x, y, endX, endY);
      if(passMap[curIndex] <= 0.0)
         newNode->passable = FALSE;
      else
         newNode->cost = passMap[curIndex];
   }
   // origin and target are guaranteed traversable
   nodeMap[cartesianToIndex(startX, startY, mapWidth)].passable = TRUE;
   nodeMap[cartesianToIndex(endX, endY, mapWidth)].passable = TRUE;
   
   // create and populate open list
   AStarList openList = {NULL, 0};
   
   // set initial state
   AStarNode* startNode = &(nodeMap[cartesianToIndex(startX, startY, mapWidth)]);
   startNode->g = 0.0;
   calcF(startNode);
   setHead(startNode, &openList);
   
   // run
   while(!pathExists && loops < MAX_LOOPS && openList.length > 0)
   {
      loops++;
      AStarNode* curNode = pop(&openList);
      // check if at target
      if(curNode->locX == endX && curNode->locY == endY)
      {
         pathExists = TRUE;
         if(curNode->parent == NULL)
            printf("Target found with no parent.\n");
      }
      // check neighbors
      for(int i = 0; i < 8; i++)
      {
         int prospectX = curNode->locX + adjVals[i]->x;
         int prospectY = curNode->locY + adjVals[i]->y;
         int nodeIndex = cartesianToIndex(prospectX, prospectY, mapWidth);
         if(isInBounds(prospectX, prospectY, mapWidth) && 
            nodeMap[nodeIndex].status != CLOSED &&
            nodeMap[nodeIndex].passable)
         {
            AStarNode* checkNode = &(nodeMap[nodeIndex]);
            // if unchecked, open
            if(checkNode->status == UNCHECKED)
            {
               push(checkNode, curNode, &openList);
            }
            // update
            updateNode(curNode, checkNode, adjVals[i]->cost);
         }
      }
      curNode->status = CLOSED;
   }
   // free memory
   clearRemaining(&openList);
   
   if(loops == MAX_LOOPS)
      printf("Max loops reached");
      
   // early exit if no path exists
   if(!pathExists)
   {
      returnArr[0] = 0;
      return;
   }
      

   // record path
   char reversePath[MAX_PATH_LENGTH];
   int pathLen = 0;
   AStarNode* curNode = &(nodeMap[cartesianToIndex(endX, endY, mapWidth)]);
   while(curNode->parent != NULL)
   {
      reversePath[pathLen] = getDirectionTo(curNode->parent, curNode);
      pathLen++;
      curNode = curNode->parent;
   }
   
   // reverse path
   for(int i = 0; i < pathLen; i++)
      returnArr[i] = reversePath[pathLen - 1 - i];
   returnArr[pathLen] = 0; // origin step to terminate

   // return
}

int isInBounds(int x, int y, int mapWidth)
{
   return x >= 0 &&
          y >= 0 &&
          x < mapWidth &&
          y < mapWidth;
}

int cartesianToIndex(int x, int y, int mapWidth)
{
   return x + (y * mapWidth);
}


/* testing */
void test()
{
   int mapWidth = 15;
   char charMap[] =
      {
         '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', '.', ',', '!', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', ',', ',', ',', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '@', ',', '.', '.', '.', '.', '#', '.', '#', ',', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 
         '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.',
      };
   double passMap[mapWidth * mapWidth];
   char outMap[mapWidth * mapWidth];
   int startX;
   int startY;
   int endX;
   int endY;
   short pathList[MAX_PATH_LENGTH];
   // good loop, then bad loop
   //for(int i = 0; i < 4; i++)
   for(int i = 0; i < 1; i++)
   {
      switch(i)
      {
         case 0 : printf("Good path: \n");
                  break;
         case 1 : printf("Bad path origin OOB: \n");
                  break;
         case 2 : printf("Bad path target OOB: \n");
                  break;
         case 3 : charMap[cartesianToIndex(5, 0, mapWidth)] = '#';
                  printf("Bad path Blocked: \n");
                  break;
      }
         
      for(int x = 0; x < mapWidth; x++)
      for(int y = 0; y < mapWidth; y++)
      {
         int curIndex = cartesianToIndex(x, y, mapWidth);
         if(charMap[curIndex] == '#')
            passMap[curIndex] = -1.0;
         else if(charMap[curIndex] == ',')
            passMap[curIndex] = 2.0;
         else
            passMap[curIndex] = 1.0;
         
         if(charMap[curIndex] == '@')
         {
            startX = x;
            startY = y;
         }
         
         if(charMap[curIndex] == '!')
         {
            endX = x;
            endY = y;
         }
      }
      
      if(i == 1)
      {
         startX = -1;
      }
      if(i == 2)
      {
         endY = -1;
      }
      // determine path
      _findPath(passMap, mapWidth, startX, startY, endX, endY, pathList);
      
      // prepare output
      for(int x = 0; x < mapWidth; x++)
      for(int y = 0; y < mapWidth; y++)
         outMap[cartesianToIndex(x, y, mapWidth)] = charMap[cartesianToIndex(x, y, mapWidth)];
      
      // display path
      int pathIndex = 0;
      int curX = startX;
      int curY = startY;
      while(pathList[pathIndex] != 0)
      {
         curX += getXTowards(pathList[pathIndex]);
         curY += getYTowards(pathList[pathIndex]);
         outMap[cartesianToIndex(curX, curY, mapWidth)] = 'X';
         pathIndex++;
      }
      
      // print
      printCharMap(outMap, mapWidth);
   }
   return;
}

int getXTowards(short directionEnum)
{
   int x = 0;
   switch(directionEnum)
   {
      case NORTH_EAST :
      case EAST :
      case SOUTH_EAST : x = 1; break;
      case NORTH_WEST :
      case WEST :
      case SOUTH_WEST : x = -1; break;
   }
   return x;
}

int getYTowards(short directionEnum)
{
   int y = 0;
   switch(directionEnum)
   {
      case NORTH_EAST :
      case NORTH :
      case NORTH_WEST : y = -1; break;
      case SOUTH_EAST :
      case SOUTH :
      case SOUTH_WEST : y = 1; break;
   }
   return y;
}

void printCharMap(char* charMap, int width)
{
   for(int y = 0; y < width; y++)
   {
      for(int x = 0; x < width; x++)
      {
         putchar(charMap[cartesianToIndex(x, y, width)]);
      }
      putchar('\n');
   }
}