#include <time.h>

extern int nXHead, nYHead;
extern int nXTail, nYTail;
extern time_t tStart, tNow;

extern void printWalls(WINDOW*);
extern void printInitSnA(WINDOW*);
extern void deleteTail(WINDOW*);
extern void addHead(WINDOW*);
