#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f1, *f2;
    int n, decider = 0;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d", &n);
    fclose(f1);
    f2 = fopen("output.txt", "w");
    int k = sqrt(n);
    if (n == 1) fprintf(f2, "NO");
    else{
    for (int i=2; i<=k; i++){
        if (n % i == 0){
            fprintf(f2, "NO");
            decider = 1;
            break;
        }
    }
    if (decider == 0)
        fprintf(f2, "YES");
    }
    fclose(f2);
    return 0;
}
