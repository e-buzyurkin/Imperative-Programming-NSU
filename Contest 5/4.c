#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, q;
    fscanf(f1, "%d %d", &n, &q);

    int primes[n+1];

    //short primes[n+1];
    primes[0] = 0; primes[1] = 0;
    for (int i = 2; i <= n; i++) primes[i] = 1;

    for (int i = 2; i <= n ; i++){
        //printf("%d\n", i);
        if (primes[i] == 1){
            if(i * 1ll * i <= n)
                for (unsigned long long j = i*i; j <= n; j += i){
                    primes[j] = 0;
                }
        }
    }

    int x;

    for (int i = 0; i < q; i++){
        fscanf(f1, "%d", &x);
        if (primes[x] == 0) fprintf(f2, "%d not\n", x);
        else fprintf(f2, "%d prime\n", x);
    }


    fclose(f1);
    fclose(f2);

    return 0;
}
