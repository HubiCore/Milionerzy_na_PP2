#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
//#include <locale.h> biblioteka wymagana do liczb losowych, na linuksie nie potrzebna
#include <string.h>
#include <ctype.h> //toupper{
#include <unistd.h>
#include "other_functions.h"
#include "kola_ratunkowe.h"
#include "question_loading.h"
typedef char string[256];
#define MAX_GRACZY 100
#define MAX_NAZWA 50
#define TOP_N 5

//funkcja wypisująca strukture

int main() {
    //system("chcp 65001");
    //setlocale(LC_ALL, " ");
    //rzeczy wymagane do polskich napisów, na linuksie nie potrzebne
    int questionNumber = 0; //to troche jest nieuzywane ale zostawiam bo smieszne
    srand(time(NULL));
    Node* head = NULL;
    int result = loadQuestionsFromFile("pytania_bhp.txt", &head);

    if (result != 0) {
        return 1;
    }
    result = loadQuestionsFromFile("pytania_psk.txt", &head);

    if (result != 0) {
        return 1;
    }
    printf("==============================\n");
    printf("    WITAJ W GRZE MILIONERZY!   \n");
    printf("==============================\n\n");

    char playerAnswer;
    string player_name;
    possibility skibidi_toilet;
    int i = 0, m_m, wynik;
    int life = 1;
    m_m = main_menu();
    if (m_m == 2){
        printf("Do zobaczenia !!!\n");
        freeList(head);
        return 0;
    }
    printf("Podaj twoje imie (jeden wyraz):\n");
    scanf(" %s", &player_name);
    printf("\n\n\n\n\n");
    int kolo_tel = 1, kolo_fifty_fifty = 1, kolo_publika = 1;
    while(1){
        if (life == 0){
            printf("Przegrałes :c");
            leaderboard(player_name, i, m_m);
            freeList(head);
            return 0;
        }
        if (m_m == 0 && i > 15){
            printf("==============================\n");
            printf("    WYGRAŁEŚ MILION ZŁOTYCH   \n");
            printf("==============================\n\n");
            return 0;
        }
        skibidi_toilet = lets_go_gambling(head);
        printf("Pytanie nr %d\n",i + 1);
        wypisz_poss(skibidi_toilet);
        printf("Podaj odpowiedź (A B C D) lub użyj koła ratunkowego (% -> 50/50 lub P -> pytanie do publiczności lub T -> telefon do przyjaciela)\n");
        while (1){
            scanf(" %c", &playerAnswer);
            if (toupper(playerAnswer) == 'q'){
                leaderboard(player_name, i, m_m);
                return 0;
            }
            if (playerAnswer == '%'){
                if (kolo_fifty_fifty == 1) {
                    fiftyFifty(skibidi_toilet.correctAnswer, skibidi_toilet.answers);
                    kolo_fifty_fifty = 0;
                }else printf("Kolo zostalo uzyte\n");
                }else if (toupper( playerAnswer) == 'P'){
                    if (kolo_publika == 1) {
                        PytanieDoPublicznosci(skibidi_toilet.correctAnswer, skibidi_toilet.answers, skibidi_toilet.question);
                        kolo_publika = 0;
                    }else printf("Kolo zostalo uzyte\n");
                }else if (toupper( playerAnswer) == 'T') {
                    if (kolo_tel == 1) {
                        call_to_friend();
                        kolo_tel = 0;
                    }else printf("Kolo zostalo uzyte\n");
                }else{

                    if (toupper(playerAnswer) == skibidi_toilet.correctAnswer) {
                        printf("Brawo! To poprawna odpowiedz!\n\n");
                        break;
                    } else {
                        printf("Niestety, to bledna odpowiedz. Prawidlowa odpowiedz to: %c\n\n", skibidi_toilet.correctAnswer);
                        life--;
                        break;
                        }
                    }
        }
    i++;
    }

    freeList(head);
    return 0;
}
