#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main_arry_rand(void) {

	srand(time(NULL));
	printf("아빠는 대머리 게임\n");
	int treatment = rand() % 4;		//발모제 선택 (0_3)

	int cntShowBottle = 0;		//게임에 보여줄 병의 갯수
	int prevCntShowBottle = 0;		//앞 게임에 보여준 병 갯수
	//서로 보여주는 병 갯수를 다르게 하여 정답률 향상(처음 2개, 다음 3개....)

	//3번의 기회(3번의 발모제 투여 시도)
	for (int i = 1; i <= 3; i++) {
		int bottle[4] = { 0,0,0,0 };	//4개의 병

		do {
			cntShowBottle = rand() % 2 + 2;	//보여줄 병 갯수(0~1 까지의 범위),(+2가 되서 2,3의 숫자가 나옴)
		} while (cntShowBottle == prevCntShowBottle);
		prevCntShowBottle = cntShowBottle;


		int islncuded = 0; //보여주 ㄹ병 중에 발모제가 포함되었는지 여부
		printf(" ---------->%d 번째 시도 : ", i);

		//보여줄 병 종류를 선택
		for (int j = 0; j < cntShowBottle; j++) {
			int randBottle = rand() % 4;

			//아직 선택되지 않은 병이면, 선택처리
			if (bottle[randBottle] == 0) {
				bottle[randBottle] = 1;
				if (randBottle == treatment) {
					islncuded = 1;
				}
			}
			//이미 선택된 병이면, 중복이므로 다시 선택
			else {
				j--;
			}
		}

		//사용자에게 문제 표시
		for (int k = 0; k < 4; k++) {
			if (bottle[k] == 1)
				printf("%d ", k + 1);
		}
		printf("물약을 머리에 바릅니다.\n\n");

		if (islncuded == 1) {
			printf("성공\n");
		}
		else {
			printf("실패\n");
		}

		printf("\n\n\n....계속 하려면 아무키나 누르세요...\n\n");
		getchar();
	}

	int answer;		//사용자 입력값

	printf("\n\n발모제는 몇 번일까요? \n");
	scanf_s("%d", &answer);

	if (answer == treatment + 1) {
		printf("정답입니다.\n");
	}
	else {
		printf("틀렸습니다.\n 정답은 %d입니다.", treatment + 1);
	}

	return 0;
}