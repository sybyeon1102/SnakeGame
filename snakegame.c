#include <stdio.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <time.h>

int nXHead, nYHead;
int nXTail, nYTail;
time_t tStart, tNow;

void printWalls(WINDOW *win)
{
	mvwprintw(win, 0, 0,"■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■i");
	for (int i = 1; i < 16; i++)
	{
		mvwprintw(win, i, 0,"■ "); 
		mvwprintw(win, i, 18*2, "■ ");
	}
	mvwprintw(win, 16, 0,"■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■i");
}

void printInitSnA(WINDOW *win)
{
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 8, 1*2, "■ ■ ■ ■ ■ ■ ■ ■ ■ ▶ ");
	
	nXHead = 8; nYHead = 10;
	nXTail = 8; nYTail = 1;

	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, 8, 14*2, "■ ");
	
}

void deleteTail(WINDOW* win)
{
		mvwprintw(win, nXTail, nYTail*2, "  ");
                nYTail++;
}
void addHead(WINDOW* win)
{
                mvwprintw(win, nXHead, nYHead*2, "■ ");
                nYHead++;
                mvwprintw(win, nXHead, nYHead*2, "▶ ");
}
