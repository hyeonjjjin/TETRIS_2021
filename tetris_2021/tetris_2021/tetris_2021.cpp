﻿#include "pch.h"
#include <iostream>
#include <iostream>
#include <time.h>//time 함수
#include <Windows.h>// Sleep 함수
#include <conio.h>//getch() 함수

#define g_xMin 24
#define g_xMax 42
#define g_yMin 7
#define g_yMax 26


//원하는 좌표로 커서 옮기기 
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//shape, direc //level, score 구조체
struct tempInfo { int shape; int direc; }; typedef tempInfo;
struct gradeInfo { int level; int score; }; typedef gradeInfo;

int ground[44][27] = { 0 };

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
	gotoxy(44, 26);	printf("> ENTER");
	getchar(); system("cls");//뭐든 입력하면 화면 지움
}

//이미 내려놓은 도형 ■로 출력
void ColorSquare() {
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

//게임 틀 출력 (+ next temp, level, score)
void SetGameGround(tempInfo next, gradeInfo grade) {
	
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
	//gotoxy(32, 8);
	//print_next(shape_next, direc_next, 36, 8);
	gotoxy(52, 8);
	printf("NEXT");
	
	
}

void setTempInfo(tempInfo *temp) {
	srand(time(NULL));
	temp->shape = rand() % 7;
	temp->direc = rand() % 4;
}

int main()
{
	system("mode con cols=100 lines=40 | title TETRIS"); // cols:가로 lines:세로
	PrintGameStart();

	tempInfo current = { 0,0 };
	tempInfo next = { 0,0 };
	gradeInfo grade = { 0,0 };
	setTempInfo(&next);
	SetGameGround(next,grade);
	

	getchar();
}
