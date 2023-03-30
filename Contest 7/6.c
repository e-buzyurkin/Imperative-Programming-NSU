#include <stdio.h>
#include <stdlib.h>

struct links{
    int next;
    int prev;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, k;
    fscanf(f1, "%d %d", &n, &k);
    struct links a[n + 1];

    for (int i = 1; i <= n; i++){
        a[i].next = i + 1;
        a[i].prev = i - 1;
    }

    a[n].next = 1;
    a[1].prev = n;

    //for (int i = 1; i <= n; i++) printf("(%d %d) ", a[i].prev, a[i].next);
    int counter = 1;
    int cur = 1;

    while (n > 0){
        if (counter % k == 0){
            a[a[cur].prev].next = a[cur].next;
            a[a[cur].next].prev = a[cur].prev;
            fprintf(f2, "%d\n", cur);
            n--;
        }
        cur = a[cur].next;
        counter++;
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
