#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, count = 0;
    fscanf(f1, "%d", &n);
    int b[n];



    for (int i=0; i < n; i++){
        fscanf(f1, "%d", &b[i]);
    }

    for (int i=0; i < n; i++){
        count = 0;
        for (int j = i + 1; j < n; j++){
            if (b[i] > b[j]) count++;
        }
        fprintf(f2, "%d ", count);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
