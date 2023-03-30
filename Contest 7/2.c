#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define one 9223372036854775808

//какой-нибудь целочисленный тип (желательно беззнаковый)
typedef unsigned long long bitword;
//инициализирует массив битов длины num, устанавливая все его биты в ноль
void bitsetZero (bitword *arr, int num){
    const unsigned long long one = 9223372036854775808;
    int id = num / 64;
    int x = num & 64;
    for (int i = 0; i <= id; i++) arr[i] = 0;
    int h = id > 0;
    for (int i = 0; i <= x; i++) arr[id + h] = arr[id + h] & ~(one >> i);
};
//возвращает значение idx-ого бита (0 или 1)
int bitsetGet (const bitword *arr , int idx){
    const unsigned long long one = 9223372036854775808;
    int id = idx / 64;
    int x = idx % 64;
    unsigned long long temp = arr[id];
    //printf("%d %d %d", id, x, temp);

    return ((temp & (one >> x)) != 0);
};
//устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet (bitword *arr , int idx , int newval){
    const unsigned long long one = 9223372036854775808;
    int id = idx / 64;
    int x = idx % 64;
    if (newval == 1){
        arr[id] = arr[id] | (one >> x);
    }
    else arr[id] = arr[id] &~ (one >> x);
}
//возвращает 1, если среди битов с номерами k
//для left <= k < right есть единичный, и 0 иначе
int bitsetAny (const bitword *arr, int left, int right){
    const unsigned long long one = 9223372036854775808;
    int leftid = left / 64;
    int rightid = right / 64;
    int leftx = left % 64;
    int rightx = right % 64;
    //printf("%d %d %d ||| %d %d %d\n", left, leftid, leftx, right, rightid, rightx);
    //printf("%d\n", arr[leftid]);
    //printf("%d, ")
    if (leftid == rightid){
        for (int i = leftx; i < rightx; i++){
            unsigned long long temp = arr[leftid];
            if (((temp & (one >> i)) != 0) == 1) return 1;
        }
    }
    else if (rightid - leftid == 1){
            unsigned long long temp = arr[leftid];
            for (int i = leftx; i < 64; i++)
                if (((temp & (one >> i)) != 0) == 1){
                    //printf("left\n");
                    return 1;
                }
            temp = arr[rightid];
            for (int i = 0; i < rightx; i++){
                //printf("right\n");
                if (((temp & (one >> i)) != 0) == 1) return 1;
            }
        }
    else{
        for (int i = leftid + 1; i < rightid; i++){
            if (arr[i] > 0) return 1;
        }
        unsigned long long temp = arr[leftid];
        for (int i = leftx; i < 64; i++)
            if (((temp & (one >> i)) != 0) == 1) return 1;
        temp = arr[rightid];
        for (int i = 0; i < rightx; i++)
            if (((temp & (one >> i)) != 0) == 1) return 1;
    }
    return 0;
}


int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    int operation, idx, temp, newval, sn;
    int left, right;

    bitword *arr;
    int size = 20000000 / 64 + 1;
    arr = malloc((size + 1) * sizeof(unsigned long long));
    //printf("declared\n");

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d", &operation);
        //printf("%d \n", operation);
        switch(operation){
            case 0:
                fscanf(f1, "%d", &size);
                bitsetZero(arr, size);
                break;
            case 1:
                fscanf(f1, "%d", &idx);
                //printf("%d\n", idx);
                temp = bitsetGet(arr, idx);
                fprintf(f2, "%d\n", temp);
                break;
            case 2:
                fscanf(f1, "%d %d", &idx, &newval);
                bitsetSet(arr, idx, newval);
                break;
            case 3:
                fscanf(f1, "%d %d", &left, &right);
                sn = bitsetAny(arr, left, right);
                if (sn == 1) fprintf(f2, "some\n");
                else fprintf(f2, "none\n");
        }
    }

    free(arr);
    fclose(f1);
    fclose(f2);

    return 0;
}
