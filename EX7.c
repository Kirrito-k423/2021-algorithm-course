/*
 * @Descripttion: 
 * @version: 
 * @Author: Shaojie Tan
 * @Date: 2021-12-04 09:37:57
 * @LastEditors: Shaojie Tan
 * @LastEditTime: 2021-12-04 16:49:05
 */
#include<stdio.h>

#include<math.h>

#include<stdlib.h>

#include<string.h>

#include<time.h>

#define ALGO_REPEAT_COUNT 1000

// global var to count linked list access

int count;

int algo_a(int n, int val[], int ptr[], int head, int x) {

    while (x > val[head]) {

    head = ptr[head];

    ++count;

    }

    return head;

}

int algo_b(int n, int val[], int ptr[], int head, int x) {

    int sqrtn = sqrt(n);

    int i, max = head;

    for (i=0; i<sqrtn; i++) {

    ++count;

    if (val[i] <= x && val[i] > val[max])

    max = i;

    }

    return algo_a(n, val, ptr, max, x);

}

int algo_c(int n, int val[], int ptr[], int head, int x) {

    int sqrtn = sqrt(n);

    int i, max = head;

    for (i=0; i<sqrtn; i++) {

    int r = rand() % n;

    ++count;

    if (val[r] <= x && val[r] > val[max])

    max = r;

    }

    return algo_a(n, val, ptr, max, x);

}

int algo_d(int n, int val[], int ptr[], int head, int x) {

    int flag = rand() % n;

    int y = val[flag];

    ++count;

    if (x < y)

    return algo_a(n, val, ptr, head, x);

    else if (x > y)

    return algo_a(n, val, ptr, ptr[flag], x);

    else

    return flag;

}

void search(int n) {
    int val[n], ptr[n], revptr[n];
    int i, j, head = 0;

    for (i=0; i<n; i++) {
        val[i] = i;
        ptr[i] = i+1;
        revptr[i] = i-1;
    }

    ptr[n-1] = 0;
    revptr[0] = n-1;

    for (i=0; i<n; i++) {
        int r = rand() % (n-i);
        int last = n-i-1;
        if (r == last)
            continue;

        int before_rand = revptr[r], after_rand = ptr[r];
        int before_last = revptr[last], after_last = ptr[last];
        int tmp = val[r];

        val[r] = val[last];
        val[last] = tmp;

        if (before_rand == last) { // adjacent
            ptr[before_last] = r;
            ptr[r] = last;
            ptr[last] = after_rand;
            revptr[r] = before_last;
            revptr[last] = r;
            revptr[after_rand] = last;
        }
        else if (before_last == r) { // adjacent
            ptr[before_rand] = last;
            ptr[last] = r;
            ptr[r] = after_last;
            revptr[last] = before_rand;
            revptr[r] = last;
            revptr[after_last] = r;
        }
        else { // ordinary case
            ptr[before_rand] = last;
            revptr[last] = before_rand;
            ptr[before_last] = r;
            revptr[r] = before_last;
            ptr[last] = after_rand;
            revptr[after_rand] = last;
            ptr[r] = after_last;
            revptr[after_last] = r;
        }
    }

    for (i=0; i<n; i++)
        if (val[i] == 0) {
            head = i;
            break;
        }

    printf("head %d \n",head);
    for (int i=0; i<n; i++) {
        printf("%3d ",val[i]);
    }
    printf("\n");
    for (int i=0; i<n; i++) {
        printf("%3d ",ptr[i]);
    }
    printf("\n");
    int (*algo[])(int, int[], int[], int, int) = {algo_a, algo_b, algo_c, algo_d};
    //int repeat_num[] = {1, 1, ALGO_REPEAT_COUNT, 1};
    int algo_num = sizeof(algo) / sizeof(algo[0]);
    int worst[algo_num];
    int total[algo_num];

    for (i=0; i<algo_num; i++) {
        worst[i] = total[i] = 0;
        for (j=0; j<ALGO_REPEAT_COUNT; j++) {
            int x = rand() % n;
            count = 0;
            algo[i](n, val, ptr, head, x);
            if (count > worst[i])
                worst[i] = count;
            total[i] += count;
        }
    }

    for (i=0; i<algo_num; i++) {
        printf("Algo %c: average %f, worst %d\n", i+'A', total[i] * 1.0 / ALGO_REPEAT_COUNT, worst[i]);
    }
}

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    srand(time(NULL));
    search(n);
    return 0;
}