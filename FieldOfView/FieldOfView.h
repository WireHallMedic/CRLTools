
int isInBounds(int index, int width);

// export function for DLL
void calcFoV(int* inputMap, int* outputMap, int mapLength, int radius);

void castLightInOctant(int* inputMap, int* outputMap, int width, int xLoc, int yLoc, 
      int oct, int radius);

void castLight(int* inputMap, int* outputMap, int width, int cx, int cy,
      int row, double start, double end, int radius, int xx, int xy, int yx, int yy);