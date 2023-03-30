#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 1000001

struct quantity_values{
    int quantity;
    char **values;
};

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    struct quantity_values *a;
    a = malloc(max_size * sizeof(struct quantity_values));

    for (int i = 0; i < max_size; i++){
        a[i].quantity = 0;
    }

    int key;
    char *value;
    value = malloc(10 * sizeof(char));

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %s", &key, value);
        a[key].values = realloc(a[key].values, (a[key].quantity + 1) * sizeof(char*));
        a[key].values[a[key].quantity] = malloc(10 * sizeof(char));
        for (int j = 0; j < strlen(value); j++)
            a[key].values[a[key].quantity][j] = value[j];
        a[key].values[a[key].quantity][strlen(value)] = '\0';
        a[key].quantity++;
    }
    
    for (int i = 0; i < max_size; i++){
        if (a[i].quantity > 0){
            for (int j = 0; j < a[i].quantity; j++)
                fprintf(f2, "%d %s\n", i, a[i].values[j]);
        }
    }

    fclose(f1);
    fclose(f2);
    return 0;
}