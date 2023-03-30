#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readTime (char *iStr , int *oHours , int *oMinutes , int *oSeconds ){
    char s[15] = "";
    int j = 0;
    int hms = 0;
    for (int i = 0; i < strlen(iStr); i++){
        s[j] = iStr[i];
        j++;
        if (iStr[i] == ':' || i == strlen(iStr) - 1){

            //printf("%s\n", s);
            if (strstr(s, "|") == NULL){
                if (hms == 0) *oHours = atoi(s);
                if (hms == 1) *oMinutes = atoi(s);
                if (hms == 2) *oSeconds = atoi(s);

                hms++;
            }
            else{
                return 0;
            }
            for (int m = 0; m <= j; m++) s[m] = '\0';
            j = 0;
        }
        //else{

    }
}
int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char iStr[15];
    int oHours = 1, oMinutes = 0, oSeconds = 0;

    fgets(iStr, 15, f1);

    if (readTime(&iStr, &oHours, &oMinutes, &oSeconds) == 0) fprintf(f2, "0 -1 -1 -1\n0 -1 -1\n0 -1");
    else if (!((0 <= oHours && oHours <= 23) && (0 <= oMinutes && oMinutes <= 59) && (0 <= oSeconds && oSeconds <= 59)))
        fprintf(f2, "0 -1 -1 -1\n0 -1 -1\n0 -1");
    else fprintf(f2, "1 %d %d %d\n1 %d %d\n1 %d", oHours, oMinutes, oSeconds, oHours, oMinutes, oHours);
    //printf("%d %d %d", oHours, oMinutes, oSeconds);


    fclose(f1);
    fclose(f2);

    return 0;
}
