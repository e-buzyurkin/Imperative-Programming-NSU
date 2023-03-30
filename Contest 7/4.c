#include <stdio.h>
#include <stdlib.h>

int binary_search(int x, int *a, int n){
    int left = -1;
    int right = n;
    int middle;
    while (left < right - 1){
        middle = (left + right) / 2;
        if (a[middle] <= x) left = middle;
        else right = middle;
    }
    if (a[left] == x)
        return left;
    return -1;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);
    int a[n];

    for (int i = 0; i < n; i++) fscanf(f1, "%d", &a[i]);

    int q;
    fscanf(f1, "%d", &q);
    int rj = 0;
    int xj, yj, res;

    //printf("%d", binary_search(2, a, n));

    for (int i = 0; i < q; i++){
        fscanf(f1, "%d", &xj);
        yj = xj + rj;
        res = binary_search(yj, a, n);
        fprintf(f2, "%d\n", res);
        rj = res;
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
