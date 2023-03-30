#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int size;
    fread(&size, sizeof(int), 1, f1);
    unsigned char t;

    char *name;
    char c;

    double doublevalue;
    unsigned char boolvalue;
    unsigned char nullvalue;
    int int32value;
    long long int64value;
    char *stringvalue;
    int empty = 0;
    int l;

    fwrite("{\r\n", sizeof(char), 3, f2);


    while (1){
        fread(&t, 1, 1, f1);
        if (t == 0) break;
        if (empty != 0) fwrite(",\r\n", sizeof(char), 3, f2);
        empty = 1;
        fwrite("    ", sizeof(char), 4, f2);
        int cur = 0;
        c = 1;
        name = malloc(sizeof(char) * 1000000);
        while (c != 0){
            fread(&c, 1, 1, f1);
            name[cur] = c;
            cur++;
        }
        fwrite("\"", sizeof(char), 1, f2);
        fwrite(name, sizeof(char), cur - 1, f2);
        fwrite("\"", sizeof(char), 1, f2);
        fwrite(": ", sizeof(char), 2, f2);
        free(name);
        switch (t){
            case 1: // double
                fread(&doublevalue, sizeof(double), 1, f1);
                //fwrite(&doublevalue, sizeof(double), 1, f2);
                fprintf(f2, "%0.15g", doublevalue);
                break;
            case 2: // string
                //cur = 0;
                fread(&l, sizeof(int), 1, f1);
                stringvalue = malloc(sizeof(char*) * l);
                for (int i = 0; i < l; i++){
                    fread(&c, sizeof(char), 1, f1);
                    stringvalue[i] = c;
                }
                //stringvalue[l - 1] = '\0';
                //printf("%s", stringvalue);
                fwrite("\"", sizeof(char), 1, f2);
                fwrite(stringvalue, sizeof(char), l - 1, f2);
                fwrite("\"", sizeof(char), 1, f2);
                free(stringvalue);
                break;
            case 8: // bool
                fread(&boolvalue, 1, 1, f1);
                if (boolvalue == 1) fwrite("true", sizeof(char), 4, f2);
                else fwrite("false", sizeof(char), 5, f2);
                break;
            case 10:
                //fread(&nullvalue, 1, 1, f1);
                fwrite("null", sizeof(char), 4, f2);
                break;
            case 16:
                fread(&int32value, sizeof(int), 1, f1);
                fprintf(f2, "%d", int32value);
                //fwrite(&int32value, sizeof(int), 1, f2);
                break;
            case 18:
                fread(&int64value, sizeof(long long), 1, f1);
                //fwrite(&int64value, sizeof(long long), 1, f2);
                fprintf(f2, "%lld", int64value);
                break;
        }
    }
    fwrite("\r\n}\r\n", sizeof(char), 5, f2);
    //printf("|%c|", '\r');
    fclose(f1);
    fclose(f2);

    return 0;
}
