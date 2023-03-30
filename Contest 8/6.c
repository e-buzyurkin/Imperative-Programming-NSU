#include <stdio.h>
#include <stdlib.h>

int overlong_check(int cs, unsigned int x){
    int len = 32;
    unsigned int one = 2147483648;
    while ((one & x) == 0 && len > 0){
        len--;
        x <<= 1;
    }
    switch (cs){
        case 2:
            if (7 < len && len <= 11) return 0;
            else return 1;
        case 3:
            if (11 < len && len <= 16) return 0;
            else return 1;
        case 4:
            if (16 < len && len <= 21) return 0;
            else return 1;
    }
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    unsigned char byte, temp;
    unsigned int outint;
    unsigned int t;
    unsigned char one = 128;
    unsigned int replacementchar = 65533;
    unsigned int unicodelimit = 1114111;
    unsigned int leftborder = 55296, rightborder = 57343;

    while (1){
        if (fread(&byte, 1, 1, f1) == 0) break;

        t = 0;
        while ((one & byte) != 0 && byte != 0){
            t++;
            byte <<= 1;
        }
        if (t != 0) byte <<= 1;

        if (t == 1 || t > 4) break;

        switch (t){
            case 0:
                outint = byte;
                fwrite(&outint, sizeof(int), 1, f2);
                break;
            case 2:
                outint = byte;
                outint <<= 3;
                if (fread(&byte, 1, 1, f1) == 0) goto endprogram;
                if ((byte >> 6) != 2) goto endprogram;
                byte <<= 2;
                byte >>= 2;
                outint = outint | byte;
                if (overlong_check(t, outint)) outint = replacementchar;
                if (outint > unicodelimit || (leftborder <= outint && outint <= rightborder)) outint = replacementchar;
                fwrite(&outint, sizeof(int), 1, f2);
                break;
            case 3:
                outint = byte;
                outint <<= 2;
                if (fread(&byte, 1, 1, f1) == 0) goto endprogram;
                if ((byte >> 6) != 2) goto endprogram;
                byte <<= 2;
                byte >>= 2;
                outint = outint | byte;
                outint <<= 6;
                if (fread(&byte, 1, 1, f1) == 0) goto endprogram;
                if ((byte >> 6) != 2) goto endprogram;
                byte <<= 2;
                byte >>= 2;
                outint = outint | byte;
                if (overlong_check(t, outint)) outint = replacementchar;
                if (outint > unicodelimit || (leftborder <= outint && outint <= rightborder)) outint = replacementchar;
                fwrite(&outint, sizeof(int), 1, f2);
                break;
            case 4:
                outint = byte;
                outint <<= 1;
                if (fread(&byte, 1, 1, f1) == 0) goto endprogram;
                if ((byte >> 6) != 2) goto endprogram;
                byte <<= 2; byte >>= 2;
                outint = outint | byte;
                outint <<= 6;
                if (fread(&byte, 1, 1, f1) == 0) goto endprogram;
                if ((byte >> 6) != 2) goto endprogram;
                byte <<= 2; byte >>= 2;
                outint = outint | byte;
                outint <<= 6;
                if (fread(&byte, 1, 1, f1) == 0) goto endprogram;
                if ((byte >> 6) != 2) goto endprogram;
                byte <<= 2; byte >>= 2;
                outint = outint | byte;
                if (overlong_check(t, outint)) outint = replacementchar;
                if (outint > unicodelimit || (leftborder <= outint && outint <= rightborder)) outint = replacementchar;
                fwrite(&outint, sizeof(int), 1, f2);
                break;
        }
    }


    endprogram:

    fclose(f1);
    fclose(f2);

    return 0;
}
