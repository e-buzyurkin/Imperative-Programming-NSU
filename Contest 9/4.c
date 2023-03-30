#include <stdio.h>
#include <stdlib.h>

static int temp[500000];

void merge(int *a1, int len1, int *a2, int len2, int *res){
    int i = 0, j = 0, k = 0;
    int x;
    while ((i < len1) || (j < len2)){
        if (i == len1)
            x = a2[j++];
        else if (j == len2)
            x = a1[i++];
        else if (a1[i] < a2[j])
            x = a1[i++];
        else
            x = a2[j++];
        res[k++] = x;
    }
}

void merge_sort(int *a, int l, int r){
    int i, m;
    m = (l + r) / 2;
    if (l < m)
        merge_sort(a, l, m);
    if (m + 1 < r)
        merge_sort(a, m + 1, r);
    merge(&a[l], m - l + 1, &a[m + 1], r - m, &temp[l]);
    for (i = l; i <= r; i++){
        a[i] = temp[i];
    }
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);

    int a[n];
    fread(&a, sizeof(int), n, f1);

    merge_sort(a, 0, n - 1);

    fwrite(&a, sizeof(int), n, f2);

    fclose(f1);
    fclose(f2);

    return 0;
}
