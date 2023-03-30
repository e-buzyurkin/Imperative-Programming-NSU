#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct key{
    int key;
    int link;
};

struct string{
    char s[10];
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    struct key keys[n];
    struct string values[n];

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %s", &keys[i].key, &values[i].s);
        keys[i].link = i;
    }
    //printf("scanned\n");
    struct key helper;

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (keys[i].key <= keys[j].key){
                helper = keys[i];
                keys[i] = keys[j];
                keys[j] = helper;
            }
        }
    }
    //printf("sorted\n");
    for (int i = n - 1; i >= 0; i--){
        fprintf(f2, "%d %s\n", keys[i].key, values[keys[i].link].s);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
