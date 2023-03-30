#include <stdio.h>
#include <stdlib.h>
#define max_size 1000000
#include <math.h>
#include <stdint.h>

uint32_t jenkins(const uint8_t* key, size_t len) {
    uint32_t hash = 0;
    for (size_t i = 0; i < len; i++) {
      hash += key[i];
      hash += hash << 10;
      hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

struct hash_tableS{
    char condition;
    int cnt;
    int *elems;
};

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.bin", "rb");
    f2 = fopen("output.bin", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);

    int *out;
    out = malloc(n * sizeof(int));
    int curlen = 0;

    struct hash_tableS *hash_table;
    hash_table = calloc(max_size, sizeof(struct hash_tableS));

    

    int x;
    int key;

    /*for (int i = 0; i < 10000000; i++){
        key = abs(jenkins(i, sizeof(int))) % max_size;
        if (key == x){
            printf("%d", i);
            break;
        }    
        else{
            hash_table[key] = 1;
        }
    }*/

    int flag;
    
    for (int i = 0; i < n; i++){
        fread(&x, sizeof(int), 1, f1);
        key = abs(jenkins(&x, sizeof(int))) % max_size;
        if (hash_table[key].condition != 1){
            hash_table[key].elems = malloc(sizeof(int));
            hash_table[key].elems[0] = x;
            hash_table[key].cnt = 1;
            hash_table[key].condition = 1;
            out[curlen] = x;
            curlen++;
        }
        else{
            flag = 1;
            for (int j = 0; j < hash_table[key].cnt; j++)
                if (hash_table[key].elems[j] == x){
                    flag = 0;
                    break;
                }
            if (flag){
                hash_table[key].elems = realloc(hash_table[key].elems, (hash_table[key].cnt + 1) * sizeof(int));
                hash_table[key].elems[hash_table[key].cnt] = x;
                hash_table[key].cnt++;
                out[curlen] = x;
                curlen++;
            }
        }
    }

    fwrite(&curlen, sizeof(int), 1, f2);
    fwrite(out, sizeof(int), curlen , f2);

    fclose(f1);
    fclose(f2);
    return 0;
}