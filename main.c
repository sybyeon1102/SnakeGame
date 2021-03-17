#include <stdio.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <unistd.h>
#include "snakegame.h"

int main()
{

	WINDOW *win; // 객체 생성
	setlocale(LC_ALL, "ko_KR.utf8");
	initscr(); //curses모드를 시작
	start_color();//color모드를 시작
	
	init_pair(1, COLOR_WHITE, COLOR_BLACK);//컬러를 설정
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

	refresh();//화면에 찍은 내용을 갱신

	win = newwin(17, 19*2, 1, 1);//새로운 윈도우를 생성
	wbkgd(win, COLOR_PAIR(1));//win에 색쌍 적용
	wattron(win, COLOR_PAIR(1));//?

	printWalls(win);
	printInitSnA(win);

	wrefresh(win); //특정 윈도우 새로고침

	//moveSnake(win);
	
	while(1)
	{       
		wattron(win, COLOR_PAIR(2));
		deleteTail(win);
		addHead(win);
		wrefresh(win);
		sleep(1);
	}
	getch();
	delwin(win);//윈도우 메모리 해제
	endwin();//윈도우 종료

	return 0;
}
