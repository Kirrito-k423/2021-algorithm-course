/*
 * @Descripttion: 
 * @version: 
 * @Author: Shaojie Tan
 * @Date: 2021-12-04 15:48:11
 * @LastEditors: Shaojie Tan
 * @LastEditTime: 2021-12-04 20:12:34
 */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define ALGO_REPEAT_COUNT 1000
#define PROJECT_SCALE 10000000

// global var to count linked list access

int count;

int rankLocation[PROJECT_SCALE];
int val[PROJECT_SCALE], ptr[PROJECT_SCALE];

int algorithmA(int n, int val[], int ptr[], int head, int x) {// x < n

    while (x > val[head]) {
        head = ptr[head];
        ++count;
    }
    return head;
}

int algorithmB(int n, int val[], int ptr[], int head, int x) {
    int sqrtn = sqrt(n);
    int i, max = head;
    for (i=0; i<sqrtn; i++) {
        ++count;
        if (val[i] <= x && val[i] > val[max])
            max = i;
    }
    return algorithmA(n, val, ptr, max, x);
}

int algorithmC(int n, int val[], int ptr[], int head, int x) {
    int sqrtn = sqrt(n);
    int i, max = head;
    for (i=0; i<sqrtn; i++) {
        int r = rand() % n;
        ++count;
        if (val[r] <= x && val[r] > val[max])
        max = r;
    }

    return algorithmA(n, val, ptr, max, x);

}

int algorithmD(int n, int val[], int ptr[], int head, int x) {
    int flag = rand() % n;
    int y = val[flag];
    ++count;
    if (x < y)
        return algorithmA(n, val, ptr, head, x);
    else if (x > y)
        return algorithmA(n, val, ptr, ptr[flag], x);
    else
        return flag;
}

void searchOrder(int n){
    // int rankLocation[n];
    // int val[n], ptr[n];
    for(int i=0; i<n; i++){
        rankLocation[i]=n-1-i;
    }
    // for(int i=0; i<n; i++){
    //     int exchangeIndex = rand() % (n-i);
    //     int lastIndex = n-i-1;
    //     int tmp = rankLocation[exchangeIndex];
    //     rankLocation[exchangeIndex]=rankLocation[lastIndex];
    //     rankLocation[lastIndex]=tmp;
    // }
    // for (int i=0; i<n; i++) {
    //     printf("%3d ",rankLocation[i]);
    // }
    // printf("\n");
    // 至此构造好了随机数列
    int firstVal=0;
    int head = rankLocation[0];
    for(int i=0; i<n-1; i++){
        int index = rankLocation[i];
        int nextIndex=rankLocation[i+1];
        ptr[index]=nextIndex;
        val[index]=firstVal;
        firstVal += 1;
    }
    int lastIndex = rankLocation[n-1];
    ptr[lastIndex]=0;
    val[lastIndex]=firstVal;
    printf("val 与 ptr 构造完成\n");
    // printf("head %d \n",head);
    // for (int i=0; i<n; i++) {
    //     printf("%3d ",val[i]);
    // }
    // printf("\n");
    // for (int i=0; i<n; i++) {
    //     printf("%3d ",ptr[i]);
    // }
    // printf("\n");
    int (*algo[])(int, int[], int[], int, int) = {algorithmA, algorithmB, algorithmC, algorithmD};
    //int repeat_num[] = {1, 1, ALGO_REPEAT_COUNT, 1};
    int algo_num = sizeof(algo) / sizeof(algo[0]);
    int worst[algo_num];
    int total[algo_num];

    for (int i=0; i<algo_num; i++) {
        worst[i] = total[i] = 0;
        for (int j=0; j<ALGO_REPEAT_COUNT; j++) {
            int x = rand() % n;
            count = 0;
            algo[i](n, val, ptr, head, x);
            if (count > worst[i])
                worst[i] = count;
            total[i] += count;
        }
    }

    for (int i=0; i<algo_num; i++) {
        printf("Algo %c: average %f, worst %d\n", i+'A', total[i] * 1.0 / ALGO_REPEAT_COUNT, worst[i]);
    }
}

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    if(n>PROJECT_SCALE){
        printf("n is bigger than PROJECT_SCALE");
        return 0;
    }
    srand(time(NULL));
    searchOrder(n);
    return 0;
}