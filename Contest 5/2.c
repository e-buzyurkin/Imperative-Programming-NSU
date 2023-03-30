#include <stdio.h>
#include <stdlib.h>

/*double c(int n, int k){
    double upper = 1; for (int i = n - k + 1; i <= n; i++) upper *= i;
    double lower1 = 1; for (int i = 2; i <= k; i++) lower1 *= i;
    double lower2 = 1;

    double res;
    res = upper / lower1;

    return res;
}*/

double C (int n, int k) {
	double res = 1;
	for (int i = 1; i <= k; i++)
		res = res * (n - k + i) / i;
	return res;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int q;
    fscanf(f1, "%d", &q);

    int n, k;
    double res;

    for (int i = 0; i < q; i++){
        fscanf(f1, "%d %d", &n, &k);
        res = C(n, k);
        fprintf(f2, "%0.10g\n", res);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
