#include <stdio.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "snakegame.h"

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

	win = newwin(17+10, 19*2, 1, 1);//새로운 윈도우를 생성
	wbkgd(win, COLOR_PAIR(1));//win에 색쌍 적용
	wattron(win, COLOR_PAIR(1));//?

	printWalls(win);
	printInitSnA(win);

	wrefresh(win); //특정 윈도우 새로고침

	//moveSnake(win);
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
			gettimeofday(&tvStart, NULL);
		}
		
		mvwprintw(win, 17, 0, "tail %d %d", nXTail, nYTail);
		for (int i = 0; i < 10; i++)
		{
			mvwprintw(win, i + 18, 0, "%d %d %d %d", 
					i, nDirection[i], 
					nXBending[i], nYBending[i]); 
		}
		wrefresh(win);
	}
	getch();
	delwin(win);//윈도우 메모리 해제
	endwin();//윈도우 종료

	return 0;
}
