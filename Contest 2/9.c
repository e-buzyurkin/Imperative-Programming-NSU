#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char c, c_next, c_note, c_end;

    while (!(feof(f1))){
        fscanf(f1, "%c", &c);
        if (feof(f1)) break;
        if (c != '/') fprintf(f2, "%c", c);
        else{ // запускаем ветвления при встрече с /
            if (fscanf(f1, "%c", &c_next) == EOF){
                fprintf(f2, "%c", c);
                break;
            }
            //fscanf(f1, "%c", &c_next);

            if (c_next == '/'){ // строчный комментарий
                while (!(feof(f1))){
                    fscanf(f1, "%c", &c); // сканируем символы, пока не встретимся с \n
                    if (c == '\n'){
                        fprintf(f2, "%c", '\n');
                        break;
                    }
                }
            }

            else if (c_next == '*'){ // блочный комментарий
                while (!(feof(f1))){
                    fscanf(f1, "%c", &c);
                    label:
                    if (c != '*') { //ждем звездочку, чтобы заверщить блочный комментарий
                        if (c == '\n') fprintf(f2, "%c", '\n');// если конец строки, то переводим на новую
                    }
                    else{ // если встречаем звездочку, то проверяем следующий символ
                        fscanf(f1, "%c", &c);
                        if (c == '*') goto label;
                        if (c == '/') break; // если след символ /, то заканчиваем блочный комментарий
                        else if (c == '\n') fprintf(f2, "%c", c); // если след символ оказался перевод строки, то выполняем его

                    }
                }
            }
            else {
                fprintf(f2, "%c", c);
                fprintf(f2, "%c", c_next); // если после первого / не последовало начала комментария,
            }                              // то пишем два символа, которые мы считали во время ветвлений
        }
    }
    if (fscanf(f1, "%c", &c_note) != 1)
        printf("1%c1 %c", c_note, c_next);
    fclose(f1);
    fclose(f2);

    return 0;
}
