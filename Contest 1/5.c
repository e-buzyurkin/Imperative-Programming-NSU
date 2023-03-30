#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE *f1, *f2;
    int a, b, rem, r_up, r_down, r_zero;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d %d", &a, &b);
    fclose(f1);

    int quot = a / b; // öåëàÿ ÷àñòü îò äåëåíèÿ
    rem = a % b; // îñòàòîê

    if (a >= 0){
        r_down = quot;
        if (rem != 0) r_up = quot + 1;
            else r_up = quot;
        r_zero = quot;
    }
    else{
        r_up = quot;
        if (rem != 0) {
            r_down = quot - 1;
            rem += b;
        }
            else r_down = quot;
        r_zero = quot;
    }

    f2 = fopen("output.txt", "w");
    fprintf(f2, "%d %d %d %d", r_down, r_up, r_zero, rem);
    fclose(f2);
    return 0;
}
