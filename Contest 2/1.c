#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int primes(int x){
    int decider = 1;
    int end = sqrt(x);
    for (int i = 2; i <= end; i++){
        if (x % i == 0){
            decider = 0;
            break;
        }
    }
    return decider;
}

int main(){
    FILE *f1, *f2;
    int n;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d", &n);
    fclose(f1);

    f2 = fopen("output.txt", "w");

    for (int i = 2; i <= n; i++){
        if (primes(i) == 1)
            fprintf(f2, "%d\n", i);
    }


    fclose(f2);
    return 0;
}
