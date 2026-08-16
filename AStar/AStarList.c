#include <stdlib.h>
#include <stdio.h>
#ifndef ASTARDEFS_H
   #include "AStarDefs.h"
#endif

#include "AStarList.h"
#include "AStarNode.h"


void setHead(AStarNode* node, AStarList* list)
{
   AStarListElement* newElement = (AStarListElement *)malloc(sizeof(AStarListElement));
   newElement->node = node;
   newElement->next = NULL;
   newElement->prev = NULL;
   node->g = 0.0;
   node->status = OPEN;
   calcF(node);
   list->head = newElement;
   list->length = 1;
}

void push(AStarNode* node, AStarNode* parent, AStarList* list)
{
   // create list element from node
   AStarListElement* newElement = (AStarListElement *)malloc(sizeof(AStarListElement));
   newElement->node = node;
   newElement->next = NULL;
   newElement->prev = NULL;
   
   // node is now on open list
   node->status = OPEN;
   node->parent = parent;
   
   double stepDist = ORTHO_STEP;
   if(parent->locX != node->locX && parent->locY != node->locY)
      stepDist = DIAG_STEP;
   node->g = calcG(parent, node, stepDist);
   calcF(node);
   
   // list is empty
   if(list->head == NULL)
   {
      list->head = newElement;
   }
   // list not empty
   else
   {
      AStarListElement* curElement = list->head;
      while(curElement != NULL)
      {
         // new element goes before current one
         if(newElement->node->f < curElement->node->f)
         {
            insertBefore(newElement, curElement);
            // inserting at first position
            if(curElement == list->head)
               list->head = newElement;
            break;
         }
         // end of list, insert at end
         else if(curElement->next == NULL)
         {
            insertAfter(newElement, curElement);
            break;
         }
         // not end of list, increment and continue
         else
         {
            curElement = curElement->next;
         }
      }
   }
   list->length++;
}

void insertBefore(AStarListElement* newNode, AStarListElement* existingNode)
{
   AStarListElement* a = existingNode->prev;
   AStarListElement* b = newNode;
   AStarListElement* c = existingNode;
   if(a != NULL)
      a->next = b;
   b->next = c;
   b->prev = a;
   c->prev = b;
}

void insertAfter(AStarListElement* newNode, AStarListElement* existingNode)
{
   AStarListElement* a = existingNode;
   AStarListElement* b = newNode;
   AStarListElement* c = existingNode->next;
   a->next = b;
   b->next = c;
   b->prev = a;
   if(c != NULL)
      c->prev = b;
}

// remove and free first element in list, return that node
AStarNode* pop(AStarList* list)
{
   // store old head element
   AStarListElement* oldHead = list->head;
   // store old head node
   AStarNode* oldHeadNode = oldHead->node;
   // set head to next element
   list->head = oldHead->next;
   // if new head is not null, set prev to null
   if(list->head != NULL)
      list->head->prev = NULL;
      
   free(oldHead);
   list->length--;
   return oldHeadNode;
}

// delete remaining links (nodes are stack, not heap)
void clearRemaining(AStarList* list)
{
   AStarListElement* curElement = list->head;
   while(curElement != NULL)
   {
      AStarListElement* oldElement = curElement;
      curElement = curElement->next;
      free(oldElement);
   }
}

