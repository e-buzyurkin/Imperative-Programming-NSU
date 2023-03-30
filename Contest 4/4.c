#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt){
    int dig = 0, low = 0, up = 0;
    int len = 0;
    for (int i = 0; i < strlen(iStr); i++){
        int num = (int) iStr[i];
        if (48 <= num && num <= 57) dig++;
        if (65 <= num && num <= 90) up++;
        if (97 <= num && num <= 122) low++;
        if (32 <= num && num <= 126) len++;
    }
    *oLowerCnt = low; *oUpperCnt = up; *oDigitsCnt = dig;
    return len;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char iStr[102];
    int oLowerCnt = 0, oUpperCnt = 0, oDigitsCnt = 0;
    int i = 1;
    while (1){
        if (fgets(&iStr, 102, f1) == NULL) break;

        oLowerCnt = 0; oUpperCnt = 0; oDigitsCnt = 0;
        int len = calcLetters(&iStr, &oLowerCnt, &oUpperCnt, &oDigitsCnt);
        int letters = oUpperCnt + oLowerCnt;
        fprintf(f2, "Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", i, len, letters, oLowerCnt, oUpperCnt, oDigitsCnt);
        i++;

    }

    fclose(f1);
    fclose(f2);

    return 0;
}
