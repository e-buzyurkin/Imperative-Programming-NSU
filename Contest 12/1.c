#include <stdio.h>
#include <stdlib.h>

void heapify(int *a, int n, int given_index){
    int max_index = given_index;   
    int l = 2 * max_index + 1;
    int r = 2 * max_index  + 2;

    if (l < n && a[l] > a[max_index])
        max_index = l;

    if (r < n && a[r] > a[max_index])
        max_index = r;

    if (max_index != given_index){
        int helper = a[given_index];
        a[given_index] = a[max_index];
        a[max_index] = helper;

        heapify(a, n, max_index);
    }
}

void heap_sort(int *a, int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i >= 0; i--){
        int helper = a[0];
        a[0] = a[i];
        a[i] = helper;
        
        heapify(a, i, 0);
    }
}

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.bin", "rb");
    f2 = fopen("output.bin", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);

    int *a;
    a = malloc(n * sizeof(int));

    fread(a, sizeof(int), n, f1);

    heap_sort(a, n);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    fwrite(a, sizeof(int), n, f2);

    fclose(f1);
    fclose(f2);
    return 0;
}