/**
 * @file button.c
 * @brief Funkcje rysujące i obsługujące przyciski przy użyciu biblioteki Allegro.
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "button.h"

/**
 * @brief Rysuje przycisk wyśrodkowany tekstem.
 *
 * @param btn Struktura Button opisująca pozycję i stan przycisku.
 * @param font Czcionka używana do wyświetlenia etykiety przycisku.
 */
void draw_button(Button btn, ALLEGRO_FONT* font) {
    ALLEGRO_COLOR bg;

    if (!btn.active) {
        bg = al_map_rgb(40, 40, 40); // nieaktywny
    } else if (btn.hovered) {
        bg = al_map_rgb(100, 100, 160); // podświetlony
    } else {
        bg = al_map_rgb(80, 80, 120); // normalny
    }

    ALLEGRO_COLOR border = al_map_rgb(200, 200, 0);
    ALLEGRO_COLOR text = al_map_rgb(255, 255, 255);

    al_draw_filled_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, bg);
    al_draw_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, border, 2);
    al_draw_text(font, text,
                 btn.x + btn.w / 2,
                 btn.y + (btn.h - al_get_font_line_height(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, btn.label);
}

/**
 * @brief Rysuje przycisk z tekstem wyrównanym do lewej (np. do pytań).
 *
 * @param btn Struktura Button opisująca pozycję i stan przycisku.
 * @param font Czcionka używana do wyświetlenia etykiety przycisku.
 */
void draw_button_not_centered(Button btn, ALLEGRO_FONT* font) {
    ALLEGRO_COLOR bg;

    if (!btn.active) {
        bg = al_map_rgb(40, 40, 40);
    } else if (btn.hovered) {
        bg = al_map_rgb(100, 100, 160);
    } else {
        bg = al_map_rgb(80, 80, 120);
    }

    ALLEGRO_COLOR border = al_map_rgb(200, 200, 0);
    ALLEGRO_COLOR text = al_map_rgb(255, 255, 255);

    al_draw_filled_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, bg);
    al_draw_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, border, 2);
    al_draw_text(font, text,
                 btn.x + 10,
                 btn.y + (btn.h - al_get_font_line_height(font)) / 2,
                 0, btn.label);
}

/**
 * @brief Rysuje kolorowy przycisk z tekstem wyrównanym do lewej.
 *
 * @param btn Struktura Button.
 * @param font Czcionka.
 * @param inactive Kolor tła dla nieaktywnego przycisku.
 * @param hovered Kolor tła dla podświetlonego przycisku.
 * @param normal Kolor tła dla zwykłego przycisku.
 * @param bord Kolor obramowania.
 * @param color_text Kolor tekstu.
 */
void draw_button_color_not_centered(Button btn, ALLEGRO_FONT* font, ALLEGRO_COLOR inactive, ALLEGRO_COLOR hovered, ALLEGRO_COLOR normal, ALLEGRO_COLOR bord, ALLEGRO_COLOR color_text) {
    ALLEGRO_COLOR bg;

    if (!btn.active) {
        bg = inactive;
    } else if (btn.hovered) {
        bg = hovered;
    } else {
        bg = normal;
    }

    ALLEGRO_COLOR border = bord;
    ALLEGRO_COLOR text = color_text;

    al_draw_filled_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, bg);
    al_draw_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, border, 2);
    al_draw_text(font, text,
                 btn.x + 10,
                 btn.y + (btn.h - al_get_font_line_height(font)) / 2,
                 0, btn.label);
}

/**
 * @brief Sprawdza, czy przycisk został kliknięty.
 *
 * @param btn Przycisk do sprawdzenia.
 * @param mouse_x Pozycja X kursora myszy.
 * @param mouse_y Pozycja Y kursora myszy.
 * @return true jeśli kliknięto aktywny przycisk.
 * @return false w przeciwnym wypadku.
 */
bool is_button_clicked(Button btn, int mouse_x, int mouse_y) {
    return btn.active &&
           mouse_x >= btn.x && mouse_x <= btn.x + btn.w &&
           mouse_y >= btn.y && mouse_y <= btn.y + btn.h;
}

/**
 * @brief Rysuje kolorowy przycisk z wyśrodkowanym tekstem.
 *
 * @param btn Struktura Button.
 * @param font Czcionka.
 * @param inactive Kolor tła dla nieaktywnego przycisku.
 * @param hovered Kolor tła dla podświetlonego przycisku.
 * @param normal Kolor tła dla zwykłego przycisku.
 * @param bord Kolor obramowania.
 * @param color_text Kolor tekstu.
 */
void draw_button_color(Button btn, ALLEGRO_FONT* font, ALLEGRO_COLOR inactive, ALLEGRO_COLOR hovered, ALLEGRO_COLOR normal, ALLEGRO_COLOR bord, ALLEGRO_COLOR color_text) {
    ALLEGRO_COLOR bg;

    if (!btn.active) {
        bg = inactive;
    } else if (btn.hovered) {
        bg = hovered;
    } else {
        bg = normal;
    }

    ALLEGRO_COLOR border = bord;
    ALLEGRO_COLOR text = color_text;

    al_draw_filled_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, bg);
    al_draw_rectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, border, 6);
    al_draw_text(font, text,
                 btn.x + btn.w / 2,
                 btn.y + (btn.h - al_get_font_line_height(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, btn.label);
}
