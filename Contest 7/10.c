#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <intrin.h>

typedef unsigned long long bitword;

void bitsetZero (bitword *arr, int num){
    const unsigned long long one = 9223372036854775808;
    int leftx = 0;
    int leftid = 0;
    int rightx = num % 64;
    int rightid = num / 64;
    unsigned long long temp;
    if (leftid == rightid){
            temp = one >> (rightx - 1);
            for (int i = leftx; i < rightx; i++){
                arr[leftid] = arr[leftid] & ~temp;
                temp <<= 1;
            }
        }
        else if (rightid - leftid == 1){
            temp = 1ULL;
            for (int i = 0; i < 64 - leftx; i++){
                arr[leftid] = arr[leftid] & ~temp;
                temp <<= 1;
            }
            temp = one;
            for (int i = 0; i < rightx; i++){
                arr[rightid] = arr[rightid] & ~temp;
                temp >>= 1;
            }
        }
        else{
            for (int i = leftid + 1; i < rightid; i++) arr[i] = 0ULL;
            temp = 1ULL;
            for (int i = 0; i < 64 - leftx; i++){
                arr[leftid] = arr[leftid] & ~temp;
                temp <<= 1;
            }
            temp = one;
            for (int i = 0; i < rightx; i++){
                arr[rightid] = arr[rightid] & ~temp;
                temp >>= 1;
            }
        }
};

int bitsetGet (const bitword *arr , int idx){
    const unsigned long long one = 9223372036854775808;
    int id = idx / 64;
    int x = idx % 64;
    unsigned long long temp = arr[id];
    //printf("%d %d %d", id, x, temp);

    return ((temp & (one >> x)) != 0);
};

void bitsetSet (bitword *arr , int idx , int newval){
    const unsigned long long one = 9223372036854775808;
    int id = idx / 64;
    int x = idx % 64;
    if (newval == 1){
        arr[id] = arr[id] | (one >> x);
    }
    else arr[id] = arr[id] & ~(one >> x);
}
//установить в val значение всех k-ых битов для left <= k < right
void bitsetSetSeg(bitword *arr, int left, int right, int newval){
    const unsigned long long one = 9223372036854775808;
    int leftid = left / 64;
    int rightid = right / 64;
    int leftx = left % 64;
    int rightx = right % 64;
    unsigned long long temp;
    //printf("set %d %d %d %d\n", leftid, leftx, rightid, rightx);
    if (newval == 1){
        if (leftid == rightid){
            temp = one >> (rightx - 1);
            //printf("%d\n", 63 - rightx);
            for (int i = leftx; i < rightx; i++){
                arr[leftid] = arr[leftid] | temp;
                temp <<= 1;
            }
        }
        else if (rightid - leftid == 1){
            temp = 1ULL;
            for (int i = 0; i < 64 - leftx; i++){
                arr[leftid] = arr[leftid] | temp;
                temp <<= 1;
            }
            temp = one;
            for (int i = 0; i < rightx; i++){
                arr[rightid] = arr[rightid] | temp;
                temp >>= 1;
            }
        }
        else{
            for (int i = leftid + 1; i < rightid; i++) arr[i] = ULLONG_MAX;
            temp = 1ULL;
            for (int i = 0; i < 64 - leftx; i++){
                arr[leftid] = arr[leftid] | temp;
                temp <<= 1;
            }
            temp = one;
            for (int i = 0; i < rightx; i++){
                arr[rightid] = arr[rightid] | temp;
                temp >>= 1;
            }
        }
    }
    else{
        if (leftid == rightid){
            temp = one >> (rightx - 1);
            for (int i = leftx; i < rightx; i++){
                arr[leftid] = arr[leftid] & ~temp;
                temp <<= 1;
            }
        }
        else if (rightid - leftid == 1){
            temp = 1ULL;
            for (int i = 0; i < 64 - leftx; i++){
                arr[leftid] = arr[leftid] & ~temp;
                temp <<= 1;
            }
            temp = one;
            for (int i = 0; i < rightx; i++){
                arr[rightid] = arr[rightid] & ~temp;
                temp >>= 1;
            }
        }
        else{
            for (int i = leftid + 1; i < rightid; i++) arr[i] = 0ULL;
            temp = 1ULL;
            for (int i = 0; i < 64 - leftx; i++){
                arr[leftid] = arr[leftid] & ~temp;
                temp <<= 1;
            }
            temp = one;
            for (int i = 0; i < rightx; i++){
                arr[rightid] = arr[rightid] & ~temp;
                temp >>= 1;
            }
        }
    }
}

//посчитать, сколько битов равно единице на отрезке left <= k < right
int bitsetCount(const bitword *arr, int left, int right){
    const unsigned long long one = 9223372036854775808;
    int count = 0;
    int leftid = left / 64;
    int rightid = right / 64;
    int leftx = left % 64;
    int rightx = right % 64;
    unsigned long long temp;
    //printf("count %d %d %d %d\n", leftid, leftx, rightid, rightx);
    //printf("%d %d %d %d\n", leftid, leftx, rightid, rightx);
    if (leftid == rightid){
        temp = arr[leftid];
        temp = temp >> (64 - rightx);
        for (int i = leftx; i < rightx; i++){
            count += (1 & temp);
            temp = temp >> 1;
        }
        //printf("%d\n", count);
    }
    else if (rightid - leftid == 1){
            temp = arr[leftid];
            //temp = temp >> (64 - rightx);
            for (int i = leftx; i < 64; i++){
                count += (1 & temp);
                temp = temp >> 1;
            }
            temp = arr[rightid];
            temp >>= (64 - rightx);
            for (int i = 0; i < rightx; i++){
                count += (1 & temp);
                temp = temp >> 1;
            }
        }
    else{
        for (int i = leftid + 1; i < rightid; i++){
            /*temp = arr[i];
            for (; temp; temp >>= 1)
                count += temp & 1;*/
            count += __builtin_popcountll(arr[i]);
        }
        temp = arr[leftid];
        //temp = temp >> (64 - rightx);
        for (int i = leftx; i < 64; i++){
            count += (1 & temp);
            temp = temp >> 1;
        }
        temp = arr[rightid];
        temp >>= (64 - rightx);
        for (int i = 0; i < rightx; i++){
            count += (1 & temp);
            temp = temp >> 1;
        }
    }

    return count;
}


int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    bitword *arr;

    int size = 20000000 / 64 + 1;
    arr = malloc((size + 1) * sizeof(unsigned long long));

    int operation, newval, left, right, idx, temp;
    int cnt;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d", &operation);
        switch(operation){
            case 0:
                fscanf(f1, "%d", &size);
                bitsetZero(arr, size);
                break;
            case 1:
                fscanf(f1, "%d", &idx);
                temp = bitsetGet(arr, idx);
                fprintf(f2, "%d\n", temp);
                break;
            case 2:
                fscanf(f1, "%d %d", &idx, &newval);
                bitsetSet(arr, idx, newval);
                break;
            case 3:
                fscanf(f1, "%d %d %d", &left, &right, &newval);
                bitsetSetSeg(arr, left, right, newval);
                break;
            case 4:
                fscanf(f1, "%d %d", &left, &right);
                cnt = bitsetCount(arr, left, right);
                fprintf(f2, "%d\n", cnt);
                break;
        }
    }


    free(arr);

    fclose(f1);
    fclose(f2);

    return 0;
}
