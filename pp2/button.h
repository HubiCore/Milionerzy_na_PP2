/**
* @file button.h
 * @brief Plik nagłówkowy do button.c
 */
#ifndef BUTTON_H
#define BUTTON_H
/**
 * @struct Button
 * @brief Struktura reprezentująca przycisk interfejsu użytkownika.
 *
 * Zawiera informacje o położeniu, rozmiarze, etykiecie oraz stanie aktywności i najechania.
 */
typedef struct {
    float x;           /**< Współrzędna X lewego górnego rogu przycisku. */
    float y;           /**< Współrzędna Y lewego górnego rogu przycisku. */
    float w;           /**< Szerokość przycisku. */
    float h;           /**< Wysokość przycisku. */
    char label[64];    /**< Tekst wyświetlany na przycisku (maks. 63 znaki). */
    bool active;       /**< Czy przycisk jest aktywny (czy reaguje na kliknięcia). */
    bool hovered;      /**< Czy kursor myszy znajduje się nad przyciskiem. */
} Button;

void draw_button(Button btn, ALLEGRO_FONT* font);
void draw_button_not_centered(Button btn, ALLEGRO_FONT* font);
void draw_button_color_not_centered(Button btn, ALLEGRO_FONT* font, ALLEGRO_COLOR inactive, ALLEGRO_COLOR hovered, ALLEGRO_COLOR normal, ALLEGRO_COLOR bord, ALLEGRO_COLOR color_text);
bool is_button_clicked(Button btn, int mouse_x, int mouse_y);
void draw_button_color(Button btn, ALLEGRO_FONT* font, ALLEGRO_COLOR inactive, ALLEGRO_COLOR hovered, ALLEGRO_COLOR normal, ALLEGRO_COLOR bord, ALLEGRO_COLOR color_text);
#endif //BUTTON_H
