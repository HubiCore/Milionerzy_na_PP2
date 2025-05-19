//
// Created by Lenovo on 06.05.2025.
//

#ifndef BUTTON_H
#define BUTTON_H
typedef struct {
    float x, y, w, h;
    char label[64];
    bool active; // czy nadal można kliknąć
    bool hovered;
} Button;
void draw_button(Button btn, ALLEGRO_FONT* font);
bool is_button_clicked(Button btn, int mouse_x, int mouse_y);
void draw_button_color(Button btn, ALLEGRO_FONT* font, ALLEGRO_COLOR inactive, ALLEGRO_COLOR hovered, ALLEGRO_COLOR normal, ALLEGRO_COLOR bord, ALLEGRO_COLOR color_text);
#endif //BUTTON_H
