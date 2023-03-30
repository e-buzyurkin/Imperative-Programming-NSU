#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    void printTime(int h, int m, int s){
        fprintf(f2, "%02d:%02d:%02d\n", h, m, s);
        return 0;
    }

    int n;
    fscanf(f1, "%d", &n);

    int h, m, s;
    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %d %d", &h, &m, &s);
        printTime(h, m, s);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}

