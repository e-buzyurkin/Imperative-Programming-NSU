#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int a = 0, b = 0;
    int res;

    fread(&a, sizeof(int), 1, f1);
    fread(&b, sizeof(int), 1, f1);

    int helper = 0;
    int isSignDif = (a < 0 && b > 0) || (a > 0 && b < 0);

    helper = ((a % 2 == -1) && (b % 2 == -1)) || ((a % 2 == 1) && (b % 2 == 1));

    /*if (a == -1 && b > 0){
        res = b - 1;
        res >>= 1;
        goto ending;
    }
    if (b == -1 && a > 0){
        res = a - 1;
        res >>= 1;
        goto ending;
    }
    if (isSignDif && (a + b == 0)){
        res = 0;
        goto ending;
    }

    //printf("%d %d\n", a, b);

    a = a / 2 - (a % 2 == -1);
    b = b / 2 - (b % 2 == -1);

    res = a + b + helper;
    */

    long long m = a;
    m += b;
    m = m / 2 - (m % 2 == -1);

    ending:
    fwrite(&m, sizeof(int), 1, f2);

    fclose(f1);
    fclose(f2);

    return 0;
}
