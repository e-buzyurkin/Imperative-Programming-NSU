#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    char p;
    fscanf(f1, "%d", &n);
    //fscanf(f1, "%d", &n);
    char start[101];
    char c;

    for (int i = 0; i < n; i++){
        int j = 0;
        for (int l = 0; l < 101; l++) start[l] = '\0';
        fscanf(f1, "%s", &start);
        reverse(start, strlen(start));
        fprintf(f2, "%s\n", start);
    }
    printf("%s", start);
    fclose(f1);
    fclose(f2);

    return 0;
}

void reverse(char *start, int len){
    char e;
    int half = len / 2;
    for (int i = 0; i < half; i++){
        e = start[i]; start[i] = start[len - 1 - i]; start[len - 1 - i] = e;
    }
}
