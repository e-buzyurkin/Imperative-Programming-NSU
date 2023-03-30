#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct LongNum{
    int len;
    int num[3000];
};

struct LongNum convert(int n){
    struct LongNum res;
    int l = 0;
    for (int i = 0; i < 3000; i++){
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

struct LongNum OneDigitMultiply(struct LongNum n, int x){
    int ed = 0;
    for (int i = 0; i <= n.len; i++){
        n.num[i] = n.num[i] * x + ed;
        ed = n.num[i] / 10;
        n.num[i] = n.num[i] % 10;
    }
    if (n.num[n.len] > 0) n.len++;
    return n;
};

struct LongNum multiplyBy10(struct LongNum n){
    for (int i = n.len; i > 0; i--){
        n.num[i] = n.num[i-1];
    }
    n.num[0] = 0; n.len++;
    return n;
};

struct LongNum multiply(struct LongNum x, struct LongNum y){
    struct LongNum res, temp;
    res = convert(0); temp = convert(0);

    int maxlen;
    if (x.len >= y.len) maxlen = x.len;
    else maxlen = y.len;

    for (int i = 0; i < y.len; i++){
        temp = OneDigitMultiply(x, y.num[i]);
        for (int j = 0; j < i; j++) temp = multiplyBy10(temp);
        res = plus(res, temp);
    }
    return res;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    struct LongNum res, x;
    res = convert(1);

    for (int i = 2; i <= n; i++){
        x = convert(i);
        res = multiply(res, x);
    }

    for (int i = res.len-1; i >= 0; i--){
        fprintf(f2, "%d", res.num[i]);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
