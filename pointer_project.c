#include<stdio.h>
#include<time.h>		//clock()�Լ� ���

/*
1. ����Ⱑ 6���� �ִ�
2. �̵��� ���׿� ������ �縷�Դϴ�.
3. �縷�� �ʹ� ������, �ʹ� �����ؼ� ���� ���� ���� �����մϴ�.
4. ���� �� �����ϱ� ���� �������� ���׿� ���� �༭ ����⸦ ����ּ���.
5. ������ �ð��� ���� ���� ���� Ŀ����.... ���߿���.... �Ծ�� �Ѵ�.
*/
int level;
int arrayFish[6];
int* cursor;

void printfFishes();
void iniData();
void decreaseWater();
int checkFishAlive();

int main_ppointer(void) {
	long startTime = 0;		//���� ���� �ð�
	long totalElapsedTime = 0;	//�� ��� �ð�
	long prevElapsedTime = 0;	//���� ��� �ð� (�ֱٿ� ���� �� �ð� ����)

	int num;		//�� �� ���׿� ���� �� ������, ����� �Է�
	iniData();

	cursor = arrayFish;	//cursor[0]..... cursor[1] ��� �����͸� �迭ó�� ���

	startTime = clock();		//���� �ð��� millisecond(1000���� 1��) ������ ��ȯ
	while (1) {
		printfFishes();
		printf("�� �� ���׿� ���� �ֽðھ��? ");
		scanf_s("%d", &num);

		//�Է°� üũ
		if (num < 1 || num>6) {
			printf("\n�Է� ���� �߸� �Ǿ����ϴ�.\n");
				continue;
		}

		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		printf("�� ��� �ð� : %ld ��\n", totalElapsedTime);

		//���� �� �� �ð�(���������� �� �� �ð�) ���ķ� �帥 �ð�
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("�ֱ� ��� �ð�  : %ld ��\n", prevElapsedTime);


		//������ ���� ���� [����]
		decreaseWater(prevElapsedTime);

		// ����ڰ� �Է��� ���׿� ���� �ش�
		// 1. ������ ���� 0�̸�? ���� ���� �ʴ´�. �̹� ��Ⱑ �� �׾...
		if (cursor[num - 1] <= 0) {			//���� �迭�� 0~5������ -1�� ���ش�.
			printf("%d�� ������ �̹� �׾����ϴ�... ���� ���� �ʽ��ϴ�\n", num);
		}

		// 2. ������ ���� 0�� �ƴ� ���? ���� �ش� !  100�� ���� �ʴ��� üũ
		// 100�� �Ѿ�� ���� ��ġ�� ������
		else if (cursor[num - 1] + 1 <= 100) {
			//���� �ش�.
			printf("%d�� ���׿� ���� �ݴϴ�.\n\n", num);
			cursor[num - 1] += 1;
		}

		// �������� �Ұ��� Ȯ�� (�������� 20�ʸ��� �� ���� ����)
		if (totalElapsedTime / 20 > level - 1) {
			level++;		// level : 1 -> level : 2 -> level : 3
			printf(" *** �� ������ ! ���� %d �������� %d ������ ���׷��̵� ***\n\n", level - 1, level);

			//���� ������ ; 5
			if (level == 5) {
				printf("\n\n �����մϴ�. �ְ� ������ �޼��ϼ̽��ϴ�. ������ �����մϴ�.\n\n");
				exit(0);	//��� ���α׷� ����
			}
		}


		//��� ����Ⱑ �׾����� Ȯ��
		if (checkFishAlive() == 0) {
			//����Ⱑ ��� �׾���.
			printf("��� ����Ⱑ... �׾����ϴ�...\n\n");
			exit(0);
		}
		else {
			//�ּ� �� ���� �̻��� ����Ⱑ ��� ����
			printf("����Ⱑ ���� ��� �־��!\n\n");
		}
		prevElapsedTime = totalElapsedTime;

		// 10�� -> 15�� (5�� : prevElapsedTime)
		// 15-> 25�� (10��....?)
	}

	return 0;
}

void iniData() {
	level = 1;	//���� ���� (1~5)
	for (int i = 0; i < 6; i++) {
		arrayFish[i] = 100;		//������ �� ����(0~100)
	}

}

void printfFishes() {
	printf("%3d�� %3d�� %3d�� %3d�� %3d�� %3d�� \n", 1, 2, 3, 4, 5, 6);			// %3d�� 3ĭ�� �Ҵ� �ް� 
	for (int i = 0; i < 6; i++) {
		printf(" %4d ", arrayFish[i]);			//%4d�� 4ĭ�� �Ҵ� �ް�
	}
	printf("\n\n");
}


void decreaseWater(long elapsedTime) {
	for (int i = 0; i < 6; i++) {
		arrayFish[i] -= (level * 3 * (int)elapsedTime);		//3 : ���̵� ������ ���� ��
		if (arrayFish[i] < 0) {
			arrayFish[i] = 0;
		}
	}
}

int checkFishAlive() {
	for (int i = 0; i < 6; i++) {
		if (arrayFish[i] > 0) {
			return 1;			//�� True�� �ǹ�
		}
		return 0;
	}
}