#include <stdio.h>
#include <stdlib.h>

int compare(const void * x1, const void * x2){
    return ( *(int*)x1 - *(int*)x2 );
}

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

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);
    
    int a[n];
    for (int i = 0; i < n; i++)
        fscanf(f1, "%d", &a[i]);

    int q;
    fscanf(f1, "%d", &q);

    int b[q];
    for (int i = 0; i < q; i++)
        fscanf(f1, "%d", &b[i]);

    qsort(a, n, sizeof (int), compare);
    qsort(b, q, sizeof (int), compare);
    
    int finalq = 0;
    int finalarr[n];


    for (int i = 0; i < n; i++){
        if (binary_search(a[i], b, q) == -1 && a[i] != a[i - 1]){
            finalarr[finalq] = a[i];
            finalq++;
        }
    }

    fprintf(f2, "%d\n", finalq);
    for (int i = 0; i < finalq; i++){
        fprintf(f2, "%d ", finalarr[i]);
    }

    fclose(f1);
    fclose(f2);
    return 0;
}