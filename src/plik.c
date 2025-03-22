#include <stdio.h>
#include <stdlib.h>
#include <time.h> //losowe liczby
#include <stdbool.h> //bool
#include <string.h>
#include <ctype.h> //toupper
typedef char string[256];


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
    newNode->next = newNode; // Wskazuje na siebie, tworząc cykl
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
//funkcja bierze liste, losuje losowy element i zwraca
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
void fiftyFifty(char correctAnswer, string answers[4]) {
    int wrongIndices[3];
    int wrongCount = 0;

    for (int i = 0; i < 4; i++) {
        if (answers[i][0] != correctAnswer) {
            wrongIndices[wrongCount++] = i;
        }
    }

    srand(time(NULL));
    int keepWrongIndex = wrongIndices[rand() % wrongCount];

    printf("Pozostaja odpowiedzi:\n");
    for (int i = 0; i < 4; i++) {
        if (answers[i][0] == correctAnswer || i == keepWrongIndex) {
            printf("%s", answers[i]);
        }
    }
}
int main() {
    int questionNumber = 0;
    srand(time(NULL));
    FILE *file = fopen("pytania_bhp.txt", "r");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku z pytaniami!\n");
        return 1;
    }
    possibility zapisywanie;
    Node* head = NULL;
    while (fgets(zapisywanie.question, sizeof(zapisywanie.question), file)) {
        // Pomijanie pustych linii
        if (zapisywanie.question[0] == '\n' || zapisywanie.question[0] == '\r') continue;

        // Wczytywanie odpowiedzi
        int validAnswers = 1;
        for (int i = 0; i < 4; i++) {
            if (fgets(zapisywanie.answers[i], sizeof(zapisywanie.answers[i]), file) == NULL || zapisywanie.answers[i][0] == '\n') {
                printf("Problem z odpowiedziami");
                validAnswers = 0;
                break;
            }
        }
        if (fscanf(file, " %c", &zapisywanie.correctAnswer) != 1) {
            printf("%d\n", zapisywanie.correctAnswer);
            printf("Blad podczas wczytywania poprawnej odpowiedzi!\n");
            fclose(file);
            return 1;
        }
        fgetc(file);
        if (!validAnswers) break;
        fgetc(file);
        insert(&head, zapisywanie);
    }
    fclose(file);
    printf("==============================\n");
    printf("    WITAJ W GRZE MILIONERZY!   \n");
    printf("==============================\n\n");
    char playerAnswer;
    possibility skibidi_toilet;
    skibidi_toilet = lets_go_gambling(head);
    wypisz_poss(skibidi_toilet);
    printf("Podaj odpowiedź (A B C D) lub użyj koła ratunkowego (% -> 50/50 lub P -> pytanie do publiczności)\n");
    while (1){
    scanf(" %c", &playerAnswer);
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
                break;
                }
            }
    }
    return 0;
}

