#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f1, *f2;
    f1 = fopen("input.txt", "r");
    int h, m, s, k;
    fscanf(f1, "%d %d %d %d", &h, &m, &s, &k);
    s += k; //óâåëè÷èâàåì êîë-âî ñåêóíä
    m += floor(s / 60); //óâåëè÷èâàåì êîë-âî ìèíóò
    s = s % 60; // óáèðàåì ëèøíèå ñåêóíäû, òàê êàê èõ íå ìîæåò áûòü áîëüøå 60
    h += floor(m / 60); //óâåëè÷èâàåì êîë-âî ÷àñîâ
    m = m % 60; //óáèðàåì ëèøíèå ìèíóòû
    h = h % 24; //óáèðàåì ëèøíèå ÷àñû
    fclose(f1);
    f2 = fopen("output.txt", "w");
    fprintf(f2, "%d %d %d", h, m, s);
    fclose(f2);
    return 0;
}
