#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    struct Node_s * prev , * next ;
    int value ;
} Node ;
//List –- вспомогательный узел, являющийся головой списка
typedef Node List;
//инициализирует поля структуры *list значениями для пустого списка
Node * initList (List * list){
    list->next = list;
    list->prev = list;
}
//создаёт новый узел со значением ptr и вставляет его после узла node
//возвращает указатель на созданный узел
Node * addAfter ( Node* node , int ptr ){
    Node * NewElem = (Node*) malloc(sizeof(Node));
    NewElem->value = ptr;

    NewElem->next = node->next;
    NewElem->prev = node;

    node->next->prev = NewElem;
    node->next = NewElem;


    return NewElem;
}
//создаёт новый узел со значением ptr и вставляет его перед узлом node
//возвращает указатель на созданный узел
Node * addBefore ( Node * node , int ptr ){
    Node* NewElem = (Node*) malloc(sizeof(*NewElem));
    NewElem->value = ptr;

    NewElem->next = node;
    NewElem->prev = node->prev;

    (node->prev)->next = NewElem;
    node->prev = NewElem;

    return NewElem;
}
//удаляет заданный узел, возвращая значение, которое в нём лежало
int erase (Node * node){
    Node* nextElem = node->next;
    Node* prevElem = node->prev;

    prevElem->next = nextElem;
    nextElem->prev = prevElem;
    return node->value;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int t;
    fscanf(f1, "%d", &t);

    int q, operation, node, value;
    List* *pointers;

    for (int g = 0; g < t; g++){
        fscanf(f1, "%d", &q);
        pointers = malloc((q + 2) * sizeof(List));
        pointers[0] = malloc(sizeof(List));
        pointers[0]->next = pointers[0];
        pointers[0]->prev = pointers[0];
        int c = 1;
        for (int i = 0; i < q; i++){
            fscanf(f1, "%d %d", &operation, &node);
            node++;
            switch(operation){
                case 1:
                    fscanf(f1, "%d", &value);
                    pointers[c] = addAfter(pointers[node], value);
                    c++;
                    break;
                case -1:
                    fscanf(f1, "%d", &value);
                    pointers[c] = addBefore(pointers[node], value);
                    c++;
                    break;
                case 0:
                    erase(pointers[node]);
                    break;
            }
        }
        Node* current = pointers[0]->next;
        while (current != pointers[0]){
            fprintf(f2, "%d\n", current->value);
            current = current->next;
        }
        fprintf(f2, "===\n");
        free(pointers);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
