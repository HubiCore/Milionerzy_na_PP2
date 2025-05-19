//
// Created by Hubi_Core on 5/5/25.
//

#ifndef QUESTION_LOADING_H
#define QUESTION_LOADING_H
typedef char string[256];
//struktura pytania (treść pytania, odpowiedzi i poprawna odpowiedź)
typedef struct possibility{ //Treść pytania, 4 odpowiedzi, poprawna odpowiedź i czy pytanie się pojawiło
    string question;
    string answers[4];
    char correctAnswer; //a, b, c lub d


}possibility;
//Bóg mi świadkiem, że ta lista to morderca studentów
typedef struct Node {
    possibility qac;
    struct Node* next;
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
