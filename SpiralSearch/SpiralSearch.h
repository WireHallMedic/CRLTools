#include<stdlib.h>

struct SearchStep
{
   int x;         
   int y;         
   struct SearchStep *next;    
};
typedef struct SearchStep SearchStep;