#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE *f1, *f2;
    f1 = fopen("input.txt", "r");
    int n;
    fscanf(f1, "%d", &n);
    fclose(f1);
    long long count = 0;

    int cube = cbrt(n);
    int sq = sqrt(n);
    printf("%d", cube);
    for (int x = 1; x <= cube; x++)
        for (int y = x; y <= sq; y++){
            int end = n / (x * y);
            if (y <= end)
                count = count + (end - y + 1);
        }

    printf("count = %lld", count);
    f2 = fopen("output.txt", "w");
    fprintf(f2, "%lld", count);
    fclose(f2);
    return 0;
}
