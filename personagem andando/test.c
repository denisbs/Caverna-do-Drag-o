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
#define SPRITE_SIZEH 32
#define SPRITE_SIZEV 40
#define NUM_SPRITES 5
#define FRAMES_PER_SHIFT 10
#define SPEED 1

#define FPS 60


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


struct Reds{
      int x, xA; // x do personagem
      int y, yA; // y do personagem
      int sprite; // imagem atual do personagem
      int direcaoS;
      int moveV;
      int moveH; //direção do personagem

      int frame;
      int arm;

};

struct Reds red;

struct trapAtiva{
    int x;
    int y;
};

struct trapAtiva TAFu;



void setmove(int lado){
    // 0 = down, 1 = esquerda, 2 = direita, 3 = cima - mapa de sprites moves
    switch(lado){
        case 1:
             red.moveH = -1;
             red.moveV = 0;
             red.direcaoS = 1;
             break;
        case 2:
             red.moveH = 1;
             red.moveV = 0;
             red.direcaoS = 2;

             break;int frame;
        case 3:
            red.moveH = 0;
            red.moveV = -1;
            red.direcaoS = 3;

            break;
        case 4:
            red.moveH = 0;
            red.moveV = 1;
            red.direcaoS = 0;
            break;
        case 0:
            red.moveH = 0;
            red.moveV = 0;
            red.direcaoS = 0;
            red.sprite = 0;
            break;
        default:
            break;
    }
}

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

int testex(){
     int esta;

            if(red.sprite == 0) {
              red.sprite = 2;
              red.frame = 0;
            }
            else {
              red.frame++;
              if(red.frame == FRAMES_PER_SHIFT) {
                red.frame = 0;

                red.sprite += red.arm;

                if(red.sprite != 2)
                  red.arm = -red.arm;
              }
            }
            esta = colision(red.x,red.y,red.moveH,0,1);

            if(esta == 0){
                red.x += red.moveH * SPEED;
            }
                if (esta == 3){


                    red.xA = red.x;
                    red.xA = red.xA/50;
                    red.xA = red.xA*50;
                    red.yA = red.y;
                    red.x += red.moveH * SPEED;

                    red.moveH = 0;

                    TAFu.x = red.x/50;
                    TAFu.y = (red.y+40)/50;

                    int inia;
                    if (mapa[TAFu.y][TAFu.x] != 3){
                        inia = TAFu.x + 1;
                        if (mapa[TAFu.y][inia] != 3){
                            TAFu.x = TAFu.x -1;
                        }else{
                            TAFu.x = inia;
                        }

                    }
                   printf("trap\n\n");


                }

                return esta;
}

int testey(){
    int esta;


     if(red.sprite == 0) {
        red.sprite = 2;
        red.frame = 0;
     }else {
        red.frame++;

        if(red.frame == FRAMES_PER_SHIFT) {
                red.frame = 0;

                red.sprite += red.arm;

                if(red.sprite != 2)
                  red.arm = -red.arm;
              }
            }
            esta = colision(red.x,red.y,0,red.moveV,2);
            if(esta == 0){
                red.y += red.moveV * SPEED;
            }else{
                if (esta == 3){

                    red.xA = red.x;
                    red.yA = red.y/50;

                    red.yA = (red.yA) * 50;
                    red.y += red.moveV * SPEED;

                    red.moveV = 0;

                    TAFu.x =  (red.x)/50;

                    TAFu.y = (red.y+40)/50;

                    int inia;
                    if (mapa[TAFu.y][TAFu.x] != 3){
                        inia = TAFu.x + 1;
                        if (mapa[TAFu.y][inia] != 3){
                            TAFu.x = TAFu.x -1;
                        }else{
                            TAFu.x = inia;
                        }

                    }



                    printf("trap\n\n");

                }

}
        return esta;
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

    for(l = 0; l < 14; l++){
            for(m = 0; m < 14; m++){
              switch(mapa[m][l]){
                    case 1 :
                        al_draw_bitmap(parede,l*50,m*50, 0);
                        break;
                    case 0 :
                        al_draw_bitmap(solo,l*50,m*50, 0);
                        break;
                    case 3 :
                        al_draw_bitmap(traps[0],l*50,m*50, 0);
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


  red.sprite = 0;
  red.direcaoS = 0;
  red.moveH = 0;
  red.moveV = 0;

  red.x = 50;
  red.y = 50;
  // 0 = down, 1 = esquerda, 2 = direita, 3 = cima
  int b; //condição de colisão com trsap


  red.frame = 0;

  red.arm = -1;

  int flags = 0;
  int pos_x_trap = 1;
  int flag_trap = 0;

  al_draw_bitmap(sprites[red.direcaoS][red.sprite], red.x, red.y, flags);

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
            setmove(1);
            flags = 0;
            refresh = 1;
        }
        break;

      case ALLEGRO_KEY_DOWN:

                if(b != 3){
                    setmove(4);
                    flags = 0;
                    refresh = 1;
                }
            break;

      case ALLEGRO_KEY_UP:
            if(b != 3){
                setmove(3);
                flags = 0;
                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_RIGHT:
            if(b != 3){
                setmove(2);
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
        if(red.moveH == -1 ) {
          setmove(0);
          refresh = 1;
        }
        break;


      case ALLEGRO_KEY_DOWN:
            if(red.moveV == 1){
                setmove(0);
                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_UP:
          if (red.moveV == -1 ){
            setmove(0);
            refresh = 1;
          }
            break;

      case ALLEGRO_KEY_RIGHT:
        if(red.moveH == 1 ) {
          setmove(0);
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

          if(red.moveH != 0){
            b = testex();
            if(b == 3){
                al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                pos_x_trap = 1;
            }
            refresh = 1;
          }

          if(red.moveV != 0){
            b = testey();
             if(b == 3){
                al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                pos_x_trap = 1;
            }
            refresh = 1;
          }



          refresh = 1;
        }
        if(event.timer.source == timer_mudanca_de_posicao_na_imagem_da_trap)
        {
            puts("hail\n");
            if(pos_x_trap <= 3 && flag_trap == 0)
            {
                pos_x_trap++;
                if(pos_x_trap == 3 && flag_trap == 0){
                        red.x = red.xA;
                        red.y = red.yA;

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


        for(l = 0; l < 14; l++){
            for(m = 0; m < 14; m++){
              switch(mapa[m][l]){
                    case 1 :
                        al_draw_bitmap(parede,l*50,m*50, 0);
                        break;
                    case 0 :
                        al_draw_bitmap(solo,l*50,m*50, 0);
                        break;
                    case 3 :
                        al_draw_bitmap(traps[0],l*50,m*50, 0);
                    default :
                        break;
              }
            }
        }

        if(b == 3)
            al_draw_bitmap(traps[pos_x_trap],TAFu.x*50,TAFu.y*50, 0);

        al_draw_bitmap(sprites[red.direcaoS][red.sprite], red.x, red.y, flags);


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

