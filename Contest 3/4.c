#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, l = 0, r = 0;
    fscanf(f1, "%d", &n);
    int a[n];

    for (int i = 0; i < n; i++)
        fscanf(f1, "%d", &a[i]);

    int max_s = -100000000000, cur_s = 0;

    for (int i = 0; i < n; i++){
        cur_s = 0;
        for (int j = i; j < n; j++){
            cur_s += a[j];
            if (cur_s > max_s){
                max_s = cur_s;
                l = i;
                r = j;
            }
            else if (cur_s == max_s){
                if (i < l){
                    l = i;
                    r = j;
                }
                else if (i == l){
                    if (j < r) r = j;
                }
            }
        }
    }
    fprintf(f2, "%d %d %d", l, r, max_s);

    fclose(f1);
    fclose(f2);

    return 0;
}
