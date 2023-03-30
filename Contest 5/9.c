#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define max_size 1009
#define decider 1008

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

struct LongNum minus(struct LongNum x, struct LongNum y){
    struct LongNum res;
    res = convert(0); res.len = 1;
    int maxlen;

    if (x.len >= y.len) maxlen = x.len;
    else maxlen = y.len;

    for (int i = 0; i < maxlen; i++){
        res.num[i] += (x.num[i] - y.num[i]);
        if (res.num[i] < 0){
            res.num[i] += 10;
            res.num[i + 1]--;
        }
    }

    if (res.num[maxlen] != -1){
        for (int i = decider - 1; i >= 0; i--)
            if (res.num[i] != 0){
                res.len = i + 1;
                break;
            }
        return res;
    }
    else{
        res = convert(0);
        res.num[decider] = 1;
        for (int i = 0; i < maxlen; i++){
            res.num[i] += (y.num[i] - x.num[i]);
            if (res.num[i] < 0){
                res.num[i] += 10;
                res.num[i + 1]--;
            }
        }
        for (int i = decider - 1; i >= 0; i--)
            if (res.num[i] != 0){
                res.len = i + 1;
                break;
            }
        return res;
    }

};

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

    for (int i = 0; i < y.len; i++){
        temp = OneDigitMultiply(x, y.num[i]);
        for (int j = 0; j < i; j++) temp = multiplyBy10(temp);
        res = plus(res, temp);
    }
    res.len = 1;
    for (int i = decider - 1; i >= 0; i--)
        if (res.num[i] != 0){
            res.len = i + 1;
            break;
        }
    if (x.num[decider] != y.num[decider]) res.num[decider] = 1;
    return res;
};

struct LongNum divide(struct LongNum x, struct LongNum y){
    struct LongNum res, temp, temp2;
    res = convert(0); res.len = 0;
    temp = convert(0);

    if (minus(x, y).num[decider] == 1 || y.len > x.len){
        res = convert(0);
        res.len = 1;
        return res;
    }
    //выделяем основу
    for (int i = 0; i < y.len; i++){
        temp.num[i] = x.num[x.len - y.len + i];
    }
    temp.len = y.len;

    int helper = 0;

    //если число с таким же кол-вом знаком не подошло, то возьмем еще один знак
    if (minus(temp, y).num[decider] == 1){
        temp = multiplyBy10(temp);
        temp.num[0] = x.num[x.len - y.len - 1];
        temp.len++;
        helper = 1;
    }


    // теперь записываем первую цифру в ответ
    for (int i = 9; i >= 0; i--){
        temp2 = OneDigitMultiply(y, i);
        if (minus(temp, temp2).num[decider] == 0){
            res.num[0] = i;
            res.len++;
            temp = minus(temp, temp2);
            break;
        }
    }

    //дальше идем по числу, пока оно не закончится
    for (int i = x.len - y.len - 1 - helper; i >= 0; i--){
        temp = multiplyBy10(temp);
        temp.num[0] = x.num[i];
        for (int j = 9; j >= 0; j--){
            temp2 = OneDigitMultiply(y, j);
            if (minus(temp, temp2).num[decider] == 0){
                res.num[res.len] = j;
                res.len++;
                temp = minus(temp, temp2);
                break;
            }
        }
    }
    return res;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    void printRes(struct LongNum res){
        if (res.num[decider] == 1) fprintf(f2, "-");
        for (int i = 0; i < res.len; i++){
            fprintf(f2, "%d", res.num[i]);
        }
        fprintf(f2, "\n");
    }

    struct LongNum readNum(char *line){
        struct LongNum n;
        n = convert(0); n.len = 0;
        int j = 0;
        if (line[0] == '-') n.num[decider] = 1;
        for (int i = strlen(line) - 1; i >= n.num[decider]; i--){
            n.num[j] = CharToInt(line[i]);
            n.len++;
            j++;
        }
        return n;
    };

    struct LongNum x, y, res;
    char s[1009];

    fscanf(f1, "%s", &s);
    x = readNum(s);
    fscanf(f1, "%s", &s);
    y = readNum(s);

    res = divide(x, y);
    printRes(res);

    fclose(f1);
    fclose(f2);

    return 0;
}
