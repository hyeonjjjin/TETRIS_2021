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

int ground[44][27] = { '\0' };

//원하는 좌표로 커서 옮기기
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//location 정보 set. 만약 입력 받은 정보대로 위치를 바꿀 수 없다면 return -1
int UpdateLocation(minoInfo mino, locationInfo* location) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape + mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		if (((x < 26) || (x > 38)) || (y > 26))
			return -1;
		*location = { x - 2,x + 4,y,y }; break;
	case BarVertical:
		if (((x < 24) || (x > 42)) || ((y > 24) || (y < 8)))
			return -1;
		*location = { x, x, y + 2, y - 1 }; break;
	case ZLVertical:
	case ZRVertical:
	case ChairL1:
	case ChairL3:
	case ChairR1:
	case ChairR3:
	case T3:
		if (((x < 24) || (x > 40)) || ((y > 25) || (y < 8)))
			return -1;
		*location = { x, x + 2,y + 1,y - 1 }; break;
	case ZLHoriz:
	case ZRHoriz:
	case ChairL0:
	case ChairL2:
	case ChairR0:
	case ChairR2:
	case T0:
		if (((x < 26) || (x > 40)) || ((y > 25) || (y < 7)))
			return -1;
		*location = { x - 2,x + 2,y + 1,y }; break;
	case Square:
		if (((x < 24) || (x > 40)) || ((y > 25) || (y < 7)))
			return -1;
		*location = { x, x + 2,y + 1,y }; break;
	case T1:
		if (((x < 26) || (x > 42)) || ((y > 25) || (y < 8)))
			return -1;
		*location = { x - 2, x, y + 1, y - 1 }; break;
	case T2:
		if (((x < 26) || (x > 40)) || ((y > 26) || (y < 8)))
			return -1;
		*location = { x - 2, x + 2, y, y - 1 }; break;
	}
	return 1;
}

//만약 입력받은 정보대로 위치를 바꿀 수 없다면 return -1
//이 함수 호출 후 return -1이 아니라면 이전 위치 지우는 함수 실행
//아래 양 옆 따로 지우는 함수 필요함
int UpdateNewPosition(minoInfo mino ) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape + mino.direc;

	switch (minoInfoIndex) {
	case BarHoriz:
		for (int i = 0; i < 4; i++) { if (ground[x - 2 + i][y] > 1) return -1; }
		for (int i = 0; i < 4; i++) ground[x - 2 + i][y] = 1;
	    break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { if(ground[x][y + i]>1) return -1; }
		for (int i = -1; i < 3; i++) { ground[x][y + i] = 1; }
		break;
	case ZLVertical:
		if (((ground[x + 2][y - 1] > 1) || (ground[x][y] > 1)) || ((ground[x + 2][y] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x + 2][y - 1] = 1; ground[x][y] = 1; ground[x + 2][y] = 1; ground[x][y + 1];
		break;
	case ZLHoriz:
		if (((ground[x - 2][y] > 1) || (ground[x][y] > 1)) || ((ground[x][y+1] > 1) || (ground[x+2][y + 1] > 1))) return -1;
		ground[x - 2][y] = 1; ground[x][y] = 1; ground[x][y + 1] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ZRVertical:
		if (((ground[x][y-1] > 1) || (ground[x][y] > 1)) || ((ground[x+2][y] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x][y] = 1; ground[x + 2][y] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ZRHoriz:
		if (((ground[x][y] > 1) || (ground[x+2][y] > 1)) || ((ground[x-2][y + 1] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x][y] = 1; ground[x + 2][y] = 1; ground[x - 2][y + 1] = 1; ground[x][y + 1] = 1;
		break;
	case Square:
		if (((ground[x][y] > 1) || (ground[x + 2][y] > 1)) || ((ground[x][y + 1] > 1) || (ground[x+2][y + 1] > 1))) return -1;
		ground[x][y] = 1; ground[x + 2][y] = 1; ground[x][y + 1] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairL0:
		if (((ground[x-2][y] > 1) || (ground[x][y] > 1)) || ((ground[x+2][y] > 1) || (ground[x - 2][y + 1] > 1))) return -1;
		ground[x - 2][y] = 1; ground[x][y] = 1; ground[x + 2][y] = 1; ground[x - 2][y + 1] = 1;
		break;
	case ChairL1:
		if (((ground[x][y-1] > 1) || (ground[x+2][y-1] > 1)) || ((ground[x + 2][y] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x + 2][y - 1] = 1; ground[x + 2][y] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairL2:
		if (((ground[x+2][y] > 1) || (ground[x - 2][y + 1] > 1)) || ((ground[x][y+1] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x + 2][y] = 1; ground[x - 2][y + 1] = 1; ground[x][y + 1] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairL3:
		if (((ground[x][y-1] > 1) || (ground[x][y] > 1)) || ((ground[x][y + 1] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x][y] = 1; ground[x][y + 1] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairR0:
		if (((ground[x-2][y] > 1) || (ground[x][y] > 1)) || ((ground[x+2][y] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x - 2][y] = 1; ground[x][y] = 1; ground[x + 2][y] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairR1:
		if (((ground[x+2][y - 1] > 1) || (ground[x+2][y] > 1)) || ((ground[x][y + 1] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x+2][y - 1] = 1; ground[x+2][y] = 1; ground[x][y + 1] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairR2:
		if (((ground[x-2][y] > 1) || (ground[x - 2][y + 1] > 1)) || ((ground[x][y + 1] > 1) || (ground[x + 2][y + 1] > 1))) return -1;
		ground[x - 2][y] = 1; ground[x - 2][y + 1] = 1; ground[x][y + 1] = 1; ground[x + 2][y + 1] = 1;
		break;
	case ChairR3:
		if (((ground[x][y - 1] > 1) || (ground[x + 2][y - 1] > 1)) || ((ground[x][y] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x + 2][y - 1] = 1; ground[x][y] = 1; ground[x][y + 1] = 1;
		break;
	case T0:
		if (((ground[x - 2][y] > 1) || (ground[x][y] > 1)) || ((ground[x + 2][y] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x - 2][y] = 1; ground[x][y] = 1; ground[x + 2][y] = 1; ground[x][y + 1] = 1;
		break;
	case T1:
		if (((ground[x][y-1] > 1) || (ground[x-2][y] > 1)) || ((ground[x][y] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x - 2][y] = 1; ground[x][y] = 1; ground[x][y + 1] = 1;
		break;
	case T2:
		if (((ground[x][y-1] > 1) || (ground[x - 2][y] > 1)) || ((ground[x][y] > 1) || (ground[x + 2][y] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x - 2][y] = 1; ground[x][y] = 1; ground[x + 2][y] = 1;
		break;
	case T3:
		if (((ground[x][y - 1] > 1) || (ground[x][y] > 1)) || ((ground[x+2][y] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x][y - 1] = 1; ground[x - 2][y] = 1; ground[x][y] = 1; ground[x][y + 1] = 1;
		break;
	}
	return 1;

}

//내려가기 가능할 때 이전 위치 흔적지워
void DeletePrevPosition_Down(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape + mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		for (int i = -1; i < 3; i++) { ground[x - 2 + i][y-1] = 0; } break;
	case BarVertical:
		ground[x][y - 2] = 0; break;
	case ZLVertical:
		ground[x + 2][y - 2] = 0; ground[x][y - 1] = 0;
		break;
	case ZLHoriz:
		ground[x - 2][y - 1] = 0; ground[x][y - 1] = 0; ground[x + 2][y] = 0; 
		break;
	case ZRVertical:
		ground[x][y - 2] = 0; ground[x+2][y - 1] = 0;
		break;
	case ZRHoriz:
		ground[x][y - 1] = 0; ground[x+2][y - 1] = 0; ground[x -2][y] = 0;
		break;
	case Square:
		ground[x][y - 1] = 0; ground[x + 2][y - 1] = 0;
		break;
	case ChairL0:
	case ChairR0:
	case T0:
		ground[x-2][y - 1] = 0; ground[x][y - 1] = 0; ground[x + 2][y-1] = 0;
		break;
	case ChairL1:
	case ChairR3:
		ground[x][y - 2] = 0; ground[x+2][y - 2] = 0;
		break;
	case ChairL2:
		ground[x+2][y - 1] = 0; ground[x-2][y] = 0; ground[x][y] = 0;
		break;
	case ChairL3:
		ground[x][y - 2] = 0; ground[x + 2][y] = 0;
		break;
	case ChairR1:
		ground[x][y - 2] = 0; ground[x][y] = 0;
		break;
	case ChairR2:
		ground[x - 2][y-1] = 0; ground[x][y] = 0; ground[x+2][y] = 0;
		break;
	case T1:
		ground[x][y - 2] = 0; ground[x - 2][y - 1] = 0;
		break;
	case T2:
		ground[x][y - 2] = 0; ground[x-2][y-1] = 0; ground[x + 2][y-1] = 0;
		break;
	case T3:
		ground[x][y - 2] = 0; ground[x + 2][y - 1] = 0;
		break;
	}
}

//left 이동할 때 이전 위치 흔적지워
void DeletePrevPosition_Left(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape + mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		ground[x+6][y] = 0; break;
	case BarVertical:
		for (int i = -1; i < 3; i++) ground[x + 2][y+i] = 0;
		break;
	case ZLVertical:
		ground[x + 4][y -1] = 0; 
		ground[x + 4][y] = 0;
		ground[x + 2][y + 1] = 0;
		break;
	case ZLHoriz:
		ground[x + 2][y] = 0;
		ground[x + 4][y + 1] = 0;
		break;
	case ZRVertical:
		ground[x + 2][y-1] = 0;
		ground[x + 4][y] = 0;
		ground[x + 4][y+1] = 0;
		break;
	case ZRHoriz:
	case T0:
		ground[x + 4][y] = 0;
		ground[x + 2][y + 1] = 0;
		break;
	case Square:
	case ChairR0:
		ground[x + 4][y] = 0;
		ground[x + 4][y+1] = 0;
		break;
	case ChairL0:
		ground[x + 4][y] = 0;
		ground[x][y+1] = 0;
		break;
	case ChairL1:
	case ChairR1:
		ground[x + 4][y-1] = 0;
		ground[x + 4][y] = 0;
		ground[x + 4][y+1] = 0;
		break;
	case ChairL2:
		ground[x + 4][y] = 0;
		ground[x + 4][y+1] = 0;
		break;
	case ChairL3:
		ground[x + 2][y-1] = 0;
		ground[x + 2][y] = 0;
		ground[x + 4][y+1] = 0;
		break;
	case ChairR2:
		ground[x][y] = 0;
		ground[x + 4][y+1] = 0;
		break;
	case ChairR3:
		ground[x + 4][y-1] = 0;
		ground[x + 2][y] = 0;
		ground[x + 2][y+1] = 0;
		break;
	case T1:
		ground[x + 2][y-1] = 0;
		ground[x + 2][y] = 0;
		ground[x + 2][y+1] = 0;
		break;
	case T2:
		ground[x + 2][y-1] = 0;
		ground[x + 4][y] = 0;
		break;
	case T3:
		ground[x + 2][y-1] = 0;
		ground[x + 4][y] = 0;
		ground[x + 2][y+1] = 0;
		break;
	}
}

//rotate 할 때 이전 위치 흔적지워
void DeletePrevPosition_Left(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape + mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		ground[x - 2][y] = 0;
		ground[x + 2][y] = 0;
		ground[x + 4][y] = 0;
		break;
	case BarVertical:
		ground[x][y-1] = 0;
		ground[x][y+1] = 0;
		ground[x][y+2] = 0;
		break;
	case ZLVertical:
		ground[x+2][y - 1] = 0;
		ground[x+2][y] = 0;
		break;
	case ZLHoriz:
		ground[x-2][y] = 0;
		ground[x+2][y + 1] = 0;
		break;
	case ZRVertical:
		ground[x][y - 1] = 0;
		ground[x+2][y + 1] = 0;
		break;
	case ZRHoriz:
		ground[x-2][y + 1] = 0;
		ground[x][y + 1] = 0;
		break;
	case ChairL0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x - 2, y + 1); printf("□");
		break;
	case ChairL1:
		gotoxy(x, y - 1); printf("□□");
		gotoxy(x + 2, y); printf("□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	case ChairL2:

		gotoxy(x + 2, y); printf("□");
		gotoxy(x - 2, y + 1); printf("□□□");
		break;
	case ChairL3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairR0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	case ChairR1:
		gotoxy(x + 2, y - 1); printf("□");
		gotoxy(x + 2, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairR2:
		gotoxy(x - 2, y); printf("□");
		gotoxy(x - 2, y + 1); printf("□□□");
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
		gotoxy(x, y - 1); printf("□");
		gotoxy(x - 2, y); printf("□□□");
		break;
	case T3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		break;
	}
}

//현재 좌표를 받아서 화면에 도형 출력, location set 분리
void PrintMino(minoInfo mino, locationInfo* location) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape + mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		gotoxy(x - 2, y); printf("□□□□"); break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { gotoxy(x, y + i); printf("□"); }
		break;
	case ZLVertical:
		gotoxy(x + 2, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		break;
	case ZLHoriz:
		gotoxy(x - 2, y); printf("□□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ZRVertical:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	case ZRHoriz:
		gotoxy(x, y); printf("□□");
		gotoxy(x - 2, y + 1); printf("□□");
		break;
	case Square:
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairL0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x - 2, y + 1); printf("□");
		break;
	case ChairL1:
		gotoxy(x, y - 1); printf("□□");
		gotoxy(x + 2, y); printf("□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	case ChairL2:
		gotoxy(x + 2, y); printf("□");
		gotoxy(x - 2, y + 1); printf("□□□");
		break;
	case ChairL3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairR0:
		gotoxy(x - 2, y); printf("□□□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	case ChairR1:
		gotoxy(x + 2, y - 1); printf("□");
		gotoxy(x + 2, y); printf("□");
		gotoxy(x, y + 1); printf("□□");
		break;
	case ChairR2:
		gotoxy(x - 2, y); printf("□");
		gotoxy(x - 2, y + 1); printf("□□□");
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
		gotoxy(x, y - 1); printf("□");
		gotoxy(x - 2, y); printf("□□□");
		break;
	case T3:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		break;
	}
}


//location 분리 전
/*
//현재 좌표를 받아서 화면에 도형 출력, location 정보 set
void PrintMino(minoInfo mino, locationInfo* location) {
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
*/