#include "myPuzzle.h"
#include<Windows.h>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>


int main()
{
	int i, count = 0, key;
	int gostop = 1;
	char userName[100];
	/*char* dirName;*/
	//char* fileName;
	int (*(func[4]))(int, int, MY_PUZZLE*) = { p2D_init, p2D_play, p2D_display, p2D_finish };
	MY_PUZZLE pz;


	p2D_setConfig(pz.size, 0, &pz);
	pz.d1.p1D = (int*)malloc((pz.size) * (pz.size) * sizeof(int));

	if (pz.d1.p1D == NULL) {
		printf("동적 할당할 메모리가 부족합니다.\n");
		return STOP;
	}

	srand(time(NULL));

	(func[0])(pz.test, 0, &pz);
	(func[2])(pz.test, 0, &pz);

	while (gostop) {

		key = getKey();
		for (i = 1; i < 4; i++) {
			count = (func[i])(key, count, &pz);
			if (i == 3 && count) {
				gostop = 0;
				break;
			}
		}
	}
	
	p2D_Score(count);

	printf("\n\nFinish!!\n");
	free(pz.d1.p1D);
	return 0;
}