#include <stdio.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include "event.h"

int nXHead, nYHead;
int nXTail, nYTail;
int nPlaying;
int nLatePt = -1;
int nOldPt = -1;
int nDirection[40];
int nXBending[40];
int nYBending[40];
int nLength = 10;

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
		char *ch;
		switch (nDirection[nLatePt])
		{
			case 0: 
				nXHead--;
				ch = "▲ ";
				break;
			case 1:
				nXHead++;
				ch = "▼ ";
				break;
                        case 2:
                                nYHead++;
                                ch = "▶ ";
                                break;

			case 3:
				nYHead--;
				ch = "◀ ";
				break;
		}	
                mvwprintw(win, nXHead, nYHead*2, "%s", ch);
}

void getInput()
{
	init_keyboard();
	if (_kbhit())
	{
		int ch1 = _getch();
		if (ch1 == 27)
		{
			int ch2 = _getch();
			int ch3 = _getch();
			
			if (nLatePt == -1 && ch3 == 68)//게임시작전 입력 키가 <-일때
				return;

			//진행방향과 같은 축의 방향키를 입력했을 때
			if (nDirection[nLatePt] == 0 ||nDirection[nLatePt] == 1)
			{
				if (ch3 == 65 || ch3 == 66)
					return;
			}
			else //2,3
			{
				if (ch3 == 67 || ch3 == 68)
					return;
			}

			nLatePt++;
			if (nLatePt >= 40)
				nLatePt -= 40;

			nXBending[nLatePt] = nXHead;
			nYBending[nLatePt] = nYHead;

			switch (ch3)
			{
				case 65://up
					nDirection[nLatePt] = 0;
					break;
				case 66://down
					nDirection[nLatePt] = 1;
					break;
				case 67://right
					nDirection[nLatePt] = 2;
					break;
				case 68://left
					nDirection[nLatePt] = 3;
					break;
			}
			
			nPlaying = 1;
				
		}
	}
}
