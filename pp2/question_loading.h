/**
* @file question_loading.h
 * @brief Plik nagłówkowy do question_loading.c
 */

#ifndef QUESTION_LOADING_H
#define QUESTION_LOADING_H
/**
 * @typedef string
 * @brief Alias na tablicę znaków o długości 256 (ciąg tekstowy zakończony znakiem null).
 */
typedef char string[256];
/**
 * @struct possibility
 * @brief Struktura reprezentująca jedno pytanie quizowe.
 *
 * Zawiera treść pytania, cztery możliwe odpowiedzi oraz oznaczenie poprawnej.
 */
typedef struct possibility {
    string question;        /**< Treść pytania. */
    string answers[4];      /**< Tablica czterech możliwych odpowiedzi (A–D). */
    char correctAnswer;     /**< Poprawna odpowiedź — litera: 'A', 'B', 'C' lub 'D'. */
} possibility;


/**
 * @struct Node
 * @brief Węzeł cyklicznej listy jednokierunkowej przechowującej pytania.
 *
 * Każdy węzeł zawiera jedno pytanie typu `possibility` oraz wskaźnik na następny element listy.
 * Bóg mi świadkiem, że ta lista to morderca studentów
 */
typedef struct Node {
    possibility qac;     /**< Dane pytania (question and choices). */
    struct Node* next;   /**< Wskaźnik na kolejny węzeł w liście. */
} Node;


void wypisz_poss(possibility pytanie_testowe);
void clearBuffer();
Node* createNode(possibility qac);
void insert(Node** head, possibility qac);
int loadQuestionsFromFile(const char* filename, Node** head);
void deleteNode(Node** head, string key);
possibility lets_go_gambling(Node* head);
void display(Node* head);
void freeList(Node* head);
#endif //QUESTION_LOADING_H
