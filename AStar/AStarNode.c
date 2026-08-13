#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "AStarNode.h"
#ifndef ASTARDEFS_H
   #include "AStarDefs.h"
#endif


void initializeNode(AStarNode* node, int locX, int locY, int targetX, int targetY)
{
   node->f = -1;
   node->g = -1;
   int xDist = locX - targetX;
   int yDist = locY - targetY;
   node->h = sqrt(xDist * xDist) + sqrt(yDist * yDist);
   node->cost = 1.0;
   node->locX = locX;
   node->locY = locY;
   node->parent = NULL;
   node->status = UNCHECKED;
   node->passable = TRUE;
}

void calcF(AStarNode* node)
{
   node->f = node->g + node->h;
}

void updateNode(AStarNode* prospectiveParent, AStarNode* prospectiveChild, double stepDist)
{
   // early exit if impassable or closed
   if(prospectiveChild->passable == FALSE ||
      prospectiveChild->status == CLOSED)
      return;
      
   double prospectiveG = calcG(prospectiveParent, prospectiveChild, stepDist);
   if(prospectiveChild->parent == NULL || prospectiveChild->g > prospectiveG)
   {
      prospectiveChild->parent = prospectiveParent;
      prospectiveChild->g = prospectiveG;
      calcF(prospectiveChild);
   }
}

double calcG(AStarNode* parent, AStarNode* child, double stepDist)
{
   return parent->g + (stepDist * child->cost);
}

char getDirectionTo(AStarNode* origin, AStarNode* adj)
{
   int xStep = adj->locX - origin->locX;
   int yStep = adj->locY - origin->locY;
   char stepDir = ORIGIN;
   if(xStep == 1) // east
   {
      switch(yStep)
      {
         case -1 : stepDir = NORTH_EAST; break;
         case 0  : stepDir = EAST; break;
         case 1  : stepDir = SOUTH_EAST; break;
      }
   }
   else if(xStep == -1) // west
   {
      switch(yStep)
      {
         case -1 : stepDir = NORTH_WEST; break;
         case 0  : stepDir = WEST; break;
         case 1  : stepDir = SOUTH_WEST; break;
      }
   }
   if(xStep == 0) // neither east nor west
   {
      switch(yStep)
      {
         case -1 : stepDir = NORTH; break;
         case 1  : stepDir = SOUTH; break;
      }
   }
   return stepDir;
}

void tracePath(AStarNode* node)
{
   printf("[%d, %d] ", node->locX, node->locY);
   if(node->parent != NULL)
      tracePath(node->parent);
   else
      printf("\n");
}