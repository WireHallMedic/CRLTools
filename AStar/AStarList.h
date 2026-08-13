#ifndef ASTARDEFS_H
   #include "AStarDefs.h"
#endif

struct AStarListElement
{
   AStarNode* node;
   struct AStarListElement* next;
   struct AStarListElement* prev;
};
typedef struct AStarListElement AStarListElement;

struct AStarList
{
   AStarListElement* head;
   int length;
};
typedef struct AStarList AStarList;

void setHead(AStarNode* node, AStarList* list);

void push(AStarNode* node, AStarNode* parent, AStarList* list);

void insertBefore(AStarListElement* newNode, AStarListElement* existingNode);

void insertAfter(AStarListElement* newNode, AStarListElement* existingNode);

AStarNode* pop(AStarList* list);

void clearRemaining(AStarList* list);