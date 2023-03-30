#include <stdio.h>
#include <stdlib.h>

typedef struct OneLinkList{
    double value;
    int next;
} List;

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n, f;
    fscanf(f1, "%d %d", &n, &f);

    List a[n];

    for (int i = 0; i < n; i++){
        fscanf(f1, "%lf %d", &a[i].value, &a[i].next);
        //printf("%f %d\n", a[i].value, a[i].next);
    }


    int current = f;

    while (current != -1){
        fprintf(f2, "%0.3lf\n", a[current].value);
        current = a[current].next;
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
