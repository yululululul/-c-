#include "myPuzzle.h"
#include<Windows.h>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <string.h>



int p2D_init(int temp1, int temp2, MY_PUZZLE*);
int p2D_display(int key, int count, MY_PUZZLE*);
int p2D_play(int key, int count, MY_PUZZLE*);
int p2D_finish(int temp1, int temp2, MY_PUZZLE*);
int p2D_setConfig(int size, int temp1, MY_PUZZLE* pz);
int p2D_Score(int count);
int getKey();

int getKey() {
	int key;
	key = _getch();
	if (key == 224) 
	{ key = _getch(); }

	return key;
}

int p2D_init(int temp1, int temp2, MY_PUZZLE* pz) {
	//2차원 배열을 1차원 배열처럼 처리;
	int i, k;
	

	if (temp1 == TEST1) {
		//test
		for (i = 0; i < (pz->size) * (pz->size) - 2; i++) {
			pz->d1.p1D[i] = i + 1;
		}
		pz->d1.p1D[(pz->size) * (pz->size) - 2] = 0;
		pz->d1.p1D[(pz->size) * (pz->size) - 1] = (pz->size) * (pz->size) - 1;
	}
	else {
		//별 위치 저장
		for (i = 0; i < (pz->size) * (pz->size); i++) {
			pz->d1.p1D[i] = rand() % ((pz->size) * (pz->size));
			for (k = 0; k < i; k++) {
				if (pz->d1.p1D[i] == pz->d1.p1D[k]) {
					i--;
					break;
				}
			}
		}
	}

	for (i = 0; i < (pz->size) * (pz->size); i++) {
		if (pz->d1.p1D[i] == 0) {
			pz->d2.row = i / (pz->size);
			pz->d2.column = i % (pz->size);
		}
	}

	return 0;
}

int p2D_display(int key, int count, MY_PUZZLE* pz, RECSCORE *rec) {
	int i, k;
	system("cls");
	printf("\n이름을 입력하시오: ");
	scanf("%c", rec->userName);
	printf("\n\n");

	for (i = 0; i < (pz->size); i++) {
		for (k = 0; k < (pz->size); k++) {
			if (pz->d1.p1D[i * (pz->size) + k] == 0) printf("%3c", '*');
			else									 printf("%3d", pz->d1.p1D[i * (pz->size) + k]);
		}
		printf("\n");
	}
	printf("count :%d", count);
	printf("\n");

	switch (key) {
	case KEY_UP:
		printf("Key : UP\n");
		break;
	case KEY_DOWN:
		printf("Key : DOWN\n");
		break;
	case KEY_RIGHT:
		printf("Key : RIGHT\n");
		break;
	case KEY_LEFT:
		printf("Key :LEFT\n");
		break;
	default:
		break;
	}
	return FAIL;
}


int p2D_play(int key, int count, MY_PUZZLE* pz) {

	int i = 0;
	int targetRow, targetColumn;
	int temp;

	targetRow = pz->d2.row;
	targetColumn = pz->d2.column;

	switch (key) {
	case KEY_UP: //up
		if (pz->d2.row > 0) targetRow--;
		count++;
		break;
	case KEY_DOWN: //down
		if (pz->d2.row < (pz->size) - 1) targetRow++;
		count++;
		break;
	case KEY_RIGHT:
		if (pz->d2.column < (pz->size) - 1) targetColumn++;
		count++;
		break;
	case KEY_LEFT:
		if (pz->d2.column > 0) targetColumn--;
		count++;
		break;
	default:
		break;
	}

	if ((pz->d2.row) != targetRow || (pz->d2.column) != targetColumn) {
		temp = pz->d1.p1D[(pz->d2.row) * (pz->size) + (pz->d2.column)];
		pz->d1.p1D[(pz->d2.row) * (pz->size) + (pz->d2.column)] = pz->d1.p1D[targetRow * (pz->size) + targetColumn];
		pz->d1.p1D[targetRow * (pz->size) + targetColumn] = temp;

		count++;

		pz->d2.row = targetRow;
		pz->d2.column = targetColumn;
	}
	return count;
}

int p2D_finish(int temp1, int temp2, MY_PUZZLE* pz) {
	int i;
	for (i = 0; i < (pz->size) * (pz->size) - 1; i++) {
		if (pz->d1.p1D[i] != (i + 1)) return 0;
	}
	return 1;
}

FILE* pConfig;


int p2D_setConfig(int size, int temp1, MY_PUZZLE* pz) {

	char buffer[500];
	char *result; 

	pConfig = fopen("config.txt", "r");
	if (pConfig == NULL) {
		pz->size = DEFAULT_SIZE;
		pz->test = RUN;
		strcpy(pz->score, SCORE);
		return SUCCESS;
	}

	// 파일이 있을 경우 한 줄씩 읽어서 처리
	while (1) {
		memset(buffer, 0x00, 500);

		result = fgets(buffer, 500, pConfig);
		if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = 0x00;

		if (result == NULL) break;

		if (strncmp("#", buffer, 1) == 0) continue;
		else if (strncmp("SIZE: ", buffer, 6) == 0) {
			pz->size = atoi(buffer + 6);
		}
		else if (strncmp("TEST: ", buffer, 6) == 0) {
			pz->test = atoi(buffer + 6);  // "TEST: " 이후 숫자를 파싱
		}
		// DIR 항목 확인
		else if (strncmp( "DIR: ", buffer, 5) == 0) {
			memset(pz->dir, 0x00, 200);
			strcpy(pz->dir, &buffer[5]);  // "DIR: " 이후 경로를 복사
		}
		// SCORE 파일 경로 확인
		else if (strncmp( "SCORE: ",buffer, 7) == 0) {
			memset(pz->score, 0x00, 200);
			strcpy(pz->score, &buffer[7]);  // "SCORE: " 이후 경로를 복사
			
		}
	}

	fclose(pConfig);

	// 설정이 제대로 읽혔는지 출력
	printf("설정 완료 - SIZE: %d, TEST: %d, DIR: %s, SCORE: %s\n", pz->size, pz->test, pz->dir, pz->score);
	return 0;
}
//
//int p2D_Score(FILE* pScore, char *user, int count, char*dirName, char *fileName) {
//
//	time_t timer;
//	struct tm* t;
//
//	if (dirName[0] == 0x00)
//		p2D_dir(SCOREDIR);
//
//	else p2D_dir(dirName);
//
//	pScore = fopen(fileName, "r");
//	if (pScore == NULL) {
//		pScore = fopen(fileName, "w");
//		if (pScore == NULL) return FAIL;
//		fprintf(pScore, "=========================");
//		fprintf(pScore, "%-15s  %-6s  %s\n", "NAME", "COUNT", "DATE");
//		fprintf(pScore, "=========================");
//	}
//	fclose(pScore);
//	pScore = NULL;
//
//	pScore = fopen(game_score, "a");
//	if (pScore == NULL) return FAIL;
//	timer = time(NULL);
//	t = localtime(&timer);
//
//	fprintf(pScore, " %-15s  %-6d  %4d-%2d-%2d (%2d:%2d:%2d) \n", user, count, t->tm_year+1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min);
//	fclose(pScore);
//	return SUCCESS;
//}


int p2D_Score(FILE* pScore, MY_PUZZLE *pz, RECSCORE *rec, int count ) {

	time_t timer;
	struct tm* t;


	pScore = fopen("game_score.txt", "r");
	if (pScore == NULL) {
		pScore = fopen("game_score.txt", "w");
		if (pScore == NULL) return FAIL;
		fprintf(pScore, "=========================\n");
		fprintf(pScore, "   %-15s  %-10s  %s\n", "NAME", "COUNT", "DATE");
		fprintf(pScore, "=========================\n");
	}
	fclose(pScore);
	pScore = NULL;

	pScore = fopen("game_score.txt", "a");
	if (pScore == NULL) return FAIL;
	timer = time(NULL);
	t = localtime(&timer);

	fprintf(pScore, " %-15s  %-10d  %4d-%2d-%2d (%2d:%2d:%2d) \n", rec->userName, count,\
		t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	
	fclose(pScore);
	return SUCCESS;
}
