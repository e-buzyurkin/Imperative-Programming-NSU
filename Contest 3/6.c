#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    const m = 100001;
    int n, k, x;
    fscanf(f1, "%d", &n);
    int a[m];
    for (int i = 0; i<=m; i++) a[i] = 0;
    int count = 0;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d", &x);
        if (a[x] == 0){
            a[x] = 1;
            count++;
        }
    }

    fscanf(f1, "%d", &k);
    for (int i = 0; i < k; i++){
        fscanf(f1, "%d", &x);
        if (a[x] == 1){
            a[x] = 0;
            count--;
        }
    }

    fprintf(f2, "%d\n", count);
    for (int i = 0; i <= m; i++){
        if (a[i] == 1) fprintf(f2, "%d ", i);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
