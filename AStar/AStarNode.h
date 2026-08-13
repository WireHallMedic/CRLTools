#ifndef ASTARDEFS_H
   #include "AStarDefs.h"
#endif

void initializeNode(AStarNode* node, int locX, int locY, int targetX, int targetY);

void calcF(AStarNode* node);

void updateNode(AStarNode* prospectiveParent, AStarNode* prospectiveChild, double stepDist);

// char used to keep lists small; we only need five bits
char getDirectionTo(AStarNode* origin, AStarNode* adj);

void tracePath(AStarNode* node);

double calcG(AStarNode* parent, AStarNode* child, double stepDist);