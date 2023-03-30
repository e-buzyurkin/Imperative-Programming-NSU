#include <stdio.h>
#include <stdlib.h>

struct LongNum{
    int len;
    int num[500];
};

struct LongNum convert(int n){
    struct LongNum res;
    int l = 0;
    for (int i = 0; i < 500; i++){
        res.num[i] = n % 10;
        if (n != 0) l++;
        n /= 10;

    }
    res.len = l;
    return res;
};

struct LongNum plus(struct LongNum x, struct LongNum y){
    struct LongNum res;
    res = convert(0);
    int maxlen;
    if (x.len >= y.len) maxlen = x.len;
    else maxlen = y.len;

    for (int i = 0; i < maxlen; i++){
        res.num[i] += x.num[i] + y.num[i];
        res.num[i + 1] += res.num[i] / 10;
        res.num[i] = res.num[i] % 10;
    }

    if (res.num[maxlen] > 0) res.len = maxlen + 1;
    else res.len = maxlen;
    return res;
}



int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    struct LongNum x1, x2, cur;

    x1 = convert(1);
    x2 = convert(1);

    for (int i = 3; i <= n; i++){
        cur = plus(x1, x2);
        x1 = x2;
        x2 = cur;
    }

    if (n == 1 || n == 2) fprintf(f2, "1");
    else
    for (int i = cur.len-1; i >= 0; i--){
        fprintf(f2, "%d", cur.num[i]);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
