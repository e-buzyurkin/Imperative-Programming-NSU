#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int l, r, k;
    int d;
    int a_last, a_over;
    int count = 0;
    fscanf(f1, "%d %d %d", &l, &r, &k);

    for (int i = l; i <= r; i++){

        int end_d = (r - i) / (k - 1);
        //printf("%d %d %d\n", i, end_d, count);
        for (int d = 1; d <= end_d; d++){
            a_last = i + (k - 1) * d;
            a_over = i + k * d;
            if (a_last <= r && a_over > r) ++count;
            //printf("%d %d %d %d %d\n", i, d, a_last, a_over, count);
        }
    }

    fprintf(f2, "%d", count);

    fclose(f1);
    fclose(f2);

    return 0;
}
