/**
* @file kola_ratunkowe.h
 * @brief Plik nagłówkowy do kola_ratunkowe.h
 */
#ifndef KOLA_RATUNKOWE_H
#define KOLA_RATUNKOWE_H

/**
 * @typedef string
 * @brief Alias na tablicę znaków o długości 256 (ciąg tekstowy zakończony znakiem null).
 */
typedef char string[256];
char fiftyFifty(char correctAnswer, string answers[4]);
void call_to_friend();
void clear_input_buffer();
void PytanieDoPublicznosci(char correctAnswer, string answers[4], string question, int buf[4]);
#endif
