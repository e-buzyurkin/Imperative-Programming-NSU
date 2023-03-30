#include <stdio.h>
#include <stdlib.h>

int daysinmonth(int month, int year){
    if (month == 2 && year % 4 != 0) return 28;
    else
    if (month == 2 && ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))) return 29;
    else if (month == 2) return 28;
    if (month % 2 == 0 && month < 8) return 30;
    if (month % 2 == 1 && month < 8) return 31;

    if (month % 2 == 0 && month >= 8) return 31;
    if (month % 2 == 1 && month >= 8) return 30;
}

struct date{
    int day;
    int month;
};

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int d, m, y, k;
    fscanf(f1, "%d %d %d %d", &d, &m, &y, &k);

    while (k > 0){
        k--;
        d++;
        if (d > daysinmonth(m, y)){
            m++;
            if (m > 12){
                y++;
                m = 1;

            }
            d = 1;
        }

    }
    //printf("%d", daysinmonth(2, 2100));
    fprintf(f2, "%d %d %d", d, m, y);
    fclose(f1);
    fclose(f2);

    return 0;
}