#include <stdio.h>
#include <stdlib.h>

struct video{
    int count;
    long long duration;
};

int digits(int n){
    int j = 0;
    while (n > 0){
        j++;
        n /= 10;
    }
    return j;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    struct video table[1001];
    for (int i = 0; i < 1001; i++){
        table[i].count = 0;
        table[i].duration = 0;
    }



    int n;
    fscanf(f1, "%d", &n);

    int id, dur;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %d", &id, &dur);
        table[id].count++;
        table[id].duration += dur;
    }

    int max_id = 0, max_count = 0, max_dur = 0;
    for (int i = 0; i < 1001; i++){
        if (table[i].count > 0 && i > max_id) max_id = i;
        if (table[i].count > max_count) max_count = table[i].count;
        if (table[i].duration > max_dur) max_dur = table[i].duration;
    }

    int dig_id = digits(max_id);
    int dig_cnt = digits(max_count);
    int dig_dur = digits(max_dur);

    void printLine(){
        fprintf(f2, "+"); for (int i = 0; i < dig_id + 2; i++) fprintf(f2, "-"); // id
        fprintf(f2, "+"); for (int i = 0; i < dig_cnt + 2; i++) fprintf(f2, "-"); // count
        fprintf(f2, "+"); for (int i = 0; i < dig_dur + 2; i++) fprintf(f2, "-"); fprintf(f2, "+\n"); // duration
    }

    printLine();

    for (int i = 0; i < 1001; i++){
        if (table[i].count > 0){
            fprintf(f2, "| "); for (int j = 0; j < dig_id - digits(i); j++) fprintf(f2, " "); fprintf(f2, "%d | ", i);
            for (int j = 0; j < dig_cnt - digits(table[i].count); j++) fprintf(f2, " "); fprintf(f2, "%d | ", table[i].count);
            for (int j = 0; j < dig_dur - digits(table[i].duration); j++) fprintf(f2, " "); fprintf(f2, "%d |\n", table[i].duration);
            printLine();
        }
    }



    fclose(f1);
    fclose(f2);

    return 0;
}

