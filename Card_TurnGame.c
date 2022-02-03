#include<stdio.h>
#include<time.h>
#include<stdlib.h>

// 10 ������ ���� �ٸ� ���� (�� ī�� 2�徿)
//����ڷκ��� 2���� �Է°��� �޾Ƽ� - > ���� ���� ã���� ī��  ������
//��� ���� ���� ã���� ���� ����
//�� ���� Ƚ�� �˷��ֱ�

int arrayAnimal[4][5];		// ī�� ���� (��ü : 20���� ī��)
int checkAnimal[4][5];		//���������� ���� Ȯ��
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

	int failCount = 0;		//�� ���� Ƚ��

	while (1) {
		int select1 = 0;		//����ڰ� ������ ó�� ��
		int select2 = 0;		// ����ڰ� ������ �ι�° ��

		printAnimals();		//���� ��ġ ���
		printQuestion();		//���� ��� (ī�� ����)

		printf("������ ī�带 2�� ���ÿ� : ");
		scanf_s("%d %d", &select1, &select2);

		if (select1 == select2) {		//���� ī�� ���� �� ��ȿó��
			continue;
		}

		//��ǥ�� �ش��ϴ� ī�带 ������ ���� ������ �� ������ Ȯ��
		int firstSelect_x = conv_pos_x(select1);
		int firstSelect_y = conv_pos_y(select1);

		int secondSelect_x = conv_pos_x(select2);
		int secondSelect_y = conv_pos_y(select2);

		//1. ī�尡 �������� �ʾҴ���
		//2. ���ÿ� �� ������ ������
		//3. �ƴϸ� �ٸ� ������ ���
		if (checkAnimal[firstSelect_x][firstSelect_y] == 0		//1. ī�尡 �������� �ʾҴ���
			&&
			checkAnimal[secondSelect_x][secondSelect_y] == 0
			&&
			arrayAnimal[firstSelect_x][firstSelect_y] == arrayAnimal[secondSelect_x][secondSelect_y] //2. ���ÿ� �� ������ ������
			) {
			printf("\n\n(����!) \n===========>  %s�߰�\n\n", strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
			checkAnimal[firstSelect_x][firstSelect_y] = 1;
			checkAnimal[secondSelect_x][secondSelect_y] = 1;
		}
		//3. �ƴϸ� �ٸ� ������ ���
		else {
			printf("\n\n ��!! (Ʋ�Ȱų� �̹� ������ ī���Դϴ�.) \n");
			printf("%d : %s\n", select1, strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
			printf("%d : %s\n", select2, strAnimal[arrayAnimal[secondSelect_x][secondSelect_y]]);
			printf("\n\n");

			failCount++;
		}

		//��� ������ ã�Ҵ��� ���� 1:�� ___ 0:����
		if (foundAllAnimals() == 1) {
			printf("\n\n �����մϴ� ! ��� ������ �� ã�ҳ׿� \n");
			printf("���ݱ��� �� %d�� �Ǽ� �Ͽ����ϴ�. \n", failCount);
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
	strAnimal[0] = "������";
	strAnimal[1] = "�ϸ�";
	strAnimal[2] = "������";
	strAnimal[3] = "�����";
	strAnimal[4] = "����";

	strAnimal[5] = "�ڳ���";
	strAnimal[6] = "�⸰";
	strAnimal[7] = "��Ÿ";
	strAnimal[8] = "Ÿ��";
	strAnimal[9] = "ȣ����";
}

void shuffleAnimal() {
	//������
	//������
	//������
	//������

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			int pos = getEmptyPosition();		//�޾ƿ� ������� ��ǥ��
			int x = conv_pos_x(pos);			//��ǥ�� ����Ʈ(��ȯ) -> X
			int y = conv_pos_y(pos);			//��ǥ�� ����Ʈ(��ȯ) -> Y

			arrayAnimal[x][y] = i;
		}
	}
}

int getEmptyPosition() {
	//������   0  1  2  3  4
	//������   5  6  7  8  9
	//������  10 11 12 13 14
	//������  15 16 17 18 19
	while (1) {
		int randPos = rand() % 20;		//0~19������ ���� ��ȯ
		//19 -> ��ǥ�� (3,4)
		// 5 -> ��ǥ�� (1,0)
		int x = conv_pos_x(randPos);
		int y = conv_pos_y(randPos);

		if (arrayAnimal[x][y] == -1) {		//-1�̸� ������̴�
			return randPos;					//������̸� ������ ��ǥ�� �ݿ�
		}
	}
	return 0;
}

int conv_pos_x(int x) {		//(10,2)�� (4,5)�� ��ǥ�� �ٲ�_________x ��ǥ
	// 19 - > (3,4)
	return x / 5;			//�� ���̸� �� 19�� 5�� ������ �� 3 (3,4)
}

int conv_pos_y(int y) {		//(10,2)�� (4,5)�� ��ǥ�� �ٲ�_________y��ǥ
	return y % 5;		//������ ���̸� �� 19�� 5�� ������ ������ 4 (3,4)
}

void printAnimals() {		//���� ��ġ ���
	//������   1  1  2  2  3
	//������   3  4  4  5  5
	//������  
	//������  
	//����ó�� ����� ������ ����
	printf("\n============�̰� ��Ʈ�Դϴ� �����ϼ�~============\n\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%8s", strAnimal[arrayAnimal[i][j]]);
		}
		printf("\n");
	}
	printf("\n=================================================\n\n");
}

void printQuestion() {		//���� ��� (ī�� ����)
	printf("\n\n(����)\n");
	int seq = 0;		//ī�忡 ���Ƿ� ��ȣ�� ���̴� ����

	//������   1  1  2  2  3
	//������   3  4  4  5  5
	//������  
	//������  

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			//ī�带 ����� ������ ���߸� '�����̸�'
			if (checkAnimal[i][j] != 0) {
				printf("%8s", strAnimal[arrayAnimal[i][j]]);
			}
			//���� ������ �������� (������ �� ���߸�) �޸� -> ��ġ�� ��Ÿ���� ����
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
			if (checkAnimal[i][j] == 0) {		//���� �� ������ ī�尡 ������
				return 0;
			}
		}
	}
	return 1;		//for���� �� ���Ҵµ��� checkAnimal[i][j] ���� ������ ��� ������ ã�Ҵٴ� ���� �ǹ�
}