#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

long long max(long long x, long long y){
    if (x >= y) return x;
    if (x <= y) return y;
}

 min(long long x, long long y){
    if (x >= y) return y;
    if (x <= y) return x;
}

struct timestamp{
    long long s;
    long long ms;
    long long mcs;
};

struct timestamp firstFrame(char *line){ // считывает время первого кадра
    struct timestamp start;
    float a1, a2;
    sscanf(line, "  %lld.%lld.%lld: Decoded first frame with timestamp: %f + %f (sec)", &start.s, &start.ms, &start.mcs, &a1, &a2);
    return start;
}

struct timestamp lastFrame(char *line){ // считывает время последнего кадра
    struct timestamp end;
    sscanf(line, "  %lld.%lld.%lld: Video ended: no more frames", &end.s, &end.ms, &end.mcs);
    return end;
}

long long packetDecoded(char *line){ // возращает время, за которое был декодирован пакет
    struct timestamp start;
    long long timeZ = 0, timeF;
    sscanf(line, "  %lld.%lld.%lld: Packet decoded in %d.%d ms", &start.s, &start.ms, &start.mcs, &timeZ, &timeF);
    int time = timeZ * 1000 + timeF;
    //printf("%d\n", time);0
    return time;
}

long long convertedToRGBA(char *line){ // возращает время, за которое пакет был конвертирован
    struct timestamp start;
    long long timeZ, timeF;
    sscanf(line, " %lld.%lld.%lld: Converted to RGBA in %lld.%lld ms", &start.s, &start.ms, &start.mcs, &timeZ, &timeF);
    long long time = timeZ * 1000 + timeF;
    //printf("%d\n", time);
    return time;
}

struct timestamp timeConvert(long long t){
    struct timestamp time;
    time.s = t / 1000;
    time.ms = t % 1000;
    time.mcs = 0;
    return time;
};

int roundDecode(long long a, long long b){
    long long Z = a / b;
    long long rem = a % b;
    long long halfb = 0;
    if (b % 2 == 0) halfb = b / 2;
    else halfb = b / 2 + 1;
    if (rem >= halfb) return Z + 1;
    else return Z;
}

struct timestamp playbackTime(struct timestamp start, struct timestamp end){ // возвращает время от первого кадра и до последнего
    long long start_time = start.s * 1000000 + start.ms * 1000 + start.mcs;
    long long end_time = end.s * 1000000 + end.ms * 1000 + end.mcs;
    long long time = end_time - start_time;
    struct timestamp playback;
    playback.s = time / 1000;
    playback.ms = time % 1000;
    playback.mcs = 0;
    return playback;
}

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char q = (char) 34; // кавычки

    struct timestamp start, end; // точки времени начала и конца

    struct timestamp min_out, avg_out, max_out, decode_out;

    long long frames_count = 0; // счетчик кадров
    long long decode_time = 0; // время декодирование, будет суммироваться Packet decoded и Converted to RGBA
    long long min_decode = 1000000, max_decode = 0, avg_decode = 0; //минимальное и максимальное время декодирования
    struct timestamp playback_time; // сколько времени прошло с первого кадра и до последнего

    int max_size = 1000000;
    char video[max_size]; // строка с названием видео
    char line[max_size]; // строка, которую мы будем считывать из файла
    long long cur_decode; // время декодирования для текущего файла
    while (!(feof(f1))){
        //if (fgets(line, max_size, f1) == NULL) break;
        if (fgets(line, max_size, f1) == NULL) break; // считываем строку
        //если строка содержит "Opened file", то запоминаем название видео
        if (strstr(line, "Opened file") != NULL) sscanf(line, "  %lld.%lld.%lld: Opened file %s", &start.s, &start.ms, &start.mcs, &video); // встретили название, записали его, запомнили время

        if (strstr(line, "Decoded first frame") != NULL){ // когда встречаем декодированный первый кадр, запускаем цикл
            start = firstFrame(line); // запоминаем время первого кадра
            while(!(feof(f1))){
                if (fgets(line, max_size, f1) == NULL) break; // считываем строку
                if (strstr(line, "Video ended") != NULL){ // если видео закончилось, то считываем точку времени конца
                                                          // и выходим из цикла текущего видео
                    int r = sscanf(line, "  %lld.%lld.%lld: Video ended: no more frames", &end.s, &end.ms, &end.mcs);
                    //assert()
                    break;
                }
                if (strstr(line, "Packet decoded in ") != NULL){ // когда встречаем Packet decoded,
                    cur_decode = packetDecoded(line);            // записываем в время декода для текущего кадра время
                    //printf("%d\n", cur_decode);
                } // нету смысла после Packet decoded запускать цикл и искать Converted to RGBA(описываю свой ход мыслей)
                  // для каждого кадра будет конвертирование, поэтому как и раньше читаем строки
                  // а когда находим это конвертирование, производим операции по сложению,
                  // обновлению максимума/минимума и прибавлению кадра
                if (strstr(line, "Converted to RGBA") != NULL){ //
                    cur_decode = cur_decode + convertedToRGBA(line);
                    //printf("%d\n", cur_decode);
                    decode_time = decode_time + cur_decode;
                    //printf("%d\n", decode_time);
                    min_decode = min(min_decode, cur_decode);
                    max_decode = max(max_decode, cur_decode);
                    frames_count++;
                }

            }
            //конвертируем числа для вывода(приводим их в вид A.BBB через структуру timestamp)
            avg_decode = roundDecode(decode_time, frames_count);
            playback_time = playbackTime(start, end);
            min_out = timeConvert(min_decode);
            avg_out = timeConvert(avg_decode);
            max_out = timeConvert(max_decode);
            decode_out = timeConvert(decode_time);
            //после конца декодирования файла переходим в фазу вывода данных на экран
            //выводим все на экран в соответствии с примером

            fprintf(f2, "Video %c%s%c:\n", q, video, q);
            fprintf(f2, "  Total frames: %lld\n", frames_count);
            fprintf(f2, "  Total decode time: %lld.%03lld ms\n", decode_out.s, decode_out.ms);
            fprintf(f2, "  Actual playback time: %lld.%03lld ms\n", playback_time.s, playback_time.ms);
            fprintf(f2, "  Min/avg/max decode time: %lld.%03lld/%lld.%03lld/%lld.%03lld ms\n\n", min_out.s, min_out.ms, avg_out.s, avg_out.ms, max_out.s, max_out.ms);
            min_decode = 1000000; max_decode = 0; frames_count = 0; decode_time = 0; //обнуляем значения для след файла
        }
    }



    fclose(f1);
    fclose(f2);

    return 0;
}
