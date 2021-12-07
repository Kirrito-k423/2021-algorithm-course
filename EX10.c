/*
 * @Descripttion: 
 * @version: 
 * @Author: Shaojie Tan
 * @Date: 2021-12-07 07:47:29
 * @LastEditors: Shaojie Tan
 * @LastEditTime: 2021-12-07 08:08:08
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define false 0
#define true 1

// judge n is strong psudoprime number or composite number
int Btest(int a, int n) // n is odd number, 1: true, 0: false
{
    int s = 0;
	int t = n-1;
    unsigned long long x = 1;
	do{
		++s;
		t=t/2;
	}while( t%2 !=1 );
	for(int i=0;i<t;++i)
		x=(x*a)%n;
	if (x == 1 || x == n-1)
		return true;
	for (int i=1; i<=s-1; ++i)
	{
		x = (x*x) % n;
		if (x == n-1)
			return true;
	}
	return false;
}

// judge n is prime or composite number, if strong psudoprime, return 1(denote prime)
int MillRab(int n)
{
    srand(time(0));
    int a = rand()%(n-3) + 2;
    return Btest(a, n);
}

int RepeatMillRab(int n, int k)
{
    for (int i=0; i<k; ++i)
	{
		if (MillRab(n) == false)
			return false;
	}
	return true;
}


int PrintPrimes(int n)
{
    int lgn, count = 0;
    double n_double = (double)n;
    lgn = (int)(log(n_double) / log(2.));
    if(RepeatMillRab(n, lgn)){
        printf("%d\t", n);
        return n;
    }
    return -1;
}


int primeForSure(int n)
{
    for (int j=2; j<= (int) sqrt((double)n); ++j)
	{
		if ( n%j == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
    int n=5, result = 0, countP = 0, countS = 0, countA=0;
    printf("2\t3\t");
    while(n <= 10000){
        result = PrintPrimes(n);
        if(n>=100 && primeForSure(n)){
            countA++;
        }
        if(result != -1 && n >= 100){
            countP++;
            if(primeForSure(n)){
                countS++;
            }
        }
        n = n + 2;
    }

    printf("\nAll prime number: %d", countA);
    printf("\nRepeatMillRab prime number: %d", countP);
    printf("\nActual prime number: %d", countS);
    printf("\nThe error rate is: %lf\n", (double)(countP-countS)/countS);

    return 0;
}