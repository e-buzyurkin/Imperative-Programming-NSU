#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * concat(char * pref, char * suff){
    strcat(pref, suff);
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    char pref[100 * 10001] = "", suff[101];

    //fscanf(f1, "%s", &pref);

    for (int i = 0; i < n; i++){
        //for (int l = 0; l < 101; l++) suff[l] = '\0';
        fscanf(f1, "%s", &suff);
        concat(pref, suff);
    }
    fprintf(f2, "%s", pref);
    printf("%d", strlen(pref));
    fclose(f1);
    fclose(f2);

    return 0;
}


