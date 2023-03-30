#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char c, w;
    int word_count = 0;

    while (!feof(f1)){
        fscanf(f1, "%c", &c);
        if ((c != '.') && (c != '\n')) {
            word_count++;
            w = '/';
            while ((w != '.') && (!feof(f1))){
                fscanf(f1, "%c", &w);
                //printf("%c", w);
            }
        }
    }

    fprintf(f2, "%d", word_count);

    fclose(f1);
    fclose(f2);

    return 0;
}
