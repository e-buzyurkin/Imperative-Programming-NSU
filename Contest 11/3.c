#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define max_size 1000000

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
    unsigned long long *elems;
    int *indexes;
};

unsigned long long m;
int a, b, c;

uint64_t func(uint64_t s){
    return (s * s * a + s * b + c ) % m;
}

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    fscanf(f1, "%lld", &m);
    fscanf(f1, "%d %d %d", &a, &b, &c);

    struct hash_tableS *hash_table;
    hash_table = calloc(max_size, sizeof(struct hash_tableS));

    unsigned long long state = 1LL;
    int key;

    int i = 0;
    int flag;

    while (1){
        key = jenkins(&state, sizeof(unsigned long long)) % max_size;
        flag = 0;
        if (hash_table[key].condition == 1){
            for (int j = 0; j < hash_table[key].cnt; j++){
                if (hash_table[key].elems[j] == state){
                    fprintf(f2, "%d %d", hash_table[key].indexes[j], i);
                    flag = 1;
                    break;
                }
            }
            if (!flag){
                hash_table[key].elems = realloc(hash_table[key].elems, (hash_table[key].cnt + 1) * sizeof(unsigned long long));
                hash_table[key].indexes = realloc(hash_table[key].indexes, (hash_table[key].cnt + 1) * sizeof(int));
                
                hash_table[key].elems[hash_table[key].cnt] = state;
                hash_table[key].indexes[hash_table[key].cnt] = i;

                hash_table[key].cnt++;
            }
        }
        else{
            hash_table[key].elems = malloc(sizeof(unsigned long long));
            hash_table[key].indexes = malloc(sizeof(int));

            hash_table[key].elems[hash_table[key].cnt] = state;
            hash_table[key].indexes[hash_table[key].cnt] = i;

            hash_table[key].cnt++;
            hash_table[key].condition = 1;
        }

        if (flag)
            break;

        state = func(state);
        i++;
    }

    fclose(f1);
    fclose(f2);
    free(hash_table);
    return 0;
}