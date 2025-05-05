#ifndef FILE_RELATED_H
#define FILE_RELATED_H
typedef char string[256];
#include <stdbool.h>
typedef struct possibility{ //Treść pytania, 4 odpowiedzi, poprawna odpowiedź i czy pytanie się pojawiło
    string question;
    string answers[4];
    char correctAnswer; //a, b, c lub d
    bool is_used; //lepszym podejściem byłoby usuwanie pytania z bazy, ale to jest zbyt nudne

}possibility;
typedef struct Node {
    possibility qac;
    struct Node* next;
} Node;


int loadQuestionsFromFile(const char* filename, Node** head);

#endif
