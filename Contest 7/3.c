#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    unsigned long long p, q, m;
    double x;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%lld/%lld xor %llx", &p, &q, &m);
        x = (float) p / q;
        unsigned long long* temp = (unsigned long long*) &x;
        unsigned long long othertemp = (*temp) ^ (m);
        double res = *((double*)&othertemp);

        fprintf(f2, "%0.15g\n", res);
    }

    fclose(f1);

    fclose(f2);

    return 0;
}
