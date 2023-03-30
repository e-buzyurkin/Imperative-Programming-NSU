#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LetterToNum(char letter){
    if ((int) letter < 58) return ((int) letter - 48);
    int num = (int) letter - 87;
    return num;
}

int NumToLetter(int n){
    if (n < 10) return ((char) (n + 48));
    int l = n + 87;
    return ((char) l);
}

int AnyToDec(int p, char *n){
    int m = 0;
    for (int i = 0; i < strlen(n); i++){
        m += LetterToNum(n[strlen(n) - 1 - i]) * pow(p, i);
    }
    return m;
}

int DecToAny(int q, int n, char *out){
    int i = 30;
    while (n > 0){
        int rem = n % q;
        out[i] = NumToLetter(rem);
        n /= q;
        i--;
    }
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int p, q;
    fscanf(f1, "%d %d ", &p, &q);

    char n[31] = "", out[31] = "", c;
    for (int i = 0; i < 31; i++) out[i] = '\0';

    int i = 30;

    fscanf(f1, "%s", &n);

    int dec = AnyToDec(p, n);

    DecToAny(q, dec, out);

    for (int i = 0; i < 31; i++)
        if (out[i] != '\0') fprintf(f2, "%c", out[i]);

    fclose(f1);
    fclose(f2);

    return 0;
}
