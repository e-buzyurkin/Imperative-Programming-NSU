#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fact(int n){
    int out = 1;
    for (int i = 2; i <= n; i++)
        out *= i;
    return out;
}

int sign(int n){
    if (n % 2 == 0) return 1;
    else return -1;
}

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    double x;

    int sgn;
    int divider;
    double dividend;

    double res;


    for (int i = 0; i < n; i++){
        fscanf(f1, "%lf", &x);
        for (int k = 0; k < 7; k++){
            sgn = sign(k);
            divider = fact(2 * k + 1);
            dividend = pow(x, 2 * k + 1);
            res = res + sgn * (dividend / divider);
        }
        res = sin(x);
        fprintf(f2, "%0.15lf\n", res);
    }

    fclose(f1);
    fclose(f2);
    return 0;
}