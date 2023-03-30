#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int RecLetter(char c){
    int n = (int) c;
    if ( (65 <= n && n <= 90) || (97 <= n && n <= 122) ) return 1;
    return 0;
}

int RecUpper(char c){
    int n = (int) c;
    if (65 <= n && n <= 90) return 1;
    return 0;
}

void calcLetters(char *line, int *up1, int *total){
    int dig = 0, low = 0, up = 0;
    for (int i = 0; i < strlen(line); i++){
        int num = (int) line[i];
        if (65 <= num && num <= 90) up++;
        if (97 <= num && num <= 122) low++;
    }
    *up1 = up; *total = up + low;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");
    //for (int i = 0; i < 1000000; i++) fprintf(f2, "A");
    char c;
    int max_size = pow(10, 6) * 2;
    char word[max_size];
    short b = 0;
    int i = 0, up1 = 0, total = 0;
    while (!(feof(f1))){
        //if (fscanf(f1, "%c", &c) == 0) break;
        fscanf(f1, "%c", &c);
        if (RecLetter(c) == 1){
            b = 1;
            int i = 0, up1 = 0, total = 0;
            word[i] = c;
            if (RecUpper(c) == 1) up1++;
            total++;
            while (1){
                fscanf(f1, "%c", &c);

                if (RecLetter(c) == 0 || feof(f1)){
                    //calcLetters(&word, &up1, &total);
                    fprintf(f2, "%d/%d %s\n", up1, i + 1, word);
                    break;
                }
                if (RecUpper(c) == 1) up1++;
                total++;
                i++;
                word[i] = c;
            }
            if (!(feof(f1))) for (int j = 0; j <= i; j++) word[j] = '\0';
        }

    }
    if (b == 0) fprintf(f2, "\n");
    fclose(f1);
    fclose(f2);

    return 0;
}
