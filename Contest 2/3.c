#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int neg_count = 0, zero_count = 0, pos_count = 0;
    int x, n;

    fscanf(f1, "%d", &n);

    for (int i = 1; i <= n; i++){
        fscanf(f1, "%d", &x);
        if (x > 0) pos_count++;
        else
        if (x == 0) zero_count++;
        else
        if (x < 0) neg_count++;
    }
    //printf("%d %d %d", neg_count, zero_count, pos_count);
    double pos_ratio = (float)pos_count / n;
    double zero_ratio = (float)zero_count / n;
    double  neg_ratio = (float)neg_count / n;

    fprintf(f2, "%0.5lf %0.5lf %0.5lf", neg_ratio, zero_ratio, pos_ratio);

    fclose(f1);
    fclose(f2);

    return 0;
}
