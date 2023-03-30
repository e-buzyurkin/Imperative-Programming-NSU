#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define max_size 3000

int CharToInt(char c){
    int num = (int) c;
    return num - 48;
}

struct LongNum{
    int len;
    int num[max_size];
};

struct LongNum convert(int n){
    struct LongNum res;
    int l = 0;
    for (int i = 0; i < max_size; i++){
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

    char x[1001];
    char y[1001];

    fscanf(f1, "%s", &x);
    printf("%s\n", x);
    fscanf(f1, "%s", &y);
    printf("%s\n", y);

    struct LongNum res, m1, m2;
    m1 = convert(0); m1.len = 0;
    m2 = convert(0); m2.len = 0;

    int j = 0;
    for (int i = strlen(x) - 1; i >= 0; i--){
        m1.num[j] = CharToInt(x[i]);
        m1.len++;
        j++;
    }

    j = 0;
    for (int i = strlen(y) - 1; i >= 0; i--){
        m2.num[m2.len] = CharToInt(y[i]);
        m2.len++;
    }

    res = multiply(m1, m2);

    for (int i = res.len-1; i >= 0; i--){
        fprintf(f2, "%d", res.num[i]);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}