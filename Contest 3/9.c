#include <stdio.h>
#include <stdlib.h>

int LetterToNum(char letter){
    int num = (int) letter - 96;
    return num;
}

int NumToLetter(int n){
    int l = n + 96;
    return ((char) l);
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    short in[n];
    for (int i = 0; i < n; i++) in[i] = 0;

    char c, space;

    while (space != '\n'){
        fscanf(f1, "%c", &space);
    }

    for (int i = 0; i < n; i++){ // сканируем данные из файла
        fscanf(f1, "%c", &c);
        in[i] = LetterToNum(c);
        fscanf(f1, "%c", &space);
    }

    int breakpoint = -1;
    for (int i = n - 1; i > 0; i--){ // ищем место, где символы не идут в возрастающем порядке
        if (in[i - 1] < in[i]){
            breakpoint = i;
            break;
        }
    }

    int min_swap = -1;
    int e;
    if (breakpoint == n - 1){ // если все символы возрастают, то меняем последний
        e = in[n - 1]; in[n - 1] = in[n - 2]; in[n - 2] = e; // с преподследним и получаем ответ
        goto end;
    }
    else if (breakpoint == -1){
        goto end;
    }
    for (int i = breakpoint + 1; i < n; i++){ // сортируем подпоследовательность после breakpoint'а
        for (int j = i + 1; j < n; j++){
            if (in[i] < in[j]){
                e = in[i]; in[i] = in[j]; in[j] = e;
            }
        }
    }


    for (int i = n - 1; i >= 0; i--){
        for (int j = n - 1; j > i; j--){
            if (in[i] < in[j] ){
                e = in[i]; in[i] = in[j]; in[j] = e;
                min_swap = i;
                goto sort;
            }
        }
    }
    //bitset()
    sort:
    for (int i = min_swap + 1; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (in[i] > in[j]){
                e = in[i]; in[i] = in[j]; in[j] = e;
            }
        }
    }

    end:

    for (int i = 0; i < n; i++) fprintf(f2, "%c ", NumToLetter(in[i]));

    fclose(f1);
    fclose(f2);

    return 0;
}
