#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StringList{
    char *str;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    int t, k;
    int j = 0, count;
    char c;

    struct StringList a[n];

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %d", &t, &k);
        //printf("%d %d\n", t, k);
        switch (t){
            case 0:
                a[j].str = malloc((k + 1) * sizeof(char));
                if (a[j].str == NULL) exit(1);
                fscanf(f1, "%s", a[j].str);
                //printf("%s\n", s);
                //printf("|%c| \n", a[j].str[0]);
                j++;
                break;
            case 1:
                //printf("del |%c|\n", a[k].str[0]);
                free(a[k].str);
                //*a[k].str = NULL;
                //printf("del |%c|\n", a[k].str[0]);
                break;
            case 2:
                fprintf(f2, "%s", a[k].str);
                fprintf(f2, "\n");
                break;
            case 3:
                fscanf(f1, " %c", &c);
                count = 0;
                for (int l = 0; l < strlen(a[k].str); l++) if (c == a[k].str[l]) count++;
                fprintf(f2, "%d\n", count);
        }
        //printf("%d %d\n", t, k);
    }
    //printf("endloop\n");
    //for (int i = 0; i <= j; i++) if (*a[i].str != NULL) free(a[i].str);
    fclose(f1);
    fclose(f2);

    return 0;
}
