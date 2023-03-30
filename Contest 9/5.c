#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);

    int *a;
    a = malloc(sizeof(int) * n);
    fread(a, sizeof(int), n, f1);

    quicksort(a, 0, n - 1);
    fwrite(a, sizeof(int), n, f2);
    //int x = 5;
    //for (int i = 0; i < 500000; i++)
    //    fwrite(&x, sizeof(int), 1, f2);

    free(a);

    fclose(f1);
    fclose(f2);

    return 0;
}
