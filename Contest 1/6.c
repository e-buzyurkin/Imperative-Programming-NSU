#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *f1, *f2;
    int n, x;
    int min_elem = 10001, min_num = 0, max_elem = -10001, max_num = 0;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d", &n);

    f2 = fopen("output.txt", "w");

    for (int i=1; i<=n; i++){
        fscanf(f1, "%d", &x);
        if (x < min_elem){
            min_elem = x;
            min_num = i;
        }
        if (x > max_elem){
            max_elem = x;
            max_num = i;
        }
    }
    f2 = fopen("output.txt", "w");
    fclose(f1);
    fprintf(f2, "%d %d %d %d", min_elem, min_num, max_elem, max_num);
    fclose(f2);
    return 0;
}
