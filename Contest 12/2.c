#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Tree_s {
    int value[2];
    struct Tree_s * left , * right ;
} Tree ;

Tree* insert_in_tree(Tree* node, int value){
    if (node == NULL){
        Tree * NewElem = (Tree*) malloc(sizeof(Tree));
        NewElem->value[0] = 1;
        NewElem->value[1] = value;

        NewElem->left = NULL;
        NewElem->right = NULL;
        
        return NewElem;
    }

    if (value == node->value[1])
        node->value[0]++;
    else if (value < node->value[1])
        node->left = insert_in_tree(node->left, value);
    else if (value > node->value[1])
        node->right = insert_in_tree(node->right, value);
    

    return node;
}

void store_sorted(Tree *root, int *a, int *i){
    if (root != NULL){
        store_sorted(root->left, a, i);
        if (root->value[0] == 1)
            a[(*i)++] = root->value[1];
        else if (root->value[0] > 1){
            for (int j = 0; j < root->value[0]; j++)
                a[(*i)++] = root->value[1];
        }
        store_sorted(root->right, a, i);
    }
}

void tree_sort(int *a, int n){
    Tree *root = NULL;

    root = insert_in_tree(root, a[0]);
    for (int i = 1; i < n; i++)
        root = insert_in_tree(root, a[i]);
  
    int i = 0;
    store_sorted(root, a, &i);
}

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.bin", "rb");
    f2 = fopen("output.bin", "wb");

    clock_t start, end;
    start = clock();


    int n;
    fread(&n, sizeof(int), 1, f1);

    int *a;
    a = malloc(n * sizeof(int));

    fread(a, sizeof(int), n, f1);

    for (int i = 0; i < n; i++) {
        int pos1 = (abs(rand()) << 16) + abs(rand());
        int pos2 = (abs(rand()) << 16) + abs(rand());
        pos1 = abs(pos1); pos2 = abs(pos2);
        pos1 %= n, pos2 %= n;
        int t = a[pos1];
        a[pos1] = a[pos2];
        a[pos2] = t;
    }

    tree_sort(a, n);

    fwrite(a, sizeof(int), n, f2);

    //free(a);
    end = clock();
    double time = ((double) (end - start)) / CLOCKS_PER_SEC;

    //printf("%lf", time);

    fclose(f1);
    fclose(f2);
    return 0;
}