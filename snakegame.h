#include "define.h"

extern int nXHead, nYHead;
extern int nXTail, nYTail;
extern int nPlaying;
extern int nLatePt;
extern int nDirection[ARR_SIZE];
extern int nXBending[ARR_SIZE];
extern int nYBending[ARR_SIZE];
extern int nLength;
extern int nPassedFirst;
extern int nNotBent;
extern int nXApple, nYApple;
extern int nAppleCount;

extern void printWalls(WINDOW* win);
extern void printInitSnA(WINDOW* win);
extern void deleteTail(WINDOW* win);
extern void addHead(WINDOW* win);
extern void addNewApple(WINDOW* win);
extern void getInput();
