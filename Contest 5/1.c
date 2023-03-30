#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct DateTime_s{
    int year, month, day;
    int hours, minutes, seconds;
};

struct DateTime_s DateTime(struct DateTime_s *arr, int cnt){
    struct DateTime_s minimal;

    void update(struct DateTime_s x){
        minimal.year = x.year; minimal.month = x.month; minimal.day = x.day;
        minimal.hours = x.hours; minimal.minutes = x.minutes; minimal.seconds = x.seconds;
    }

    update(*arr);

    for (int i = 0; i < cnt; i++){
        if (arr->year < minimal.year) update(*arr);

        else if (arr->year == minimal.year && arr->month < minimal.month) update(*arr);

        else if (arr->year == minimal.year && arr->month == minimal.month && arr->day < minimal.day) update(*arr);

        else if (arr->year == minimal.year && arr->month == minimal.month && arr->day == minimal.day
                 && arr->hours < minimal.hours) update(*arr);

        else if (arr->year == minimal.year && arr->month == minimal.month && arr->day == minimal.day
                 && arr->hours == minimal.hours && arr->minutes < minimal.minutes) update(*arr);

        else if (arr->year == minimal.year && arr->month == minimal.month && arr->day == minimal.day
                 && arr->hours == minimal.hours && arr->minutes == minimal.minutes && arr->seconds < minimal.seconds)
                    update(*arr);
        arr++;
    }

    return minimal;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    struct DateTime_s arr[n];

    for (int i = 0; i < n; i++){
        fscanf(f1, "%d %d %d %d %d %d", &arr[i].year, &arr[i].month, &arr[i].day, &arr[i].hours, &arr[i].minutes, &arr[i].seconds);

    }

    struct DateTime_s min;
    min = DateTime(arr, n);
    fprintf(f2, "%d %d %d %d %d %d", min.year, min.month, min.day, min.hours, min.minutes, min.seconds);

    fclose(f1);
    fclose(f2);

    return 0;
}
