/**
* @file main_menu.h
 * @brief Plik nagłówkowy do main_menu.c
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

//
// Created by Lenovo on 07.05.2025.
//

#ifndef TEMP_H
#define TEMP_H
typedef char string[256];
int main_menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font);
void to_jest_koniec(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, int runda, int tryb);
void pobierz_imie(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, string name_buffer);
int ret_zycia();
#endif //TEMP_H
