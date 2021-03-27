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

//int ground[44][27] = { 0 };
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
	PrintMino(next, location);
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
void PrintCurrentMino() {
	for (int j = g_yMin; j <= g_yMax; j++)
	{
		for (int i = g_xMin; i <= g_xMax; i += 2)
		{
			if (ground[i][j] == 1)
			{
				gotoxy(i, j);
				printf("□");
			}
			else {
				gotoxy(i, j);
				printf("  ");
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
void CheckKeyAndAction(minoInfo* mino, locationInfo* location, int* speedUp) {
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
			if (location->left_x >= 24)	{//지우기, location 정보 새로고침
				mino->x -= 2;
				//틀 이탈 or 내려놓은 도형과의 충돌 상황이라면 안내려!
				int CheckColoringMino = UpdateNewPosition(*mino);
				if(UpdateLocation(*mino, location) < 0 || CheckColoringMino < 0) mino->x += 2;
//				else DeletePrevPosition_Left(*mino);
			}
			break;
		case k_right:
			if (location->right_x <= 42){ 
				mino->x += 2;
				if (UpdateLocation(*mino, location) < 0) mino->x -= 2;
			}
			break;
		case k_down:
			*speedUp = 5; break;
		case k_rotate:
			int rotateTempDirec = mino->direc;
			if (mino->shape < 3) mino->direc == 0 ? 1 : 0;
			else if (mino->shape == 3) mino->direc = 0;
			else { mino->direc = (mino->direc) + 1; if (mino->direc == 4) mino->direc = 0; }
			//틀 이탈 or 내려놓은 도형과의 충돌 상황이라면 안내려!
			int CheckColoringMino = UpdateNewPosition(*mino);
			if (UpdateLocation(*mino, location) < 0 || CheckColoringMino < 0) mino->direc = rotateTempDirec;
			
		}
		PrintCurrentMino();
		system("cls");
		//PrintMino(*mino, location);
	}
}

//speed 에 맞춰서 일정 시간 단위로 mino 떨구기, down키에 따른 동작조건 필요
void AutoDownMino(minoInfo* mino,locationInfo location, int* fixMino) {
	int CheckColoringMino = 0;
	if ((location.bottom_y < 26)) {//지우기, location 정보 새로고침
		mino->y += 1;
		//틀 이탈 or 내려놓은 도형과의 충돌 상황이라면 안내려!
		CheckColoringMino = UpdateNewPosition(*mino);
		if (UpdateLocation(*mino, &location) < 0 || CheckColoringMino < 0) {
			mino->y -= 1;
			*fixMino = 1;
		}
		//외의 경우 mino 하강 가능하므로 Array에서 이전 위치 지우기
		else {
			DeletePrevPosition_Down(*mino);
			PrintCurrentMino();
			//PrintMino(*mino, &location);
		}
	}
}

//커서 숨기기 함수. 블로그에서 퍼왔어욘 >> https://seokjin2.tistory.com/50
void CursorView(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int main()
{
	//게임창 세팅
	system("mode con cols=100 lines=40 | title TETRIS"); // cols:가로 lines:세로
	PrintGameStart();
	CursorView(false); // 커서 숨기기

	//초기화
	minoInfo current = { 0,0,center_x, center_y};
	minoInfo next = { 0,0,next_x,next_y };
	gradeInfo grade = { 0,0 };
	locationInfo location = { 0,0,0,0 };
	int currentCenterX = 42;
	int currentCenterY = 7;

	int fixMino = 0;

	//게임 화면 세팅
	srand(time(NULL));
	SetMinoInfo(&next);
	SetGameGround(next,grade, &location);
	SetMinoInfo(&current);
	PrintMino(current, &location);
	UpdateLocation(current, &location);
	//gotoxy(30, 17);
	//printf("minx= %d maxx= %d miny= %d maxy= %d", location.left_x, location.right_x, location.bottom_y, location.top_y);
	
	int speedUp = 0;
	while (1) {
		CheckKeyAndAction(&current, &location, &speedUp);
		SetGameGround(next, grade, &location);
		AutoDownMino(&current, location, &fixMino);
		Sleep(500);
		//PrintMino(current, &location);
	}
	getchar();	
}
