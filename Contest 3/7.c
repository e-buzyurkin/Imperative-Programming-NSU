#include <stdio.h>
#include <stdlib.h>

int quicksort(int a[], int l, int r){
    int x, w;
    int i, j;
    i = l; j = r;
    x = a[(l + r)/2];
    do{
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
    while (i < j);
    if (l < j) quicksort(a, l, j);
    if (i < r) quicksort(a, i, r);
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);
    int a[n];
    for (int i = 0; i < n; i++){
        fscanf(f1, "%d", &a[i]);
    }

    quicksort(a, 0, n-1);

    for (int i = 0; i < n; i++) fprintf(f2, "%d ", a[i]);

    fclose(f1);
    fclose(f2);

    return 0;
}
