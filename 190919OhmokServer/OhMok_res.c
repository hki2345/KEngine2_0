#include <stdio.h>

int board[10][10];				//33�� �������� ���� ���� Ȯ��Ǿ�� ��
void init_board();
void display_board();
int win_lose_Draw();
int player1_do();
void player2_do();
int SamSam_01(int n1, int n2);

int player1_do()
{					//����ڷ� �Ͽ��� ���� ��ġ�� �Է¹���
	int x, y;
	printf("���� �� ��ǥ�� �Է��ϼ���(x:1-10 y:1-10):");
	scanf("%d %d", &x, &y);
	x; y;
	x--; y--;

	if (x >= 10 || y >= 10 || x <= -1 || y <= -1) {
		printf("�������� ������ϴ�. ��ǥ�� �ٽ� �Է�!!\n");
		player1_do();
	}

	else if (board[x][y] == 'o' || board[x][y] == 'x') {
		printf("�̹� ���ҽ��ϴ�. �ٽ� �Է�!!\n");
		player1_do();
	}
	else
		board[x][y] = 'x';

	if (SamSam_01(x, y) == 1) {
		printf("�ݼ��Դϴ�. ���� ���Ͽ����ϴ�.\n");
		return 1;
	}

	return 0;
}

void player2_do()
{					//����ڷ� �Ͽ��� ���� ��ġ�� �Է¹���
	int x, y;
	printf("���� �� ��ǥ�� �Է��ϼ���(x:1-10 y:1-10):");
	scanf("%d %d", &x, &y);
	x; y;
	x--; y--;

	if (x >= 10 || y >= 10 || x <= -1 || y <= -1) {
		printf("�������� ������ϴ�. ��ǥ�� �ٽ� �Է�!!\n");
		player2_do();
	}
	else if (board[x][y] == 'o' || board[x][y] == 'x') {
		printf("�̹� ���ҽ��ϴ�. �ٽ� �Է�!!\n");
		player2_do();
	}
	else
		board[x][y] = 'o';
}

int SamSam_01(int n1, int n2)
{
	int h, k = 0;						//h->���� �� ��ġ ���� || k->���� ����, �� �˿� 
	int i = 0, count = 0;				//i->�� �迭 ���� || count->��ȯ ��

	if (n1<2 || n1>9 || n2<2 || n2>9) return 0;		//33 ���� ��ġ �⺻ ����

	for (h = 1; h<5; h++) {			//���� ���� �������� ������ �ڽ��� ���� ������ �ִ��� ���� (����)

		for (i = 0; i<6; i++) if (board[n1][n2 + (i - h)] != 'o') k++;

		if (k != 6) {					//���� ���� ���� ���� ��� �� ��ǥ �� ��ġ���� �ٽ� ����
			k = 0;
			continue;
		}
		else if (k == 6) {			//33 ���� ���� ���� ������ ����
			k = 0;
			for (i = 0; i<4; i++) if (board[n1][n2 + (i - h) + 1] == 'x') k++;
			if (k == 3) {				//���� 3���̹Ƿ� 33�� ���ǿ� �մ���
				count++;
				k = 0;
				break;
			}
		}
		k = 0;						//���簡 ���� �����Ƿ� �ٽ� ���� ������ 0���� ����
	}

	for (h = 1; h<5; h++) {			//(����)

		for (i = 0; i<6; i++) if (board[n1 + (i - h)][n2] != 'o') k++;

		if (k != 6) {
			k = 0;
			continue;
		}
		else if (k == 6) {
			k = 0;
			for (i = 0; i<4; i++) if (board[n1 + (i - h) + 1][n2] == 'x') k++;
			if (k == 3) {
				count++;
				k = 0;
				break;
			}
		}
		k = 0;
	}

	for (h = 1; h<5; h++) {		//(���밢)

		for (i = 0; i<6; i++) if (board[n1 + (i - h)][n2 + (i - h)] != 'o') k++;

		if (k != 6) {
			k = 0;
			continue;
		}
		else if (k == 6) {
			k = 0;
			for (i = 0; i<4; i++) if (board[n1 + (i - h) + 1][n2 + (i - h) + 1] == 'x') k++;
			if (k == 3) {
				count++;
				k = 0;
				break;
			}
		}
		k = 0;
	}


	for (h = 1; h<5; h++) {		//(���밢)

		for (i = 0; i<6; i++) if (board[n1 - (i - h)][n2 + (i - h)] != 'o') k++;

		if (k != 6) {
			k = 0;
			continue;
		}
		else if (k == 6) {
			k = 0;
			for (i = 0; i<4; i++) if (board[n1 - (i - h) - 1][n2 + (i - h) + 1] == 'x') k++;
			if (k == 3) {
				count++;
				k = 0;
				break;
			}
		}
		k = 0;
	}

	if (count == 2) return 1;
	else return 0;
}

int win_lose_Draw()
{					//���� ������
	int i, j;
	int cnt;		//�� �̻� �� ���� ���� ����� ��

	for (i = 0; i<10; i++) {		//���� �� �˿�
		for (j = 0; j<6; j++) {
			if (board[i][j] == board[i][j + 1] &&
				board[i][j + 1] == board[i][j + 2] &&
				board[i][j + 2] == board[i][j + 3] &&
				board[i][j + 3] == board[i][j + 4])
			{
				if (board[i][j + 2] == 'x')
					return 1;
				else if (board[i][j + 2] == 'o')
					return 2;
			}
		}
	}

	for (i = 0; i<10; i++) {			//���� �� �˿�
		for (j = 0; j<6; j++) {
			if (board[j][i] == board[j + 1][i] &&
				board[j + 1][i] == board[j + 2][i] &&
				board[j + 2][i] == board[j + 3][i] &&
				board[j + 3][i] == board[j + 4][i])
			{
				if (board[j + 2][i] == 'x')
					return 1;
				else if (board[j + 2][i] == 'o')
					return 2;
			}
		}
	}

	for (i = 0; i<6; i++) {				//�밢�� �˿�
		for (j = 0; j<6; j++) {

			if (board[i][j] == board[i + 1][j + 1] &&					//�¿��� ���
				board[i + 1][j + 1] == board[i + 2][j + 2] &&
				board[i + 2][j + 2] == board[i + 3][j + 3] &&
				board[i + 3][j + 3] == board[i + 4][j + 4]) {
				if (board[i + 2][j + 2] == 'x')
					return 1;
				else if (board[i + 2][j + 2] == 'o')
					return 2;
			}
		}
	}

	for (i = 4; i<10; i++) {			//�밢�� �˿�
		for (j = 0; j<6; j++) {
			if (board[i][j] == board[i - 1][j + 1] &&					//�쿡�� �·�
				board[i - 1][j + 1] == board[i - 2][j + 2] &&
				board[i - 2][j + 2] == board[i - 3][j + 3] &&
				board[i - 3][j + 3] == board[i - 4][j + 4]) {

				if (board[i - 2][j + 2] == 'x')
					return 1;
				else if (board[i - 2][j + 2] == 'o')
					return 2;
			}
		}
	}

	cnt = 99;				//��� ó��
	cnt--;

	if (cnt == 0)
		return 3;

	return 0;				//��� ����
}


int main()
{						//�÷���
	int r = 0;
	init_board();
	display_board();

	while (1) {
		if (player1_do() == 1) r = 2;
		if (r == 2) break;
		display_board();
		r = win_lose_Draw();
		if (r != 0)
			break;

		player2_do();
		display_board();
		r = win_lose_Draw();
		if (r != 0)
			break;
	}

	if (r == 1)
	{
		printf("���� �¸��Ͽ����ϴ�!!\n");
	}
	else if (r == 2)
	{
		printf("���� �¸��Ͽ����ϴ�!!\n");
	}
	else if (r == 3)
	{
		printf("�����ϴ�!!\n");
	}


	//���� ȭ���� ���� ��� ���� �ʴ´�.
	//�ش� �Լ��� �߰��Ͽ� ���� ������ ������
	while (1)
	{
		if (quit() == 0)
			return;
	}
}

int quit()
{
	int x;
	scanf("%d", &x);

	return 0;
}

void init_board()
{						//���� �����ڸ�
	int i, j;
	for (i = 0; i<10; i++)
		for (j = 0; j<10; j++) board[i][j] = '\0';
}

void display_board()
{						//������
	int i, j;

	printf("\n x    y\t");

	for (i = 0; i<9; i++) printf(" %d |", i + 1);		//�� �� ����

	printf(" %d", 10);		//����
	printf("\n\n");

	for (i = 0; i<10; i++) {	//������ ��

		printf(" %d \t", i + 1);

		for (j = 0; j<9; j++) printf(" %c |", board[i][j]);

		printf(" %c \n", board[i][9]);


		if (i == 9) {			//������ ---�� ���� �ʱ� ���� Ż�⹮
			printf("\n");
			break;
		}

		printf("---\t");

		for (j = 0; j<9; j++) printf("---+");

		printf("---\n");

	}
}