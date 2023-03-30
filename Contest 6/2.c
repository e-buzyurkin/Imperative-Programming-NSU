#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List{
    char value[10];
    int next;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int t;
    fscanf(f1, "%d", &t);

    int n, f, q;

    int operation, next, current, g;

    struct List *a;

    for (int i = 0; i < t; i++){
        printf("i = %d\n", i);
        fscanf(f1, "%d %d %d", &n, &f, &q);
        printf(" %d %d %d\n", n, f, q);
        a = malloc((n + q + 1) * sizeof(struct List));
        if (a == NULL) return 1;
        for (int l = 0; l < n; l++){
            printf("start\n");
            fscanf(f1, "%s %d", a[l].value, &a[l].next);
            printf("%c %d\n", a[l].value[0], a[l].next);
        }
        printf("finish\n");
        g = n;
        for (int j = 0; j < q; j++){
            printf("opers\n");
            fscanf(f1, "%d %d ", &operation, &next);
            printf("%d %d\n", operation, next);
            //printf("|%c|\n", a[g].value[0]);
            switch(operation){
                case 0:
                    a[g].next = next;
                    fscanf(f1, "%s", &a[g].value);
                    if (a[g].next == -1){
                        a[g].next = f;
                        f = g;
                    }
                    else{
                        if (a[a[g].next].next == -1){
                            a[a[g].next].next = g;
                            a[g].next = -1;
                        }
                        else{
                            int help = a[g].next; // 1
                            a[g].next = a[help].next;
                            a[help].next = g;

                        }
                    }
                    fprintf(f2, "%d\n", g);
                    g++;
                    break;
                case 1:
                    if (next != -1){
                        fprintf(f2, "%s", a[a[next].next].value);
                        a[next].next = a[a[next].next].next; // a[2].next
                        fprintf(f2, "\n");
                    }
                    else{
                        fprintf(f2, "%s", a[f].value);
                        f = a[f].next;
                        fprintf(f2, "\n");
                    }
                    break;
            }
        }
        fprintf(f2, "===\n");
        printf("===\n");
        current = f;
        printf("%d\n", f);
        for (int i = 0; i < n + q; i++) printf("|%d| ", a[i].next);
        printf("startprint\n");
        while (current != -1){
            fprintf(f2, "%s", a[current].value);
            fprintf(f2, "\n");
            current = a[current].next;
        }
        printf("endprint\n");
        fprintf(f2, "===\n");
        free(a);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
