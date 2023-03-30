#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long bitword;

int bitsetGet (const bitword *arr , int idx){
    const unsigned long long one = 1ULL << 63;
    int id = idx / 64;
    int x = idx % 64;
    unsigned long long temp = arr[id];
    //printf("%d %d %d", id, x, temp);

    return ((temp & (one >> x)) != 0);
};

void bitsetSet (bitword *arr , int idx , int newval){
    const unsigned long long one = 1ULL << 63;
    int id = idx / 64;
    int x = idx % 64;
    if (newval == 1){
        arr[id] = arr[id] | (one >> x);
    }
    else arr[id] = arr[id] & ~(one >> x);
}

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d\n", &n);

    unsigned long long **r;
    r = malloc(n * sizeof(unsigned long long*));
    for (int i = 0; i < n; i++){
        r[i] = malloc((n / 64 + 1) * sizeof(bitword));
    }

    char c;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fscanf(f1, "%c", &c);
            c = c - '0';
            bitsetSet(r[i], j, c);
        }
        fscanf(f1, "%c", &c);
    }

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            if (bitsetGet(r[i], k) == 1)
                for (int j = 0; j < n / 64 + 1; j++){
                    r[i][j] = r[i][j] | r[k][j];
                }
        }
    }

    for (int i = 0; i < n; i++)
        bitsetSet(r[i], i, 1);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            fprintf(f2, "%d", bitsetGet(r[i], j));
        fprintf(f2, "\n");
    }

    fclose(f1);
    fclose(f2);
    return 0;
}  