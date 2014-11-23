#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <winsock.h>



#define WIDTH 650
#define HEIGHT 650

#define TILE_SIZEH 50
#define TILE_SIZEV 50
#define SPRITE_SIZEH 48
#define SPRITE_SIZEV 64
#define NUM_SPRITES 5
#define FRAMES_PER_SHIFT 10
#define SPEED 1

#define FPS 60

int mapa[13][13] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1
};   // mapa base







void error(char *message)
{
    fprintf(stderr, "ERROR: %s\n", message);

    exit(EXIT_FAILURE);
}


int main()
{
    if(!al_init())
        error("failed to initialize");

    if(!al_install_keyboard())
        error("failed to install keyboard");

    if(!al_init_image_addon())
        error("failed to initialize image addon");

    if(!al_init_primitives_addon())
        error("failed to initialize primitives addon");

    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    if(!display)
        error("failed to create display");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if(!queue)
        error("failed to create event queue");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if(!timer)
        error("failed to create timer");

    /**********/
    ALLEGRO_BITMAP *solo = al_load_bitmap("solo.png");
    if(!solo)
        error("failed to load solo");


    ALLEGRO_BITMAP *parede = al_load_bitmap("paredes.png");
    if(!solo)
        error("failed to load paredes");

    int l,m;

    for(l = 0; l < 14; l++)
    {
        for(m = 0; m < 14; m++)
        {
            if(mapa[l][m] == 1)
            {
                al_draw_bitmap(parede,l*50,m*50, 0);
            }
            else
            {
                al_draw_bitmap(solo,l*50,m*50, 0);
            }
        }
    }

    /**********/

    ALLEGRO_BITMAP *sheet = al_load_bitmap("images.png");
    if(!sheet)
        error("failed to load sheet");

    ALLEGRO_BITMAP *sprites[NUM_SPRITES][NUM_SPRITES];

    int shift, shiftb;

    for(shift = 0; shift < NUM_SPRITES; shift++)
    {
        for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++)
        {
            sprites[shift][shiftb] = al_create_sub_bitmap(sheet, shiftb * SPRITE_SIZEH, shift * SPRITE_SIZEV, SPRITE_SIZEH, SPRITE_SIZEV);
        }
    }
    shift = 0;
    shiftb = 0;

    // 0 = down, 1 = esquerda, 2 = direita, 3 = cima
    int direction = 0;

    int directionV = 0;

    int frame = 0;

    int arm = -1;

    int x = (WIDTH - SPRITE_SIZEH) / 2;

    int y = (HEIGHT - SPRITE_SIZEV)/2;

    int flags = 0;

    al_draw_bitmap(sprites[shift][shiftb], x, y, flags);

    /**********/

    al_flip_display();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    /**********/

    int running = 1;

    int refresh = 0;

    al_start_timer(timer);

    while(running)
    {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);


        switch(event.type)
        {
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                direction = -1;

                directionV = 0;

                shiftb = 1;

                flags = 0;

                refresh = 1;

                break;

            case ALLEGRO_KEY_DOWN:
                directionV = 1;

                direction = 0;

                shiftb = 0;

                flags = 0;

                refresh = 1;

                break;

            case ALLEGRO_KEY_UP:
                directionV = -1;

                direction = 0;

                shiftb = 3;

                flags = 0;

                refresh = 1;

                break;

            case ALLEGRO_KEY_RIGHT:
                direction = 1;

                directionV = 0;

                shiftb = 2;

                flags = 0;

                refresh = 1;

                break;
            default:
                printf("unknown key down\n");
            }
            break;


        case ALLEGRO_EVENT_KEY_UP:
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                if(direction == -1)
                {
                    shift = 0;

                    shiftb = 0;

                    direction = 0;

                    refresh = 1;
                }
                break;


            case ALLEGRO_KEY_DOWN:
                if(directionV == 1)
                {
                    shift = 0;

                    shiftb = 0;

                    directionV = 0;

                    refresh = 1;
                }
                break;

            case ALLEGRO_KEY_UP:
                if (directionV == -1)
                {
                    shift = 0;

                    shiftb = 0;

                    directionV = 0;

                    refresh = 1;
                }
                break;

            case ALLEGRO_KEY_RIGHT:
                if(direction == 1)
                {
                    shift = 0;

                    shiftb = 0;

                    direction = 0;

                    refresh = 1;
                }
                break;
            default:
                printf("unknown key up\n");
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            running = 0;

            break;
        case ALLEGRO_EVENT_TIMER:
            if(direction != 0)
            {
                if(shift == 0)
                {
                    shift = 2;

                    frame = 0;
                }
                else
                {
                    frame++;

                    if(frame == FRAMES_PER_SHIFT)
                    {
                        frame = 0;

                        shift += arm;

                        if(shift != 2)
                            arm = -arm;
                    }
                }

                x += direction * SPEED;
                refresh = 1;

            }

            if(directionV != 0)
            {
                if(shift == 0)
                {
                    shift = 2;

                    frame = 0;
                }
                else
                {
                    frame++;

                    if(frame == FRAMES_PER_SHIFT)
                    {
                        frame = 0;

                        shift += arm;

                        if(shift != 2)
                            arm = -arm;
                    }
                }

                y += directionV * SPEED;

                refresh = 1;


            }

            break;
        default:
            printf("unknown event\n");
        }

        if(refresh)
        {

            for(l = 0; l < 14; l++)
            {
                for(m = 0; m < 14; m++)
                {
                    if(mapa[l][m] == 1)
                    {
                        al_draw_bitmap(parede,l*50,m*50, 0);
                    }
                    else
                    {
                        al_draw_bitmap(solo,l*50,m*50, 0);
                    }
                }
            }



            al_draw_bitmap(sprites[shiftb][shift], x, y, flags);


            al_flip_display();

            refresh = 0;
        }
    }

    /**********/

    al_stop_timer(timer);

    al_unregister_event_source(queue, al_get_timer_event_source(timer));
    al_unregister_event_source(queue, al_get_display_event_source(display));
    al_unregister_event_source(queue, al_get_keyboard_event_source());


    for(l = 0; l < 14; l++)
    {
        for(m = 0; m < 14; m++)
        {
            if(mapa[l][m] == 1)
            {
                al_destroy_bitmap(parede);
            }
            else
            {
                al_destroy_bitmap(solo);
            }
        }
    }




    for(shift = 0; shift < NUM_SPRITES; shift++)
        for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++)
            al_destroy_bitmap(sprites[shift][shiftb]);



    al_destroy_bitmap(sheet);



    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_uninstall_keyboard();
    al_uninstall_system();

    return EXIT_SUCCESS;
}


