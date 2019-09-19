#include <stdio.h>

int board[10][10];				//33의 판정으로 인해 판이 확장되어야 함
void init_board();
void display_board();
int win_lose_Draw();
int player1_do();
void player2_do();
int SamSam_01(int n1, int n2);

int player1_do()
{					//사용자로 하여금 돌의 위치를 입력받음
	int x, y;
	printf("흑의 돌 좌표를 입력하세요(x:1-10 y:1-10):");
	scanf("%d %d", &x, &y);
	x; y;
	x--; y--;

	if (x >= 10 || y >= 10 || x <= -1 || y <= -1) {
		printf("오목판을 벗어났습니다. 좌표값 다시 입력!!\n");
		player1_do();
	}

	else if (board[x][y] == 'o' || board[x][y] == 'x') {
		printf("이미 놓았습니다. 다시 입력!!\n");
		player1_do();
	}
	else
		board[x][y] = 'x';

	if (SamSam_01(x, y) == 1) {
		printf("금수입니다. 흑이 패하였습니다.\n");
		return 1;
	}

	return 0;
}

void player2_do()
{					//사용자로 하여금 돌의 위치를 입력받음
	int x, y;
	printf("백의 돌 좌표를 입력하세요(x:1-10 y:1-10):");
	scanf("%d %d", &x, &y);
	x; y;
	x--; y--;

	if (x >= 10 || y >= 10 || x <= -1 || y <= -1) {
		printf("오목판을 벗어났습니다. 좌표값 다시 입력!!\n");
		player2_do();
	}
	else if (board[x][y] == 'o' || board[x][y] == 'x') {
		printf("이미 놓았습니다. 다시 입력!!\n");
		player2_do();
	}
	else
		board[x][y] = 'o';
}

int SamSam_01(int n1, int n2)
{
	int h, k = 0;						//h->놓은 돌 위치 보정 || k->돌의 갯수, 값 검열 
	int i = 0, count = 0;				//i->돌 배열 도움 || count->반환 값

	if (n1<2 || n1>9 || n2<2 || n2>9) return 0;		//33 가능 위치 기본 조사

	for (h = 1; h<5; h++) {			//놓은 돌을 기준으로 주위에 자신의 돌만 세개가 있는지 조사 (가로)

		for (i = 0; i<6; i++) if (board[n1][n2 + (i - h)] != 'o') k++;

		if (k != 6) {					//범위 내에 백이 있을 경우 한 좌표 옆 위치에서 다시 조사
			k = 0;
			continue;
		}
		else if (k == 6) {			//33 범위 내에 흑의 갯수를 조사
			k = 0;
			for (i = 0; i<4; i++) if (board[n1][n2 + (i - h) + 1] == 'x') k++;
			if (k == 3) {				//흑이 3개이므로 33의 정의에 합당함
				count++;
				k = 0;
				break;
			}
		}
		k = 0;						//조사가 실패 했으므로 다시 돌의 갯수를 0으로 맞춤
	}

	for (h = 1; h<5; h++) {			//(세로)

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

	for (h = 1; h<5; h++) {		//(정대각)

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


	for (h = 1; h<5; h++) {		//(역대각)

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
{					//승패 가르기
	int i, j;
	int cnt;		//더 이상 둘 곳이 없을 경우의 수

	for (i = 0; i<10; i++) {		//가로 열 검열
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

	for (i = 0; i<10; i++) {			//세로 열 검열
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

	for (i = 0; i<6; i++) {				//대각선 검열
		for (j = 0; j<6; j++) {

			if (board[i][j] == board[i + 1][j + 1] &&					//좌에서 우로
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

	for (i = 4; i<10; i++) {			//대각선 검열
		for (j = 0; j<6; j++) {
			if (board[i][j] == board[i - 1][j + 1] &&					//우에서 좌로
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

	cnt = 99;				//비김 처리
	cnt--;

	if (cnt == 0)
		return 3;

	return 0;				//계속 진행
}


int main()
{						//플레이
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
		printf("흑이 승리하였습니다!!\n");
	}
	else if (r == 2)
	{
		printf("백이 승리하였습니다!!\n");
	}
	else if (r == 3)
	{
		printf("비겼습니다!!\n");
	}


	//종료 화면이 정상 출력 되지 않는다.
	//해당 함수를 추가하여 종료 시점을 제어함
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
{						//오목 놓을자리
	int i, j;
	for (i = 0; i<10; i++)
		for (j = 0; j<10; j++) board[i][j] = '\0';
}

void display_board()
{						//오목판
	int i, j;

	printf("\n x    y\t");

	for (i = 0; i<9; i++) printf(" %d |", i + 1);		//위 쪽 숫자

	printf(" %d", 10);		//정리
	printf("\n\n");

	for (i = 0; i<10; i++) {	//오목판 값

		printf(" %d \t", i + 1);

		for (j = 0; j<9; j++) printf(" %c |", board[i][j]);

		printf(" %c \n", board[i][9]);


		if (i == 9) {			//마지막 ---을 긋지 않기 위한 탈출문
			printf("\n");
			break;
		}

		printf("---\t");

		for (j = 0; j<9; j++) printf("---+");

		printf("---\n");

	}
}