#define ASTARDEFS_H

#define ORIGIN 0
#define NORTH 1
#define NORTH_EAST 2
#define EAST 3
#define SOUTH_EAST 4
#define SOUTH 5
#define SOUTH_WEST 6
#define WEST 7
#define NORTH_WEST 8

#define UNCHECKED 0
#define OPEN 1
#define CLOSED 2

#define FALSE 0
#define TRUE 1

#define ORTHO_STEP 1.0
#define DIAG_STEP 1.4

#define MAX_PATH_LENGTH 64

#define MAX_LOOPS 5000

struct AStarNode
{
   double f;         // g + h
   double g;         // estimated distance to target
   double h;         // distance from origin
   double cost;      // cost multiplier to enter (1.0 default)
   int locX;         // Cartesian coords of this node
   int locY;         
   struct AStarNode* parent;  // node path enters from
   int status;       // unchecked, open, or closed
   int passable;     // true/false
};
typedef struct AStarNode AStarNode;