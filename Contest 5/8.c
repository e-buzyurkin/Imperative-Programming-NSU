#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define max_size 301
#define decider 300

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
    if (res.len == 1 && res.num[0] == 0) res.num[decider] = 0;
    return res;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    void printRes(struct LongNum res){
        if (res.num[decider] == 1) fprintf(f2, "-");
        for (int i = res.len-1; i >= 0; i--){
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

    int n, t, r;
    fscanf(f1, "%d", &n);

    char x[301];

    struct LongNum nums[n + 1];
    int m1, m2;
    struct LongNum res;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d", &t);
        switch(t){
            case 0: // const
                fscanf(f1, "%s", &x);
                nums[i] = readNum(x);
                break;
            case 1: // plus
                fscanf(f1, "%d %d", &m1, &m2);
                if (nums[m1].num[decider] == nums[m2].num[decider]){
                    res = plus(nums[m1], nums[m2]);
                    res.num[decider] = nums[m1].num[decider];
                }
                else{
                    if (nums[m1].num[decider] == 1) res = minus(nums[m2], nums[m1]);
                    else if (nums[m2].num[decider] == 1) res = minus(nums[m1], nums[m2]);
                }
                nums[i] = res;
                break;
            case 2: // minus
                fscanf(f1, "%d %d", &m1, &m2);
                if (nums[m1].num[decider] == 0 && nums[m2].num[decider] == 0)
                    res = minus(nums[m1], nums[m2]);
                else if (nums[m1].num[decider] == 1 && nums[m2].num[decider] == 1){
                    res = minus(nums[m2], nums[m1]);
                    //res.num[decider] = 1;
                }
                else {
                    res = plus(nums[m1], nums[m2]);
                    if (nums[m1].num[decider] == 1) res.num[decider] = 1;
                }
                nums[i] = res;
                break;
            case 3: // multiply
                fscanf(f1, "%d %d", &m1, &m2);
                res = multiply(nums[m1], nums[m2]);
                nums[i] = res;
                break;
        }
    }

    for (int i = 0; i < n; i++)
        printRes(nums[i]);

    fclose(f1);
    fclose(f2);

    return 0;
}
