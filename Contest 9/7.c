#include <stdio.h>
#include <stdlib.h>

void quicksort(int *a, int l, int r){
    if (l < r){
        int x, w;
        int i = l, j = r;
        x = a[(rand() % (r - l + 1)) + l];
        while (i < j){
            while (a[i] < x) i++;
            while (x < a[j]) j--;
            if (i <= j){
                w = a[i];
                a[i] = a[j];
                a[j] = w;
                i++;
                j--;
            }
        }
        if (l < j) quicksort(a, l, j);
        if (i < r) quicksort(a, i, r);
    }
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    int a[n];
    for (int i = 0; i < n; i++)
        fscanf(f1, "%d", &a[i]);

    quicksort(a, 0, n - 1);

    int out[n];
    int count = 1;
    out[0] = a[0];

    for (int i = 1; i < n; i++){
        if (out[count - 1] != a[i]){
            out[count] = a[i];
            count++;
        }
    }

    fprintf(f2, "%d\n", count);

    for (int i = 0; i < count; i++)
        fprintf(f2, "%d\n", out[i]);

    fclose(f1);
    fclose(f2);

    return 0;
}
