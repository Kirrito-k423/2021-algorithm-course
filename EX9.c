/*
 * @Descripttion: 
 * @version: 
 * @Author: Shaojie Tan
 * @Date: 2021-12-04 20:23:11
 * @LastEditors: Shaojie Tan
 * @LastEditTime: 2021-12-04 20:53:57
 */
#include<stdio.h>
#include<stdlib.h>
typedef unsigned char bool;
#define TRIALS 1000

bool queens_lv(int n, int k, int try[], bool col[], bool diag45[], bool diag135[], int* try_count) {
	int i, row;
	for (i=0; i<n; i++)
		col[i] = 0;
	for (i=0; i<2*n; i++)
		diag45[i] = diag135[i] = 0;
	for (row=0; row<k; row++) {
		int open = 0;
		int selected = 0;
		for (i=0; i<n; i++) {
			if (!col[i] && !diag45[n+i-row] && !diag135[i+row]) {
				++open;
				if (rand() % open == 0)
					selected = i;
			}
		}
		if (open == 0)
			return 0;
		++*try_count;
		try[row] = selected;
		col[selected] = 1;
		diag45[n+selected-row] = 1;
		diag135[selected+row] = 1;
	}
	return 1;
}

bool backtrack(int n, int row, int try[], bool col[], bool diag45[], bool diag135[], int* try_count) {
	int i;
	if (row == n)
		return 1;
	for (i=0; i<n; i++) {
		if (!col[i] && !diag45[n+i-row] && !diag135[i+row]) {
			++*try_count;
			try[row] = i;
			col[i] = diag45[n+i-row] = diag135[i+row] = 1;
			if (backtrack(n, row+1, try, col, diag45, diag135, try_count))
				return 1;
			col[i] = diag45[n+i-row] = diag135[i+row] = 0;
		}
	}
	return 0;
}

int search_queens(int n, int k) {
	int try[n];
	bool col[n], diag45[2*n], diag135[2*n];
	int try_count = 0;
	while (1) {
		if (queens_lv(n, k, try, col, diag45, diag135, &try_count)) {
			if (backtrack(n, k, try, col, diag45, diag135, &try_count))
				return try_count;
		}
	}
}

int main() {
	int n, k, i;
	int now, min, bestk;
	for (n=12; n<=20; n++) {
		bestk = 0;
		for (k=0; k<=n; k++) {
			now = 0;
			for (i=0; i<TRIALS; i++) {
				now += search_queens(n, k);
			}
			if (bestk == 0 || now < min) {
				bestk = k;
				min = now;
			}
		}
		printf("n=%d bestk=%d nodes=%f\n", n, bestk, min * 1.0 / TRIALS);
	}
	return 0;
}