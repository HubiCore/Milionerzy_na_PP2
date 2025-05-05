//
// Created by Hubi_Core on 5/3/25.
//

#ifndef OTHER_FUNCTIONS_H
#define OTHER_FUNCTIONS_H
typedef char string[256];
typedef struct {
    string nazwa;
    int wynik;
} Gracz;
int main_menu();
int porownaj_graczy(const void* a, const void* b);
void zapisz_top5(Gracz gracze[], int liczbaGraczy, const int tryb);
void wyswietl_leaderboard(int tryb) ;
int leaderboard(const char* imie, int wynik, const int tryb);
#endif //OTHER_FUNCTIONS_H
