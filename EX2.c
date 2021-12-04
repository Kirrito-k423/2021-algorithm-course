/*
 * @Descripttion: 
 * @version: 
 * @Author: Shaojie Tan
 * @Date: 2021-12-03 19:25:33
 * @LastEditors: Shaojie Tan
 * @LastEditTime: 2021-12-03 19:39:10
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double func(double x) {
    return sqrt(1 - x*x);
}

double integrate(double a, double b, int n) {
    int i;
    double sum = 0;

    for (i=0; i<n; i++) {
        sum += func(rand() * 1.0 / RAND_MAX * (b-a) + a);

    }
    return sum * (b-a) / n;

}

int main(int argc,char *argv[]) {
    for(int i=1; i<argc; i++){
        int num = atoi(argv[i]);
        printf("num : %d\n",num);
        double right=3.14159265358979323846;
        double prediction=4 * integrate(0, 1, num);
        printf("%lf %lf\n", prediction, right-prediction);
    }
}
