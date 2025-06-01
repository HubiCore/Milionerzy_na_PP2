/**
* @file kola_ratunkowe.c
 * @brief Implementacja kół ratunkowych w grze (50:50, telefon do przyjaciela, pytanie do publiczności).
 *
 * Funkcje pomocnicze używane w quizie typu "Milionerzy".
 */

#include "kola_ratunkowe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/**
 * @brief Czyści bufor wejściowy standardowego wejścia.
 *
 * Pomocne przy oczekiwaniu na znak Enter w konsoli, aby uniknąć zalegających znaków.
 */

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Koło ratunkowe 50 na 50 — pozostawia jedną poprawną i jedną losową złą odpowiedź.
 *
 * @param correctAnswer Litera oznaczająca poprawną odpowiedź (np. 'A').
 * @param answers Tablica 4 możliwych odpowiedzi w formacie np. "A) Odpowiedź".
 * @return Litera pozostawionej błędnej odpowiedzi.
 */
char fiftyFifty(char correctAnswer, string answers[4]) {
    int wrongIndices[3];
    int wrongCount = 0;

    for (int i = 0; i < 4; i++) {
        if (answers[i][0] != correctAnswer) {
            wrongIndices[wrongCount++] = i;
        }
    }
    srand(time(NULL));
    int keepWrongIndex = wrongIndices[rand() % wrongCount];
    return answers[keepWrongIndex][0];
}
/**
 * @brief Koło ratunkowe „Telefon do przyjaciela” — wyświetla licznik 30 sekund.
 *
 * Funkcja odlicza czas, żeby gracz wiedział, ile ma czasu na dzwonienie z kolegą (poleganie na uczciwości gracza)
 */
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

/**
 * @brief Koło ratunkowe „Pytanie do publiczności” — generuje losowy rozkład procentowy odpowiedzi.
 *
 * @param correctAnswer Litera poprawnej odpowiedzi (np. 'C').
 * @param answers Tablica 4 możliwych odpowiedzi (z literą na początku).
 * @param question Treść pytania (obecnie niewykorzystywana wewnątrz funkcji).
 * @param buf Tablica, w której zapisywane są procentowe głosy publiczności (buf[0] -> A, buf[1] -> B itd.).
 */

void PytanieDoPublicznosci(char correctAnswer, string answers[4], string question, int buf[4]) {
    int sum = 100, temp;
    int votes[4] = {0,0,0,0};
    int CorrectIndex = toupper(correctAnswer) - 'A';
    if (rand()%(100 +1 ) == 11){
        buf[CorrectIndex] = 0;
    }else{
        buf[CorrectIndex] = (rand() % 41) + 30;
        sum -= buf[CorrectIndex];
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
            buf[i] = pozostale[j];
            j++;
        }
    }
}
