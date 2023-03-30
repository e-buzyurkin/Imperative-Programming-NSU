#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    unsigned long long a[n];
    for (int i = 0; i < n; i++) fscanf(f1, "%llx", &a[i]);

    int count = 0;

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if ((a[i] & a[j]) == 0) count++;
        }
    }

    fprintf(f2, "%d", count);

    fclose(f1);
    fclose(f2);

    return 0;
}
