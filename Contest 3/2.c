#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, j, cur_sum = 0;
    fscanf(f1, "%d", &n);
    int a[n+1];

    for (int i=1; i<=n; i++){
        fscanf(f1, "%d", &a[i]);
    }

    for (int k=1; k<=n; k++){
        cur_sum = 0;
        j = k;
        while (j <= n){
            if (j <= n) cur_sum += a[j];
            j += k;
        }
        fprintf(f2, "%d\n", cur_sum);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
