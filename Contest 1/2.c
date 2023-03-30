#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>


int main(){
    FILE *f1, *f2;
    int x, y, z;
    int sq;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d %d %d", &x, &y, &z);
    fclose(f1);
    f2 = fopen("output.txt", "w");
    if (x > 0 and y > 0 and z > 0){
        sq = 2 * (x * y + x * z + y * z);
    }
    else{
        if (not(x > 0)) sq = -1;
        else if (not(y > 0)) sq = -2;
        else if (not(z > 0)) sq = -3;
    }
    fprintf(f2, "%d", sq);
    fclose(f2);
    return 0;
}
