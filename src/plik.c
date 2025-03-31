#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
#include <stdbool.h> //bool
#include <string.h>
#include <ctype.h> //toupper
#include "kola_ratunkowe.h"
typedef char string[256];

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
                printf("tabela");
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
typedef struct possibility{ //Treść pytania, 4 odpowiedzi, poprawna odpowiedź i czy pytanie się pojawiło
        string question;
        string answers[4];
        char correctAnswer; //a, b, c lub d
        bool is_used; //lepszym podejściem byłoby usuwanie pytania z bazy, ale to jest zbyt nudne

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
//losowanie z pliku
int loadQuestionsFromFile(const char* filename, Node** head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku z pytaniami!\n");
        return 1; // Error opening file
    }

    possibility zapisywanie;
    int validAnswers;

    while (fgets(zapisywanie.question, sizeof(zapisywanie.question), file)) {
        // Skip empty lines
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
            return 1; // Error reading correct answer
        }

        fgetc(file);  // To consume the newline character after the correct answer
        if (!validAnswers) break;
        fgetc(file);  // To consume any extra newline character after answers

        insert(head, zapisywanie); // Insert the question into the linked list
    }

    fclose(file); // Close the file
    return 0; // Success
}
//funkcja bierze liste, losuje losowy element i zwraca
//TODO: jeżeli funkcja została użyta to skipuje pytanie lub je usuwa
possibility lets_go_gambling(Node* head){
    if (head == NULL){
        printf("Lista jest pusta \n");
    }
    int randomNumber = rand()%200 + 1;
    Node* temp = head;
    for (int i=0; i < randomNumber; i++){
        temp = temp -> next;
    }
    temp->qac.is_used = true;
    return temp->qac;
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
        if (strcmp(temp->qac.question, key) == 0) break;
    } while (temp != *head);

    if (strcmp(temp->qac.question, key) != 0) return;
    prev->next = temp->next;
    if (*head == temp) *head = prev->next;
    free(temp);
}
//Funkcja czyszcząca liste
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int questionNumber = 0;
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
        return 0;
    }
    printf("Podaj twoje imie:\n");
    scanf(" %s", &player_name);
    printf("\n\n\n\n\n");
    while(1){
        if (life == 0){
            printf("Przegrałes :c");
            return 0;
        }
        if (m_m == 0 && i > 15){
            printf("==============================\n");
            printf("    WYGRAŁEŚ MILION ZŁOTYCH   \n");
            printf("==============================\n\n");
            return 0;
        }
        skibidi_toilet = lets_go_gambling(head);
        wypisz_poss(skibidi_toilet);
        printf("Podaj odpowiedź (A B C D) lub użyj koła ratunkowego (% -> 50/50 lub P -> pytanie do publiczności)\n");
        while (1){
            scanf(" %c", &playerAnswer);
            if (playerAnswer == 'q'){
                return 0;
            }
            if (playerAnswer == '%'){
                    fiftyFifty(skibidi_toilet.correctAnswer, skibidi_toilet.answers);
                }else if (playerAnswer == 'P'){
                    printf("tutaj inne kolo ratunkowe\n");
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
    return 0;
}
