#include<stdio.h>
#include<time.h>
#include<stdlib.h>

// 10 마리의 서로 다른 동물 (각 카드 2장씩)
//사용자로부터 2개의 입력값을 받아서 - > 같은 동물 찾으면 카드  뒤집기
//모든 동물 쌍을 찾으면 게임 종료
//총 실패 횟수 알려주기

int arrayAnimal[4][5];		// 카드 지도 (전체 : 20장의 카드)
int checkAnimal[4][5];		//뒤집혔는지 여부 확인
char *strAnimal[10];

void initAnimalArray();
void initAnimalNmae();
void shuffleAnimal();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
void printAnimals();
void printQuestion();
int foundAllAnimals();

int main(void) {
	srand(time(NULL));

	initAnimalArray();
	initAnimalNmae();
	shuffleAnimal();

	int failCount = 0;		//총 실패 횟수

	while (1) {
		int select1 = 0;		//사용자가 선택한 처음 수
		int select2 = 0;		// 사용자가 선택한 두번째 수

		printAnimals();		//동물 위치 출력
		printQuestion();		//문제 출력 (카드 지도)

		printf("뒤집을 카드를 2개 고르시오 : ");
		scanf_s("%d %d", &select1, &select2);

		if (select1 == select2) {		//같은 카드 선택 시 무효처리
			continue;
		}

		//좌표에 해당하는 카드를 뒤집어 보고 같은지 안 같은지 확인
		int firstSelect_x = conv_pos_x(select1);
		int firstSelect_y = conv_pos_y(select1);

		int secondSelect_x = conv_pos_x(select2);
		int secondSelect_y = conv_pos_y(select2);

		//1. 카드가 뒤집히지 않았는지
		//2. 동시에 두 동물이 같은지
		//3. 아니면 다른 동물인 경우
		if (checkAnimal[firstSelect_x][firstSelect_y] == 0		//1. 카드가 뒤집히지 않았는지
			&&
			checkAnimal[secondSelect_x][secondSelect_y] == 0
			&&
			arrayAnimal[firstSelect_x][firstSelect_y] == arrayAnimal[secondSelect_x][secondSelect_y] //2. 동시에 두 동물이 같은지
			) {
			printf("\n\n(빙고!) \n===========>  %s발견\n\n", strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
			checkAnimal[firstSelect_x][firstSelect_y] = 1;
			checkAnimal[secondSelect_x][secondSelect_y] = 1;
		}
		//3. 아니면 다른 동물인 경우
		else {
			printf("\n\n 땡!! (틀렸거나 이미 뒤집힌 카드입니다.) \n");
			printf("%d : %s\n", select1, strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
			printf("%d : %s\n", select2, strAnimal[arrayAnimal[secondSelect_x][secondSelect_y]]);
			printf("\n\n");

			failCount++;
		}

		//모든 동물을 찾았는지 여부 1:참 ___ 0:거짓
		if (foundAllAnimals() == 1) {
			printf("\n\n 축하합니다 ! 모든 동물을 다 찾았네요 \n");
			printf("지금까지 총 %d번 실수 하였습니다. \n", failCount);
			break;
		}
	}

	return 0;
}

void initAnimalArray() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			arrayAnimal[i][j] = -1;
		}
	}
}

void initAnimalNmae() {
	strAnimal[0] = "원숭이";
	strAnimal[1] = "하마";
	strAnimal[2] = "강아지";
	strAnimal[3] = "고양이";
	strAnimal[4] = "돼지";

	strAnimal[5] = "코끼리";
	strAnimal[6] = "기린";
	strAnimal[7] = "낙타";
	strAnimal[8] = "타조";
	strAnimal[9] = "호랑이";
}

void shuffleAnimal() {
	//□□□□□
	//□□□□□
	//□□□□□
	//□□□□□

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			int pos = getEmptyPosition();		//받아온 빈공간의 좌표를
			int x = conv_pos_x(pos);			//좌표를 컨버트(변환) -> X
			int y = conv_pos_y(pos);			//좌표를 컨버트(변환) -> Y

			arrayAnimal[x][y] = i;
		}
	}
}

int getEmptyPosition() {
	//□□□□□   0  1  2  3  4
	//□□□□□   5  6  7  8  9
	//□□□□□  10 11 12 13 14
	//□□□□□  15 16 17 18 19
	while (1) {
		int randPos = rand() % 20;		//0~19사이의 숫자 반환
		//19 -> 좌표상 (3,4)
		// 5 -> 좌표상 (1,0)
		int x = conv_pos_x(randPos);
		int y = conv_pos_y(randPos);

		if (arrayAnimal[x][y] == -1) {		//-1이면 빈공간이다
			return randPos;					//빈공간이면 지금의 좌표를 반영
		}
	}
	return 0;
}

int conv_pos_x(int x) {		//(10,2)를 (4,5)의 좌표로 바꿀_________x 좌표
	// 19 - > (3,4)
	return x / 5;			//몫 값이면 됌 19를 5로 나누면 몫 3 (3,4)
}

int conv_pos_y(int y) {		//(10,2)를 (4,5)의 좌표로 바꿀_________y좌표
	return y % 5;		//나머지 값이면 됌 19를 5로 나누면 나머지 4 (3,4)
}

void printAnimals() {		//동물 위치 출력
	//□□□□□   1  1  2  2  3
	//□□□□□   3  4  4  5  5
	//□□□□□  
	//□□□□□  
	//위에처럼 공통된 동물이 들어가면
	printf("\n============이건 힌트입니다 참고하셈~============\n\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%8s", strAnimal[arrayAnimal[i][j]]);
		}
		printf("\n");
	}
	printf("\n=================================================\n\n");
}

void printQuestion() {		//문제 출력 (카드 지도)
	printf("\n\n(문제)\n");
	int seq = 0;		//카드에 임의로 번호를 붙이는 역할

	//□□□□□   1  1  2  2  3
	//□□□□□   3  4  4  5  5
	//□□□□□  
	//□□□□□  

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			//카드를 뒤집어서 정답을 맞추면 '동물이름'
			if (checkAnimal[i][j] != 0) {
				printf("%8s", strAnimal[arrayAnimal[i][j]]);
			}
			//아직 뒤집지 못했으면 (정답을 못 맞추면) 뒷면 -> 위치를 나타내는 숫자
			else {	
				printf("%8d", seq);
			}
			seq++;
		}
		printf("\n");
	}
}

int foundAllAnimals() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (checkAnimal[i][j] == 0) {		//아직 안 뒤집힌 카드가 있으면
				return 0;
			}
		}
	}
	return 1;		//for문을 다 돌았는데도 checkAnimal[i][j] 값에 없으면 모든 동물을 찾았다는 것을 의미
}