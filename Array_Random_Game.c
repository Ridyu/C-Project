#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main_arry_rand(void) {

	srand(time(NULL));
	printf("�ƺ��� ��Ӹ� ����\n");
	int treatment = rand() % 4;		//�߸��� ���� (0_3)

	int cntShowBottle = 0;		//���ӿ� ������ ���� ����
	int prevCntShowBottle = 0;		//�� ���ӿ� ������ �� ����
	//���� �����ִ� �� ������ �ٸ��� �Ͽ� ����� ���(ó�� 2��, ���� 3��....)

	//3���� ��ȸ(3���� �߸��� ���� �õ�)
	for (int i = 1; i <= 3; i++) {
		int bottle[4] = { 0,0,0,0 };	//4���� ��

		do {
			cntShowBottle = rand() % 2 + 2;	//������ �� ����(0~1 ������ ����),(+2�� �Ǽ� 2,3�� ���ڰ� ����)
		} while (cntShowBottle == prevCntShowBottle);
		prevCntShowBottle = cntShowBottle;


		int islncuded = 0; //������ ���� �߿� �߸����� ���ԵǾ����� ����
		printf(" ---------->%d ��° �õ� : ", i);

		//������ �� ������ ����
		for (int j = 0; j < cntShowBottle; j++) {
			int randBottle = rand() % 4;

			//���� ���õ��� ���� ���̸�, ����ó��
			if (bottle[randBottle] == 0) {
				bottle[randBottle] = 1;
				if (randBottle == treatment) {
					islncuded = 1;
				}
			}
			//�̹� ���õ� ���̸�, �ߺ��̹Ƿ� �ٽ� ����
			else {
				j--;
			}
		}

		//����ڿ��� ���� ǥ��
		for (int k = 0; k < 4; k++) {
			if (bottle[k] == 1)
				printf("%d ", k + 1);
		}
		printf("������ �Ӹ��� �ٸ��ϴ�.\n\n");

		if (islncuded == 1) {
			printf("����\n");
		}
		else {
			printf("����\n");
		}

		printf("\n\n\n....��� �Ϸ��� �ƹ�Ű�� ��������...\n\n");
		getchar();
	}

	int answer;		//����� �Է°�

	printf("\n\n�߸����� �� ���ϱ��? \n");
	scanf_s("%d", &answer);

	if (answer == treatment + 1) {
		printf("�����Դϴ�.\n");
	}
	else {
		printf("Ʋ�Ƚ��ϴ�.\n ������ %d�Դϴ�.", treatment + 1);
	}

	return 0;
}