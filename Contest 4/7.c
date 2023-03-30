#include <stdio.h>
#include <stdlib.h>



int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    long long alphabet[127];
    for (int i = 0; i < 127; i++) alphabet[i] = 0;

    char c;

    while (!(feof(f1))){
        fscanf(f1, "%c", &c);
        if (feof(f1)) break;
        alphabet[(int) c]++;
    }

    for (int i = 32; i < 127; i++){
        if (alphabet[i] != 0){
            fprintf(f2, "%c ", (char) i);
            for (int j = 0; j < alphabet[i]; j++) fprintf(f2, "%c", '#');
            fprintf(f2, "%c", '\n');
        }
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
