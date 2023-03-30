#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define max_size 25003

int CharToInt(char c){
    int num = (int) c;
    return num - 48;
}

struct LongNum{
    int len;
    int *num;
};

struct LongNum minus(struct LongNum x, struct LongNum y){
    int maxlen;

    if (x.len >= y.len) maxlen = x.len;
    else maxlen = y.len;

    for (int i = 0; i < maxlen; i++){
        x.num[i] -= y.num[i];
        if (x.num[i] < 0){
            x.num[i] += 10;
            x.num[i + 1]--;
        }
    }
    //for (int i = 0; i < maxlen; i++) printf("%d", x.num[i]);
    //printf("\n");
    for (int i = maxlen - 1; i >= 0; i--){
        if (x.num[i] != 0){
            x.len = i + 1;
            break;
        }
    }
    return x;
};

struct LongNum OneDigitMultiply(struct LongNum n, int x){
    struct LongNum res;
    res.num = malloc(max_size * (sizeof(int)));
    int ed = 0;
    res.len = n.len;
    for (int i = 0; i <= n.len; i++){
        res.num[i] = n.num[i] * x + ed;
        ed = res.num[i] / 10;
        res.num[i] = res.num[i] % 10;
    }
    if (res.num[res.len] > 0) res.len++;
    return res;
};

/*struct LongNum multiplyBy10(struct LongNum n){
    struct LongNum res;
    res.num = malloc(max_size * (sizeof(int)));
    for (int i = n.len; i > 0; i--){
        res.num[i] = n.num[i-1];
    }
//    for (int i = n.len + 1)
    res.num[0] = 0; res.len = n.len + 1;
    return res;
};*/

int resNegative(struct LongNum x, struct LongNum y){
    int maxlen;
    if (x.len > y.len){
        maxlen = x.len;
        for (int i = y.len; i < x.len; i++) y.num[i] = 0;
    }
    else if (y.len > x.len){
        maxlen = y.len;
        for (int i = x.len; i < y.len; i++) x.num[i] = 0;
    }
    else maxlen = x.len;

    for (int i = maxlen - 1; i >= 0; i--){
        if (x.num[i] > y.num[i]) return 0;
        else if (x.num[i] == y.num[i]) continue;
        else return 1;
    }
    return 0;
};

struct LongNum divide(struct LongNum x, struct LongNum y){
    struct LongNum res, temp;
    res.num = malloc(max_size * sizeof(int));
    temp.num = malloc(max_size * sizeof(int));
    res.len = 0;
    // если x > y, то результат 0
    if (y.len > x.len || resNegative(x, y) == 1){
        res.num[0] = 0;
        res.len = 1;
        return res;
    }
    //for (int i = 0; i < x.len + 1; i++) temp.num[i] = 0;
    temp.num[y.len + 1] = 0;
    //создадим таблицу умножения для y
    struct LongNum multiTable[10];
    for (int i = 0; i < 10; i++){
        //multiTable[i].num = malloc(max_size * (sizeof(int)));
        multiTable[i] = OneDigitMultiply(y, i);
        multiTable[i].num[y.len + 1] = 0;
    }
    //for (int i = 0; i < 10; i++) printf("%d%d\n", multiTable[i].num[1], multiTable[i].num[0]);
    //выделяем основу
    for (int i = 0; i < y.len; i++){
        temp.num[i] = x.num[x.len - y.len + i];
    }
    temp.len = y.len;

    int helper = 0;
    //printf("%d%d\n", temp.num[1], temp.num[0]);
    //если число с таким же кол-вом знаком не подошло, то возьмем еще один знак
    if (resNegative(temp, y) == 1){
        for (int i = temp.len; i > 0; i--){
            temp.num[i] = temp.num[i-1];
        }
        temp.num[0] = 0; temp.len = temp.len + 1;
        temp.num[0] = x.num[x.len - y.len - 1];
        temp.len++;
        helper = 1;
    }

    // теперь записываем первую цифру в ответ
    for (int i = 9; i >= 0; i--){
        if (resNegative(temp, multiTable[i]) == 0){
            res.num[0] = i;
            res.len++;
            temp = minus(temp, multiTable[i]);
            break;
        }
    }

    //дальше идем по числу, пока оно не закончится
    for (int i = x.len - y.len - 1 - helper; i >= 0; i--){
        for (int i = temp.len; i > 0; i--){
            temp.num[i] = temp.num[i-1];
        }
        temp.num[0] = 0; temp.len = temp.len + 1;
        temp.num[0] = x.num[i];
        //printf("%d%d\n", temp.num[1], temp.num[0]);
        for (int j = 9; j >= 0; j--){
            if (resNegative(temp, multiTable[j]) == 0){
                //printf("%d%d %d %d %d\n", temp.num[1], temp.num[0], temp.len, temp.num[2], temp.num[3]);
                //printf("%d%d %d\n", multiTable[j].num[1], multiTable[j].num[0], multiTable[j].len);
                //printf("%d\n\n", resNegative(temp, multiTable[i]));
                /*if (j == 9){
                printf("%d%d%d%d%d%d\n", temp.num[5], temp.num[4], temp.num[3], temp.num[2], temp.num[1], temp.num[0]);
                printf("%d%d%d%d%d%d\n", multiTable[j].num[5], multiTable[j].num[4], multiTable[j].num[3], multiTable[j].num[2], multiTable[j].num[1], multiTable[j].num[0]);
                printf("%d\n", j);
                }*/
                res.num[res.len] = j;
                res.len++;
                temp = minus(temp, multiTable[j]);
                break;
            }
        }

    }
    for (int i = 0; i < 10; i++) free(multiTable[i].num);
    free(temp.num);
    return res;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    void printRes(struct LongNum res){
        for (int i = 0; i < res.len; i++){
            fprintf(f2, "%d", res.num[i]);
        }
        fprintf(f2, "\n");
    }

    struct LongNum x, y, res;
    res.num = malloc(max_size * sizeof(int));
    x.num = malloc(max_size * sizeof(int));
    y.num = malloc(max_size * sizeof(int));
    char s[25002];

    fscanf(f1, "%s", &s);

    x.len = 0;
    int len = strlen(s);
    for (int i = len - 1; i >= 0; i--){
        x.num[x.len] = CharToInt(s[i]);
        x.len++;
    }
    int x_maxsize = x.len;

    fscanf(f1, "%s", &s);
    y.len = 0;
    len = strlen(s);
    for (int i = len - 1; i >= 0; i--){
        y.num[y.len] = CharToInt(s[i]);
        y.len++;
    }

    for (int i = y.len; i < x_maxsize; i++) y.num[i] = 0;

    //printf("%d", resNegative(x, y));

    res = divide(x, y);
    printRes(res);

    free(res.num);
    free(x.num);
    free(y.num);
    fclose(f1);
    fclose(f2);

    return 0;
}
