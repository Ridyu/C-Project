#include<stdio.h>
#include<time.h>		//clock()함수 사용

/*
1. 물고기가 6마리 있다
2. 이들은 어항에 살지만 사막입니다.
3. 사막이 너무 더워서, 너무 건조해서 물이 아주 빨리 증가합니다.
4. 물이 다 증발하기 전에 부지런히 어항에 물을 줘서 물고기를 살려주세요.
5. 물고기는 시간이 지날 수록 점점 커져서.... 나중에는.... 먹어야 한다.
*/
int level;
int arrayFish[6];
int* cursor;

void printfFishes();
void iniData();
void decreaseWater();
int checkFishAlive();

int main_ppointer(void) {
	long startTime = 0;		//게임 시작 시간
	long totalElapsedTime = 0;	//총 경과 시간
	long prevElapsedTime = 0;	//직전 경과 시간 (최근에 물을 준 시간 간격)

	int num;		//몇 번 어항에 물을 줄 것인지, 사용자 입력
	iniData();

	cursor = arrayFish;	//cursor[0]..... cursor[1] 등등 포인터를 배열처럼 사용

	startTime = clock();		//현재 시간을 millisecond(1000분의 1초) 단위로 변환
	while (1) {
		printfFishes();
		printf("몇 번 어항에 물을 주시겠어요? ");
		scanf_s("%d", &num);

		//입력값 체크
		if (num < 1 || num>6) {
			printf("\n입력 값이 잘못 되었습니다.\n");
				continue;
		}

		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		printf("총 경과 시간 : %ld 초\n", totalElapsedTime);

		//직전 물 준 시간(마지막으로 물 준 시간) 이후로 흐른 시간
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("최근 경과 시간  : %ld 초\n", prevElapsedTime);


		//어항의 물을 감소 [증발]
		decreaseWater(prevElapsedTime);

		// 사용자가 입력한 어항에 물을 준다
		// 1. 어항의 물이 0이면? 물을 주지 않는다. 이미 고기가 다 죽어서...
		if (cursor[num - 1] <= 0) {			//실제 배열은 0~5까지니 -1을 해준다.
			printf("%d번 물고기는 이미 죽었습니다... 물을 주지 않습니다\n", num);
		}

		// 2. 어항의 물이 0이 아닐 경우? 물을 준다 !  100을 넘지 않는지 체크
		// 100이 넘어가면 물이 넘치기 때문에
		else if (cursor[num - 1] + 1 <= 100) {
			//물을 준다.
			printf("%d번 어항에 물을 줍니다.\n\n", num);
			cursor[num - 1] += 1;
		}

		// 레벨업을 할건지 확인 (레벨업은 20초마다 한 번씩 수행)
		if (totalElapsedTime / 20 > level - 1) {
			level++;		// level : 1 -> level : 2 -> level : 3
			printf(" *** 축 레벨업 ! 기존 %d 레벨에서 %d 레벨로 업그레이드 ***\n\n", level - 1, level);

			//최종 레벨은 ; 5
			if (level == 5) {
				printf("\n\n 축하합니다. 최고 레벨을 달성하셨습니다. 게임을 종료합니다.\n\n");
				exit(0);	//모든 프로그램 종료
			}
		}


		//모든 물고기가 죽었는지 확인
		if (checkFishAlive() == 0) {
			//물고기가 모두 죽었다.
			printf("모든 물고기가... 죽었습니다...\n\n");
			exit(0);
		}
		else {
			//최소 한 마리 이상의 물고기가 살아 있음
			printf("물고기가 아직 살아 있어요!\n\n");
		}
		prevElapsedTime = totalElapsedTime;

		// 10초 -> 15초 (5초 : prevElapsedTime)
		// 15-> 25초 (10초....?)
	}

	return 0;
}

void iniData() {
	level = 1;	//게임 레벨 (1~5)
	for (int i = 0; i < 6; i++) {
		arrayFish[i] = 100;		//어항의 물 높이(0~100)
	}

}

void printfFishes() {
	printf("%3d번 %3d번 %3d번 %3d번 %3d번 %3d번 \n", 1, 2, 3, 4, 5, 6);			// %3d는 3칸을 할당 받고 
	for (int i = 0; i < 6; i++) {
		printf(" %4d ", arrayFish[i]);			//%4d는 4칸을 할당 받고
	}
	printf("\n\n");
}


void decreaseWater(long elapsedTime) {
	for (int i = 0; i < 6; i++) {
		arrayFish[i] -= (level * 3 * (int)elapsedTime);		//3 : 난이도 조절을 위한 길
		if (arrayFish[i] < 0) {
			arrayFish[i] = 0;
		}
	}
}

int checkFishAlive() {
	for (int i = 0; i < 6; i++) {
		if (arrayFish[i] > 0) {
			return 1;			//참 True를 의미
		}
		return 0;
	}
}