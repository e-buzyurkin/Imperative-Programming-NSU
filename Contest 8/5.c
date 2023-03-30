#include <stdio.h>
#include <stdlib.h>
#define NEEDTOADD 1
#define NONEED -1
#include <math.h>

typedef struct bitset_s{
    unsigned long long value;
    int len;
} bitset;

unsigned char invert(unsigned char x)
{
    int base = 256;

    unsigned char  res = 0;
    while (x != 0)
    {
        res += (x & 1) * (base >>= 1);
        x >>= 1;
    }

    return res;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);

    bitset seq[n];
    int l;
    char byte;

    for (int i = 0; i < n; i++){
        fread(&l, sizeof(int), 1, f1);
        seq[i].value = 0ULL;
        seq[i].len = l;

        fread(&byte, sizeof(char), 1, f1);
        seq[i].value = seq[i].value | byte;

        for (int j = 1; j < l; j++){
            fread(&byte, sizeof(char), 1, f1);
            seq[i].value <<= 1;
            seq[i].value = seq[i].value | byte;
        }
    }

    int m;
    fread(&m, sizeof(int), 1, f1);

    int num;
    int curbits = 0, rembits;
    unsigned char acc = 0;
    unsigned long long cur;

    for (int i = 0; i < m; i++){
        fread(&num, 2, 1, f1);
        cur = seq[num].value;
        rembits = seq[num].len;
        while (rembits > 0){
            acc = acc | (cur >> (rembits - 1));
            cur <<= abs(63 - rembits);
            cur >>= abs(63 - rembits);
            rembits--;
            curbits++;

            if (curbits == 8){
                acc = invert(acc);
                fwrite(&acc, 1, 1, f2);
                //printf("%x ", acc);
                acc = 0;
                curbits = 0;
            }
            acc <<= 1;
        }
    }
    acc >>= 1;
    acc <<= (8 - curbits);
    if (curbits > 0){
        acc = invert(acc);
        fwrite(&acc, 1, 1, f2);
    }
    //int x = 123;
    //a <<= -1;
    //printf("%x", a);
    fclose(f1);
    fclose(f2);

    return 0;
}
