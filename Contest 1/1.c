#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f1, *f2;
    int n;
    int sum = 0;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d", &n);
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    fclose(f1);
    f2 = fopen("output.txt", "w");
    fprintf(f2, "%d", sum);
    fclose(f2);
    return 0;
}
