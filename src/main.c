#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define WIDTH  512
#define HEIGHT 512

typedef enum {
    MENU, GAME
} state;

void draw_menu() {
    al_draw_rectangle((WIDTH/2)-100, (HEIGHT/2)-100, (WIDTH/2)+100, (HEIGHT/2)+20, al_map_rgb(0, 0, 0), 5);
    al_draw_rectangle((WIDTH/2)-40, (HEIGHT/2)+40, (WIDTH/2)+40, (HEIGHT/2)+70, al_map_rgb(0, 0, 0), 5);

}

int main() {

    if(!al_init())                  { printf("\033[1;31mINIT_ERR\033[0m: Couldn't initialize allegro!\n"); return -1; }       else { printf("\033[32mINIT\033[0m: Initialized allegro.\n");}
    if(!al_install_keyboard())      { printf("\033[1;31mINIT_ERR\033[0m: Couldn't install keyboard!\n"); return -1;}          else { printf("\033[32mINIT\033[0m: Initialized keyboard.\n");}
    if(!al_install_mouse())         { printf("\033[1;31mINIT_ERR\033[0m: Couldn't install mouse!\n"); return -1;}             else { printf("\033[32mINIT\033[0m: Initialized mouse.\n");}
    if(!al_install_audio())         { printf("\033[1;31mINIT_ERR\033[0m: Couldn't install audio!\n"); return -1;}             else { printf("\033[32mINIT\033[0m: Initialized audio.\n");}
    if(!al_init_image_addon())      { printf("\033[1;31mINIT_ERR\033[0m: Couldn't initilize image addon\n"); return -1;}      else { printf("\033[32mINIT\033[0m: Initialized image addon.\n");}
    if(!al_init_primitives_addon()) { printf("\033[1;31mINIT_ERR\033[0m: Couldn't initilize primitives addon\n"); return -1;} else { printf("\033[32mINIT\033[0m: Initialized primitives addon.\033[0m\n");}
    if(!al_init_ttf_addon())        { printf("\033[1;31mINIT_ERR\033[0m: Couldn't initilize ttf addon\n"); return -1;}        else { printf("\033[32mINIT\033[0m: Initialized ttf addon.\n");}
    if(!al_init_acodec_addon())     { printf("\033[1;31mINIT_ERR\033[0m: Couldn't initilize acodec addon\n"); return -1;}     else { printf("\033[32mINIT\033[0m: Initialized acodec addon.\n");}


    ALLEGRO_TIMER* timer       = al_create_timer(1.0 / 60.0);         if(!timer)   { printf("\033[1;31mINIT_ERR: Couldn't create timer!\033[0m\n"); return -1;}        else{ printf("\33[;32mINIT: Created timer.\033[0m\n");}
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();             if(!queue)   { printf("\033[1;31mINIT_ERR: Couldn't create event queue!\033[0mn\n"); return -1;} else{ printf("\33[;32mINIT: Created event queue.\033[0m\n");}
    ALLEGRO_DISPLAY* display   = al_create_display(WIDTH, HEIGHT);    if(!display) { printf("\033[1;31mINIT_ERR: Couldn't create display!\033[0m\n"); return -1;}      else{ printf("\33[;32mINIT: Created display.\033[0m\n");}
    ALLEGRO_FONT* font24       = al_load_ttf_font("font.ttf", 24, 0); if(!font24)  { printf("\033[1;31mINIT_ERR: Couldn't create font!\033[0m\n"); return -1;}         else{ printf("\33[;32mINIT: Created font.\033[0m\n");}
    ALLEGRO_FONT* font40       = al_load_ttf_font("font.ttf", 40, 0); if(!font40)  { printf("\033[1;31mINIT_ERR: Couldn't create font!\033[0m\n"); return -1;}         else{ printf("\33[;32mINIT: Created font.\033[0m\n");}

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;

    state game_state = MENU;

    ALLEGRO_EVENT event;
    // ALLEGRO_MOUSE_STATE mouse_state;

    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    while(!done)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                redraw = true;

                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN;

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                // al_get_mouse_state(&mouse_state);

                // if (mouse_state.display != NULL)
                // {
                    
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        
        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(178, 244, 244));

            switch (game_state)
            {
            case MENU:
                draw_menu();
                break;
            
            case GAME:
                /* code */
                break;

            default:
                break;
            }
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_font(font24);
    al_destroy_font(font40);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return 0;
}
