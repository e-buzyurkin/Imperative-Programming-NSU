#include <stdio.h>
#include <stdlib.h>

void quicksort(int *a, int l, int r){
    int x, w;
    int i = l, j = r;
    x = a[(l + r) / 2];
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

int partition (int *a , int n , int pivot){
    int *res;
    res = malloc(sizeof(int) * (n + 1));
    int help[n];

    int left = 0, right = 0;
    int flagleft = 0;


    for (int i = 0; i < n; i++){
        if (a[i] < pivot){
            res[left] = a[i];
            left++;
        }
        else if (a[i] > pivot){
            help[right] = a[i];
            right++;
        }
        else if (a[i] == pivot){
            if (flagleft == 0){
                res[left] = a[i];
                left++;
                flagleft = 1;
            }
            else{
                help[right] = a[i];
                right++;
                flagleft = 0;
            }
        }
    }
    //quicksort(res, 0, left - 1);
    //quicksort(help, 0, right - 1);
    for (int i = 0; i < right; i++){
        res[i + left] = help[i];
    }
    res[n] = left;
    return res;
}



int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);

    int pivot;
    fread(&pivot, sizeof(int), 1, f1);

    int a[n];
    fread(&a, sizeof(int), n, f1);

    int *res;

    //for (int i = 0; i < n; i++) printf("%d ", a[i]);

    res = partition(a, n, pivot);

    fwrite(&res[n], sizeof(int), 1, f2);
    //for (int i = 0; i < n; i++)
    fwrite(res, sizeof(int), n, f2);



    free(res);

    fclose(f1);
    fclose(f2);

    return 0;
}
