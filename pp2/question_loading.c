/**
 * @file question_loading.c
 * @brief Obsługa wczytywania i przetwarzania pytań testowych z pliku do listy cyklicznej.
 */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "question_loading.h"

/**
 * @brief Wypisuje pytanie i możliwe odpowiedzi na standardowe wyjście.
 *
 * @param pytanie_testowe Struktura zawierająca pytanie i odpowiedzi.
 */
void wypisz_poss(possibility pytanie_testowe){
    printf("%s\n", pytanie_testowe.question);
    for (int i = 0; i < 4; i++) {
        printf("%s\n", pytanie_testowe.answers[i]);
    }
}

/**
 * @brief Czyści bufor wejścia, pomocne przy scanf/getchar.
 */
void clearBuffer() {
    while (getchar() != '\n');
}

/**
 * @brief Tworzy nowy węzeł listy cyklicznej.
 *
 * @param qac Pytanie z odpowiedziami do wstawienia.
 * @return Wskaźnik na nowy węzeł.
 */
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

/**
 * @brief Dodaje nowe pytanie na koniec cyklicznej listy jednokierunkowej.
 *
 * @param head Wskaźnik do wskaźnika na głowę listy.
 * @param qac Struktura zawierająca pytanie i odpowiedzi.
 */
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

/**
 * @brief Wczytuje pytania z pliku tekstowego i zapisuje je do listy.
 *
 * @param filename Nazwa pliku z pytaniami.
 * @param head Wskaźnik do wskaźnika na głowę listy.
 * @return 0 jeśli sukces, 1 jeśli wystąpił błąd.
 */
int loadQuestionsFromFile(const char* filename, Node** head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku z pytaniami!\n");
        return 1;
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

        fgetc(file); // Przejście do nowej linii po odpowiedzi
        if (!validAnswers) break;
        fgetc(file); // Pusta linia między pytaniami

        insert(head, zapisywanie);
    }

    fclose(file);
    return 0;
}

/**
 * @brief Usuwa węzeł z listy na podstawie treści pytania.
 *
 * @param head Wskaźnik do wskaźnika na głowę listy.
 * @param key Pytanie, które ma zostać usunięte.
 */
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

/**
 * @brief Losuje pytanie z listy, usuwa je i zwraca.
 *
 * @param head Wskaźnik na głowę listy.
 * @return Losowo wybrane pytanie.
 */
possibility lets_go_gambling(Node* head) {
    srand(time(NULL));
    if (head == NULL) {
        printf("Lista jest pusta \n");
    }

    int randomNumber = rand() % 200 + 1;
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

    deleteNode(&head, result.question);
    return result;
}

/**
 * @brief Wyświetla wszystkie pytania z listy.
 *
 * @param head Wskaźnik na głowę listy.
 */
void display(Node* head) {
    Node* temp = head;
    int i = 0;
    do {
        printf("Pytanie nr%d: %s\n", i++, temp->qac.question);
        temp = temp->next;
    } while (temp != head);
}

/**
 * @brief Zwalnia pamięć zajmowaną przez całą listę pytań.
 *
 * @param head Wskaźnik na głowę listy.
 */
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
