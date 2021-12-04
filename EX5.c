/*
 * @Descripttion: 
 * @version: 
 * @Author: Shaojie Tan
 * @Date: 2021-12-03 20:54:12
 * @LastEditors: Shaojie Tan
 * @LastEditTime: 2021-12-03 21:03:50
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define REPEAT_COUNT 10000

int main(int argc, char** argv) {

for(int i=1; i<argc; i++){
	int n;
	int repeat;
	double all_k = 0;
	unsigned char *set;

	n = atoi(argv[i]);

	srand(time(NULL));

	set = (unsigned char*)malloc(n * sizeof(unsigned char));

	for (repeat = 0; repeat < REPEAT_COUNT; repeat++) {
		int k;
		memset(set, 0, n * sizeof(unsigned char));
		for (k=1; ; k++) {
			int a = rand() % n;
			if (set[a])
				break;
			set[a] = 1;
		}
		all_k += k;
	}
	double avg_k=all_k * 1.0 / REPEAT_COUNT;
	double pre = 2.0 * avg_k * avg_k / 3.1415926;
	printf("%f %f%\n", pre, (n-pre)/pre);
}
return 0;

}