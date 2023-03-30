#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE *f1, *f2;
    int n;
    int m, p, k, l;
    f1 = fopen("input.txt", "r");
    fscanf(f1, "%d", &n);
    fscanf(f1, "%d %d %d %d", &m, &p, &k, &l);

    int qonf = (float)m / ((p - 1) * l - 1 + k); // находим кол-во квартир на этаже
    int fl_p = ceil((float)n / qonf); // считаем сколько этажей нужно отсчитать, чтобы попасть к больному
    int pod = (float)fl_p / l; //считаем сколько подъездов мы пропускаем, чтобы дойти до нашего
    int floor = fl_p % l; //считаем какой этаж у больного
    //если остаток будет нулевым, это будет обозначать, что больной находится на последнем этаже в подъезде pod
    //если остаток будет ненулевым, то больной будет находится в подъезде pod + 1 и этаже floor
    if (floor == 0) floor = l;
    else pod += 1;

    fclose(f1);
    f2 = fopen("output.txt", "w");
    fprintf(f2, "%d %d", pod, floor);
    fclose(f2);
    return 0;
}
