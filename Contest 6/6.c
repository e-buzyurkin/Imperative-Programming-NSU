#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 1000003
#include <assert.h>


struct Tokens{
    int num;
    char **arr;
};

void tokensSplit(struct Tokens* tokens, const char *str, const char *delims){
    //если tokens пустой, то считаем кол-во слов в строке
    if (tokens->arr == NULL){
        int count = 0;
        int length = strlen(str);
        int i = 0;
        while (i < length){
            if (strchr(delims, str[i]) == NULL){
                while (1){
                    if (strchr(delims, str[i]) != NULL || i >= length) break;
                    i++;
                }
                count++;
            }
            i++;
        }
        tokens->num = count;
    }
    else{
        int i = 0, startind, endind;
        int curr = 0;
        int length = strlen(str);
        while (i < length){
            if (strchr(delims, str[i]) == NULL){
                startind = i;
                endind = i;
                i++;
                while (1){
                    if (strchr(delims, str[i]) != NULL || i >= length) break;
                    endind = i;
                    i++;
                }
                printf("%d %d\n", startind, endind);
                tokens->arr[curr] = malloc((endind - startind + 2) * sizeof(char));
                int l = 0;
                for (int j = startind; j <= endind; j++){
                    tokens->arr[curr][l] = str[j];
                    //fprintf(f2, "%c", str[j]);
                    l++;
                }
                tokens->arr[curr][l] = '\0';
                curr++;
            }
            i++;
        }
    }
}

struct Tokens tokensFree(struct Tokens *tokens){
    for (int i = 0; i < tokens->num; i++){
        free(tokens->arr[i]);
    }
    tokens->num = 0;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char str[2 * max_size];
    char delims[5] = ":;,.";
    //fgets(str, 100, f1);
    fscanf(f1, "%s", &str);
    //printf("|%s|\n", str);
    struct Tokens tokens;
    tokens.arr = NULL;

    tokensSplit(&tokens, str, delims);
    tokens.arr = malloc(tokens.num * sizeof(char*));
    tokensSplit(&tokens, str, delims);
    fprintf(f2, "%d\n", tokens.num);
    for (int i = 0; i < tokens.num; i++){
        fprintf(f2, "%s", tokens.arr[i]);
        fprintf(f2, "\n");
    }
    //for (int i = 0; i < tokens.num; i++) printf("%d\n", strlen(tokens.arr[i]));
    //assert(tokens.num < 6);
    //printf("1");
    tokensFree(&tokens);
    //tokensFree(&tokens);
    fclose(f1);
    fclose(f2);

    return 0;
}
