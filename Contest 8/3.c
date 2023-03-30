#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file{
    char name[22];
    unsigned long long size;
    char isDir;
    unsigned long long c;
    unsigned long long m;
    char isHid;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "rb");
    f2 = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, f1);
    //fwrite(&n, sizeof(int), 1, f2);
    //printf("%d\n", n);
    unsigned long long a, b;
    fread(&a, sizeof(unsigned long long), 1, f1);
    fread(&b, sizeof(unsigned long long), 1, f1);
    //printf("%lld %lld\n", a, b);
    char filename[21];
    unsigned long long filesize;
    unsigned long long c, m;
    char isDirectory, isHidden;
    struct file curfile;
    struct file files[n];
    int cur = 0;

    for (int i = 0; i < n; i++){
        fread(&curfile.name, sizeof(char), 21, f1);
        fread(&curfile.size, sizeof(unsigned long long), 1, f1);
        fread(&curfile.isDir, 1, 1, f1);
        fread(&curfile.c, sizeof(unsigned long long), 1, f1);
        fread(&curfile.m, sizeof(unsigned long long), 1, f1);
        fread(&curfile.isHid, 1, 1, f1);
        //printf("%d\n", curfile.isDir);

        if (curfile.c >= a && curfile.m <= b && !curfile.isDir && !curfile.isHid){
            files[cur] = curfile;
            cur++;
        }

    }
    struct file help;

    for (int i = 0; i < cur; i++)
        for (int j = i + 1; j < cur; j++)
            if (strncmp(files[i].name, files[j].name, 21) > 0){
                help = files[i];
                files[i] = files[j];
                files[j] = help;
            }

    for (int i = 0; i < cur; i++){
        fwrite(&files[i].name, sizeof(char), 21, f2);
        fwrite(&files[i].size, sizeof(unsigned long long), 1, f2);
        fwrite(&files[i].isDir, sizeof(char), 1, f2);
        fwrite(&files[i].c, sizeof(unsigned long long), 1, f2);
        fwrite(&files[i].m, sizeof(unsigned long long), 1, f2);
        fwrite(&files[i].isHid, sizeof(char), 1, f2);
    }


    fclose(f1);
    fclose(f2);

    return 0;
}
