#include <stdio.h>
#include <string.h>

int main()
{
    char str[4];
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    fgets(str, 4, f1);

    fclose(f1);

    if (strcmp(str, "Mon") == 0) fprintf(f2, "1");
    else if (strcmp(str, "Tue") == 0) fprintf(f2, "2");
    else if (strcmp(str, "Wed") == 0) fprintf(f2, "3");
    else if (strcmp(str, "Thu") == 0) fprintf(f2, "4");
    else if (strcmp(str, "Fri") == 0) fprintf(f2, "5");
    else if (strcmp(str, "Sat") == 0) fprintf(f2, "6");
    else if (strcmp(str, "Sun") == 0) fprintf(f2, "7");

    fclose(f2);

    return 0;
}
