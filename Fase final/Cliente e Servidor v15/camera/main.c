#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <winsock.h>



#define WIDTH 300
#define HEIGHT 300

#define TILE_SIZEH 50
#define TILE_SIZEV 50
#define SPRITE_SIZEH 32
#define SPRITE_SIZEV 40
#define NUM_SPRITES 5
#define FRAMES_PER_SHIFT 10
#define SPEED 1

#define FPS 60

// the world size
int worldWidth = 650;
int worldHeight = 650;

// the camera's position
int cameraX = 0;
int cameraY = 0;

int mapa[13][13] = {
                    1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,3,0,1,0,1,0,1,0,1,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,3,0,1,0,1,0,1,0,1,0,1,
                    1,0,0,0,1,1,0,0,0,0,0,0,1,
                    1,0,0,0,1,0,1,0,1,0,1,0,1,
                    1,0,3,0,3,0,0,0,0,0,0,1,1,
                    1,0,0,0,1,0,1,0,1,0,1,0,1,
                    1,0,0,0,1,0,0,0,0,0,0,0,1,
                    1,0,0,0,1,0,1,0,1,0,1,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1
                    };   // mapa base





int colision(int xa, int ya, int posix, int posiy, int eixo){
       int px, py;
       int coli = 0;
       int anaX, anaY;
       px = xa;
       py = ya;

       if(eixo == 1){
                 px += posix * SPEED;
                        //ponto de borda sprite 1

                        anaX = (px/50);
                        anaY = (py/50);

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        //ponto de borda sprite 2
                        anaX = (px+32)/50;
                        anaY = (py/50);

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        //ponto de borda sprite 3
                        anaX = (px+32)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        if(mapa[anaY][anaX] == 3)
                            coli = 3;

                        //ponto de borda sprite 4
                        anaX = (px)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        if(mapa[anaY][anaX] == 3)
                            coli = 3;




       }else {
                if(eixo == 2){
                            py += posiy * SPEED;
                                 //ponto de borda sprite 1

                        anaX = (px/50);
                        anaY = (py/50);

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        //ponto de borda sprite 2
                        anaX = (px+32)/50;
                        anaY = (py/50);

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        //ponto de borda sprite 3
                        anaX = (px+32)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                       if(mapa[anaY][anaX] == 3)
                            coli = 3;


                        //ponto de borda sprite 4
                        anaX = (px)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        if(mapa[anaY][anaX] == 3)
                            coli = 3;




                    }

       }


        return coli;

}



void error(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);

  exit(EXIT_FAILURE);
}


 int main() {
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
  ALLEGRO_TIMER *timer_mudanca_de_posicao_na_imagem_da_trap = al_create_timer(0.5);

  /**********/
  ALLEGRO_BITMAP *solo = al_load_bitmap("solo.png");
  if(!solo)
    error("failed to load solo");


  ALLEGRO_BITMAP *parede = al_load_bitmap("paredes.png");
  if(!parede)
    error("failed to load paredes");

  ALLEGRO_BITMAP *trap = al_load_bitmap("trap.png");
  if(!trap)
    error("failed to load trap");

    ALLEGRO_BITMAP *traps[5];
    int trapshift;

    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[trapshift]= al_create_sub_bitmap(trap, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }


    int l,m;

    for(l = 0; l < 13; l++){
            for(m = 0; m < 13; m++){
              switch(mapa[m][l]){
                    case 1 :
                        al_draw_bitmap(parede,(l*50)-cameraX,(m*50)-cameraY, 0);
                        break;
                    case 0 :
                        al_draw_bitmap(solo,(l*50)-cameraX,(m*50)-cameraY, 0);
                        break;
                    case 3 :
                        al_draw_bitmap(traps[0],(l*50)-cameraX,(m*50)-cameraY, 0);
                    default :
                        break;
              }
            }
    }

  /**********/

  ALLEGRO_BITMAP *sheet = al_load_bitmap("Red.png");
  if(!sheet)
    error("failed to load sheet");

  ALLEGRO_BITMAP *sprites[NUM_SPRITES][NUM_SPRITES];

  int shift, shiftb;

  for(shift = 0; shift < NUM_SPRITES; shift++){
    for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++){
        sprites[shift][shiftb] = al_create_sub_bitmap(sheet, shiftb * SPRITE_SIZEH, shift * SPRITE_SIZEV, SPRITE_SIZEH, SPRITE_SIZEV);
    }
  }
  shift = 0;
  shiftb = 0;

  // 0 = down, 1 = esquerda, 2 = direita, 3 = cima
  int direction = 0;

  int b;

  int tx, ty;

  int directionV = 0;

  int frame = 0;

  int arm = -1;

  int x = 50;

  int xA;
  int yA;

  int y = 50;

  int flags = 0;

  int pos_x_trap = 1;
  int flag_trap = 0;

  al_draw_bitmap(sprites[shift][shiftb], x-cameraX, y-cameraY, flags);

  /**********/

  al_flip_display();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_timer_event_source(timer_mudanca_de_posicao_na_imagem_da_trap));

  /**********/

  int running = 1;

  int refresh = 0;

  al_start_timer(timer);

  while(running) {
    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);


    switch(event.type) {
    case ALLEGRO_EVENT_KEY_DOWN:
      switch(event.keyboard.keycode) {
      case ALLEGRO_KEY_LEFT:
        if(b != 3){
            direction = -1;
            directionV = 0;
            shiftb = 1;
            flags = 0;
            refresh = 1;
        }
        break;

      case ALLEGRO_KEY_DOWN:

                if(b != 3){
                    directionV = 1;
                    direction = 0;
                    shiftb = 0;
                    flags = 0;
                    refresh = 1;
                }
            break;

      case ALLEGRO_KEY_UP:
            if(b != 3){
                directionV = -1;
                direction = 0;
                shiftb = 3;
                flags = 0;
                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_RIGHT:
            if(b != 3){
                direction = 1;
                directionV = 0;
                shiftb = 2;
                flags = 0;
                refresh = 1;
            }
        break;
      default:
        printf("unknown key down\n");
      }
      break;


    case ALLEGRO_EVENT_KEY_UP:
      switch(event.keyboard.keycode) {
      case ALLEGRO_KEY_LEFT:
        if(direction == -1 ) {
          shift = 0;
          shiftb = 0;
          direction = 0;
          refresh = 1;
        }
        break;


      case ALLEGRO_KEY_DOWN:
            if(directionV == 1){
                shift = 0;
                shiftb = 0;
                directionV = 0;
                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_UP:
          if (directionV == -1 ){
            shift = 0;
            shiftb = 0;
            directionV = 0;
            refresh = 1;
          }
            break;

      case ALLEGRO_KEY_RIGHT:
        if(direction == 1 ) {
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
        if(event.timer.source == timer)
        {
          if(direction != 0) {
            if(shift == 0) {
              shift = 2;
              frame = 0;
            }
            else {
              frame++;
              if(frame == FRAMES_PER_SHIFT) {
                frame = 0;

                shift += arm;

                if(shift != 2)
                  arm = -arm;
              }
            }
            b = colision(x,y,direction,0,1);

            if(b == 0){
                x += direction * SPEED;
                cameraX = x - WIDTH/2;

            }else{
                if (b == 3){
                    al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);

                    pos_x_trap = 1;
                    xA = x;
                    xA = xA/50;
                    xA = xA*50;
                    yA = y;
                    x += direction * SPEED;
                    cameraX = x - WIDTH/2;
                    direction = 0;

                    tx = x/50;
                    ty = (y+40)/50;

                    int inia;
                    if (mapa[ty][tx] != 3){
                        inia = tx + 1;
                        if (mapa[ty][inia] != 3){
                            tx = tx -1;
                        }else{
                            tx = inia;
                        }

                    }
                   printf("trap\n\n");


                }else{
                    x = x;
                }
            }
             // making sure the camera stays within the boundary of the game world
            if (cameraX < 0)
                cameraX = 0;
            if (cameraY < 0)
                cameraY = 0;
            if (cameraX > worldWidth - WIDTH)
                cameraX = worldWidth - WIDTH;
            if (cameraY > worldHeight - HEIGHT)
                cameraY = worldHeight - HEIGHT;


            refresh = 1;
          }

          if(directionV != 0) {
            if(shift == 0) {
              shift = 2;

              frame = 0;
            }
            else {
              frame++;

              if(frame == FRAMES_PER_SHIFT) {
                frame = 0;

                shift += arm;

                if(shift != 2)
                  arm = -arm;
              }
            }
            b = colision(x,y,0,directionV,2);
            if(b == 0){
                y += directionV * SPEED;
                cameraY = y - HEIGHT/2;
            }else{
                if (b == 3){
                    al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                    pos_x_trap = 1;

                    xA = x;
                    yA = y/50;

                    yA = (yA) * 50;
                    y += directionV * SPEED;
                    cameraY = y - HEIGHT/2;

                    directionV = 0;

                    tx =  (x)/50;
                    ty = (y+40)/50;

                       int inia;
                    if (mapa[ty][tx] != 3){
                        inia = tx + 1;
                        if (mapa[ty][inia] != 3){
                            tx = tx -1;
                        }else{
                            tx = inia;
                        }

                    }


                    printf("trap\n\n");

                }else{
                    y =y;
                }

            }
                // making sure the camera stays within the boundary of the game world
            if (cameraX < 0)
                cameraX = 0;

            if (cameraY < 0)
                cameraY = 0;

            if (cameraX > worldWidth - WIDTH)
                cameraX = worldWidth - WIDTH;

            if (cameraY > worldHeight - HEIGHT)
                cameraY = worldHeight - HEIGHT;


            refresh = 1;


          }



        }
        if(event.timer.source == timer_mudanca_de_posicao_na_imagem_da_trap)
        {
            puts("hail\n");
            if(pos_x_trap <= 3 && flag_trap == 0)
            {
                pos_x_trap++;
                if(pos_x_trap == 3 && flag_trap == 0){
                        x = xA;
                        y = yA;

                }
            }
            else
            {

                flag_trap = 1;
                pos_x_trap--;

                if(pos_x_trap == 0)
                {
                    puts("1");
                    al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                    puts("2");
                    b = 0;
                    flag_trap = 0;
                }
            }
            refresh = 1;
        }

    break;
    default:
      printf("unknown event\n");
    }

    if(refresh) {


        for(l = 0; l < 13; l++){
            for(m = 0; m < 13; m++){
              switch(mapa[m][l]){
                    case 1 :
                        al_draw_bitmap(parede,(l*50)-cameraX,(m*50)-cameraY, 0);
                        break;
                    case 0 :
                        al_draw_bitmap(solo,(l*50)-cameraX,(m*50)-cameraY, 0);
                        break;
                    case 3 :
                        al_draw_bitmap(traps[0],(l*50)-cameraX,(m*50)-cameraY, 0);
                    default :
                        break;
              }
            }
        }

        if(b == 3)
            al_draw_bitmap(traps[pos_x_trap],(tx*50)-cameraX,(ty*50)-cameraY, 0);

        al_draw_bitmap(sprites[shiftb][shift], x-cameraX, y-cameraY, flags);

        // make the camera follow the player


      al_flip_display();

      refresh = 0;

    }



  }

  /**********/

  al_stop_timer(timer);

  al_unregister_event_source(queue, al_get_timer_event_source(timer));
  al_unregister_event_source(queue, al_get_display_event_source(display));
  al_unregister_event_source(queue, al_get_keyboard_event_source());

  al_destroy_bitmap(parede);
  al_destroy_bitmap(trap);
  al_destroy_bitmap(solo);







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
