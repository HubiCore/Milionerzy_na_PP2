/**
 * @file other_functions.c
 * @brief Obsługa leaderboardów: zapisywanie wyników, sortowanie i wyświetlanie.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "other_functions.h"

#define MAX_GRACZY 100  ///< Maksymalna liczba graczy na leaderboardzie.
#define MAX_NAZWA 50    ///< Maksymalna długość nazwy gracza.
#define TOP_N 5         ///< Liczba graczy w top5.

/**
 * @brief Funkcja porównująca dwóch graczy według wyniku malejąco (do sortowania).
 *
 * @param a Wskaźnik na pierwszego gracza.
 * @param b Wskaźnik na drugiego gracza.
 * @return Różnica wyników: dodatnia jeśli b > a.
 */
int porownaj_graczy(const void* a, const void* b) {
    return ((Gracz*)b)->wynik - ((Gracz*)a)->wynik;
}

/**
 * @brief Zapisuje top 5 graczy do pliku, zależnie od trybu gry.
 *
 * @param gracze Tablica struktur Gracz.
 * @param liczbaGraczy Liczba wszystkich graczy w tablicy.
 * @param tryb Tryb gry: 0 - klasyczny, 1 - nieskończony.
 */
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

/**
 * @brief Wyświetla zawartość leaderboardu z pliku odpowiedniego dla danego trybu.
 *
 * @param tryb Tryb gry: 0 - klasyczny, 1 - nieskończony.
 */
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

/**
 * @brief Aktualizuje leaderboard: dodaje/edytuje wynik gracza i zapisuje top5.
 *
 * @param imie Imię gracza.
 * @param wynik Uzyskany wynik.
 * @param tryb Tryb gry: 0 - klasyczny, 1 - nieskończony.
 * @return 0 jeśli sukces, 1 jeśli błąd.
 */
int leaderboard(const char* imie, int wynik, const int tryb) {
    string nazwaPliku;

    if (tryb == 0) {
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
            if (wynik > gracze[i].wynik) {
                gracze[i].wynik = wynik;
            }
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
