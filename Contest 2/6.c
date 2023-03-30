#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int reverse(char s[8]){
    char p;
    for (int i = 0; i < 4; i++){
        p = s[i];
        s[i] = s[7 - i];
        s[7 - i] = p;
    }
    return s;
}

int zoro(char c){
    if (c == '1') return 1;
    else return 0;
}

int binary(char s[8]){
    int num = 0;
    for (int i = 0; i < strlen(s); i++){

        num = num + zoro(s[i]) * pow(2, i);
    }
    return num;
}

int main()
{

    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");
    int n;
    fscanf(f1, "%d/n", &n);

    char s[9];
    char c;
    int ch_count = 0;
    fscanf(f1, "%c", &c);


    for (int i = 0; i < n; i++){
        fscanf(f1, "%c", &c);
        s[ch_count] = c;
        ++ch_count;
        if (ch_count == 8){
            fprintf(f2, "%d ", binary(s));
            //printf("%s\n", s);
            ch_count = 0;
            for (int i = 0; i < 9; i++) s[i] = '\0';
        }
    }
    //if (c != '\n') s[ch_count - 1] = '\0';
    //printf("%s", s);
    if (n % 8 != 0) fprintf(f2, "%d", binary(s));

    fclose(f1);
    fclose(f2);

    return 0;
}
