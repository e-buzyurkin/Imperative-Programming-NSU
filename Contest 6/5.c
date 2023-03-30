#include <stdio.h>
#include <stdlib.h>
#define k_max 1000001

struct Links{
    int first;
    int last;
};

struct ListElem{
    char value[10];
    int next;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");
    //printf("n\n");
    int n;
    fscanf(f1, "%d", &n);
    //printf("arrays\n");
    struct Links a[k_max];
    for (int i = 0; i < k_max; i++) a[i].first = -1;
    struct ListElem elems[n];
    int k;
    //printf("beforeloop\n");
    for (int i = 0; i < n; i++){
        fscanf(f1, "%d", &k);
        fscanf(f1, " %s", &elems[i].value);
        if (a[k].first == -1){
            a[k].first = i;
            elems[i].next = -1;
            a[k].last = i;
        }
        else{
            elems[a[k].last].next = i;
            elems[i].next = -1;
            a[k].last = i;
        }
    }

    int current;
    for (int k = 0; k < k_max; k++){
        if (a[k].first != -1){
            current = a[k].first;
            while (current != -1){
                fprintf(f2, "%d %s\n", k, elems[current].value);
                current = elems[current].next;
            }
        }
    }
    //for (int i = 0; i < n; i++) printf("%d %s ", elems[i].next, elems[i].value);
    //printf("\n");
    //for (int i = 0; i < n; i++) printf("(%d  %d)", i, a[i].first);
    fclose(f1);
    fclose(f2);

    return 0;
}
