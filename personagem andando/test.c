#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <winsock.h>
#include <time.h>


#define WIDTH 900
#define HEIGHT 650

#define WIDTHM 500
#define HEIGHTM 450

#define TILE_SIZEH 50
#define TILE_SIZEV 50
#define SPRITE_SIZEH 32
#define SPRITE_SIZEV 40
#define NUM_SPRITES 5
#define FRAMES_PER_SHIFT 10
#define SPEED 1
#define mapa_size 13



#define FPS 60


int vencedor;

int mapa[13][13] = {
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
                    };   //mapa base;

void sorteaA(){
    int a, C;
    int nL, nC;
    C = 0;
    srand((unsigned)time(NULL));
    for (a = 0; a < 7; a++ ){
        nL = rand()%mapa_size;
        nC = rand()%mapa_size;
        while (C == 0){
            if(mapa[nC][nL] == 0){
                mapa[nC][nL] = 3;
                C = 1;
                printf("\n trap em: %d - %d", nL, nC);
            }else{
                nL = rand()%mapa_size;
                nC = rand()%mapa_size;
            }
        }
        C = 0;

    }
}

struct pontoNas{
        int x[8];
        int y[8];
        int ativa[8];

};

struct pontoNas inicios;

void setI(){

inicios.x[0] = 1;
inicios.y[0] = 1;
mapa[1][1] = 4;

inicios.x[1] = 1;
inicios.y[1] = 11;
mapa[1][11] = 4;

inicios.x[2] = 11;
inicios.y[2] = 11;
mapa[11][11] = 4;

inicios.x[3] = 11;
inicios.y[3] = 1;
mapa[11][1] = 4;

inicios.x[4] = 1;
inicios.y[4] = 6;
mapa[1][6] = 4;

inicios.x[5] = 6;
inicios.y[5] = 11;
mapa[6][11] = 4;

inicios.x[6] = 11;
inicios.y[6] = 6;
mapa[11][6] = 4;

inicios.x[7] = 6;
inicios.y[7] = 1;
mapa[6][1] = 4;


}

struct Reds{
      int x, xA; // x do personagem;
      int y, yA; // y do personagem;
      int sprite; // imagem atual do personagem;
      int direcaoS;
      int moveV;
      int moveH; //dire??o do personagem;

      int vida;

      int frame;
      int arm;

      int b;
};

struct Reds red[2];

struct trapAtiva{
    int x;
    int y;
};

struct trapAtiva TAFu[2];

void sortearNas(int player){
   int p, C;
   red[player].vida = 3;
   C = 1;
   srand((unsigned)time(NULL));
   while(C == 1){

        p = rand()%8;
        if(inicios.ativa[p] != 1 ){
            red[player].x = inicios.x[p]*50;
            red[player].y = inicios.y[p]*50;
            inicios.ativa[p] = 1;
            C=0;
        }
   }

}

void setmove(int lado, int p){
    // 0 = down, 1 = esquerda, 2 = direita, 3 = cima - mapa de sprites moves
    switch(lado){
        case 1:
             red[p].moveH = -1;
             red[p].moveV = 0;
             red[p].direcaoS = 1;
             break;
        case 2:
             red[p].moveH = 1;
             red[p].moveV = 0;
             red[p].direcaoS = 2;

             break;
        case 3:
            red[p].moveH = 0;
            red[p].moveV = -1;
            red[p].direcaoS = 3;

            break;
        case 4:
            red[p].moveH = 0;
            red[p].moveV = 1;
            red[p].direcaoS = 0;
            break;
        case 0:
            red[p].moveH = 0;
            red[p].moveV = 0;
            red[p].direcaoS = 0;
            red[p].sprite = 0;
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

                        if(mapa[anaY][anaX] == 5)
                            coli = 5;

                        //ponto de borda sprite 4
                        anaX = (px)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        if(mapa[anaY][anaX] == 3)
                            coli = 3;

                        if(mapa[anaY][anaX] == 5)
                            coli = 5;



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

                         if(mapa[anaY][anaX] == 5)
                            coli = 5;

                        //ponto de borda sprite 4
                        anaX = (px)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] == 1 )
                            coli = 1;

                        if(mapa[anaY][anaX] == 3)
                            coli = 3;

                         if(mapa[anaY][anaX] == 5)
                            coli = 5;



                    }

       }


        return coli;

}

int testex(int p){
     int esta;

            if(red[p].sprite == 0) {
              red[p].sprite = 2;
              red[p].frame = 0;
            }
            else {
              red[p].frame++;
              if(red[p].frame == FRAMES_PER_SHIFT) {
                red[p].frame = 0;

                red[p].sprite += red[p].arm;

                if(red[p].sprite != 2)
                  red[p].arm = -red[p].arm;
              }
            }
            esta = colision(red[p].x,red[p].y,red[p].moveH,0,1);

            if(esta == 0){
                red[p].x += red[p].moveH * SPEED;
            }
                if (esta == 3){


                    red[p].xA = red[p].x;
                    red[p].xA = red[p].xA/50;
                    red[p].xA = red[p].xA*50;
                    red[p].yA = red[p].y;
                    red[p].x += red[p].moveH * SPEED;

                    red[p].moveH = 0;

                    TAFu[p].x = red[p].x/50;
                    TAFu[p].y = (red[p].y+40)/50;

                    int inia;
                    if (mapa[TAFu[p].y][TAFu[p].x] != 3){
                        inia = TAFu[p].x + 1;
                        if (mapa[TAFu[p].y][inia] != 3){
                            TAFu[p].x = TAFu[p].x -1;
                        }else{
                            TAFu[p].x = inia;
                        }

                    }
                    red[p].sprite = 0;

                }
                if(esta == 5){
                    vencedor = p;
                }
                return esta;
}

int testey(int p){
    int esta;


     if(red[p].sprite == 0) {
        red[p].sprite = 2;
        red[p].frame = 0;
     }else {
        red[p].frame++;

        if(red[p].frame == FRAMES_PER_SHIFT) {
                red[p].frame = 0;

                red[p].sprite += red[p].arm;

                if(red[p].sprite != 2)
                  red[p].arm = -red[p].arm;
              }
            }
            esta = colision(red[p].x,red[p].y,0,red[p].moveV,2);

            if(esta == 0){
                red[p].y += red[p].moveV * SPEED;
            }else{
                if (esta == 3){

                    red[p].xA = red[p].x;
                    red[p].yA = red[p].y/50;
                    if(red[p].moveV == -1)
                        red[p].yA = red[p].yA + 1;

                    red[p].yA = (red[p].yA) * 50;
                    red[p].y += red[p].moveV * SPEED;



                    red[p].moveV = 0;

                    TAFu[p].x =  (red[p].x)/50;

                    TAFu[p].y = (red[p].y+40)/50;

                    int inia;
                    if (mapa[TAFu[p].y][TAFu[p].x] != 3){
                        inia = TAFu[p].x + 1;
                        if (mapa[TAFu[p].y][inia] != 3){
                            TAFu[p].x = TAFu[p].x -1;
                        }else{
                            TAFu[p].x = inia;
                        }

                    }


                    red[p].sprite = 0;
                    //printf("trap\n\n");

                }

                }

                if(esta == 5){
                    vencedor = p;
                }

        return esta;
}

void error(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);

  exit(EXIT_FAILURE);
}

struct relogio{
    int minutos;
    int segundos;
};
struct relogio reloginho;

void maisumseg(){
    reloginho.segundos += 1;
    if(reloginho.segundos  == 60)
    {
        reloginho.segundos = 0;
        reloginho.minutos += 1;
    }

}


int game() {
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
  ALLEGRO_TIMER *timer_mudanca_de_posicao_na_imagem_da_trap_B = al_create_timer(0.5);
  ALLEGRO_TIMER *timer_contador = al_create_timer(1.0);
  /**********/
  ALLEGRO_BITMAP *solo = al_load_bitmap("solo.png");
  if(!solo)
    error("failed to load solo");


  ALLEGRO_BITMAP *area_central = al_create_bitmap(250, 650);
    if (!area_central)
        error("Falha ao criar bitmap.");

  ALLEGRO_BITMAP *parede = al_load_bitmap("paredes.png");
  if(!parede)
    error("failed to load paredes");

  ALLEGRO_BITMAP *life2 = al_load_bitmap("heart2.png");
  if(!life2)
    error("faled to load life");

  ALLEGRO_BITMAP *life = al_load_bitmap("heart.png");
  if(!life2)
    error("faled to load life");

  ALLEGRO_BITMAP *trap = al_load_bitmap("trap.png");
  if(!trap)
    error("failed to load trap");

  ALLEGRO_BITMAP *sheet = al_load_bitmap("Red.png");
  if(!sheet)
    error("failed to load sheet");

  ALLEGRO_BITMAP *sheet2 = al_load_bitmap("Red2.png");
  if(!sheet2)
    error("failed to load sheet2");

  ALLEGRO_BITMAP *saida = al_load_bitmap("exit.png");
  if(!saida)
    error("failed to load saida");


    ALLEGRO_FONT *fonte = al_load_font("bin/Debug/aspartam.ttf", 20, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");

  //
    ALLEGRO_BITMAP *traps[5];
    int trapshift;

    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[trapshift]= al_create_sub_bitmap(trap, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }


  ALLEGRO_BITMAP *sprites[NUM_SPRITES][NUM_SPRITES];
  ALLEGRO_BITMAP *sprites2[NUM_SPRITES][NUM_SPRITES];

  int shift, shiftb;

  for(shift = 0; shift < NUM_SPRITES; shift++){
    for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++){
        sprites[shift][shiftb] = al_create_sub_bitmap(sheet, shiftb * SPRITE_SIZEH, shift * SPRITE_SIZEV, SPRITE_SIZEH, SPRITE_SIZEV);
    }
  }

  for(shift = 0; shift < NUM_SPRITES; shift++){
    for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++){
        sprites2[shift][shiftb] = al_create_sub_bitmap(sheet2, shiftb * SPRITE_SIZEH, shift * SPRITE_SIZEV, SPRITE_SIZEH, SPRITE_SIZEV);
    }
  }


    setI();
    int l,m;
    sorteaA();


    for(l = 0; l < 13; l++){
            for(m = 0; m < 13; m++){
              switch(mapa[m][l]){
                    case 1 :
                        al_draw_bitmap(parede,l*50,m*50, 0);
                        break;
                    case 0 :
                        al_draw_bitmap(solo,l*50,m*50, 0);
                        break;
                    case 3 :
                        al_draw_bitmap(traps[0],l*50,m*50, 0);
                        break;
                    case 4 :
                        al_draw_bitmap(solo,l*50,m*50, 0);
                        break;

                    default :
                        break;
              }
            }
    }
    al_set_target_bitmap(area_central);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(area_central, 650,0,0);
  /**********/




  red[0].sprite = 0;
  red[0].direcaoS = 0;
  red[0].moveH = 0;
  red[0].moveV = 0;

  red[1].sprite = 0;
  red[1].direcaoS = 0;
  red[1].moveH = 0;
  red[1].moveV = 0;


  sortearNas(0);
  sortearNas(1);
  // 0 = down, 1 = esquerda, 2 = direita, 3 = cima
   red[0].b = 0;
   red[1].b = 0; //condi??o de colis?o com trsap
    int ai;

  red[0].frame = 0;
  red[1].frame = 0;

  red[0].arm = -1;
  red[1].arm = -1;

  int flags = 0;
  int pos_x_trap[2];

  pos_x_trap[0] = 1;
  pos_x_trap[1] = 1;

  int flag_trap[2];

    flag_trap[0] = 0;
    flag_trap[1] = 0;

    reloginho.segundos = 0;
    reloginho.minutos = 0;


    int px, py;

  /**********/

  al_flip_display();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_timer_event_source(timer_mudanca_de_posicao_na_imagem_da_trap));
  al_register_event_source(queue, al_get_timer_event_source(timer_mudanca_de_posicao_na_imagem_da_trap_B));
  al_register_event_source(queue, al_get_timer_event_source(timer_contador));

  /**********/

  int running = 1;

  int refresh = 0;

  al_start_timer(timer);
  al_start_timer(timer_contador);

  while(running) {

    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);


    switch(event.type) {
    case ALLEGRO_EVENT_KEY_DOWN:
      switch(event.keyboard.keycode) {
          case ALLEGRO_KEY_LEFT:
            if(red[0].b < 3){
                setmove(1,0);
                flags = 0;
                refresh = 1;
            }
            break;

          case ALLEGRO_KEY_DOWN:

                    if(red[0].b < 3){
                        setmove(4,0);
                        flags = 0;
                        refresh = 1;
                    }
                break;

          case ALLEGRO_KEY_UP:
                if(red[0].b < 3){
                    setmove(3,0);
                    flags = 0;
                    refresh = 1;
                }
                break;

          case ALLEGRO_KEY_RIGHT:
                if(red[0].b < 3){
                    setmove(2,0);
                    flags = 0;
                    refresh = 1;
                }
            break;

            //player 2
            case ALLEGRO_KEY_A:
            if(red[1].b < 3){
                setmove(1,1);
                flags = 0;
                refresh = 1;
            }
            break;

          case ALLEGRO_KEY_S:

                    if(red[1].b < 3){
                        setmove(4,1);
                        flags = 0;
                        refresh = 1;
                    }
                break;

          case ALLEGRO_KEY_W:
                if(red[1].b < 3){
                    setmove(3,1);
                    flags = 0;
                    refresh = 1;
                }
                break;

          case ALLEGRO_KEY_D:
                if(red[1].b < 3){
                    setmove(2,1);
                    flags = 0;
                    refresh = 1;
                }
            break;

          case ALLEGRO_KEY_ESCAPE:
            running = 0;
            break;
          default:
            printf("");
          }
          break;


    case ALLEGRO_EVENT_KEY_UP:
      switch(event.keyboard.keycode) {
          case ALLEGRO_KEY_LEFT:
            if(red[0].moveH == -1 ) {
              setmove(0,0);
              refresh = 1;
            }
            break;


          case ALLEGRO_KEY_DOWN:
                if(red[0].moveV == 1){
                    setmove(0,0);
                    refresh = 1;
                }
                break;

          case ALLEGRO_KEY_UP:
              if (red[0].moveV == -1 ){
                setmove(0,0);
                refresh = 1;
              }
                break;

          case ALLEGRO_KEY_RIGHT:
            if(red[0].moveH == 1 ) {
              setmove(0,0);
              refresh = 1;
            }
            break;
            //Second Player

            case ALLEGRO_KEY_A:
            if(red[1].moveH == -1 ) {
              setmove(0,1);
              refresh = 1;
            }
            break;


          case ALLEGRO_KEY_S:
                if(red[1].moveV == 1){
                    setmove(0,1);
                    refresh = 1;
                }
                break;

          case ALLEGRO_KEY_W:
              if (red[1].moveV == -1 ){
                setmove(0,1);
                refresh = 1;
              }
                break;

          case ALLEGRO_KEY_D:
            if(red[1].moveH == 1 ) {
              setmove(0,1);
              refresh = 1;
            }
            break;



          case ALLEGRO_KEY_ESCAPE:
            running = 0;
            break;
          default:
            printf("");
          }
          break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      running = 0;
      break;
    case ALLEGRO_EVENT_TIMER:

        if(event.timer.source == timer)
        {
                if(red[0].moveH != 0){
                    ai = red[0].moveH;
                    red[0].b = testex(0);
                    if(red[0].b == 3){
                        red[0].x = (TAFu[0].x*50) + (9);
                        red[0].y = (TAFu[0].y*50) + (5);
                        al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                        pos_x_trap[0] = 1;
                    }
                    refresh = 1;
                  }

                   if(red[1].moveH != 0){
                    ai = red[1].moveH;
                    red[1].b = testex(1);
                    if(red[1].b == 3){
                        red[1].x = (TAFu[1].x*50) + (9);
                        red[1].y = (TAFu[1].y*50) + (5);
                        al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap_B);
                        pos_x_trap[1] = 1;
                    }
                    refresh = 1;
                  }

                  if(red[0].moveV != 0){
                    ai = red[0].moveV;
                    red[0].b = testey(0);
                     if(red[0].b == 3){
                        red[0].x = (TAFu[0].x*50) + (9);
                        red[0].y = (TAFu[0].y*50) - (5* ai);

                        al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                        pos_x_trap[0] = 1;
                    }
                    refresh = 1;
                  }

                  if(red[1].moveV != 0){
                    ai = red[1].moveV;
                    red[1].b = testey(1);
                     if(red[1].b == 3){
                        red[1].x = (TAFu[1].x*50) + (9);
                        red[1].y = (TAFu[1].y*50) - (5* ai);

                        al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap_B);
                        pos_x_trap[1] = 1;
                    }
                    refresh = 1;
                  }
                  if(red[0].b== 5 || red[1].b == 5 ){
                    red[0].b =5;
                    red[1].b =5;
                  }

                  refresh = 1;
        }

        if(event.timer.source == timer_mudanca_de_posicao_na_imagem_da_trap)
        {

                    if(pos_x_trap[0] <= 3 && flag_trap[0] == 0)
                    {
                        pos_x_trap[0]++;
                        if(pos_x_trap[0] == 4 && flag_trap[0] == 0){
                                red[0].x = red[0].xA;
                                red[0].y = red[0].yA;
                                if(red[0].vida >1)
                                 {
                                     red[0].vida -= 1;
                                 }else{
                                     sortearNas(0);
                                 }

                        }
                    }
                    else
                    {
                        flag_trap[0] = 1;
                        pos_x_trap[0]--;

                        if(pos_x_trap[0] == 0)
                        {
                            al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                            if (red[0].b != 4)
                                red[0].b = 0;

                            flag_trap[0] = 0;
                        }
                    }

            refresh = 1;
        }

        //trap para P2
        if(event.timer.source == timer_mudanca_de_posicao_na_imagem_da_trap_B)
        {

                    if(pos_x_trap[1] <= 3 && flag_trap[1] == 0)
                    {
                        pos_x_trap[1]++;
                        if(pos_x_trap[1] == 4 && flag_trap[1] == 0){
                                red[1].x = red[1].xA;
                                red[1].y = red[1].yA;
                                if(red[1].vida >1)
                                 {
                                     red[1].vida -= 1;
                                 }else{
                                     sortearNas(1);
                                 }

                        }
                    }
                    else
                    {
                        flag_trap[1] = 1;
                        pos_x_trap[1]--;

                        if(pos_x_trap[1] == 0)
                        {
                            al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap_B);
                            if (red[1].b != 4)
                                red[1].b = 0;

                            flag_trap[1] = 0;
                        }
                    }

            refresh = 1;
        }


        if(event.timer.source == timer_contador)
            {
                    maisumseg();
                    if(reloginho.segundos == 15 && reloginho.minutos == 0 )
                        mapa[6][6] = 5;

                    if( reloginho.minutos == 1 && reloginho.segundos == 30){
                        red[0].b = 4;
                        red[1].b = 4;
                        al_stop_timer(timer_contador);
                        al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                        al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap_B);
                    }
            }
      break;
        default:
            printf("");
        }

    if(refresh) {


        if(red[0].b != 5 && red[1].b != 5){
                        al_set_target_bitmap(al_get_backbuffer(display));


                          al_draw_bitmap(area_central, 650, 0, 0);
                          if(reloginho.segundos < 10){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 775, 50, ALLEGRO_ALIGN_CENTRE, "0%d : 0%d", reloginho.minutos, reloginho.segundos);
                          }else{
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 775, 50, ALLEGRO_ALIGN_CENTRE, "0%d : %d", reloginho.minutos, reloginho.segundos);
                          }
                          if(red[0].b == 4)
                            al_draw_textf(fonte, al_map_rgb(0, 0, 0), 800, 135, ALLEGRO_ALIGN_CENTRE, "Fim de jogo");


                            px = red[0].x/50;
                            py = red[0].y/50;
                            for(l = -1; l < 2; l++){
                                for(m = -1; m < 2; m++){
                                  switch(mapa[py + m][px + l]){
                                        case 1 :
                                            al_draw_bitmap(parede,(px+l)*50,(py+m)*50, 0);
                                            break;
                                        case 0 :
                                            al_draw_bitmap(solo,(px+l)*50,(py+m)*50, 0);
                                            break;
                                        case 3 :
                                            al_draw_bitmap(traps[0],(px+l)*50,(py+m)*50, 0);
                                            break;
                                         case 4 :
                                            al_draw_bitmap(solo,(px+l)*50,(py+m)*50, 0);
                                            break;
                                         case 5 :
                                            al_draw_bitmap(saida,(px+l)*50,(py+m)*50, 0);
                                        default :
                                            break;
                                  }
                                }
                            }

                            px = red[1].x/50;
                            py = red[1].y/50;

                            for(l = -1; l < 2; l++){
                                for(m = -1; m < 2; m++){
                                  switch(mapa[py + m][px + l]){
                                        case 1 :
                                            al_draw_bitmap(parede,(px+l)*50,(py+m)*50, 0);
                                            break;
                                        case 0 :
                                            al_draw_bitmap(solo,(px+l)*50,(py+m)*50, 0);
                                            break;
                                        case 3 :
                                            al_draw_bitmap(traps[0],(px+l)*50,(py+m)*50, 0);
                                            break;
                                         case 4 :
                                            al_draw_bitmap(solo,(px+l)*50,(py+m)*50, 0);
                                            break;
                                         case 5 :
                                            al_draw_bitmap(saida,(px+l)*50,(py+m)*50, 0);
                                        default :
                                            break;
                                  }
                                }
                            }




                            for(l = 0; l < red[0].vida; l++)
                                al_draw_bitmap(life,(660+l*70),250, 0);

                            for(l = 0; l < red[1].vida; l++)
                                al_draw_bitmap(life2,(660+l*70),330, 0);


                            if(red[0].b == 3)
                                al_draw_bitmap(traps[pos_x_trap[0]],TAFu[0].x*50,TAFu[0].y*50, 0);

                            if(red[1].b == 3)
                                al_draw_bitmap(traps[pos_x_trap[1]],TAFu[1].x*50,TAFu[1].y*50, 0);




                            al_draw_bitmap(sprites[red[0].direcaoS][red[0].sprite], red[0].x, red[0].y, flags);
                            al_draw_bitmap(sprites2[red[1].direcaoS][red[1].sprite], red[1].x, red[1].y, flags);

        }else{
            al_draw_textf(fonte, al_map_rgb(0, 0, 0), 800, 135, ALLEGRO_ALIGN_CENTRE, "Fim de jogo");
            al_draw_textf(fonte, al_map_rgb(0, 0, 0), 750, 400, ALLEGRO_ALIGN_CENTRE, "O jogador venceu %d", vencedor + 1);

            al_draw_bitmap(solo,6*50,5*50, 0);
            al_draw_bitmap(solo,6*50,7*50, 0);
            al_draw_bitmap(solo,5*50,6*50, 0);
            al_draw_bitmap(solo,7*50,6*50, 0);

            al_draw_bitmap(solo,7*50,7*50, 0);
            al_draw_bitmap(solo,7*50,5*50, 0);
            al_draw_bitmap(solo,5*50,7*50, 0);
            al_draw_bitmap(solo,5*50,5*50, 0);

            al_draw_bitmap(saida,6*50,6*50, 0);

            if(vencedor == 0){

                red[0].x = (6*50) + (9);
                red[0].y = (6*50) + (5);
                al_draw_bitmap(sprites[0][0], red[0].x, red[0].y, flags);
                al_draw_bitmap(sprites2[0][0], red[1].x, red[1].y, flags);
            }else{
                red[1].x = (6*50) + (9);
                red[1].y = (6*50) + (5);
                al_draw_bitmap(sprites2[0][0], red[1].x, red[1].y, flags);
                al_draw_bitmap(sprites[0][0], red[0].x, red[0].y, flags);
            }


        }



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
  al_destroy_bitmap(area_central);





for(shift = 0; shift < NUM_SPRITES; shift++)
  for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++)
    al_destroy_bitmap(sprites[shift][shiftb]);



  al_destroy_bitmap(sheet);



  al_destroy_timer(timer);
  al_destroy_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
  al_destroy_event_queue(queue);
  al_destroy_display(display);


  al_shutdown_primitives_addon();
  al_shutdown_image_addon();
  al_uninstall_keyboard();
  al_uninstall_system();

  return 0;
}

int menu() {
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0, *btt_mult=0;

    ALLEGRO_FONT *fonte = NULL, *fontT = NULL;

    // Flag que condicionar? nosso looping
    int sair = 0;

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    al_init_font_addon();

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return -1;
    }

    janela = al_create_display(WIDTHM, HEIGHTM);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }

    fonte = al_load_font("bin/Debug/aspartam.ttf", 24, 0);
    if (!fonte)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return -1;
    }

    fontT = al_load_font("bin/Debug/aspartam.ttf", 50, 0);
    if (!fontT)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fontT.\n");
        return -1;
    }



    // Configura o t?tulo da janela
    al_set_window_title(janela, "Rotinas de Mouse - www.rafaeltoledo.net");

    //configurar textos
    char *texto1 = "Programa teste";
    char *texto2 = "Mutiplayer";
    char *texto3 = "Sair";
    char *titulo1 = "Riddle Story";
    char *titulo2 = " of ";
    char *titulo3 = "devil degree";
    // Torna apto o uso de mouse na aplica??o
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padr?o do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Alocamos o ret?ngulo central da tela
    area_central = al_create_bitmap(250, 50);
    if (!area_central)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return -1;
    }
    //bot?o multiplayer
    btt_mult = al_create_bitmap(250, 50);
    if (!btt_mult)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return -1;
    }



    // Alocamos o bot?o para fechar a aplica??o
    botao_sair = al_create_bitmap(100, 50);
    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar bot?o de sa?da.\n");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    // Flag indicando se o mouse est? sobre o ret?ngulo central
    int na_area_central = 0;
    int no_btt_multi = 0;
    while (!sair)
    {
        // Verificamos se h? eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            // Se o evento foi de movimenta??o do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                // Verificamos se ele est? sobre a regi?o do ret?ngulo central
                if (evento.mouse.x >= 200 &&
                    evento.mouse.x <= 450 &&
                    evento.mouse.y >= 250 &&
                    evento.mouse.y <= 300)
                {
                    na_area_central = 1;
                }
                else
                {
                    na_area_central = 0;
                     if (evento.mouse.x >= 200 && evento.mouse.x <= 450 && evento.mouse.y >= 320 && evento.mouse.y <= 370)
                    {
                        no_btt_multi = 1;
                    }else{
                        no_btt_multi = 0;
                    }
                }
            }
            // Ou se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= WIDTHM - al_get_bitmap_width(botao_sair) - 10 && evento.mouse.x <= WIDTHM - 10 && evento.mouse.y <= HEIGHT - 10 && evento.mouse.y >= HEIGHTM - al_get_bitmap_height(botao_sair) - 10)
                {
                    sair = 1;
                }
                else{
                    if( evento.mouse.x >= 200 && evento.mouse.x <= 450 && evento.mouse.y >= 250 && evento.mouse.y <= 300){
                           al_destroy_bitmap(botao_sair);
                           al_destroy_bitmap(area_central);
                           al_destroy_bitmap(btt_mult);

                           al_destroy_display(janela);
                           al_destroy_event_queue(fila_eventos);


                           return 1;
                    }else{
                        if( evento.mouse.x >= 200 && evento.mouse.x <= 450 && evento.mouse.y >= 320 && evento.mouse.y <= 370){
                           al_destroy_bitmap(botao_sair);
                           al_destroy_bitmap(area_central);
                           al_destroy_bitmap(btt_mult);

                           al_destroy_display(janela);
                           al_destroy_event_queue(fila_eventos);
                           return 2;
                        }
                    }
                }
            }
        }

        // Limpamos a tela
       al_clear_to_color(al_map_rgb(0, 0, 0));

        // Colorimos o bitmap correspondente ao ret?ngulo central,
        // com a cor condicionada ao conte?do da flag na_area_central
        al_set_target_bitmap(area_central);
        if (!na_area_central)
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }
        //no segundo bot?o
        al_set_target_bitmap(btt_mult);
        if (!no_btt_multi)
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }


        // Colorimos o bitmap do bot?o de sair


        al_set_target_bitmap(botao_sair);
        al_clear_to_color(al_map_rgb(255, 0, 0));

        // Desenhamos os ret?ngulos na tela
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(area_central, 100, 250, 0);
        al_draw_textf(fonte, al_map_rgb(0, 0, 0), 220, 260, ALLEGRO_ALIGN_CENTRE, "%s", texto1);


        al_draw_bitmap(btt_mult, 100, 320, 0);
        al_draw_textf(fonte, al_map_rgb(0, 0, 0), 220, 330, ALLEGRO_ALIGN_CENTRE, "%s", texto2);

        al_draw_bitmap(botao_sair, WIDTHM - al_get_bitmap_width(botao_sair) - 10, HEIGHTM - al_get_bitmap_height(botao_sair) - 10, 0);
        al_draw_textf(fonte, al_map_rgb(0, 0, 0), WIDTHM - al_get_bitmap_width(botao_sair)+25, HEIGHTM - al_get_bitmap_height(botao_sair) , ALLEGRO_ALIGN_CENTRE, "%s", texto3);
        // Atualiza a tela

        al_draw_textf(fontT, al_map_rgb(250, 0, 0), 220, 50, ALLEGRO_ALIGN_CENTRE, "%s", titulo1);
        al_draw_textf(fontT, al_map_rgb(250, 0, 0), 220, 75, ALLEGRO_ALIGN_CENTRE, "%s", titulo2);
        al_draw_textf(fontT, al_map_rgb(250, 0, 0), 220, 100, ALLEGRO_ALIGN_CENTRE, "%s", titulo3);

        al_flip_display();
    }

    // Desaloca os recursos utilizados na aplica??o
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(area_central);
    al_destroy_bitmap(btt_mult);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 1;
}

int waitplayer(){
    if(!al_init())
        error("failed to initialize");

    if(!al_init_image_addon())
        error("failed to initialize image addon");

    if(!al_init_primitives_addon())
        error("failed to initialize primitives addon");

    ALLEGRO_DISPLAY *display = al_create_display(650, 650);
    if(!display)
        error("failed to create display");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if(!queue)
        error("failed to create event queue");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_TIMER *timer_contador = al_create_timer(1.0);

    ALLEGRO_FONT *fonte = al_load_font("bin/Debug/NIv.ttf", 20, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");

    ALLEGRO_FONT *fonte2 = al_load_font("bin/Debug/NIv.ttf", 30, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");

    ALLEGRO_BITMAP *area_central = al_create_bitmap(650, 650);
    if (!area_central)
        error("Falha ao criar bitmap.");


    int saida = 1;
    int conf1, conf2, conf3, conf4, confT;
    int timerF;
    int ret; // retorno

    conf1 = 0;
    conf2 = 0;
    conf3 = 0;
    conf4 = 0;
    confT = 0;

    char *texto1 = "Voce  o player N";

    char *texto2 = "Aguardando mapa";
    char *texto21 = "Mapa carregado";

    char *texto3 = "Aguardando Player N";
    char *texto4 = "Player N ok";

    char *texto5 = "Posi??es inicias definidas";

    char *texto6 = " Iniciando ";
    char *texto7 = " Esperando todas as condioes ";

    char *titulo = "Riddle Story of devil degree";

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(timer_contador));

    timerF = 5;
    al_start_timer(timer);
    while(saida){

        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        switch(event.type) {
               case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    saida = 0;
                    ret = 0;
                    break;
              case ALLEGRO_EVENT_TIMER:
                if(event.timer.source == timer)
                {
                             if(conf1 == 0){
                            //recebe mapa
                                if(mapa[0][0] == 1)
                                    conf1 = 1;
                            }
                            if(conf2 == 0){
                                //recebe informa??o sobre os personagems
                                // conf 3 seu personagem, conf 4 os outros
                                if(conf3 == 0){
                                    //persoangens local confere se n?o t? no 0 0
                                    conf3 = 1;
                                }
                                 if(conf4 == 0){
                                    //persoangens confere se nenhum personagem tirando o local n?o t? no 0 0
                                    conf4 = 1;
                                }
                                if(conf3 == 1 && conf4 == 1)
                                    conf2 = 1;

                            }
                            if (conf1 && conf2 && conf3 && conf4)
                                al_start_timer(timer_contador);


                    }
                    if(event.timer.source == timer_contador){
                                    confT = 1;
                                    if(timerF > 0){
                                        timerF = timerF - 1;
                                    }else{
                                        ret = 1;
                                        saida = 0;
                                        al_stop_timer(timer_contador);
                                    }
                                    break;
                            default:
                                break;
                            }


        //Olha o desenho ae pessoal


            al_set_target_bitmap(area_central);
            al_clear_to_color(al_map_rgb(0, 0, 0));


            al_set_target_bitmap(al_get_backbuffer(display));


            al_draw_bitmap(area_central, 0, 0, 0);

            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, 50, ALLEGRO_ALIGN_CENTRE, "%s", titulo);

            if(conf1 == 1){
               al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, 100, ALLEGRO_ALIGN_CENTRE, "%s", texto21);
            }else{
                   al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, 100, ALLEGRO_ALIGN_CENTRE, "%s", texto2);
            }
            //definir qual o player ? por hora ele ? 0 4
            int i;
            for(i = 0; i< 4; i++){
                  if(i != 4)  {
                        if(conf4 == 1){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s: %d", texto4, i);
                        }else{
                           al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s: %d", texto3, i);
                        }
                  }else{
                        if(conf3 == 1){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s: %d", texto1, i);
                        }else{
                           al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "Arguandando informa??o do serve");
                        }
                  }
            }

            if(conf4 == 1 && conf3 == 1)
            {
                al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, 400, ALLEGRO_ALIGN_CENTRE, "%s", texto5);

            }

            if(confT == 1){
                al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, 450, ALLEGRO_ALIGN_CENTRE, "%s", texto6);
                al_draw_textf(fonte2, al_map_rgb(140, 255, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "%d segundo", timerF);
            }else{
                    al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, 450, ALLEGRO_ALIGN_CENTRE, "%s", texto7);
                }

            al_flip_display();
        }
    }
    al_destroy_font(fonte);
    al_destroy_timer(timer_contador);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);


    al_shutdown_primitives_addon();

    return ret;


}

int main(){
    int qual = menu();
    int q2;
   // if(qual == 1)
     //   q2 = waitplayer();



    switch(qual){
        case 1:
            game();
            break;
        case 2:
            q2 = waitplayer();
            if(q2 == 1)
                game();
            break;
        default:
            break;
    }

    return 0;
}
