#pragma once
#include <stdio.h>
#include <Windows.h>

//shape, direc //level, score 구조체
struct minoInfo { int shape; int direc; int x; int y; }; typedef minoInfo;
struct gradeInfo { int level; int score; }; typedef gradeInfo;
struct locationInfo { int left_x; int right_x; int bottom_y; int top_y; } typedef locationInfo;

enum Shape { BAR, CHAIR_L, CHAIR_R,SQUARE,Z_L,Z_R,T};
//enum Direc {UP,RIGHT,DOWN,LEFT};
enum PrintIndex {BarHoriz, BarVertical, ZLVertical, ZLHoriz, ZRVertical, ZRHoriz, Square, ChairL0, ChairL1, ChairL2, ChairL3,
																		ChairR0, ChairR1, ChairR2, ChairR3,  T0, T1, T2, T3 };

//원하는 좌표로 커서 옮기기
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//현재 좌표를 받아서 화면에 도형 출력, location 정보 set
void PrintTemp(minoInfo mino, locationInfo* location) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape+ mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		gotoxy(x - 2, y); printf("□□□□"); *location = {x-2,x+4,y,y}; break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { gotoxy(x, y+i); printf("□"); }
		*location = { x,x,y+2,y-1 };
		break;
	case ZLVertical:
		gotoxy(x+2, y-1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y+1); printf("□");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ZLHoriz:
		gotoxy(x - 2, y); printf("□□");
		gotoxy(x, y + 1); printf("□□");
		*location = { x - 2,x + 2,y+1,y };
		break; 
	case ZRVertical:
		gotoxy(x, y-1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x+2, y+1); printf("□");
		*location = { x,x+2,y+1,y-1};
		break;
	case ZRHoriz:
		gotoxy(x, y); printf("□□");
		gotoxy(x-2, y+1); printf("□□");
		*location = {x-2,x + 2,y+1,y};
		break;
	case Square:
		gotoxy(x, y); printf("□□");
		gotoxy(x, y+1); printf("□□");
		*location = {x,x+2,y+1,y };
		break;
	case ChairL0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x - 2, y+1); printf("□");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairL1:
		gotoxy(x, y - 1); printf("□□");
		gotoxy(x+2, y); printf("□");
		gotoxy(x+2, y + 1); printf("□");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ChairL2:
		gotoxy(x+2, y); printf("□");
		gotoxy(x-2, y+1); printf("□□□");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairL3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ChairR0:
		gotoxy(x-2, y); printf("□□□");
		gotoxy(x+2, y+1); printf("□");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairR1:
		gotoxy(x+2, y - 1); printf("□");
		gotoxy(x+2, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ChairR2:
		gotoxy(x-2, y); printf("□");
		gotoxy(x-2, y + 1); printf("□□□");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairR3:
		gotoxy(x, y - 1); printf("□□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□");
		*location = { x,x + 2,y + 1,y-1 };
		break;
	case T0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x, y + 1); printf("□");
		*location = { x-2,x + 2,y + 1,y };
		break;
	case T1:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x - 2, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		*location = { x - 2,x,y + 1,y-1 };
		break;
	case T2:
		gotoxy(x, y-1); printf("□");
		gotoxy(x - 2, y); printf("□□□");
		*location = { x - 2,x + 2,y,y-1 };
		break;
	case T3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		*location = { x,x + 2,y + 1,y-1 };
		break;
	}
}
