/**
* @file other_functions.h
 * @brief Plik nagłówkowy do other_function.c
 */

#ifndef OTHER_FUNCTIONS_H
#define OTHER_FUNCTIONS_H
/**
 * @typedef string
 * @brief Alias na tablicę znaków o długości 256 (ciąg tekstowy zakończony znakiem null).
 */
typedef char string[256];
/**
 * @struct Gracz
 * @brief Struktura przechowująca dane gracza.
 *
 * Zawiera nazwę gracza oraz jego osiągnięty wynik w grze.
 */
typedef struct {
    string nazwa;  /**< Nazwa gracza (ciąg znaków o maks. długości 255). */
    int wynik;     /**< Wynik gracza zapisany jako liczba całkowita. */
} Gracz;

int porownaj_graczy(const void* a, const void* b);
void zapisz_top5(Gracz gracze[], int liczbaGraczy, const int tryb);
void wyswietl_leaderboard(int tryb) ;
int leaderboard(const char* imie, int wynik, const int tryb);
#endif //OTHER_FUNCTIONS_H
