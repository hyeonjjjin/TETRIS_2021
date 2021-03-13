#pragma once
#include <stdio.h>
#include <Windows.h>

#define square "□"

//shape, direc //level, score 구조체
struct tempInfo { int shape; int direc; }; typedef tempInfo;
struct gradeInfo { int level; int score; }; typedef gradeInfo;

enum Shape { BAR, CHAIR_L, CHAIR_R,SQUARE,Z_L,Z_R,T};
enum Direc {UP,RIGHT,DOWN,LEFT};
enum PrintIndex {BarVertical, BarHoriz, ZLVertical, ZLHoriz, ZRVertical, ZRHoriz, Square, ChairL0, ChairL1, ChairL2, ChairL3,
																		ChairR0, ChairR1, ChairR2, ChairR3,  T0, T1, T2, T3 };

//원하는 좌표로 커서 옮기기
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void PrintTemp(tempInfo temp, int x, int y) {
	int printIndex = -1;
	int tempInfoIndex = temp.shape+temp.direc;
	switch (tempInfoIndex) {
	case BarVertical:
		for (int i = -1; i < 3; i++) { gotoxy(x, y + i*2); printf(square); }break;
	case BarHoriz:
		gotoxy(x-2, y); printf("□□□□"); break;
	case ZLVertical:
		gotoxy(x, y-1); printf("□");
		gotoxy(x-2, y); printf("□□");
		gotoxy(x-2, y+1); printf("□");
		break;
	case ZLHoriz:
		gotoxy(x - 2, y); printf("□□");
		gotoxy(x, y + 1); printf("□□");
		break; 
	case ZRVertical:
		gotoxy(x-2, y-1); printf("□");
		gotoxy(x-2, y); printf("□□");
		gotoxy(x, y+1); printf("□");
		break;
	case ZRHoriz:
		gotoxy(x, y); printf("□□");
		gotoxy(x-2, y+1); printf("□□");
		break;
	case Square:
		gotoxy(x, y); printf("□□");
		gotoxy(x, y+1); printf("□□");
		break;
	case ChairL0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x - 2, y+1); printf("□");
		break;
	case ChairL1:
		gotoxy(x - 2, y - 1); printf("□□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□");
		break;
	case ChairL2:
		gotoxy(x+2, y); printf("□");
		gotoxy(x-2, y+1); printf("□□□");
		break;
	case ChairL3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairR0:
		gotoxy(x-2, y); printf("□□□");
		gotoxy(x+2, y+1); printf("□");
		break;
	case ChairR1:
		gotoxy(x+2, y - 1); printf("□");
		gotoxy(x+2, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairR2:
		gotoxy(x-2, y); printf("□");
		gotoxy(x-2, y + 1); printf("□□□");
		break;
	case ChairR3:
		gotoxy(x, y - 1); printf("□□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□");
		break;
	case T0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x, y + 1); printf("□");
		break;
	case T1:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x - 2, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		break;
	case T2:
		gotoxy(x, y-1); printf("□");
		gotoxy(x - 2, y); printf("□□□");
		break;
	case T3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		break;
	}
	/*
	if (temp.shape == SQUARE) printIndex = Square;
	else if (temp.shape == BAR) (temp.direc == UP || temp.direc == DOWN)? printIndex = BarVertical: printIndex = BarHoriz;
	else if (temp.shape == Z_L) (temp.direc == UP || temp.direc == DOWN) ? printIndex = ZLVertical : printIndex = ZLHoriz;
	else if (temp.shape == Z_R) (temp.direc == UP || temp.direc == DOWN) ? printIndex = ZRVertical : printIndex = ZRHoriz;
	else if (temp.shape == CHAIR_L) {
		if (temp.direc == UP) printIndex = ChairL0;
		else if (temp.direc == RIGHT)  printIndex = ChairL1;
		else if (temp.direc == DOWN)  printIndex = ChairL2;
		else if (temp.direc == LEFT)  printIndex = ChairL3;
	}
	else if (temp.shape == CHAIR_R) {
		if (temp.direc == UP) printIndex = ChairR0;
		else if (temp.direc == RIGHT)  printIndex = ChairR1;
		else if (temp.direc == DOWN)  printIndex = ChairR2;
		else if (temp.direc == LEFT)  printIndex = ChairR3;
	}
	else if (temp.shape == T) {
		if (temp.direc == UP) printIndex = T0;
		else if (temp.direc == RIGHT)  printIndex = T1;
		else if (temp.direc == DOWN)  printIndex = T2;
		else if (temp.direc == LEFT)  printIndex = T3;
	}*/

}
