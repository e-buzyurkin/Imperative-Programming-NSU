#include <stdio.h>
#include <stdlib.h>

int merge ( const int *a , int ak , const int *b , int bk , int *res ){
    res = malloc(sizeof(int) * (ak + bk));
    int i = 0, j = 0, k = 0;

    while (i < ak && j < bk){
        if (a[i] < b[j])
            res[k++] = a[i++];
        else
            res[k++] = b[j++];
    }

    while (i < ak)
        res[k++] = a[i++];

    while (j < bk)
        res[k++] = b[j++];

    return res;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int n, m;
    fread(&n, sizeof(int), 1, f1);
    fread(&m, sizeof(int), 1, f1);

    int a[n];
    fread(&a, sizeof(int), n, f1);

    int b[m];
    fread(&b, sizeof(int), m, f1);

    int *res;
    res = merge(a, n, b, m, res);

    for (int i = 0; i < n + m; i++){
        fwrite(&res[i], sizeof(int), 1, f2);
    }

    free(res);

    fclose(f1);
    fclose(f2);

    return 0;
}
