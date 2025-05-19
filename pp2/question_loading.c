#include <string.h>
#include <ctype.h> //toupper{
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
#include "question_loading.h"

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
   srand(time(NULL));
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

