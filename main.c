#include <stdio.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "snakegame.h"
#include "define.h"

int main()
{

	WINDOW *win; // 객체 생성
	setlocale(LC_ALL, "ko_KR.utf8");
	initscr(); //curses모드를 시작
	
	curs_set(0);
	noecho();

	start_color();//color모드를 시작
	
	init_pair(1, COLOR_WHITE, COLOR_BLACK);//컬러를 설정
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

	refresh();//화면에 찍은 내용을 갱신

	win = newwin(WALL_BOTTOM + 2, (WALL_RIGHT + 1)*2, 1, 1);//새로운 윈도우를 생성
	wbkgd(win, COLOR_PAIR(1));
	wattron(win, COLOR_PAIR(1));

	printWalls(win);
	printInitSnA(win);

	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, WALL_BOTTOM + 1, WALL_LEFT, "Apples : %d", nAppleCount);

	wrefresh(win); //특정 윈도우 새로고침

	nPlaying = 0;
	struct timeval tvStart, tvNow, tvGep;
	gettimeofday(&tvStart, NULL);
	while(1)
	{       
		if (!nPlaying)
		{
			getInput();
		}
		gettimeofday(&tvNow,NULL);
		tvGep.tv_sec = tvNow.tv_sec - tvStart.tv_sec;
		tvGep.tv_usec = tvNow.tv_usec - tvStart.tv_usec;
		if (tvGep.tv_usec < 0)
		{
			tvGep.tv_usec += 1000000;
		}

		if (nPlaying && tvGep.tv_usec >= 250000)
		{
			wattron(win, COLOR_PAIR(2));
			getInput();
			deleteTail(win);
			addHead(win);
			wrefresh(win);
			gettimeofday(&tvStart, NULL);
		
			if (!nPlaying)
			{
				wattron(win, COLOR_PAIR(3));
				mvwprintw(win, WALL_BOTTOM/2, (WALL_RIGHT/2 - 2)*2, 
						"GAME  OVER");
				mvwprintw(win, WALL_BOTTOM/2 + 1, (WALL_RIGHT/2 - 4)*2, 
						"Press 'q' to exit.");
				wrefresh(win);
				break;
			}
		}
	
		wattron(win, COLOR_PAIR(3));	
		mvwprintw(win, WALL_BOTTOM + 1, WALL_LEFT, "Apples : %d", nAppleCount);
	}
	char ch;
	while(1)
	{
		ch = getchar();
		if (ch == 'q')
		{
			delwin(win);//윈도우 메모리 해제
			endwin();//윈도우 종료
			return 0;
		}

	}
}
