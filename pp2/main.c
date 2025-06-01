/**
* @file main.c
 * @brief Główny plik
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "question_loading.h"
#include "button.h"
#include "kola_ratunkowe.h"
#include "other_functions.h"
#include "main_menu.h"
/**
 * @brief Szerokość okna aplikacji (w pikselach).
 */
const int SCREEN_W = 1920;

/**
 * @brief Wysokość okna aplikacji (w pikselach).
 */
const int SCREEN_H = 1080;

/**
 * @brief Liczba klatek na sekundę (FPS).
 */
const float FPS = 60.0;

/**
 * @typedef string
 * @brief Alias na tablicę znaków o długości 256 (ciąg tekstowy zakończony znakiem null).
 */
typedef char string[256];


int main() {
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(0);
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_BITMAP* tlo = al_load_bitmap("tlo_lepsze2.png");
    ALLEGRO_BITMAP* icon = al_load_bitmap("icon.png");
    if (!icon) {
        fprintf(stderr, "Nie udało się załadować ikony!\n");
        return -1;
    }
    al_set_display_icon(display, icon);
    if (!tlo) {
        fprintf(stderr, "Nie udało się załadować tła!\n");
        return -1;
    }
    ALLEGRO_FONT* font = al_load_ttf_font("DejaVuSans.ttf", 24, 0);
    if (!display) {
        fprintf(stderr, "Nie udało się stworzyć ekranu\n");
        return -1;
    }
    if (!queue) {
        fprintf(stderr, "Nie udało się stworzyć kolejki zdarzeń\n");
        return -1;
    }
    if (!timer) {
        fprintf(stderr, "Nie udało się stworzyć timera\n");
        return -1;
    }
    if (!font) {
        fprintf(stderr, "Nie udało się załadować fontu\n");
        return -1;
    }
    Node* head = NULL;
    int result = loadQuestionsFromFile("pytania_bhp.txt", &head);
    if (result != 0) {
        return 1;
    }
    result = loadQuestionsFromFile("pytania_fnaf.txt", &head);
    if (result != 0) {
        return 1;
    }
    result = loadQuestionsFromFile("pytania_granie.txt", &head);

    if (result != 0) {
        return 1;
    }
    result = loadQuestionsFromFile("pytania_jedzenie.txt", &head);
    if (result != 0) {
        return 1;
    }
    result = loadQuestionsFromFile("pytania_kielce.txt", &head);
    if (result != 0) {
        return 1;
    }
    result = loadQuestionsFromFile("pytania_psk.txt", &head);
    if (result != 0) {
        return 1;
    }
    ALLEGRO_SAMPLE *click_sound = al_load_sample("button.wav");
    if (!click_sound) {
        fprintf(stderr, "Nie udało się załadować dźwięku!\n");
    }

    //rzeczy do dźwięków
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    int m_m = main_menu(display, queue, font);
    string imie;
    pobierz_imie(queue, font, imie);
    al_start_timer(timer);

    
    bool running = true;
    bool answered = false;
    int question_count = 1;
    int selected = -1;
    int feedback_time = 0;
    possibility skibidi_toilet;
    Button lifeline_buttons[3];
    bool show_audience_votes = false;
    int audience_votes[4] = {0};
    int zycia = ret_zycia();
    bool show_fifty_fifty = false;
    bool show_phone = false;
    int odliczanie = 30;
    float countdown = 30.0f;
    char wrong_fifty;
    string ilosc_zyc_wypisz = "Ilość życ: ";
    bool no_idea = false; //to g*wno jest potrzebne by dekrementacja tylko raz się wykonała
    string labels[3] = { "telefon do przyjaciela", "50/50", "pytanie do publiczności" };
    bool wrong = false;
    for (int i = 0; i < 3; i++) {
        lifeline_buttons[i].x = 100 + i * 580;
        lifeline_buttons[i].y = 930;
        lifeline_buttons[i].w = 560;
        lifeline_buttons[i].h = 50;
        snprintf(lifeline_buttons[i].label, sizeof(lifeline_buttons[i].label), "%s", labels[i]);
        lifeline_buttons[i].active = true;
    }
    Button leave;
    leave.x = SCREEN_W - 100;
    leave.y = 10;
    leave.w = 90;
    leave.h = 90;
    leave.hovered = false;
    snprintf(leave.label, sizeof(leave.label), "%s", "X");
    leave.active = true;
    skibidi_toilet = lets_go_gambling(head);
    Button answer_buttons[4];
    for (int i = 0; i < 4; i++) {
        answer_buttons[i].x = 100;
        answer_buttons[i].y = 600 + i * 80;
        answer_buttons[i].w = SCREEN_W - 200;
        answer_buttons[i].h = 60;
        snprintf(answer_buttons[i].label, sizeof(answer_buttons[i].label), "%s", skibidi_toilet.answers[i]);
        answer_buttons[i].active = true;
        answer_buttons[i].hovered = false;
    }


    int bruh;
    bool used = false;
    while (running) {

            ALLEGRO_EVENT ev;
            al_wait_for_event(queue, &ev);
            if (ev.type == ALLEGRO_EVENT_TIMER) {

                if (show_phone) {
                    if (used == false) {
                        bruh = question_count;
                        used = true;
                    }
                    if (bruh != question_count) {
                        show_phone = false;
                        odliczanie = 0;
                        used = false;
                    }
                    if (countdown > 0.0f) {
                        countdown -= 1.0f / FPS;
                    }
                    static int countdown_frames = 0;
                    countdown_frames++;

                    if (countdown_frames >= FPS) {
                        odliczanie--;
                        countdown_frames = 0;

                        if (odliczanie <= 0) {
                            show_phone = false;
                            odliczanie = 0;
                            used = false;

                        }
                    }
                }
                // po udzieleniu odpowiedzi pokazujemy odpowiedz poprawna na 2 sekundy
                if (answered) {
                    feedback_time++;

                    if (feedback_time > FPS * 2) {
                        if (zycia == 0 || (question_count == 13 && m_m == 0)) {
                            leaderboard(imie,question_count, m_m);
                            printf("Dokonano");
                            to_jest_koniec(queue,font,question_count, m_m);
                            al_destroy_font(font);
                            al_destroy_timer(timer);
                            al_destroy_event_queue(queue);
                            al_destroy_display(display);
                            freeList(head);
                            return 0;
                        }
                        else {
                            // Przejdź do kolejnego pytania
                            skibidi_toilet = lets_go_gambling(head); // nowe pytanie
                            for (int i = 0; i < 4; i++) {
                                answer_buttons[i].x = 100;
                                answer_buttons[i].y = 600 + i * 80;
                                answer_buttons[i].w = SCREEN_W - 200;
                                answer_buttons[i].h = 60;
                                snprintf(answer_buttons[i].label, sizeof(answer_buttons[i].label), "%s", skibidi_toilet.answers[i]);
                                answer_buttons[i].active = true;
                                answer_buttons[i].hovered = false;
                            }

                            answered = false;
                            selected = -1;
                            feedback_time = 0;
                            show_fifty_fifty = false;
                            show_audience_votes = false;
                            no_idea = false;
                            if (wrong == false) {
                                question_count++;
                            }
                            else {
                                wrong = false;
                            }
                            for (int i = 0; i < 4; i++) audience_votes[i] = 0;
                        }
                    }
                }


                // rysowanie
                al_draw_bitmap(tlo, 0, 0, 0);

                //al_clear_to_color(al_map_rgb(30, 30, 60));//kolor tl
                for (int i = 0; i < 3; i++) {
                    draw_button(lifeline_buttons[i], font);
                }

                draw_button_color(leave, font, al_map_rgb(80, 0, 0), al_map_rgb(255, 100, 100), al_map_rgb(160, 0, 0), al_map_rgb(100, 0, 0), al_map_rgb(255, 255, 255));
                // pytanie
                string tekst ="";
                snprintf(tekst, sizeof(tekst), "Pytanie nr %d: %s", question_count, skibidi_toilet.question);
                al_draw_text(font, al_map_rgb(255,255,255),
                             SCREEN_W/2, 50, ALLEGRO_ALIGN_CENTRE, tekst);
                snprintf(ilosc_zyc_wypisz, sizeof(ilosc_zyc_wypisz), "Zostało żyć: %d", zycia);
                al_draw_text(font, al_map_rgb(255,255,255),
                             200, 100, ALLEGRO_ALIGN_CENTRE, ilosc_zyc_wypisz);

                for (int i = 0; i < 4; i++) {
                    if (show_fifty_fifty) {
                        int correctIndex = skibidi_toilet.correctAnswer - 'A';
                        int badIndex = wrong_fifty - 'A';
                        answer_buttons[i].active = (i == correctIndex || i == badIndex);
                    } else {
                        answer_buttons[i].active = true;
                    }
                    if (show_phone) {
                        char buffer[64];
                        sprintf(buffer, "%d", odliczanie);
                        al_draw_filled_circle(1700, 513, 35, al_map_rgb(80,80,120));
                        al_draw_circle(1700, 513, 35, al_map_rgb(255, 255, 255), 4);
                        float angle = (countdown/ 30.0f) * ALLEGRO_PI * 2.0;
                        al_draw_arc(1700, 513, 35 - 10, -ALLEGRO_PI / 2, angle, al_map_rgb(227, 110, 14), 8);
                        al_draw_text(font, al_map_rgb(255, 255, 255), 1700, 500, ALLEGRO_ALIGN_CENTRE, buffer);

                    }
                    if (answer_buttons[i].active) {
                        if (answered) {
                            int correctIndex = skibidi_toilet.correctAnswer - 'A';
                            if (i == correctIndex) {
                                draw_button_color_not_centered(answer_buttons[i], font, //correct
                                                  al_map_rgb(0, 200, 0),
                                                  al_map_rgb(0, 255, 0),
                                                  al_map_rgb(0, 160, 0),
                                                  al_map_rgb(0, 100, 0),
                                                  al_map_rgb(255, 255, 255));
                            } else if (i == selected && selected != correctIndex) { //wrong
                                draw_button_color_not_centered(answer_buttons[i], font,
                                                  al_map_rgb(200, 0, 0),
                                                  al_map_rgb(255, 0, 0),
                                                  al_map_rgb(160, 0, 0),
                                                  al_map_rgb(100, 0, 0),
                                                  al_map_rgb(255, 255, 255));
                                if (no_idea == false) {
                                    zycia--;
                                    wrong = true;
                                    no_idea = true;}
                            } else {
                                draw_button_not_centered(answer_buttons[i], font);
                            }
                        } else {
                            draw_button_not_centered(answer_buttons[i], font);
                        }

                        // dodaj % głosów jeśli trzeba
                        if (show_audience_votes) {
                            char vote_text[16];
                            sprintf(vote_text, "%d%%", audience_votes[i]);
                            al_draw_text(font, al_map_rgb(255, 255, 255),
                                         answer_buttons[i].x + answer_buttons[i].w - 70,
                                         answer_buttons[i].y + 17, 0, vote_text);
                        }
                    }
                }


                al_flip_display();
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false;
            }
            else if (!answered && ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (ev.keyboard.keycode >= ALLEGRO_KEY_1 &&
                    ev.keyboard.keycode <= ALLEGRO_KEY_4) {
                    selected = ev.keyboard.keycode - ALLEGRO_KEY_1;
                    answered = true;
                    }
            }
            else if (!answered && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mx = ev.mouse.x, my = ev.mouse.y;
                if (is_button_clicked(leave, mx, my)) {
                    leaderboard(imie,question_count, m_m);
                    al_destroy_font(font);
                    al_destroy_timer(timer);
                    al_destroy_event_queue(queue);
                    al_destroy_display(display);
                    freeList(head);
                    return 0;
                }
                for (int i = 0; i < 4; i++) {
                    if (answer_buttons[i].active && is_button_clicked(answer_buttons[i], mx, my)) {
                        selected = i;
                        answered = true;
                    }
                }

                for (int i = 0; i < 3; i++) {
                    if (is_button_clicked(lifeline_buttons[i], mx, my)) {
                        printf("Kliknięto: %s\n", lifeline_buttons[i].label);
                        if (i == 0) { //telefon
                            al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                show_phone = true;
                        } else if (i == 1) { //50/50
                            al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            wrong_fifty = fiftyFifty(skibidi_toilet.correctAnswer,skibidi_toilet.answers);
                            show_fifty_fifty = true;
                        } else if (i == 2) { //publicznosc
                            al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            PytanieDoPublicznosci(skibidi_toilet.correctAnswer,skibidi_toilet.answers,skibidi_toilet.question,audience_votes);
                            show_audience_votes = true;
                        }

                        lifeline_buttons[i].active = false; // Wyłącz użyty przycisk
                    }
                }

            }
            if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
                int mx = ev.mouse.x;
                int my = ev.mouse.y;
                leave.hovered = mx >= leave.x && mx <= leave.x + leave.w &&
                    my >= leave.y && my <= leave.y + leave.h;
                for (int i = 0; i < 3; i++) {
                    lifeline_buttons[i].hovered =
                        lifeline_buttons[i].active &&
                        mx >= lifeline_buttons[i].x &&
                        mx <= lifeline_buttons[i].x + lifeline_buttons[i].w &&
                        my >= lifeline_buttons[i].y &&
                        my <= lifeline_buttons[i].y + lifeline_buttons[i].h;
                }
                for (int i = 0; i < 4; i++) {
                    answer_buttons[i].hovered = answer_buttons[i].active &&
                        mx >= answer_buttons[i].x &&
                        mx <= answer_buttons[i].x + answer_buttons[i].w &&
                        my >= answer_buttons[i].y &&
                        my <= answer_buttons[i].y + answer_buttons[i].h;
                }

            }
        }

    // --- Sprzątanie ---
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    freeList(head);
    return 0;
}
