#include "pch.h"
#include "PrintTemp.h"
#include <iostream>
#include <time.h>//time 함수
#include <Windows.h>// Sleep 함수
#include <conio.h>//getch() 함수

#define g_xMin 24
#define g_xMax 42
#define g_yMin 7
#define g_yMax 26

#define center_x 32
#define center_y 7

#define next_x 52
#define next_y 11

int ground[44][27] = { 0 };
enum Key { k_left=75, k_right=77, k_rotate=72, k_down=80 };

//초기화면, tetris 출력
void PrintGameStart() {
	//T
	gotoxy(23, 10);	printf("□□□□");
	gotoxy(26, 11);	printf("□");
	gotoxy(26, 12);	printf("□");
	gotoxy(26, 13);	printf("□");
	gotoxy(26, 14);	printf("□");
	//E
	gotoxy(32, 10);	printf("□□□");
	gotoxy(32, 11);	printf("□");
	gotoxy(32, 12);	printf("□□□");
	gotoxy(32, 13);	printf("□");
	gotoxy(32, 14);	printf("□□□");
	//T
	gotoxy(39, 10);	printf("□□□□");
	gotoxy(42, 11);	printf("□");
	gotoxy(42, 12);	printf("□");
	gotoxy(42, 13);	printf("□");
	gotoxy(42, 14);	printf("□");
	//R
	gotoxy(48, 10);	printf("□□□");
	gotoxy(48, 11);	printf("□   □");
	gotoxy(48, 12);	printf("□□□");
	gotoxy(48, 13);	printf("□   □");
	gotoxy(48, 14);	printf("□   □");
	//I
	gotoxy(57, 10);	printf("□□□");
	gotoxy(59, 11);	printf("□");
	gotoxy(59, 12);	printf("□");
	gotoxy(59, 13);	printf("□");
	gotoxy(57, 14);	printf("□□□");
	//S
	gotoxy(65, 10);	printf("□□□");
	gotoxy(64, 11);	printf("□");
	gotoxy(65, 12);	printf("□□□");
	gotoxy(70, 13);	printf("□");
	gotoxy(65, 14);	printf("□□□");
	
	gotoxy(42, 24);	printf("- GAME START");
	gotoxy(70, 30);	printf("ver. 2021");
	gotoxy(44, 26);	printf("> ENTER");

	getchar(); system("cls");//뭐든 입력하면 화면 지움
}

//게임 틀 출력 (+ next temp, level, score)
void SetGameGround(minoInfo next, gradeInfo grade, locationInfo* location) {
	
	char print_1[45] = "□□□□□□□□□□□□□□□□□□□□□□";
	char print_2[26] = "□□\t\t\t\b\b\b\b□□\t\t\b\b\b\b□□";
	char print_3[32] = "□□□□□□\n\t\t\t\t\t\t□□□□□□";

	gotoxy(20, 5); printf(print_1);
	gotoxy(20, 6); printf(print_1);
	
	for (int i = 0; i < 20; i++) { gotoxy(20, 7+i); printf(print_2); }
	gotoxy(48, 15); printf(print_3);
	gotoxy(48, 20); printf(print_3);
	gotoxy(20, 27); printf(print_1);
	gotoxy(20, 28); printf(print_1);
	
	gotoxy(51, 18); printf("LEVEL %d",grade.level);
	gotoxy(51, 23);	printf("SCORE");
	if (grade.score == 0)	gotoxy(53, 25);
	else if (grade.score > 1000) gotoxy(51, 25);
	else gotoxy(52, 25);
	printf("%d", grade.score);

	//다음도형 출력
	gotoxy(52, 8);
	printf("NEXT");
	//next 예쁜 위치에 출력하기 위한 if문
	if ((next.shape + next.direc) % 2 == 1)	next.x = 53;
	else next.x = 52;
	PrintTemp(next, location);
}

//이미 내려놓은 도형 ■로 출력
void ColoringTemp() {
	for (int j = g_yMin; j <= g_yMax; j++)
	{
		for (int i = g_xMin; i <= g_xMax; i += 2)
		{
			if (ground[i][j] == 2)
			{
				gotoxy(i, j);
				printf("■");
			}
		}
	}
}

//내려가는 도형 □로 출력
void PrintDropTemp() {
	for (int j = g_yMin; j <= g_yMax; j++)
	{
		for (int i = g_xMin; i <= g_xMax; i += 2)
		{
			if (ground[i][j] == 1)
			{
				gotoxy(i, j);
				printf("□");
			}
		}
	}
}

//떨굴 도형 모양, 방향 설정
void SetMinoInfo(minoInfo *mino) {
	mino->shape = rand() % 7;
	if (mino->shape < 3) mino->direc = rand() % 2;
	else if (mino->shape == 3) mino->direc = 0;
	else mino->direc = rand() % 4;
}

//방향키 입력에 따라 동작
void CheckKey(locationInfo* location, int* speedUp) {
	int input = 0;
	//방향 키 입력 받아오기
	if (_kbhit())
	{
		input = _getch();
		if (input == 224)
		{
			do {
				input = _getch();
			} while (input == 224);
		}

		switch (input)
		{
		case k_left:
			if (location->left_x >= 24)
			{
				//지우기, location 정보 새로고침
				location->left_x -= 2;
				location->right_x -= 2;

				/*
				uaaaa = shift_l(shape, *direc, *x, y, max_x, background);//지우는거 새로 만들어야할듯
				if (uaaaa > 0) {
					*x -= spacee;
					system("cls");
				}
				*/
			}
			break;
		case k_right:
			if (location->right_x <= 42)//얘도
			{
				//지우기, location 정보 새로고침
				location->left_x += 2;
				location->right_x += 2;
				/*
				uaaaa = shift_r(shape, *direc, *x, y, max_x, background);
				if (uaaaa > 0) {
					*x += spacee;
					system("cls");
				}*/
			}
			break;
		case k_down:
			*speedUp = 5;
			break;
		case k_rotate:
			//	system("cls");
			system("cls");
			/*
			switch (shape)
			{
			case 0:
				delete_bar(shape, *direc, *x, y, background, 0);

				break;
			case 1:
				delete_a1(shape, *direc, *x, y, background, 0);

				break;
			case 2:
				delete_a2(shape, *direc, *x, y, background, 0);

				break;
			case 3:
				delete_square(shape, *direc, *x, y, background, 0);

				break;
			case 4:
				delete_b1(*direc, *x, y, background, 0);

				break;
			case 5:
				delete_b2(*direc, *x, y, background, 0);

				break;
			case 6:
				delete_o(*direc, *x, y, background, 0);
				break;
			}
			if (*direc == 3)
				*direc = 0;
			else
				(*direc)++;//돌리면 멈춘다,,, 지우기 해야함
			break;//돌았ㅇ을때 겹치는게 없으면 돌고 아님 못돌고
			*/
		}
	}
}

/*
void check_input(tempInfo temp,locationInfo location,int shape, int* direc, int* x, int y, int* max_x, int background[28][24], int* input_down, int flag_1, int flag_2)
{
	int input = 0;
	int uaaaa = 0;
	if (_kbhit())
	{
		input = _getch();
		if (input == 224)
		{
			do {
				input = _getch();
			} while (input == 224);
		}
		switch (input)
		{
		case k_left:
			//system("cls");
			if (location.left_x >= 24)
			{
				uaaaa = shift_l(shape, *direc, *x, y, max_x, background);//지우는거 새로 만들어야할듯
				if (uaaaa > 0) {
					*x -= spacee;
					system("cls");
				}
			}
			break;
		case k_right:
			//	system("cls");
			if (location.right_x <= 42)//얘도
			{
				uaaaa = shift_r(shape, *direc, *x, y, max_x, background);
				if (uaaaa > 0) {
					*x += spacee;
					system("cls");
				}
			}
			break;
		case k_down:
			*input_down = 5;
			break;
		case k_rotate:
			//	system("cls");
			system("cls");
			switch (shape)
			{
			case 0:
				delete_bar(shape, *direc, *x, y, background, 0);

				break;
			case 1:
				delete_a1(shape, *direc, *x, y, background, 0);

				break;
			case 2:
				delete_a2(shape, *direc, *x, y, background, 0);

				break;
			case 3:
				delete_square(shape, *direc, *x, y, background, 0);

				break;
			case 4:
				delete_b1(*direc, *x, y, background, 0);

				break;
			case 5:
				delete_b2(*direc, *x, y, background, 0);

				break;
			case 6:
				delete_o(*direc, *x, y, background, 0);
				break;
			}
			if (*direc == 3)
				*direc = 0;
			else
				(*direc)++;//돌리면 멈춘다,,, 지우기 해야함
			break;//돌았ㅇ을때 겹치는게 없으면 돌고 아님 못돌고
		}

	}
}*/
/*
void SetCurrentLocation(int tempInfoIndex,locationInfo* location) {
	switch (tempInfoIndex) {
		//min_x = x-2
	case BarHoriz:
	case ZLHoriz:
	case ZRHoriz:
	case ChairL0:
	case ChairL2:
	case ChairR0:
	case ChairR2:

	//case BarHoriz:
		//gotoxy(x - 2, y); printf("□□□□"); break;
	case BarVertical:
		for (int i = -1; i < 3; i++) { gotoxy(x, y + i); printf("□"); }break;

	case ZLVertical:
		gotoxy(x + 2, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□");
		break;
	//case ZLHoriz:
		//gotoxy(x - 2, y); printf("□□");
		//gotoxy(x, y + 1); printf("□□");
		//break;
	case ZRVertical:
		gotoxy(x, y - 1); printf("□");
		gotoxy(x, y); printf("□□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	//case ZRHoriz:
		//gotoxy(x, y); printf("□□");
		//gotoxy(x - 2, y + 1); printf("□□");
		//break;
	case Square:
		gotoxy(x, y); printf("□□");
		gotoxy(x, y + 1); printf("□□");
		break;
	//case ChairL0:
		//gotoxy(x - 2, y); printf("□□□");
		//gotoxy(x - 2, y + 1); printf("□");
		//break;
	case ChairL1:
		gotoxy(x, y - 1); printf("□□");
		gotoxy(x + 2, y); printf("□");
		gotoxy(x + 2, y + 1); printf("□");
		break;
	//case ChairL2:
	//	gotoxy(x + 2, y); printf("□");
	//	gotoxy(x - 2, y + 1); printf("□□□");
	//	break;
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
*/

int main()
{
	//게임창 세팅
	system("mode con cols=100 lines=40 | title TETRIS"); // cols:가로 lines:세로
	PrintGameStart();

	//초기화
	minoInfo current = { 0,0,center_x, center_y};
	minoInfo next = { 0,0,next_x,next_y };
	gradeInfo grade = { 0,0 };
	locationInfo location = { 0,0,0,0 };
	int currentCenterX = 42;
	int currentCenterY = 7;

	//게임 화면 세팅
	//srand(time(NULL));
	SetMinoInfo(&next);
	SetGameGround(next,grade, &location);
	SetMinoInfo(&current);
	PrintTemp(current, &location);

	gotoxy(30, 17);
	printf("minx= %d maxx= %d miny= %d maxy= %d", location.left_x, location.right_x, location.bottom_y, location.top_y);
	//while (1) {


	//}
	getchar();
	
}
