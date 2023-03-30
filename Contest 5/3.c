#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Label{
    char name[16];
    int age;
};

struct NameStats{
    int cntTotal;
    int cntLong;
};

struct AgeStats{
    int cntTotal;
    int cntAdults;
    int cntKids;
};

void calcStats(struct Label *arr, int cnt, struct NameStats *oNames, struct AgeStats *oAges){
    struct NameStats outNames; outNames.cntLong = 0;
    struct AgeStats outAges; outAges.cntAdults = 0; outAges.cntKids = 0;

    outNames.cntTotal = cnt; outAges.cntTotal = cnt;

    for (int i = 0; i < cnt; i++){
        if (strlen(arr[i].name) > 10) outNames.cntLong++;

        if (arr[i].age >= 18) outAges.cntAdults++;
        if (arr[i].age < 14) outAges.cntKids++;
    }
    *oNames = outNames;
    *oAges = outAges;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    struct Label arr[n];
    struct NameStats oNames;
    struct AgeStats oAges;

    for (int i = 0; i < n; i++){
        fscanf(f1, "%s %d let", &arr[i].name, &arr[i].age);
    }

    calcStats(arr, n, &oNames, &oAges);

    fprintf(f2, "names: total = %d\nnames: long = %d\n", oNames.cntTotal, oNames.cntLong);
    fprintf(f2, "ages: total = %d\nages: adult = %d\nages: kid = %d", oAges.cntTotal, oAges.cntAdults, oAges.cntKids);

    fclose(f1);
    fclose(f2);

    return 0;
}
