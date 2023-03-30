#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    struct Node_s *prev;
    struct Node_s *next;
    double value;
} Node;
//List –- вспомогательный узел, являющийся головой списка
typedef Node List;
//инициализирует поля структуры *list значениями для пустого списка
Node * initList (List * list){
    list->next = list;
    list->prev = list;
}

//определяет следующий элемент после заданного
//(для вспом. узла возвращает первый элемент)
double * getNext ( double * curr );
//определяет предыдущий элемент перед заданным
//(для вспом. узла возвращает последний элемент)
double * getPrev ( double * curr );

//создаёт новый узел со значением ptr и вставляет его после узла node
//возвращает указатель на созданный узел
double * addAfter ( double * ptr , double newval ){
    Node * NewElem = (Node*) malloc(sizeof(Node));
    NewElem->value = newval;

    Node * node = (Node*) ptr;

    NewElem->next = node->next;
    NewElem->prev = node;

    node->next->prev = NewElem;
    node->next = NewElem;

    return (double*)NewElem;
}
//создаёт новый узел со значением ptr и вставляет его перед узлом node
//возвращает указатель на созданный узел
double * addBefore (double * ptr , double newval){
    Node* NewElem = (Node*) malloc(sizeof(*NewElem));
    NewElem->value = newval;

    Node * node = (Node*) ptr;

    NewElem->next = node;
    NewElem->prev = node->prev;

    (node->prev)->next = NewElem;
    node->prev = NewElem;

    return (double*)NewElem;
}
//удаляет заданный узел, возвращая значение, которое в нём лежало
int erase (double * ptr){
    Node* node = (Node*) ptr;

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

    int q, operation, node;
    double value;
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
                    fscanf(f1, "%lf", &value);
                    pointers[c] = (Node*) addAfter(pointers[node], value);
                    c++;
                    break;
                case -1:
                    fscanf(f1, "%lf", &value);
                    pointers[c] = (Node*) addBefore(pointers[node], value);
                    c++;
                    break;
                case 0:
                    fprintf(f2, "%0.3lf\n", pointers[node]->value);
                    erase(pointers[node]);
                    break;
            }
        }
        fprintf(f2, "===\n");
        Node* current = pointers[0]->next;
        while (current != pointers[0]){
            fprintf(f2, "%0.3lf\n", current->value);
            current = current->next;
        }
        fprintf(f2, "===\n");
        free(pointers);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
