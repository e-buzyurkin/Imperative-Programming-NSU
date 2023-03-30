#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binary_search(int x, int *a, int n){
    int left = -1;
    int right = n;
    int middle;
    while (left < right - 1){
        middle = (left + right) / 2;
        if (a[middle] < x) left = middle;
        else right = middle;
    }
    return right;

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
    int xj, yj, res, out1, out2;

    //printf("%d", binary_search(2, a, n));

    for (int i = 0; i < q; i++){
        fscanf(f1, "%d", &xj);
        yj = xj;
        res = binary_search(yj, a, n);
        out1 = abs(a[res] - yj);
        out2 = abs(a[res - 1] - yj);
        if (out1 <= out2) fprintf(f2, "%d %d\n", res, out1);
        else fprintf(f2, "%d %d\n", res - 1, out2);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
