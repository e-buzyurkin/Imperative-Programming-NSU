#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    long long s = 0LL;

    int n;
    fread(&n, sizeof(int), 1, f1);

    int x;

    if (n >= 1 && n <= 10000){
        for (int i = 0; i < n; i++){
            fread(&x, sizeof(int), 1, f1);
            s += x;
        }
        fwrite(&s, sizeof(int), 1, f2);
    }
    else{
        n = __builtin_bswap32(n);
        //printf("%d\n", n);
        for (int i = 0; i < n; i++){
            fread(&x, sizeof(int), 1, f1);
            x = __builtin_bswap32(x);
            //printf("%x\n", x);
            s += x;
        }
        s = __builtin_bswap32(s);
        fwrite(&s, sizeof(int), 1, f2);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
