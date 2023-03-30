#include <stdio.h>
#include <stdlib.h>

FILE *f1, *f2;

struct digits{
    int m;
    int t;
    int s;
};

struct digits split(int n){
    struct digits num;
    num.s = 0; num.t = 0; num.m = 0;
    num.s = n % 1000;
    n /= 1000;
    num.t = n % 1000;
    n /= 1000;
    num.m = n % 1000;
    return num;
};

struct digits splitSotni(int n){
    struct digits num;
    num.s = 0; num.t = 0; num.m = 0;
    num.s = n % 10;
    n /= 10;
    num.t = n % 10;
    n /= 10;
    num.m = n % 10;
    return num;
};

void sotni(int n){
    switch(n){
        case 1:
            fprintf(f2, "sto ");
            break;
        case 2:
            fprintf(f2, "dvesti ");
            break;
        case 3:
            fprintf(f2, "trista ");
            break;
        case 4:
            fprintf(f2, "chetyresta ");
            break;
        case 5:
            fprintf(f2, "pyat'sot ");
            break;
        case 6:
            fprintf(f2, "shest'sot ");
            break;
        case 7:
            fprintf(f2, "sem'sot ");
            break;
        case 8:
            fprintf(f2, "vosem'sot ");
            break;
        case 9:
            fprintf(f2, "devyat'sot ");
            break;
    }
}

void dsat(int n){
    switch(n){
        case 0:
            fprintf(f2, "desyat' ");
            break;
        case 1:
            fprintf(f2, "odinnadtsat' ");
            break;
        case 2:
            fprintf(f2, "dvenadtsat' ");
            break;
        case 3:
            fprintf(f2, "trinadtsat' ");
            break;
        case 4:
            fprintf(f2, "chetyrnadtsat' ");
            break;
        case 5:
            fprintf(f2, "pyatnadtsat' ");
            break;
        case 6:
            fprintf(f2, "shestnadtsat' ");
            break;
        case 7:
            fprintf(f2, "semnadtsat' ");
            break;
        case 8:
            fprintf(f2, "vosemnadtsat' ");
            break;
        case 9:
            fprintf(f2, "devyatnadtsat' ");
            break;
    }
}

void desyatki(int n){
    switch (n){
        case 2:
            fprintf(f2, "dvadtsat' ");
            break;
        case 3:
            fprintf(f2, "tridtsat' ");
            break;
        case 4:
            fprintf(f2, "sorok ");
            break;
        case 5:
            fprintf(f2, "pyat'desyat ");
            break;
        case 6:
            fprintf(f2, "shest'desyat ");
            break;
        case 7:
            fprintf(f2, "sem'desyat ");
            break;
        case 8:
            fprintf(f2, "vosem'desyat ");
            break;
        case 9:
            fprintf(f2, "devyanosto ");
            break;
    }
}

void edinici_mil(int n){
    switch(n){
        case 0:
            fprintf(f2, "millionov ");
            break;
        case 1:
            fprintf(f2, "odin million ");
            break;
        case 2:
            fprintf(f2, "dva milliona ");
            break;
        case 3:
            fprintf(f2, "tri milliona ");
            break;
        case 4:
            fprintf(f2, "chetyre milliona ");
            break;
        case 5:
            fprintf(f2, "pyat' millionov ");
            break;
        case 6:
            fprintf(f2, "shest' millionov ");
            break;
        case 7:
            fprintf(f2, "sem' millionov ");
            break;
        case 8:
            fprintf(f2, "vosem' millionov ");
            break;
        case 9:
            fprintf(f2, "devyat' millionov ");
            break;
    }
}

void edinici_tis(int n){
    switch(n){
        case 0:
            fprintf(f2, "tysyach ");
            break;
        case 1:
            fprintf(f2, "odna tysyacha ");
            break;
        case 2:
            fprintf(f2, "dve tysyachi ");
            break;
        case 3:
            fprintf(f2, "tri tysyachi ");
            break;
        case 4:
            fprintf(f2, "chetyre tysyachi ");
            break;
        case 5:
            fprintf(f2, "pyat' tysyach ");
            break;
        case 6:
            fprintf(f2, "shest' tysyach ");
            break;
        case 7:
            fprintf(f2, "sem' tysyach ");
            break;
        case 8:
            fprintf(f2, "vosem' tysyach ");
            break;
        case 9:
            fprintf(f2, "devyat' tysyach ");
            break;
    }
}

void edinici_stroki(int n){
    switch(n){
        case 0:
            fprintf(f2, "strok");
            break;
        case 1:
            fprintf(f2, "odna stroka");
            break;
        case 2:
            fprintf(f2, "dve stroki");
            break;
        case 3:
            fprintf(f2, "tri stroki");
            break;
        case 4:
            fprintf(f2, "chetyre stroki");
            break;
        case 5:
            fprintf(f2, "pyat' strok");
            break;
        case 6:
            fprintf(f2, "shest' strok");
            break;
        case 7:
            fprintf(f2, "sem' strok");
            break;
        case 8:
            fprintf(f2, "vosem' strok");
            break;
        case 9:
            fprintf(f2, "devyat' strok");
            break;
    }
}

int main()
{


    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int t;
    fscanf(f1, "%d", &t);
    //printf("%d\n", t);
    long long n;
    struct digits x;
    x.m = 0; x.t = 0; x.s = 0;

    for (int i = 0; i < t; i++){
        fscanf(f1, "%lld", &n);
        if (n < 1) continue;
        x = split(n);
        //миллионы
        if (x.m != 0){
            struct digits mil;
            mil = splitSotni(x.m);
            sotni(mil.m);
            if (mil.t == 1){
                dsat(mil.s);
                fprintf(f2, "millionov ");
            }
            else{
                desyatki(mil.t);
                edinici_mil(mil.s);
            }
        }

        //тысячи

        if (x.t != 0){
            struct digits tis;
            tis = splitSotni(x.t);
            sotni(tis.m);
            if (tis.t == 1){
                dsat(tis.s);
                fprintf(f2, "tysyach ");
            }
            else{
                desyatki(tis.t);
                edinici_tis(tis.s);
            }
        }

        //сотни


        struct digits sot;
        sot = splitSotni(x.s);
        sotni(sot.m);
        if (sot.t == 1){
            dsat(sot.s);
            fprintf(f2, "strok");
        }
        else{
            desyatki(sot.t);
            edinici_stroki(sot.s);
        }

        fprintf(f2, "\n");
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
