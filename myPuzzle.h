#ifndef MY_PUZZLE_H
#define MY_PUZZLE_H

//상수 및 문자열 정의 

#define KEY_UP			72
#define KEY_DOWN		80
#define KEY_RIGHT		77
#define KEY_LEFT		75

#define GOSTOP			0
#define STOP			1

#define MAX_SIZE		10
#define MIN_SIZE		3
#define DEFAULT_SIZE	3

#define FUNC_INIT       0
#define FUNC_PLAY       2
#define FUNC_DISPLAY    1
#define FUNC_FINISH     3

#define FAIL            1
#define SUCCESS         0

#define TEST1           1

#define CONFIG			"./config.txt"
#define SCORE			"./scoreFile/game_score.txt"
#define SCOREDIR		"./score"

#define RUN				0
#define SET				0
#define DEFAULT			0

//구조체 정의 
typedef struct _D1_pz {
	int index;
	int* p1D;
} D1_PZ;

typedef struct _D2_pz {
	int row;
	int column;
	int** p2D;
} D2_PZ;

typedef struct _MY_PUZZLE {
	int size;
	D1_PZ d1;
	D2_PZ d2;
	char dir[200];
	char score[200];
	int test;

} MY_PUZZLE;

typedef struct _RECSCORE {
	char userName[100];
	int date;
	int count;
}RECSCORE;

int p2D_init(int temp1, int temp2, MY_PUZZLE* pz);
int p2D_display(int key, int count, MY_PUZZLE* pz);
int p2D_play(int key, int count, MY_PUZZLE* pz);
int p2D_finish(int temp1, int temp2, MY_PUZZLE* pz);
int p2D_setConfig(int size, int temp1, MY_PUZZLE* pz);
int p2D_Score(int count);

//int p2D_memory(int, MY_PUZZLE*);
int getKey();

#endif