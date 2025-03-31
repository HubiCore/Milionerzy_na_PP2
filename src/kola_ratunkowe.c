#include "kola_ratunkowe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
#include <stdbool.h> //bool
#include <string.h>
#include <ctype.h> //toupper
//typedef char string[256];


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
