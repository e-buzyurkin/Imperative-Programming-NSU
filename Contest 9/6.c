#include <stdio.h>
#include <stdlib.h>

typedef struct KeyArray {
    unsigned int key;
    unsigned int value;
} KeyArray;

void radixsort_step(KeyArray *from, KeyArray *dest, unsigned int n, unsigned int *offset, unsigned char sortable_bit){
    unsigned char *b = (unsigned char*) &from[n].key + sortable_bit;
    KeyArray *v = &from[n];

    while (v >= from){
        dest[--offset[*b]] = *v--;
        b -= sizeof(KeyArray);
    }
}

void radix_sort(KeyArray *a, unsigned int n){

    KeyArray *a_temp = (KeyArray*) malloc(sizeof(KeyArray) * n);

    unsigned int s[4 * 256] = {0};

    unsigned char *b = (unsigned char*) &a[n-1].key;

    while (b >= (unsigned char*) &a[0].key){
        for (int digit = 0; digit < 4; digit++)
            s[*(b + digit) + 256 * digit]++;

        b -= sizeof(KeyArray);
    }

    for (unsigned int i = 1; i < 256; i++)
        for (int digit = 0; digit < 4; digit++)
            s[i + 256 * digit] += s[i - 1 + 256 * digit];

    for (int digit = 0; digit < 4; digit++){
        radixsort_step(a, a_temp, n - 1, &s[256 * digit], digit);
        KeyArray *temp = a;
        a = a_temp;
        a_temp = temp;
    }

    free(a_temp);
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    unsigned int n;
    fread(&n, sizeof(int), 1, f1);

    KeyArray a[n];
    fread(&a, sizeof(KeyArray), n, f1);

    radix_sort(a, n);

    fwrite(&a, sizeof(KeyArray), n, f2);

    fclose(f1);
    fclose(f2);

    return 0;
}
