#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    const k = 10001;
    int n, x;
    fscanf(f1, "%d", &n);
    int a[k];
    for (int i=0; i<k; i++) a[i] = 0;

    for (int i=0; i<n; i++){
        fscanf(f1, "%d", &x);
        a[x]++;
    }

    for (int i=1; i < k; i++){
        if (a[i] != 0){
            fprintf(f2, "%d: %d\n", i, a[i]);
        }
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
