#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int contains(int x, int *a, int n){
    for (int i = 0; i < n; i++){
        if (a[i] == x)
            return 1;
    }
    return 0;
}

int main(){
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, m;
    fscanf(f1, "%d %d", &n, &m);

    int a[n + 1][n + 1];

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            a[i][j] = 0;
        }
    }

    int u, v;

    for (int i = 0; i < m; i++){
        fscanf(f1, "%d %d", &u, &v);
        if (a[v][u] == 0){
            a[v][u] = 1;
            a[0][v]++;
        }
    }
    
    int p[n];
    int cnt_p = 0;

    int cnt_v = n;

    int flag = 0;

    while (cnt_p < cnt_v){

        for (int i = 1; i <= n; i++){
            if (a[0][i] == 0 && a[i][0] == 0){
                v = i;
                flag = 1;
                break;
            }
        }

        if (flag == 0){
            fprintf(f2, "bad course");
            goto ending;
        }

        p[cnt_p] = v;
        cnt_p++;
        a[v][0] = 1;

        for (int i = 1;  i <= n; i++){
            if (a[i][v] == 1){
                a[i][v] = 0;
                a[0][i]--;
            }
        }
        flag = 0;
    }

    for (int i = 0; i < cnt_p; i++)
        fprintf(f2, "%d ", p[i]);

    ending:

    fclose(f1);
    fclose(f2);
    return 0;
}
