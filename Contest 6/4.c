#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List{
    int prev;
    int value;
    int next;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int t;
    fscanf(f1, "%d", &t);

    int n, f, l, q;

    int operation, next, current, g;

    struct List *a;

    for (int i = 0; i < t; i++){
        fscanf(f1, "%d %d %d %d", &n, &f, &l, &q);

        a = malloc((n + q + 2) * sizeof(struct List));
        if (a == NULL) return 1;

        a[0].next = f + 1; a[0].prev = l + 1; a[0].value = -1;
        for (int l = 1; l <= n; l++){
            fscanf(f1, "%d %d %d", &a[l].value, &a[l].next, &a[l].prev);
            a[l].next++; a[l].prev++;
        }
        g = n + 1;
        for (int j = 0; j < q; j++){
            fscanf(f1, "%d %d ", &operation, &next);
            next++;
            switch(operation){
                case 1:
                    fscanf(f1, "%d", &a[g].value);

                    a[g].prev = next;
                    a[g].next = a[next].next;

                    a[a[next].next].prev = g;
                    a[next].next = g;

                    fprintf(f2, "%d\n", g - 1);
                    g++;
                    break;
                case -1: // next = 0
                    fscanf(f1, "%d", &a[g].value);

                    a[g].next = next;
                    a[g].prev = a[next].prev;

                    a[a[next].prev].next = g;
                    a[next].prev = g;

                    fprintf(f2, "%d\n", g - 1);
                    g++;
                    break;
                case 0:
                    fprintf(f2, "%d\n", a[next].value);
                    a[a[next].prev].next = a[next].next;
                    a[a[next].next].prev = a[next].prev;
                    break;
            }
        }
        fprintf(f2, "===\n");

        current = a[0].next;

        while (current != 0){
            fprintf(f2, "%d\n", a[current].value);
            current = a[current].next;
        }

        fprintf(f2, "===\n");

        free(a);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
