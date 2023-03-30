#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char Char2Hex(char c){
    if (c < 65)
        return c - '0';
    else
        return c - 'A' + 10;
}

int main(){
    FILE *f1, *f2;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int n;
    fscanf(f1, "%d", &n);

    int leftn = n;
    int rightn = n;

    int *left_deck;
    int *right_deck;

    left_deck = malloc((2 * n + 1) * sizeof(int));
    right_deck = malloc((2 * n + 1) * sizeof(int));

    int left_first = 0, left_last = n - 1;
    int right_first = 0, right_last = n - 1;

    int right_cnt = n, left_cnt = n;

    for (int i = 0; i < n; i++){
        left_deck[i] = i + 1;
        right_deck[i] = - (i + 1);
    }

    int q;
    fscanf(f1, "%d\n", &q);

    char oper;
    int current_card;

    for (int i = 0; i < q; i++){
        fscanf(f1, "%c", &oper);
        oper = Char2Hex(oper);
        assert(right_cnt + left_cnt == 2 * n);
        //if (oper == 0 || oper == 15 || oper == 10 || oper == 5)
        //    continue;
        //take card
        if ((oper & 0x08) != 0){ // right deck
            if (right_cnt == 0)
                continue;
            if ((oper & 0x04) != 0){ // bottom
                current_card = right_deck[right_last];
                right_deck[right_last] = 0;
                if (right_last > 0){
                    right_last = right_last - 1;
                }
                else{
                    right_last = 2 * n;
                }
            }
            else{ // top 
                current_card = right_deck[right_first];
                right_deck[right_first] = 0;
                if (right_first != 2 * n){
                    right_first = right_first + 1;
                }
                else{
                    right_first = 0;
                }
            }
            right_cnt--;
        }
        else{ // left deck
            if (left_cnt == 0)
                continue;
            if ((oper & 0x04) != 0){ // bottom
                current_card = left_deck[left_last];
                left_deck[left_last] = 0;
                if (left_last > 0){
                    left_last = left_last - 1;
                }
                else{
                    left_last = 2 * n;
                }
            }
            else{ // top 
                current_card = left_deck[left_first];
                left_deck[left_first] = 0;
                if (left_first != 2 * n){
                    left_first = left_first + 1;
                }
                else{
                    left_first = 0;
                }
            }
            left_cnt--;
        }
        //put card
        if ((oper & 0x02) != 0){ // right deck
            if ((oper & 0x01) != 0){ //bottom
                if (right_last != 2 * n){
                    right_last = right_last + 1;
                    right_deck[right_last] = current_card;
                }
                else{
                    right_last = 0;
                    right_deck[right_last] = current_card;
                }
            }
            else{ // top
                if (right_first != 0){
                    right_first = right_first - 1;
                    right_deck[right_first] = current_card;
                }
                else{
                    right_first = 2 * n;
                    right_deck[right_first] = current_card;
                }
            }
            right_cnt++;
        }
        else{ // left deck
            if ((oper & 0x01) != 0){ //bottom
                if (left_last != 2 * n){
                    left_last = left_last + 1;
                    left_deck[left_last] = current_card;
                }
                else{
                    left_last = 0;
                    left_deck[left_last] = current_card;
                }
            }
            else{ // top
                if (left_first != 0){
                    left_first = left_first - 1;
                    left_deck[left_first] = current_card;
                }
                else{
                    left_first = 2 * n;
                    left_deck[left_first] = current_card;
                }
            }
            left_cnt++;
        }
    }

    int i = left_first;
    fprintf(f2, "%d ", left_cnt);
    if (left_cnt > 0){
        int cnt = 0;
        while (cnt < left_cnt){
            fprintf(f2, "%d ", left_deck[i % (2 * n + 1)]);
            i = (i + 1) % (2 * n + 1);
            cnt++;
        }
        //fprintf(f2, "%d", left_deck[left_last]);
    }
    fprintf(f2, "\n");

    fprintf(f2, "%d ", right_cnt);
    i = right_first;
    if (right_cnt > 0){
        int cnt = 0;
        while (cnt < right_cnt){
            fprintf(f2, "%d ", right_deck[i % (2 * n + 1)]);
            i = (i + 1) % (2 * n + 1);
            cnt++;
        }
        //fprintf(f2, "%d", right_deck[right_last]);
    }
    

    fclose(f1);
    fclose(f2);
    return 0;
}