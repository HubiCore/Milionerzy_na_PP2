#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
//#include <locale.h> biblioteka wymagana do liczb losowych, na linuksie nie potrzebna
#include <string.h>
#include <ctype.h> //toupper{
#include <unistd.h>

#include "kola_ratunkowe.h"
typedef char string[256];
#define MAX_GRACZY 100
#define MAX_NAZWA 50
#define TOP_N 5

typedef struct {
    string nazwa;
    int wynik;
} Gracz;

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
//struktura pytania (treść pytania, odpowiedzi i poprawna odpowiedź)
typedef struct possibility{ //Treść pytania, 4 odpowiedzi, poprawna odpowiedź i czy pytanie się pojawiło
        string question;
        string answers[4];
        char correctAnswer; //a, b, c lub d


}possibility;

//funkcja wypisująca strukture
void wypisz_poss(possibility pytanie_testowe){
    printf("%s\n",pytanie_testowe.question);
        int i;
        for (i = 0; i < 4; i++){
                printf("%s\n", pytanie_testowe.answers[i]);
        }
}
//funkcja czyszcząca bufor
void clearBuffer() {
    while (getchar() != '\n');
}

//Bóg mi świadkiem, że ta lista to morderca studentów
typedef struct Node {
    possibility qac;
    struct Node* next;
} Node;

// Funkcja tworząca nowy węzeł
Node* createNode(possibility qac) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Error!\n");
        exit(1);
    }
    newNode->qac = qac;
    newNode->next = newNode;
    return newNode;
}

// Funkcja dodająca element na koniec listy
void insert(Node** head, possibility qac) {
    Node* newNode = createNode(qac);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}
//funkcja ładująca tekst z pliku do stuktury
int loadQuestionsFromFile(const char* filename, Node** head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku z pytaniami!\n");
        return 1; // Error opening file
    }

    possibility zapisywanie;
    int validAnswers;

    while (fgets(zapisywanie.question, sizeof(zapisywanie.question), file)) {
        if (zapisywanie.question[0] == '\n' || zapisywanie.question[0] == '\r') continue;

        validAnswers = 1;
        for (int i = 0; i < 4; i++) {
            if (fgets(zapisywanie.answers[i], sizeof(zapisywanie.answers[i]), file) == NULL || zapisywanie.answers[i][0] == '\n') {
                printf("Problem z odpowiedziami\n");
                validAnswers = 0;
                break;
            }
        }

        if (fscanf(file, " %c", &zapisywanie.correctAnswer) != 1) {
            printf("Blad podczas wczytywania poprawnej odpowiedzi!\n");
            fclose(file);
            return 1;
        }
        fgetc(file);
        if (!validAnswers) break;
        fgetc(file);
        insert(head, zapisywanie);
    }
    fclose(file);
    return 0;
}
// Funkcja usuwająca element z listy
void deleteNode(Node** head, string key) {
    if (*head == NULL) return;
    Node *temp = *head, *prev = NULL;

    if (strcmp(temp->qac.question, key) == 0 && temp->next == *head) {
        free(temp);
        *head = NULL;
        return;
    }

    do {
        prev = temp;
        temp = temp->next;

        if (strcmp(temp->qac.question, key) == 0) {
            break;
        }
    } while (temp != *head);

    if (strcmp(temp->qac.question, key) != 0) return;

    prev->next = temp->next;
    if (*head == temp) *head = prev->next;
    free(temp);
}

//funkcja bierze liste, losuje losowy element i zwraca
//DONE: jeżeli funkcja została użyta to skipuje pytanie lub je usuwa
//trzeba głęboko kopiować (deep copy) i twedy zwracać wynik
possibility lets_go_gambling(Node* head){
    if (head == NULL){
        printf("Lista jest pusta \n");
    }
    int randomNumber = rand()%200 + 1;
    Node* temp = head;
    for (int i = 0; i < randomNumber; i++) {
        temp = temp->next;
    }
    possibility result;
    strcpy(result.question, temp->qac.question);
    for (int i = 0; i < 4; i++) {
        strcpy(result.answers[i], temp->qac.answers[i]);
    }
    result.correctAnswer = temp->qac.correctAnswer;



    //possibility result = temp->qac;
    deleteNode(&head, result.question);
    return result;
}
// Funkcja wyświetlająca elementy listy
void display(Node* head) {
    Node* temp = head;
    int i = 0;
    do {
        printf("Pytanie nr%d: %s\n", i++, temp->qac.question);
        temp = temp->next;
    } while (temp != head);
}


//Funkcja czyszcząca liste
void freeList(Node* head) {
    if (head == NULL) return;
    Node* temp = head;
    Node* nextNode = NULL;

    do {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    } while (temp != head);

    head = NULL;
}

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
