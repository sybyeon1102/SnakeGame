#include <stdio.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"
#include "define.h"

int nXHead, nYHead;
int nXTail, nYTail;
int nPlaying;
int nLatePt;
int nDirection[ARR_SIZE];
int nXBending[ARR_SIZE];
int nYBending[ARR_SIZE];
int nLength;
int nPassedFirst;
int nNotBent;
int nXApple, nYApple;
int nAppleCount;

void printWalls(WINDOW *win)
{
	mvwprintw(win, WALL_TOP, WALL_LEFT*2,
			"■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■i");
	for (int i = WALL_TOP + 1; i < WALL_BOTTOM; i++)
	{
		mvwprintw(win, i, WALL_LEFT*2,"■ "); 
		mvwprintw(win, i, WALL_RIGHT*2, "■ ");
	}
	mvwprintw(win, WALL_BOTTOM, WALL_LEFT*2,
			"■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■i");
}

void printInitSnA(WINDOW *win)
{
	//***뱀 사과 위치 초기화 및 출력
	nXHead = WALL_BOTTOM/2; nYHead = WALL_LEFT + 3;
	nXTail = WALL_BOTTOM/2; nYTail = WALL_LEFT + 1;

	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, nXTail, nYTail*2, "■ ■ ▶ ");
	
	nXApple = WALL_BOTTOM/2; nYApple = WALL_RIGHT - 4;
	
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, nXApple, nYApple*2, "■ ");
	
	//***기타 전역변수 초기화
	nLatePt = -1;
	nLength = 3;
	nPassedFirst = 0;
	nNotBent = 1;
	nAppleCount = 0;
}

void deleteTail(WINDOW* win)
{
	mvwprintw(win, nXTail, nYTail*2, " ");
	//게임을 시작한 후 몸통을 꺾은 적 없음
	if (nLatePt == 0 && nNotBent == 1)
	{
		nYTail++;
		return;
	}
	//몸통을 꺾었으나 꼬리가 첫 꺾인 점 못 지남
	if (!nPassedFirst && nLatePt 
			&& nXTail == nXBending[nLatePt] && nYTail < nYBending[nLatePt])
	{
		nYTail++;
		nNotBent = 0;
		return;
	}
	//꼬리가 첫 꺾인 점 지남
	nPassedFirst = 1;
	nXTail = nXHead; nYTail = nYHead;
	int len = nLength;
	int pt = nLatePt;
	while (len > 2)
	{
		if (nXTail == nXBending[pt] && nYTail == nYBending[pt])
		{
			pt--;
			if (pt < 0)
			{
				pt += ARR_SIZE;
			}
		}
		switch (nDirection[pt])
		{
			case UP:
				nXTail++;
				break;
			case DOWN:
				nXTail--;
				break;
			case RIGHT:
				nYTail--;
				break;
			case LEFT:
				nYTail++;
				break;
		}
		len--;
	}
}

void addNewApple(WINDOW* win)
{
        if (nXHead == nXApple && nYHead == nYApple)
        {
		nAppleCount++;
		nLength++;
		
		int x = nXHead; int y = nYHead;
		int len = nLength; int pt = nLatePt;
		while(len > 1)// -1)
		{	
			if (nXApple == x && nYApple == y)
			{
				len = nLength;
				x = nXHead; y = nYHead;
				pt = nLatePt;

				srand(time(NULL));
				nXApple = rand() % (WALL_BOTTOM - 1) ; nXApple++;
				nYApple = rand() % (WALL_RIGHT - 1); nYApple++;
			}
			else
			{
	                	if (x == nXBending[pt] && y == nYBending[pt])
	                	{
        	                	pt--;
                	        	if (pt < 0)
 	                        	{
	                                	pt += ARR_SIZE;
        	                	}
	                	}
	               		switch (nDirection[pt])
		        	{
      		  	        	case UP:
                				x++;
            		            	        break;
	     			        case DOWN:
        	      	        	        x--;
	               	        	        break;
        	               		case RIGHT:
                	               		y--;
                        			break;
	 	      	                case LEFT:
        		      	                y++;
               	        		        break;
	       			}
			}
			len--;
		}
		wattron(win, COLOR_PAIR(3));
		mvwprintw(win, nXApple, nYApple*2, "■ ");
        }
}

int isCrushing()
{
	//벽과 충돌
	if (nXHead == WALL_TOP || nXHead == WALL_BOTTOM 
			|| nYHead == WALL_LEFT || nYHead == WALL_RIGHT)
	{
		return 1;
	}
	//몸통과 충돌
	int x = nXHead; int y = nYHead;
	int pt = nLatePt; int len = nLength;
	while(len > 0)//1)
	{
		if (x == nXBending[pt] && y == nYBending[pt])
		{
			pt--;
			if (pt < 0)
			{
				pt += ARR_SIZE;
			}
		}
                switch (nDirection[pt])
                {
                        case UP:
                                x++;
                                break;
                        case DOWN:
                                x--;
                                break;
                        case RIGHT:
                                y--;
                                break;
                        case LEFT:
                                y++;
                                break;
                }
		if(x == nXHead && y == nYHead)
		{
			return 1;
		}
		len--;
	}

	return 0;
}
void addHead(WINDOW* win)
{
        mvwprintw(win, nXHead, nYHead*2, "■ ");
        char *ch;
        switch (nDirection[nLatePt])
        {
                case UP:
                        nXHead--;
                        ch = "▲ ";
                        break;
                case DOWN:
                        nXHead++;
                        ch = "▼ ";
                        break;
                case RIGHT:
                        nYHead++;
                        ch = "▶ ";
                        break;
                case LEFT:
                        nYHead--;
                        ch = "◀ ";
                        break;
        }
        mvwprintw(win, nXHead, nYHead*2, "%s", ch);

	if (isCrushing())
	{
		nPlaying = 0;
		return;
	}
        addNewApple(win);
}

void getInput()
{
	init_keyboard();
	if (_kbhit())
	{
		int ch1 = _getch();
		if (ch1 == KBRD_DIRECTION)
		{
			int ch2 = _getch();
			int ch3 = _getch();
			
			if (nLatePt == -1 && ch3 == KBRD_LEFT)//게임시작전 입력 키가 <-일때
				return;

			//진행방향과 같은 축의 방향키를 입력했을 때
			if (nDirection[nLatePt] == UP || nDirection[nLatePt] == DOWN)
			{
				if (ch3 == KBRD_UP || ch3 == KBRD_DOWN)
					return;
			}
			else //입력 값이 ->, <- 일때
			{
				if (ch3 == KBRD_RIGHT || ch3 == KBRD_LEFT)
					return;
			}

			nLatePt++;
			if (nLatePt >= ARR_SIZE)
				nLatePt -= ARR_SIZE;

			nXBending[nLatePt] = nXHead;
			nYBending[nLatePt] = nYHead;

			switch (ch3)
			{
				case KBRD_UP:
					nDirection[nLatePt] = UP;
					break;
				case KBRD_DOWN:
					nDirection[nLatePt] = DOWN;
					break;
				case KBRD_RIGHT:
					nDirection[nLatePt] = RIGHT;
					break;
				case KBRD_LEFT:
					nDirection[nLatePt] = LEFT;
					break;
			}

			nPlaying = 1;
		}
	}
	close_keyboard();
}
