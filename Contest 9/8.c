#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binary_search(long long x, long long *a, int left, int right){
    //int left = -1;
    //int right = n;
    int middle;
    while (left < right - 1){
        middle = (left + right) / 2;
        if (a[middle] < x) left = middle;
        else right = middle;
    }
    return right;

}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    long long a[n];
    for (int i = 0; i < n; i++)
        fscanf(f1, "%lld", &a[i]);

    int switchorder = 0;
    long long dx[n];
    long long temp;
    for (int i = 0; i < n - 1; i++){
        temp = a[i + 1];
        temp -= a[i];
        dx[i] = temp;
        if (temp <= 0){
            switchorder = i;
        }
    }
    int q;
    fscanf(f1, "%d", &q);

    int c;
    long long mindif, curdif;
    int minind;
    long long minf;
    int curf;

    for (int j = 0; j < q; j++){
        fscanf(f1, "%d", &c);
/*
        minf = a[0];
        minind = 0;
        for (int i = 1; i < n; i++){
            curf = c * i;
            curf += a[i];

            if (curf < minf){
                minind = i;
                minf = curf;
            }
        }
        fprintf(f2, "c = %d| %d ", c, minind);
*/
        int start = 0;
        //if (c < 0) start = switchorder;
/*
        for (int i = start; i < n; i++){
            curdif = dx[i] + c;
            if (curdif >= 0){
                minind = i;
                break;
            }

        }

        fprintf(f2, "%d\n", minind);
*/

        if (c < 0){
            minind = binary_search(-c, dx, switchorder - 1, n - 1);
        }
        else
            minind = binary_search(-c, dx, -1, switchorder + 1);
        fprintf(f2, "%d\n", minind);
    }


    fclose(f1);
    fclose(f2);

    return 0;
}
