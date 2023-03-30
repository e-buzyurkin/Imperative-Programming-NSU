#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d\n", &n);

    int r[n][n];

    char c;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fscanf(f1, "%c", &c);
            c = c - '0';
            r[i][j] = c;
        }
        fscanf(f1, "%c", &c);
    }

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                r[i][j] = r[i][j] || (r[i][k] && r[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
        r[i][i] = 1;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            fprintf(f2, "%d", r[i][j]);
        fprintf(f2, "\n");
    }

    fclose(f1);
    fclose(f2);
    return 0;
}