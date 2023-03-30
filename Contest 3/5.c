#include <stdio.h>
#include <stdlib.h>

int criteria2(int *r, int m){
    for (int i = 1; i <= m; i++){
        if (r[i] == 0) return 0;
    }
    return 1;
}

int criteria3(int *r, int m){
    for (int i = 1; i <= m; i++){
        if (r[i] > 0){
            for (int j = i + 1; j <= m; j++){
                if (r[i] == r[j]) return 0;
            }
        }
    }
    return 1;
}

int criteria4(int *r, int m){
    int decider = 0;
    for (int i = 1; i <= m; i++){
        decider = 0;
        for (int j = 1; j <= m; j++){
            if (r[j] == i) decider = 1;
        }
        if (decider == 0) return 0;
    }
    return 1;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, m;
    fscanf(f1, "%d %d", &m, &n);
    int r[m + 1];

    for (int i = 0; i <= m; i++) r[i] = 0;

    int x, y;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %d", &x, &y);
        if (r[x] == 0) r[x] = y;
        else{
            fprintf(f2, "%d", 0);
            return 0;
        }
    }

    fprintf(f2, "%d ", 1);
    if (criteria2(r, m) == 1) fprintf(f2, "%d ", 2);
    if (criteria3(r, m) == 1) fprintf(f2, "%d ", 3);
    if (criteria4(r, m) == 1) fprintf(f2, "%d ", 4);
    if (criteria3(r, m) == 1 && criteria4(r, m) == 1) fprintf(f2, "%d", 5);

    fclose(f1);
    fclose(f2);

    return 0;
}

