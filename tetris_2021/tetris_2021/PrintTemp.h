#pragma once
#include <stdio.h>
#include <Windows.h>

//shape, direc //level, score ����ü
struct minoInfo { int shape; int direc; int x; int y; }; typedef minoInfo;
struct gradeInfo { int level; int score; }; typedef gradeInfo;
struct locationInfo { int left_x; int right_x; int bottom_y; int top_y; } typedef locationInfo;

enum Shape { BAR, CHAIR_L, CHAIR_R,SQUARE,Z_L,Z_R,T};
//enum Direc {UP,RIGHT,DOWN,LEFT};
enum PrintIndex {BarHoriz, BarVertical, ZLVertical, ZLHoriz, ZRVertical, ZRHoriz, Square, ChairL0, ChairL1, ChairL2, ChairL3,
																		ChairR0, ChairR1, ChairR2, ChairR3,  T0, T1, T2, T3 };

int ground[44][27] = { '\0' };

//���ϴ� ��ǥ�� Ŀ�� �ű��
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//location ���� set. ���� �Է� ���� ������� ��ġ�� �ٲ� �� ���ٸ� return -1
int UpdateLocation(minoInfo mino, locationInfo* location) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else  minoInfoIndex = mino.shape * 4 + mino.direc - 9;
	switch (minoInfoIndex) {
	case BarHoriz:
		if (((x < 26) || (x > 38)) || (y > 26))
			return -1;
		*location = { x - 2,x + 4,y,y }; break;
	case BarVertical:
		if (((x < 24) || (x > 42)) ||(y > 24))
			return -1;
		*location = { x, x, y + 2, y - 1 }; break;
	case ZLVertical:
	case ZRVertical:
	case ChairL1:
	case ChairL3:
	case ChairR1:
	case ChairR3:
	case T3:
		if (((x < 24) || (x > 40)) || (y > 25))
			return -1;
		*location = { x, x + 2,y + 1,y - 1 }; break;
	case ZLHoriz:
	case ZRHoriz:
	case ChairL0:
	case ChairL2:
	case ChairR0:
	case ChairR2:
	case T0:
		if (((x < 26) || (x > 40)) || (y > 25) )
			return -1;
		*location = { x - 2,x + 2,y + 1,y }; break;
	case Square:
		if (((x < 24) || (x > 40)) || (y > 25) )
			return -1;
		*location = { x, x + 2,y + 1,y }; break;
	case T1:
		if (((x < 26) || (x > 42)) || (y > 25) )
			return -1;
		*location = { x - 2, x, y + 1, y - 1 }; break;
	case T2:
		if (((x < 26) || (x > 40)) || (y > 26) )
			return -1;
		*location = { x - 2, x + 2, y, y - 1 }; break;
	}
	return 1;
}

//���� �Է¹��� ������� ��ġ�� �ٲ� �� ���ٸ� return -1
//�� �Լ� ȣ�� �� return -1�� �ƴ϶�� ���� ��ġ ����� �Լ� ����
//�Ʒ� �� �� ���� ����� �Լ� �ʿ���
int UpdateNewPosition(minoInfo mino ) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex= mino.shape * 4 + mino.direc - 9;

	switch (minoInfoIndex) {
	case BarHoriz:
		for (int i = 0; i < 4; i++) { if (ground[x - 2 + 2*i][y] > 1) return -1; }
		for (int i = 0; i < 4; i++) ground[x - 2 + 2*i][y] = 1;
	    break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { if(ground[x][y + i]>1) return -1; }
		for (int i = -1; i < 3; i++) { ground[x][y + i] = 1; }
		break;
	case ZLVertical:
		if (((ground[x + 2][y - 1] > 1) || (ground[x][y] > 1)) || ((ground[x + 2][y] > 1) || (ground[x][y + 1] > 1))) return -1;
		ground[x + 2][y - 1] = 1; ground[x][y] = 1; ground[x + 2][y] = 1; ground[x][y + 1]=1;
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
		ground[x][y - 1] = 1; ground[x][y] = 1; ground[x+2][y] = 1; ground[x][y + 1] = 1;
		break;
	}
	return 1;

}

void FixCurrentMino(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex = mino.shape * 4 + mino.direc - 9;
	switch (minoInfoIndex) {
	case BarHoriz:
		ground[x - 2][y] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x + 4][y] = 2;
		gotoxy(x - 2, y); printf("�����"); break;
	case BarVertical:
		for (int i = -1; i < 3; i++) ground[x][y+i] = 2;
		break;
	case ZLVertical:
		ground[x + 2][y-1] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x][y+1] = 2;
		break;
	case ZLHoriz:
		ground[x - 2][y] = 2; ground[x][y] = 2; ground[x][y+1] = 2; ground[x + 2][y+1] = 2;
		break;
	case ZRVertical:
		ground[x][y-1] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x + 2][y+1] = 2;
		break;
	case ZRHoriz:
		ground[x][y] = 2; ground[x + 2][y] = 2; ground[x - 2][y+1] = 2; ground[x][y+1] = 2;
		break;
	case Square:
		ground[x][y] = 2; ground[x + 2][y] = 2; ground[x][y+1] = 2; ground[x+2][y+1] = 2;
		break;
	case ChairL0:
		ground[x - 2][y] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x - 2][y+1] = 2;
		break;
	case ChairL1:
		ground[x][y-1] = 2; ground[x + 2][y-1] = 2; ground[x + 2][y] = 2; ground[x + 2][y+1] = 2;
		break;
	case ChairL2:
		ground[x + 2][y] = 2; ground[x - 2][y+1] = 2; ground[x][y+1] = 2; ground[x + 2][y+1] = 2;
		break;
	case ChairL3:
		ground[x][y-1] = 2; ground[x][y] = 2; ground[x][y+1] = 2; ground[x + 2][y+1] = 2;
		break;
	case ChairR0:
		ground[x - 2][y] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x + 2][y+1] = 2;
		break;
	case ChairR1:
		ground[x + 2][y-1] = 2; ground[x + 2][y] = 2; ground[x][y+1] = 2; ground[x + 2][y+1] = 2;
		break;
	case ChairR2:
		ground[x - 2][y] = 2; ground[x - 2][y+1] = 2; ground[x][y+1] = 2; ground[x +2][y+1] = 2;
		break;
	case ChairR3:
		ground[x][y-1] = 2; ground[x+2][y-1] = 2; ground[x][y] = 2; ground[x][y+1] = 2;
		break;
	case T0:
		ground[x - 2][y] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x][y+1] = 2;
		break;
	case T1:
		ground[x][y-1] = 2; ground[x - 2][y] = 2; ground[x][y] = 2; ground[x][y+1] = 2;
		break;
	case T2:
		ground[x][y-1] = 2; ground[x - 2][y] = 2; ground[x][y] = 2; ground[x + 2][y] = 2;
		break;
	case T3:
		ground[x][y-1] = 2; ground[x][y] = 2; ground[x + 2][y] = 2; ground[x][y+1] = 2;
		break;
	}
}

//�������� ������ �� ���� ��ġ ��������
void DeletePrevPosition_Down(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex = mino.shape * 4 + mino.direc - 9;
	switch (minoInfoIndex) {
	case BarHoriz:
		for (int i = 0; i < 4; i++) { ground[x - 2 + 2*i][y-1] = 0; } break;
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
		ground[x+2][y - 2] = 0; ground[x][y] = 0;
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

//left �̵��� �� ���� ��ġ ��������
void DeletePrevPosition_Left(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex =0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex= mino.shape * 4 + mino.direc - 9;
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

//right �̵��� �� ���� ��ġ ��������
void DeletePrevPosition_Right(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex = mino.shape * 4 + mino.direc - 9;
	switch (minoInfoIndex) {
	case BarHoriz:
		ground[x - 4][y] = 0; break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { ground[x-2][y + i]=0; }
		break;
	case ZLVertical:
		ground[x][y - 1] = 0; ground[x - 2][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case ZLHoriz:
	case T0:
		ground[x - 4][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case ZRVertical:
		ground[x - 2][y - 1] = 0; ground[x - 2][y] = 0; ground[x][y + 1] = 0;
		break;
	case ZRHoriz:
		ground[x - 2][y] = 0; ground[x - 4][y + 1] = 0;
		break;
	case Square:
		ground[x - 2][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case ChairL0:
	case ChairR2:
		ground[x - 4][y] = 0; ground[x - 4][y + 1] = 0;
		break;
	case ChairL1:
		ground[x - 2][y - 1] = 0; ground[x][y] = 0; ground[x][y + 1] = 0;
		break;
	case ChairL2:
		ground[x][y] = 0; ground[x - 4][y + 1] = 0;
		break;
	case ChairL3:
	case T3:
		ground[x - 2][y - 1] = 0; ground[x - 2][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case ChairR0:
		ground[x - 4][y] = 0; ground[x][y + 1] = 0;
		break;
	case ChairR1:
		ground[x][y - 1] = 0; ground[x][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case ChairR3:
		ground[x - 2][y - 1] = 0; ground[x - 2][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case T1:
		ground[x - 2][y - 1] = 0; ground[x - 4][y] = 0; ground[x - 2][y + 1] = 0;
		break;
	case T2:
		ground[x - 2][y - 1] = 0; ground[x - 4][y] = 0;
		break;
	}
}

//rotate �� �� ���� ��ġ ��������
void DeletePrevPosition_Rotate(minoInfo mino) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if (mino.shape < 3)
		minoInfoIndex = mino.shape * 2 + mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex =  mino.shape * 4 + mino.direc - 9;
	switch (minoInfoIndex) {
	case BarHoriz:
		ground[x][y - 1] = 0; ground[x][y + 1] = 0; ground[x][y + 2] = 0;
		break;
	case BarVertical:
		ground[x - 2][y] = 0; ground[x + 2][y] = 0; ground[x + 4][y] = 0;
		break;
	case ZLVertical:
		ground[x - 2][y] = 0; ground[x + 2][y + 1] = 0;
		break;
	case ZLHoriz:
		ground[x + 2][y - 1] = 0; ground[x + 2][y] = 0;
		break;
	case ZRVertical:
		ground[x - 2][y + 1] = 0; ground[x][y + 1] = 0;
		break;
	case ZRHoriz:
		ground[x][y - 1] = 0; ground[x + 2][y + 1] = 0;
		break;
	case ChairL0:
		ground[x][y - 1] = 0; ground[x][y + 1] = 0; ground[x + 2][y + 1] = 0;
		break;
	case ChairL1:
		ground[x - 2][y] = 0; ground[x][y] = 0; ground[x - 2][y + 1] = 0;	
		break;
	case ChairL2:
		ground[x][y - 1] = 0; ground[x + 2][y - 1] = 0;
		break;
	case ChairL3:
		ground[x - 2][y+1] = 0; ground[x + 2][y] = 0;
		break;
	case ChairR0:
		ground[x][y - 1] = 0; ground[x + 2][y - 1] = 0; ground[x][y + 1] = 0;
		break;
	case ChairR1:
		ground[x - 2][y] = 0; ground[x][y] = 0;
		break;
	case ChairR2:
		ground[x + 2][y - 1] = 0; ground[x + 2][y] = 0;
		break;
	case ChairR3:
		ground[x - 2][y] = 0; ground[x - 2][y + 1] = 0; ground[x + 2][y + 1] = 0;
		break;
	case T0:
		ground[x][y - 1] = 0; break;
	case T1:
		ground[x + 2][y] = 0; break;
	case T2:
		ground[x][y + 1] = 0; break;
	case T3:
		ground[x - 2][y] = 0; break;
	}
}



//���� ��ǥ�� �޾Ƽ� ȭ�鿡 ���� ���, location set �и�
void PrintMino(minoInfo mino, locationInfo* location) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = 0;
	if(mino.shape<3)
		minoInfoIndex = mino.shape*2+ mino.direc;
	else if (mino.shape == 3) minoInfoIndex = 6;
	else minoInfoIndex = mino.shape * 4 + mino.direc-9;
	switch (minoInfoIndex) {
	case BarHoriz:
		gotoxy(x - 2, y); printf("�����"); break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { gotoxy(x, y + i); printf("��"); }
		break;
	case ZLVertical:
		gotoxy(x + 2, y - 1); printf("��");
		gotoxy(x, y); printf("���");
		gotoxy(x, y + 1); printf("��");
		break;
	case ZLHoriz:
		gotoxy(x - 2, y); printf("���");
		gotoxy(x, y + 1); printf("���");
		break;
	case ZRVertical:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x, y); printf("���");
		gotoxy(x + 2, y + 1); printf("��");
		break;
	case ZRHoriz:
		gotoxy(x, y); printf("���");
		gotoxy(x - 2, y + 1); printf("���");
		break;
	case Square:
		gotoxy(x, y); printf("���");
		gotoxy(x, y + 1); printf("���");
		break;
	case ChairL0:
		gotoxy(x - 2, y); printf("����");
		gotoxy(x - 2, y + 1); printf("��");
		break;
	case ChairL1:
		gotoxy(x, y - 1); printf("���");
		gotoxy(x + 2, y); printf("��");
		gotoxy(x + 2, y + 1); printf("��");
		break;
	case ChairL2:
		gotoxy(x + 2, y); printf("��");
		gotoxy(x - 2, y + 1); printf("����");
		break;
	case ChairL3:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x, y); printf("��");
		gotoxy(x, y + 1); printf("���");
		break;
	case ChairR0:
		gotoxy(x - 2, y); printf("����");
		gotoxy(x + 2, y + 1); printf("��");
		break;
	case ChairR1:
		gotoxy(x + 2, y - 1); printf("��");
		gotoxy(x + 2, y); printf("��");
		gotoxy(x, y + 1); printf("���");
		break;
	case ChairR2:
		gotoxy(x - 2, y); printf("��");
		gotoxy(x - 2, y + 1); printf("����");
		break;
	case ChairR3:
		gotoxy(x, y - 1); printf("���");
		gotoxy(x, y); printf("��");
		gotoxy(x, y + 1); printf("��");
		break;
	case T0:
		gotoxy(x - 2, y); printf("����");
		gotoxy(x, y + 1); printf("��");
		break;
	case T1:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x - 2, y); printf("���");
		gotoxy(x, y + 1); printf("��");
		break;
	case T2:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x - 2, y); printf("����");
		break;
	case T3:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x, y); printf("���");
		gotoxy(x, y + 1); printf("��");
		break;
	}
}


//location �и� ��
/*
//���� ��ǥ�� �޾Ƽ� ȭ�鿡 ���� ���, location ���� set
void PrintMino(minoInfo mino, locationInfo* location) {
	int x = mino.x; int y = mino.y;
	int minoInfoIndex = mino.shape+ mino.direc;
	switch (minoInfoIndex) {
	case BarHoriz:
		gotoxy(x - 2, y); printf("�����"); *location = {x-2,x+4,y,y}; break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { gotoxy(x, y+i); printf("��"); }
		*location = { x,x,y+2,y-1 };
		break;
	case ZLVertical:
		gotoxy(x+2, y-1); printf("��");
		gotoxy(x, y); printf("���");
		gotoxy(x, y+1); printf("��");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ZLHoriz:
		gotoxy(x - 2, y); printf("���");
		gotoxy(x, y + 1); printf("���");
		*location = { x - 2,x + 2,y+1,y };
		break; 
	case ZRVertical:
		gotoxy(x, y-1); printf("��");
		gotoxy(x, y); printf("���");
		gotoxy(x+2, y+1); printf("��");
		*location = { x,x+2,y+1,y-1};
		break;
	case ZRHoriz:
		gotoxy(x, y); printf("���");
		gotoxy(x-2, y+1); printf("���");
		*location = {x-2,x + 2,y+1,y};
		break;
	case Square:
		gotoxy(x, y); printf("���");
		gotoxy(x, y+1); printf("���");
		*location = {x,x+2,y+1,y };
		break;
	case ChairL0:
		gotoxy(x - 2, y); printf("����");
		gotoxy(x - 2, y+1); printf("��");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairL1:
		gotoxy(x, y - 1); printf("���");
		gotoxy(x+2, y); printf("��");
		gotoxy(x+2, y + 1); printf("��");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ChairL2:
		gotoxy(x+2, y); printf("��");
		gotoxy(x-2, y+1); printf("����");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairL3:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x, y); printf("��");
		gotoxy(x, y + 1); printf("���");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ChairR0:
		gotoxy(x-2, y); printf("����");
		gotoxy(x+2, y+1); printf("��");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairR1:
		gotoxy(x+2, y - 1); printf("��");
		gotoxy(x+2, y); printf("��");
		gotoxy(x, y + 1); printf("���");
		*location = { x,x+2,y+1,y-1 };
		break;
	case ChairR2:
		gotoxy(x-2, y); printf("��");
		gotoxy(x-2, y + 1); printf("����");
		*location = { x-2,x+2,y+1,y };
		break;
	case ChairR3:
		gotoxy(x, y - 1); printf("���");
		gotoxy(x, y); printf("��");
		gotoxy(x, y + 1); printf("��");
		*location = { x,x + 2,y + 1,y-1 };
		break;
	case T0:
		gotoxy(x - 2, y); printf("����");
		gotoxy(x, y + 1); printf("��");
		*location = { x-2,x + 2,y + 1,y };
		break;
	case T1:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x - 2, y); printf("���");
		gotoxy(x, y + 1); printf("��");
		*location = { x - 2,x,y + 1,y-1 };
		break;
	case T2:
		gotoxy(x, y-1); printf("��");
		gotoxy(x - 2, y); printf("����");
		*location = { x - 2,x + 2,y,y-1 };
		break;
	case T3:
		gotoxy(x, y - 1); printf("��");
		gotoxy(x, y); printf("���");
		gotoxy(x, y + 1); printf("��");
		*location = { x,x + 2,y + 1,y-1 };
		break;
	}
}
*/