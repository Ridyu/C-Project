#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS


#include<stdio.h>
#include<stdlib.h>		//문자열 변환 함수, 난수생성 함수, 동적 할당 관련 함수, 실행환경 변수,

void init_board(char[][3]);
void display_board(char board[3][3]);

int main(void) {

	char board[3][3];
	int quit = 0;

	//init_  프로그램 내에서 실행되는 최초의 메서드 초기화 후에 시작함으 의미
	init_board(board);		//보드 함수 초기화

	while (1) {
		display_board(board);
		quit = get_player_move(0, board);

		if (quit == 1) {
			break;
		}
		display_board(board);
		quit = quit = get_player_move(1, board);

		if (quit == 1) {
			break;
		}
	}


	return 0;
}


void init_board(char board[][3]) {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			board[x][y] = ' ';		//2차원 배열을 ''로 초기화
		}
	}
}

void display_board(char board[3][3]) {
	for (int i = 0; i < 3; i++) {
		printf("---|---|---\n");
		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
		
	}
	printf("---|---|---\n");
}

int get_player_move(int player, char board[3][3]) {
	int x, y, done=0;

	while (done != 1) {
		printf("(x,y) 좌표 (종료 : -1,-1) : ");
		scanf("%d %d", &x, &y);
		if (x == -1 && y == -1) {
			return 1;			//종료조건
		}
		if (board[x][y] == ' ') {
			break;		//올바른 위치이면 반복문을 이어나감
		}
		else {
			printf("잘못된 위치입니다.\n");
		}
	}

	if (player == 0) {
		board[x][y] = 'X';
	}
	else {
		board[x][y] = 'O';
	}

	return 0;
}
