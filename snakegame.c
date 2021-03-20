#include <stdio.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
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
int nPassedFirst = 0;
int nNotBent = 1;
int nXApple, nYApple;

void printWalls(WINDOW *win)
{
	mvwprintw(win, 0, 0,"■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■i");
	for (int i = 1; i < 16; i++)
	{
		mvwprintw(win, i, 0,"■ "); 
		mvwprintw(win, i, 18*2, "■ ");
//		mvwprintw(win, i, 0, "■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■i");
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
	
	nXApple = 8; nYApple = 14;
}

void deleteTail(WINDOW* win)
{
	mvwprintw(win, nXTail, nYTail*2, " ");
	//*****꼬리좌표 업데이트*****
	//꺾은 적 없음
	if (nLatePt == 0 && nNotBent == 1)
	{
		nYTail++;
		return;
	}
	//꺾었으나 첫 꺾인 점 못 지남
	if (nPassedFirst == 0 && nLatePt == 1 && nXTail == nXBending[1] && nYTail < nYBending[1])
	{
		nYTail++;
		nNotBent = 0;
		return;
	}
	
	//첫 꺾인 점 지남
	nXTail = nXHead; nYTail = nYHead;
	nPassedFirst = 1;
	int temp = nLength;
	int pt = nLatePt;
	while (temp > 1)
	{
		if (nXTail == nXBending[pt] && nYTail == nYBending[pt])
		{
			pt--;
			if (pt < 0)
			{
				pt += 40;
			}
		}
		//nDirection[pt]사용하여 머리부터 꼬리까지 따라가기
		switch (nDirection[pt])
		{
			case 0:
				nXTail++;
				break;
			case 1:
				nXTail--;
				break;
			case 2:
				nYTail--;
				break;
			case 3:
				nYTail++;
				break;
		}
		temp--;
	}
}

void addNewApple(WINDOW* win)
{
        if (nXHead == nXApple && nYHead == nYApple)
        {
                //nLength++;

                srand(time(NULL));
                nXApple = rand() % 15; nXApple++;
                nYApple = rand() % 17; nYApple++;
		int len = nLength; int pt = nLatePt;
		while(len > 1)
		{
			if (x == nXApple && y == nYApple)
			{
				len = nLength;
				x = nXHead; y = nYHead;
				nXApple = rand() % 15; nXApple++;
				nYApple = rand() % 17; nYApple++;
			}
	                if (x == nXBending[pt] && y == nYBending[pt])
	                {
        	                pt--;
                	        if (pt < 0)
 	                       {
	                                pt += 40;
        	                }
	                }
        	        //nDirection[pt]사용하여 머리부터 꼬리까지 따라가기
               		 switch (nDirection[pt])
	                {
        	                case 0:
                	                x++;
                        	        break;
	                        case 1:
        	                        x--;
                	                break;
                        	case 2:
                                	y--;
	                                break;
        	                case 3:
                	                y++;
                        	        break;
	                }
			len--;
		}

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, nXApple, nYApple*2, "■ ");
        }


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

        addNewApple(win);
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
