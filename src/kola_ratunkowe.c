#include "kola_ratunkowe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
#include <stdbool.h> //bool
#include <string.h>
#include <ctype.h> //toupper
#include <unistd.h>
//typedef char string[256];

//usuwaie buffera
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//kolo ratunkowe 50 na 50, funkcja wypisuje wypisuje jedno poprawne pytanie i jego złe pytanie
void fiftyFifty(char correctAnswer, string answers[4]) {
    int wrongIndices[3];
    int wrongCount = 0;

    for (int i = 0; i < 4; i++) {
        if (answers[i][0] != correctAnswer) {
            wrongIndices[wrongCount++] = i;
        }
    }
    srand(time(NULL));
    int keepWrongIndex = wrongIndices[rand() % wrongCount];

    printf("Pozostaja odpowiedzi:\n");
    for (int i = 0; i < 4; i++) {
        if (answers[i][0] == correctAnswer || i == keepWrongIndex) {
            printf("%s", answers[i]);
        }
    }
}
//telefon do przyjaciela, klikasz, dzwonisz do przyjaciela, mówisz zasady, jak wie o co chodzi klikasz enter, koniec czasu to się rozłączasz
void call_to_friend(){
    clear_input_buffer();
    printf("Nacisnij Enter, aby rozpoczac odliczanie 30 sekund...\n");
    getchar();
    printf("Odliczanie rozpoczete !!!\n");
    printf("Zostało: ");
    for (int i = 30; i > 0; i--) {
        printf("%2ds ", i);
        sleep(1);
        fflush(stdout);

    }
    printf("\nKoniec czasu!\n");

}
//kolo ratunkowe pytanie do publiczności, funkcja zwraca wyniki procentowe, szansa 1 na 100, ze poprawna odpowiedz jest rowna 0
void PytanieDoPublicznosci(char correctAnswer, string answers[4], string question) {
    int sum = 100, temp;
    int votes[4] = {0,0,0,0};
    int CorrectIndex = toupper(correctAnswer) - 'A';
    if (rand()%(100 +1 ) == 11){
        votes[CorrectIndex] = 0;
    }else{
        votes[CorrectIndex] = (rand() % 41) + 30;
        sum -= votes[CorrectIndex];
    }

    int pozostale[3];
    int a = rand() % (sum + 1);
    int b = rand() % (sum - a + 1);
    int c = sum - a - b;
    pozostale[0]= a;
    pozostale[1] = b;
    pozostale[2] = c;
    int j = 0;
    for (int i = 0; i < 4; i++){
        if (CorrectIndex == i){
            continue;
        }
        else{
            votes[i] = pozostale[j];
            j++;
        }
    }
    printf("%s\n",question);
    printf("%s -> %d%% \n",answers[0], votes[0]);
    printf("%s -> %d%% \n",answers[1], votes[1]);
    printf("%s -> %d%% \n",answers[2], votes[2]);
    printf("%s -> %d%% \n",answers[3], votes[3]);

}
