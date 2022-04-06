// Week4_Homework.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Ranking.h"
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define DIM 4

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };
static int Dirkey[4] = { Left, Right, Up, Down };
static int map[DIM][DIM];
static int x, y;
static int nMove;
static clock_t tStart;

static void init() {
	for (int i = 0; i < DIM * DIM - 1; i++)
		map[i / DIM][1 % DIM] = i + 1;
	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1; y = DIM - 1;

	srand(time(NULL));
	tStart = clock();
	nMove = 0;

}

static void display() {
	system("cls");
	printf("\tFifteen Puzzle\n\t");
	printf("--------------\n\t");
	for (int r = 0; r < DIM; r++) {
		for (int c = 0; c < DIM; c++) {
			if (map[r][c] > 0)
				printf("%3d", map[r][c]);
			else printf(" ");
		}
		printf("\n\t");
	}
	printf("--------------\n\t");
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	printf("\n\t이동횟수::%6d\n\t소요시간:%6.1f\n\n", nMove, d);
}
static bool move(int dir) {
	if (dir == Right && x > 0) {
		map[y][x] = map[y][x - 1];
		map[y][--x] = 0;
	}
	else if (dir == Left && x < DIM - 1) {
		map[y][x] = map[y][x + 1];
		map[y][++x] = 0;
	}
	else if (dir == Up && y < DIM - 1) {
		map[y][x] = map[y + 1][x];
		map[++y][x] = 0;
	}
	else if (dir == Down && y > 0) {
		map[y][x] = map[y - 1][x];
		map[--y][x] = 0;
	}
	else return false;

	nMove++;
	return true;

}

static void shuffle(int nShuffle) {
	for (int i = 0; i < nShuffle; i++) {
		int key = Dirkey[rand() % 4];
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
	}
}
 
static bool isDone() {
	for (int r = 0; r < DIM; r++) {
		for (int c = 0; c < DIM; c++) {
			if (map[r][c] != r * DIM + c + 1)
				return (r == DIM - 1) && (c == DIM - 1);
		}
	}
	return true;
}

static int getDirkey() { return _getche() == 224 ? _getche() : 0; }
int playFifrteenPuzzle() {
	init();
	display();
	printRanking();
	printf("\n 퍼즐을 섞어주세요(엔터)...");
	_getche();
	shuffle(100);
	printf("\n 게임이 시작됩니다...");
	_getche();

	nMove = 0;
	tStart = clock();
	while (!isDone()) {
		move(getDirkey());
		display();
	}
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	return addRanking(nMove, d);
	
}









// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
