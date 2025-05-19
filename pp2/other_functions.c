#include <string.h>
#include <ctype.h> //toupper{
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
#include "other_functions.h"

#define MAX_GRACZY 100
#define MAX_NAZWA 50
#define TOP_N 5




// Created by Hubi_Core on 5/3/25.



// Funkcja porównująca do sortowania malejącego
int porownaj_graczy(const void* a, const void* b) {
    return ((Gracz*)b)->wynik - ((Gracz*)a)->wynik;
}

// Zapisz top 5 graczy do osobnego pliku
void zapisz_top5(Gracz gracze[], int liczbaGraczy, const int tryb) {
    string nazwaPliku;

    if (tryb == 0) {
        strcpy(nazwaPliku, "top5_klasyczny.txt");
    } else {
        strcpy(nazwaPliku, "top5_nieskonczony.txt");
    }

    FILE *file = fopen(nazwaPliku, "w");
    if (file == NULL) {
        printf("Błąd przy zapisie top5!\n");
        return;
    }

    int limit = liczbaGraczy < TOP_N ? liczbaGraczy : TOP_N;
    for (int i = 0; i < limit; i++) {
        fprintf(file, "%s %d\n", gracze[i].nazwa, gracze[i].wynik);
    }

    fclose(file);
}
//Funkcja wypisująca tablice wyników dla konkretnego trybu gry (klasyczny, nieskonczony)
void wyswietl_leaderboard(int tryb) {
    string nazwaPliku;

    if (tryb == 0) {
        strcpy(nazwaPliku, "top5_klasyczny.txt");
    } else if (tryb == 1) {
        strcpy(nazwaPliku, "top5_nieskonczony.txt");
    } else {
        printf("Nieznany tryb gry!\n");
        return;
    }

    FILE *file = fopen(nazwaPliku, "r");
    if (file == NULL) {
        printf("Nie udało się otworzyć pliku z leaderboardem!\n");
        return;
    }

    string nazwa;
    int wynik;
    while (fscanf(file, "%s %d", nazwa, &wynik) == 2) {
        printf("%s - %d\n", nazwa, wynik);
    }

    fclose(file);
}
//wszystko co ważne do leaderboardów (tworzenie leaderboard_klasyczny i nieskonczony i top5...)

int leaderboard(const char* imie, int wynik, const int tryb) {
    string nazwaPliku;


    if (tryb== 0) {
        strcpy(nazwaPliku, "leaderboard_klasyczny.txt");
    } else if (tryb == 1) {
        strcpy(nazwaPliku, "leaderboard_nieskonczony.txt");
    } else {
        printf("Nieznany tryb gry!\n");
        return 1;
    }

    FILE *file = fopen(nazwaPliku, "r");
    Gracz gracze[MAX_GRACZY];
    int liczbaGraczy = 0;
    int znaleziono = 0;


    if (file != NULL) {
        while (fscanf(file, "%s %d", gracze[liczbaGraczy].nazwa, &gracze[liczbaGraczy].wynik) == 2) {
            liczbaGraczy++;
            if (liczbaGraczy >= MAX_GRACZY) break;
        }
        fclose(file);
    }


    for (int i = 0; i < liczbaGraczy; i++) {
        if (strcmp(gracze[i].nazwa, imie) == 0) {
            gracze[i].wynik += wynik;
            znaleziono = 1;
            break;
        }
    }

    if (!znaleziono && liczbaGraczy < MAX_GRACZY) {
        strncpy(gracze[liczbaGraczy].nazwa, imie, MAX_NAZWA - 1);
        gracze[liczbaGraczy].nazwa[MAX_NAZWA - 1] = '\0';
        gracze[liczbaGraczy].wynik = wynik;
        liczbaGraczy++;
    }


    qsort(gracze, liczbaGraczy, sizeof(Gracz), porownaj_graczy);


    file = fopen(nazwaPliku, "w");
    if (file == NULL) {
        printf("Błąd przy otwieraniu pliku do zapisu!\n");
        return 1;
    }

    for (int i = 0; i < liczbaGraczy; i++) {
        fprintf(file, "%s %d\n", gracze[i].nazwa, gracze[i].wynik);
    }

    fclose(file);


    zapisz_top5(gracze, liczbaGraczy, tryb);

    return 0;
}
/*
//glowne menu
//zwraca 0 -> tryb normalny
//zwraca 1 -> tryb nieskonczony
//zwraca 2 -> wychodzisz z gry
int main_menu(){
    printf("1.Start\n");
    printf("2.Tabela wynikow\n");
    printf("3.Autorzy\n");
    printf("4.Wyjscie\n");
    while (1){
        int odpowiedz, odpowiedz2;
        scanf("%d", &odpowiedz);
        switch(odpowiedz)
        {
            case 1:
                printf("1.Normalny\n");
            printf("2.Nieskonczony\n");
            scanf("%d", &odpowiedz2);
            if (odpowiedz2 == 1){
                return 0;
            }
            else{
                return 1;
            }
            break;
            case 2:
                printf("Tryb normalny:\n");
            wyswietl_leaderboard(0);
            printf("Tryb nieskonczony:\n");
            wyswietl_leaderboard(1);
            break;
            case 3:
                printf("Wiktor Wieczorek\nHubert Wilczynski\nHubert Stojek\n");
            break;
            case 4:
                return 2;
            break;
        }
    }
}
*/