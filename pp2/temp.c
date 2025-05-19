#include "temp.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "button.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
typedef char string[256];
int ilosc_zyc = 1;
ALLEGRO_SAMPLE *aktualna_muzyka = NULL;
ALLEGRO_SAMPLE_INSTANCE *muzyka_instance = NULL;
//Funkcja pokazująca tabele wyników
void tabela_wynikow(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, ALLEGRO_SAMPLE *sound) {
    int SCREEN_W = 1920;
    int SCREEN_H = 1080;

    Button cofnij;
    cofnij.x = SCREEN_W / 2 - 280;
    cofnij.y = SCREEN_H - 150;
    cofnij.w = 560;
    cofnij.h = 90;
    snprintf(cofnij.label, sizeof(cofnij.label), "%s", "Cofnij");
    cofnij.active = true;
    cofnij.hovered = false;

    string top5_nor[5][2], top5_nies[5][2];
    int count_nor = 0, count_nies = 0;
    string nazwa;
    int wynik;

    FILE *file = fopen("top5_klasyczny.txt", "r");
    if (file != NULL) {
        while (count_nor < 5 && fscanf(file, "%255s %d", nazwa, &wynik) == 2) {
            strcpy(top5_nor[count_nor][0], nazwa);
            sprintf(top5_nor[count_nor][1], "%d", wynik);
            count_nor++;
        }
        fclose(file);
    }

    file = fopen("top5_nieskonczony.txt", "r");
    if (file != NULL) {
        while (count_nies < 5 && fscanf(file, "%255s %d", nazwa, &wynik) == 2) {
            strcpy(top5_nies[count_nies][0], nazwa);
            sprintf(top5_nies[count_nies][1], "%d", wynik);
            count_nies++;
        }
        fclose(file);
    }

    while (true) {
        al_clear_to_color(al_map_rgb(20, 20, 50));

        al_draw_text(font, al_map_rgb(255, 255, 0),
                     SCREEN_W / 2, 50, ALLEGRO_ALIGN_CENTRE, "Tabela wyników");

        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 4, 120, 0, "Tryb klasyczny:");
        for (int i = 0; i < count_nor; i++) {
            string buf;
            snprintf(buf, sizeof(buf), "%s   %s", top5_nor[i][0], top5_nor[i][1]);
            al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 4, 180 + i * 30, 0, buf);
        }

        al_draw_text(font, al_map_rgb(255, 255, 255), (SCREEN_W / 4) * 3 - 150, 120, 0, "Tryb nieskończony:");
        for (int i = 0; i < count_nies; i++) {
            string buf;
            snprintf(buf, sizeof(buf), "%s   %s", top5_nies[i][0], top5_nies[i][1]);
            al_draw_text(font, al_map_rgb(255, 255, 255), (SCREEN_W / 4) * 3 - 150, 180 + i * 30, 0, buf);
        }

        draw_button(cofnij, font);
        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit(0);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            int mx = ev.mouse.x, my = ev.mouse.y;
            cofnij.hovered =
                mx >= cofnij.x && mx <= cofnij.x + cofnij.w &&
                my >= cofnij.y && my <= cofnij.y + cofnij.h;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = ev.mouse.x, my = ev.mouse.y;
            if (is_button_clicked(cofnij, mx, my)) {
                al_play_sample(sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break; // powrót do menu
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                   ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
        }
    }
}
//Funkcja pokazująca autorów
void autorzy(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, ALLEGRO_SAMPLE *sound) {

    int SCREEN_W = 1920;
    int SCREEN_H = 1080;
    al_init_image_addon();
    Button cofnij;
    cofnij.x = SCREEN_W / 2 - 280;
    cofnij.y = SCREEN_H - 150;
    cofnij.w = 560;
    cofnij.h = 90;
    snprintf(cofnij.label, sizeof(cofnij.label), "%s", "Cofnij");
    cofnij.active = true;
    cofnij.hovered = false;


    // Załaduj bitmapy (upewnij się, że pliki istnieją)
    ALLEGRO_BITMAP *autor1 = al_load_bitmap("autor3.png");
    ALLEGRO_BITMAP *autor2 = al_load_bitmap("autor2.png");
    ALLEGRO_BITMAP *autor3 = al_load_bitmap("autor1.png");

    while (true) {
        al_clear_to_color(al_map_rgb(20, 20, 50));
        al_draw_text(font, al_map_rgb(255, 255, 0),
                     SCREEN_W / 2, 50, ALLEGRO_ALIGN_CENTRE, "Autorzy");

        if (autor1) {
            al_draw_scaled_bitmap(autor1, 0, 0,
                                  al_get_bitmap_width(autor1), al_get_bitmap_height(autor1),
                                  200 -75, 200, 350, 350, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), 200, 560, 0, "Wiktor Wieczorek");
        }
        else {
            printf("Sperma"); //ważne do debuggingu
        }

        if (autor2) {
            al_draw_scaled_bitmap(autor2, 0, 0,
                                  al_get_bitmap_width(autor2), al_get_bitmap_height(autor2),
                                  860 - 75, 200, 350, 350, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), 860, 560, 0, "Hubert Wilczyński");
        }

        if (autor3) {
            al_draw_scaled_bitmap(autor3, 0, 0,
                                  al_get_bitmap_width(autor3), al_get_bitmap_height(autor3),
                                  1520 - 75, 200, 350, 350, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), 1540, 560, 0, "Hubert Stojek");
        }
        al_draw_text(font, al_map_rgb(255, 255, 255),
                     SCREEN_W/2, 650, ALLEGRO_ALIGN_CENTRE, "Muzyka autorstwa:");
        al_draw_text(font, al_map_rgb(255, 255, 255),
                     SCREEN_W/2, 675, ALLEGRO_ALIGN_CENTRE, "Bartłomiej Drogosz");
        draw_button(cofnij, font);
        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit(0);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            cofnij.hovered =
                mx >= cofnij.x && mx <= cofnij.x + cofnij.w &&
                my >= cofnij.y && my <= cofnij.y + cofnij.h;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            if (is_button_clicked(cofnij, mx, my)) {
                al_play_sample(sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break; // wróć do menu
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                   ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
        }
    }

    al_destroy_bitmap(autor1);
    al_destroy_bitmap(autor2);
    al_destroy_bitmap(autor3);
}

//Funkcja pokazująca możliwość wybrania dwóch trybów (normalny i nieskończony) lub wyjścia spowrotem do głównego menu
int select_game_mode(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, ALLEGRO_SAMPLE *sound, ALLEGRO_SAMPLE *cancel) {

    Button modes[2];
    string labels[2] = { "Tryb normalny", "Tryb nieskończony",};
    int SCREEN_W = 1920;
    int SCREEN_H = 1080;
    Button cofnij;
    cofnij.x = SCREEN_W / 2 - 280;
    cofnij.y = SCREEN_H - 150;
    cofnij.w = 560;
    cofnij.h = 90;
    snprintf(cofnij.label, sizeof(cofnij.label), "%s", "Cofnij");
    cofnij.active = true;
    cofnij.hovered = false;
    for (int i = 0; i < 2; i++) {
        modes[i].x = SCREEN_W / 2 - 280;
        modes[i].y = 300 + i * 100;
        modes[i].w = 560;
        modes[i].h = 90;
        snprintf(modes[i].label, sizeof(modes[i].label), "%s", labels[i]);
        modes[i].active = true;
        modes[i].hovered = false;
    }

    while (true) {
        al_clear_to_color(al_map_rgb(20, 20, 50));

        al_draw_text(font, al_map_rgb(255, 255, 255),
                     SCREEN_W / 2, 150, ALLEGRO_ALIGN_CENTRE, "Wybierz tryb gry");

        for (int i = 0; i < 2; i++) {
            draw_button(modes[i], font);
        }
        draw_button(cofnij, font);
        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit(0);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            cofnij.hovered =
                mx >= cofnij.x && mx <= cofnij.x + cofnij.w &&
                my >= cofnij.y && my <= cofnij.y + cofnij.h;
            for (int i = 0; i < 2; i++) {
                modes[i].hovered =
                    modes[i].active &&
                    mx >= modes[i].x &&
                    mx <= modes[i].x + modes[i].w &&
                    my >= modes[i].y &&
                    my <= modes[i].y + modes[i].h;
            }

        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            if (is_button_clicked(cofnij, mx, my)) {
                al_play_sample(cancel, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                return -1;
            }
            for (int i = 0; i < 2; i++) {
                if (is_button_clicked(modes[i], mx, my)) {
                    al_play_sample(sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    return i; // 0 - normalny, 1 - nieskończony
                }
            }

            } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                return -1;
            }
        }
    }
//Funkcja zwracająca ilość żyć
int ret_zycia() {
    return ilosc_zyc;

}
//Funkcja pokazująca ustawienia (zmiana ilości żyć i muzyki)
void ustawienia(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, ALLEGRO_SAMPLE *sound, ALLEGRO_SAMPLE *cancel) {
    int SCREEN_W = 1920;
    int SCREEN_H = 1080;
    Button cofnij;

    cofnij.x = SCREEN_W / 2 - 280;
    cofnij.y = SCREEN_H - 150;
    cofnij.w = 560;
    cofnij.h = 90;
    snprintf(cofnij.label, sizeof(cofnij.label), "%s", "Cofnij");
    cofnij.active = true;
    cofnij.hovered = false;
    Button zycia[3];
    snprintf(zycia[0].label, sizeof(zycia[0].label), "%s", "-");
    snprintf(zycia[1].label, sizeof(zycia[1].label), "%s", "+");
    for (int i = 0; i < 3; i++) {
        zycia[i].x = SCREEN_W / 2 - 225 + 90 * (i + 1);
        zycia[i].y = 200;
        zycia[i].w = 90;
        zycia[i].h = 90;
        zycia[i].active = true;
        zycia[i].hovered = false;
    }
    string utwory[] = { "muzyka1.mp3", "muzyka2.mp3", "muzyka3.mp3" };
    string nazwy[] = { "Bartek - Sześćdziesiona", "PBG - Tralalelo Tralala", "KML - Spinning Monkeys" };

    Button przyciski[3];
    for (int i = 0; i < 3; i++) {
        przyciski[i].x = SCREEN_W / 2 - 200;
        przyciski[i].y = 450 + i * 100;
        przyciski[i].w = 400;
        przyciski[i].h = 90;
        snprintf(przyciski[i].label, sizeof(przyciski[i].label), "%s", nazwy[i]);
        przyciski[i].active = true;
        przyciski[i].hovered = false;
    }
    while (true) {
        al_clear_to_color(al_map_rgb(20, 20, 50));
        al_draw_text(font, al_map_rgb(255, 255, 0),
                     SCREEN_W / 2, 50, ALLEGRO_ALIGN_CENTRE, "Ustawienia");
        snprintf(zycia[2].label, sizeof(zycia[1].label), "%d", ilosc_zyc);
        al_draw_text(font, al_map_rgb(255, 255, 255),
                     SCREEN_W / 2, 150, ALLEGRO_ALIGN_CENTRE, "Ilość żyć");

        al_draw_text(font, al_map_rgb(255, 255, 255),
                     SCREEN_W / 2, 350, ALLEGRO_ALIGN_CENTRE, "Zmień piosenkę");

        draw_button(cofnij, font);
        draw_button(zycia[0], font);
        draw_button(zycia[1], font);
        draw_button(zycia[2], font);
        for (int i = 0; i < 3; i++)
            draw_button(przyciski[i], font);
        al_flip_display();
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit(0);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            for (int i = 0; i < 3; i++){
                przyciski[i].hovered = mx >= przyciski[i].x && mx <= przyciski[i].x + przyciski[i].w &&
                                       my >= przyciski[i].y && my <= przyciski[i].y + przyciski[i].h;
            }
                cofnij.hovered = mx >= cofnij.x && mx <= cofnij.x + cofnij.w &&
                             my >= cofnij.y && my <= cofnij.y + cofnij.h;
            cofnij.hovered =
                mx >= cofnij.x && mx <= cofnij.x + cofnij.w &&
                my >= cofnij.y && my <= cofnij.y + cofnij.h;
            for (int i = 0; i < 2; i++) {
                zycia[i].hovered =
                mx >= zycia[i].x && mx <= zycia[i].x + zycia[i].w &&
                my >= zycia[i].y && my <= zycia[i].y + zycia[i].h;
            }

        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            for (int i = 0; i < 3; i++) {
                if (is_button_clicked(przyciski[i], mx, my)) {
                    al_play_sample(sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    if (muzyka_instance) al_stop_sample_instance(muzyka_instance);
                    if (aktualna_muzyka) al_destroy_sample(aktualna_muzyka);
                    if (muzyka_instance) al_destroy_sample_instance(muzyka_instance);

                    aktualna_muzyka = al_load_sample(utwory[i]);
                    if (aktualna_muzyka) {
                        muzyka_instance = al_create_sample_instance(aktualna_muzyka);
                        al_attach_sample_instance_to_mixer(muzyka_instance, al_get_default_mixer());
                        al_set_sample_instance_playmode(muzyka_instance, ALLEGRO_PLAYMODE_LOOP);
                        al_play_sample_instance(muzyka_instance);
                    }
                }
            }
            if (is_button_clicked(cofnij, mx, my)) {
                al_play_sample(cancel, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            }
            if (is_button_clicked(zycia[0], mx, my)) {
                al_play_sample(cancel, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                if (ilosc_zyc > 1) {
                    ilosc_zyc--;
                }
            }
            if (is_button_clicked(zycia[1], mx, my)) {
                al_play_sample(sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                ilosc_zyc++;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            al_play_sample(sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            break;
        }
    }

}
//glowne menu
//zwraca 0 -> tryb normalny
//zwraca 1 -> tryb nieskonczony
//zwraca 2 -> wychodzisz z gry
int main_menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font) {
    al_init();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    if (muzyka_instance) {
        al_stop_sample_instance(muzyka_instance);
        al_destroy_sample_instance(muzyka_instance);
        muzyka_instance = NULL;
    }
    if (aktualna_muzyka) {
        al_destroy_sample(aktualna_muzyka);
        aktualna_muzyka = NULL;
    }
    aktualna_muzyka = al_load_sample("muzyka3.mp3");
    if (!aktualna_muzyka) {
        fprintf(stderr, "Nie udało się załadować muzyki!\n");
        return -1;
    }
    ALLEGRO_SAMPLE *click_sound = al_load_sample("button.wav"),
    *cancel_sound = al_load_sample("button_cancel.wav");
    if (!click_sound) {
        fprintf(stderr, "Nie udało się załadować dźwięku!\n");
    }
    if (!cancel_sound) {
        fprintf(stderr, "Nie udało się załadować dźwięku!\n");
    }
    bool in_menu = true;
    int SCREEN_W = 1920;
    int SCREEN_H = 1080;
    const float FPS = 60.0;
    muzyka_instance = al_create_sample_instance(aktualna_muzyka);
    al_attach_sample_instance_to_mixer(muzyka_instance, al_get_default_mixer());
    al_set_sample_instance_playmode(muzyka_instance, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(muzyka_instance);

    while (in_menu) {
        Button starters[5];
        string labels[5] = { "Start", "Tabela wyników", "Ustawienia","Autorzy","Wyjdź" };
        for (int i = 0; i < 5; i++) {
            starters[i].x = SCREEN_W / 2 - 280;
            starters[i].y = 100 * i + 400;
            starters[i].w = 560;
            starters[i].h = 90;
            snprintf(starters[i].label, sizeof(starters[i].label), "%s", labels[i]);
            starters[i].active = true;
        }



        al_clear_to_color(al_map_rgb(20, 20, 50));

        al_draw_text(font, al_map_rgb(255, 255, 0),
                     SCREEN_W / 2, SCREEN_H / 2 - 300,
                     ALLEGRO_ALIGN_CENTRE, "MILIONERZY");


        for (int i = 0; i < 5; i++) {
            draw_button(starters[i], font);
        }
        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit(0);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            for (int i = 0; i < 5; i++) {
                starters[i].hovered =
                    starters[i].active &&
                    mx >= starters[i].x &&
                    mx <= starters[i].x + starters[i].w &&
                    my >= starters[i].y &&
                    my <= starters[i].y + starters[i].h;
            }

        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;

            for (int i = 0; i < 5; i++) {
                if (is_button_clicked(starters[i], mx, my)) {
                    // czemu są dwa te same ify to nie wiem, ale tego nie zmieniam
                    if (i == 0) {
                        if (i == 0) { // Start
                            al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            int mode = select_game_mode(queue, font, click_sound, cancel_sound);
                            if (mode == 0) {
                                return 0;
                                in_menu = false;
                            } else if (mode == 1) {
                                return 1;
                                in_menu = false;
                            }
                            else if (mode == -1) {
                                printf("Powrot");
                            }

                        }
                    } else if (i == 1) { //tabela wyników
                        al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        tabela_wynikow(queue, font, cancel_sound);
                    } else if (i == 2) { //Ustawienia
                        al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        ustawienia(queue, font, click_sound, cancel_sound);
                    } else if (i == 3) { //Autorzy
                        al_play_sample(click_sound, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        autorzy(queue, font, cancel_sound);
                    } else if (i == 4) { //Bye bye
                        exit(0);
                    }
                }
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                //al_destroy_sample(music);
                exit(0);
            }
        }
    }
}


void to_jest_koniec(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font,int runda) {

    int SCREEN_W = 1920;
    int SCREEN_H = 1080;
    int wygrane[13] = {0, 500, 1000, 2000, 5000, 10000, 20000, 40000, 75000, 125000, 250000, 500000, 1000000};
    Button wyjdz;
    wyjdz.x = SCREEN_W / 2 - 280;
    wyjdz.y = SCREEN_H - 150;
    wyjdz.w = 560;
    wyjdz.h = 90;
    snprintf(wyjdz.label, sizeof(wyjdz.label), "%s", "Wyjdź z gry");
    wyjdz.active = true;
    wyjdz.hovered = false;
    string tekst = "";
    snprintf(tekst, sizeof(tekst), "Wygrałeś %d złotych",wygrane[runda - 1]);
    while (1) {
        draw_button(wyjdz, font);
        al_draw_text(font, al_map_rgb(255,255,255),
                     SCREEN_W/2, 70, ALLEGRO_ALIGN_CENTRE, tekst);
        al_flip_display();


        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        al_clear_to_color(al_map_rgb(20, 20, 50));
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit(0);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            wyjdz.hovered =
                mx >= wyjdz.x && mx <= wyjdz.x + wyjdz.w &&
                my >= wyjdz.y && my <= wyjdz.y + wyjdz.h;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;
            if (is_button_clicked(wyjdz, mx, my)) {
                return;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                   ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
                   }
    }
}
void pobierz_imie(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font, string name_buffer) {
    bool done = false;
    int name_length = 0;
    name_buffer[0] = '\0';

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (ev.keyboard.unichar >= 32 && ev.keyboard.unichar <= 126 && name_length < 255) {
                name_buffer[name_length++] = (char)ev.keyboard.unichar;
                name_buffer[name_length] = '\0';
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && name_length > 0) {
                name_length--;
                name_buffer[name_length] = '\0';
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER && name_length > 0) {
                done = true;
            }
        }

        al_clear_to_color(al_map_rgb(20, 20, 50));
        al_draw_text(font, al_map_rgb(255, 255, 255), 960, 400, ALLEGRO_ALIGN_CENTER, "Podaj swoje imię:");
        al_draw_text(font, al_map_rgb(255, 255, 0), 960, 500, ALLEGRO_ALIGN_CENTER, name_buffer);
        al_flip_display();
    }
}


