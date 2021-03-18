#include <time.h>

extern int nXHead, nYHead;
extern int nXTail, nYTail;
extern int nPlaying;
extern int nLatePt, nOldPt;
extern int nDirection[40];
extern int nXBending[40];
extern int nYBending[40];

extern void printWalls(WINDOW*);
extern void printInitSnA(WINDOW*);
extern void deleteTail(WINDOW*);
extern void addHead(WINDOW*);
extern void getInput();
