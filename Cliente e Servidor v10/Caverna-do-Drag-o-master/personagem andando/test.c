#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <windows.h>

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

WSADATA data; //Variíveis que recebem o valor da inicialização e criação do socket.
//SOCKET winsock; //Variíveis que recebem o valor da inicialização e criação do socket.
SOCKADDR_IN sock; //Variíveis que recebem o valor da inicialização e criação do socket.

int descritorCliente;
int posicaoServidor;
char ip [1024];
int posicaoPersonagem[4][4];

int vencedor;

int mapa[13][13] = {
                    0,1,1,1,1,1,1,1,1,1,1,1,1,
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
      int x, xA; // x do personagem
      int y, yA; // y do personagem
      int sprite; // imagem atual do personagem
      int direcaoS;
      int moveV;
      int moveH; //direção do personagem

      int b; //estados
      int vida;

      int frame;
      int arm;


};

struct Pdfora{
    int x;
    int y;

    int estado;

    int spritel;
    int spritec;

    int trapX;
    int trapY;
    int spriteT;
    int vida;

    int inicia;
};
struct Reds red;
struct Pdfora personas[4];
struct Pdfora eu;

struct trapAtiva{
    int x;
    int y;
};

struct trapAtiva TAFu;

void* recebeClientes(void* arg){
    int sockEntrada = (*(int *) arg);
    //printf("%d\n",sockEntrada);
    while(1)
    {

    	//int j;
    	//for (j = 0; j >= 3; j++)
    	//{
		recv(descritorCliente, (void*)&personas, sizeof(personas),0);
		//printf("Posicao x %d\n",red[sockEntrada].x);
        //printf("Posicao y %d\n",red[sockEntrada].y);
        //Sleep(1500);
        //Sleep(1000);
    	//}
    		//printf("%f\n", dadosClientes[0][1]);
    }
}

void* enviaClientes(void* arg){
    int sockEntrada = (*(int *) arg);
    printf("%d\n", sockEntrada);
    while(1){
        //printf("%d\n",personagens[sockEntrada].x);
        //printf("%d\n",personagens[sockEntrada].y);
        //if (red[sockEntrada].x != 0 || red[sockEntrada].y != 0){
        eu.x = red.x;
        eu.y = red.y;
        eu.spritel = red.direcaoS;
        eu.spritec = red.sprite;
        eu.trapX = TAFu.x;
        eu.trapY = TAFu.y;
        eu.vida = red.vida;

            Sleep(1);
            send(descritorCliente, (void*)&eu, sizeof(eu),0);
        //}
    }

}


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

             break;
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

void sortearNas(){
   int p, C;
   red.vida = 3;
   C = 1;
   srand((unsigned)time(NULL));
   while(C == 1){

        p = rand()%8;
        if(inicios.ativa[p] != 1 ){
            red.x = inicios.x[p]*50;
            red.y = inicios.y[p]*50;
            inicios.ativa[p] = 1;
            C=0;
        }
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


        //para o personagem
        int px1;
        int py1;
       int contador;
       for (contador = 0; contador < 4; contador++ ){
            if(contador != posicaoServidor){
                px1 =  personas[contador].x+32;
                py1 =  personas[contador].y+40;

                if(red.x == personas[contador].x)
                    coli = 1;

                if(red.x == px1)
                    coli = 1;

                if(red.y ==  personas[contador].y)
                    coli = 1;

                if(red.y == py1)
                    coli = 1;



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
                    red.sprite = 0;

                }
                if(esta == 5){
                    vencedor = posicaoServidor;
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
                    if(red.moveV == -1)
                        red.yA = red.yA + 1;

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


                    red.sprite = 0;
                    //printf("trap\n\n");

                }

                }

                if(esta == 5){
                    vencedor = posicaoServidor;
                }

        return esta;
}

void error(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);

  exit(EXIT_FAILURE);
}

void zeraPersonagens(){
    int i;
    for(i = 0; i < 4; i++){
        red.sprite = 0;
        red.direcaoS = 0;
        red.moveH = 0;
        red.moveV = 0;
        red.frame = 0;
        red.arm = -1;
    }
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

int game(int servidor) {
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
  ALLEGRO_BITMAP *solo = al_load_bitmap("C:/Users/denis.loliveira/Desktop/solo.png");
  if(!solo)
    error("failed to load solo");


  ALLEGRO_BITMAP *area_central = al_create_bitmap(250, 650);
    if (!area_central)
        error("Falha ao criar bitmap.");

  ALLEGRO_BITMAP *parede = al_load_bitmap("C:/Users/denis.loliveira/Desktop/paredes.png");
  if(!parede)
    error("failed to load paredes");

  ALLEGRO_BITMAP *life = al_load_bitmap("C:/Users/denis.loliveira/Desktop/heart.png");
  if(!life)
    error("faled to load life");

  ALLEGRO_BITMAP *trap = al_load_bitmap("C:/Users/denis.loliveira/Desktop/trap.png");
  if(!trap)
    error("failed to load trap");

  ALLEGRO_BITMAP *sheet = al_load_bitmap("C:/Users/denis.loliveira/Desktop/Red.png");
  if(!sheet)
    error("failed to load sheet");

  ALLEGRO_BITMAP *saida = al_load_bitmap("C:/Users/denis.loliveira/Desktop/exit.png");
  if(!saida)
    error("failed to load saida");


    ALLEGRO_FONT *fonte = al_load_font("C:/Users/denis.loliveira/Desktop/aspartam.ttf", 20, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");



    ALLEGRO_BITMAP *traps[5];
    int trapshift;

    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[trapshift]= al_create_sub_bitmap(trap, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }


  ALLEGRO_BITMAP *sprites[NUM_SPRITES][NUM_SPRITES];

  int shift, shiftb;

  for(shift = 0; shift < NUM_SPRITES; shift++){
    for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++){
        sprites[shift][shiftb] = al_create_sub_bitmap(sheet, shiftb * SPRITE_SIZEH, shift * SPRITE_SIZEV, SPRITE_SIZEH, SPRITE_SIZEV);
    }
  }


    setI();
    int l,m;
    //sorteaA();


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
  // 0 = down, 1 = esquerda, 2 = direita, 3 = cima
  int b; //condição de colisão com trsap
  int ai;

  int flags = 0;
  int pos_x_trap = 1;
  int flag_trap = 0;
    int px;
    int py;

    red.frame = 0;
    eu.spriteT = 0;
    red.arm = -1;


    red.vida = 3;

    reloginho.segundos = 0;
    reloginho.minutos = 0;

  /************/
  //Gerando personagens na tela
  int contador;
  /*for (contador = 0; contador < 4; contador++){
        //sortearNas(contador);
       if(contador != servidor)
            al_draw_bitmap(sprites[personas[contador].spritel][personas[contador].spritec], personas[contador].x, personas[contador].y, flags);
  }
  al_draw_bitmap(sprites[red.direcaoS][red.sprite], red.x, red.y, flags);
*/
  /**********/

  al_flip_display();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_timer_event_source(timer_mudanca_de_posicao_na_imagem_da_trap));
  al_register_event_source(queue, al_get_timer_event_source(timer_contador));
  /**********/

  int running = 1;

    int refresh = 0;
    red.sprite = 0;

    al_start_timer(timer);
    al_start_timer(timer_contador);
  while(running) {
    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);


    switch(event.type) {
    case ALLEGRO_EVENT_KEY_DOWN:
      switch(event.keyboard.keycode) {
      case ALLEGRO_KEY_LEFT:
        if(red.b != 3){
            setmove(1 );
            flags = 0;
            refresh = 1;
        }
        break;

      case ALLEGRO_KEY_DOWN:

                if(red.b != 3){
                    setmove(4);
                    flags = 0;
                    refresh = 1;
                }
            break;

      case ALLEGRO_KEY_UP:
            if(red.b != 3){
                setmove(3);
                flags = 0;

                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_RIGHT:
            if(red.b != 3){
                setmove(2);
                flags = 0;
                refresh = 1;
            }
        break;
      case ALLEGRO_KEY_ESCAPE:
        running = 0;
        break;
      default:
        printf("a");
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
      case ALLEGRO_KEY_ESCAPE:
        running = 0;
        break;
      default:
        printf("b");
      }
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      running = 0;

      break;
    case ALLEGRO_EVENT_TIMER:

        if(event.timer.source == timer)
        {
                if(red.moveH != 0){
                    ai = red.moveH;
                    red.b = testex();
                    if(red.b == 3){
                        red.x = (TAFu.x*50) + (9);
                        red.y = (TAFu.y*50) + (5);
                        al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                        pos_x_trap = 1;
                    }
                    refresh = 1;
                  }

                  if(red.moveV != 0){
                    ai = red.moveV;
                    red.b = testey();
                     if(red.b == 3){
                        red.x = (TAFu.x*50) + (9);
                        red.y = (TAFu.y*50) - (5* ai);

                        al_start_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                        pos_x_trap = 1;
                    }
                    refresh = 1;
                    }
                    refresh = 1;

        }

        if(event.timer.source == timer_mudanca_de_posicao_na_imagem_da_trap)
        {

            if(pos_x_trap <= 3 && flag_trap == 0)
            {
                pos_x_trap++;
                if(pos_x_trap == 4 && flag_trap == 0){
                        red.x = red.xA;
                        red.y = red.yA;
                        if(red.vida >1)
                         {
                             red.vida -= 1;
                         }else{
                             sortearNas();
                         }

                }
            }
            else
            {
                flag_trap = 1;
                pos_x_trap--;

                if(pos_x_trap == 0)
                {
                    al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                    red.b = 0;
                    flag_trap = 0;
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
                        red.b = 4;

                        al_stop_timer(timer_contador);
                        al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap);
                    }
            }
            break;
        default:
            printf("");
        }

    if(refresh) {
        //send(descritorCliente, (void*)&red, sizeof(red),0);
        //recv(descritorCliente, (void*)&red, sizeof(red),0);

            if(red.b != 5)
                {
                         al_set_target_bitmap(al_get_backbuffer(display));


                          al_draw_bitmap(area_central, 650, 0, 0);

                          if(reloginho.segundos < 10){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 775, 50, ALLEGRO_ALIGN_CENTRE, "0%d : 0%d", reloginho.minutos, reloginho.segundos);
                          }else{
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 775, 50, ALLEGRO_ALIGN_CENTRE, "0%d : %d", reloginho.minutos, reloginho.segundos);
                          }

                          if(red.b == 4)
                            al_draw_textf(fonte, al_map_rgb(0, 0, 0), 800, 135, ALLEGRO_ALIGN_CENTRE, "Fim de jogo");


                            px = red.x/50;
                            py = red.y/50;

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
                                                break;
                                            default :
                                                break;
                                            }
                                    }
                            }


                        for (contador = 0; contador < 4; contador++){
                            if(contador != servidor){
                                px = personas[contador].x/50;
                                py = personas[contador].y/50;

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
                                                al_draw_bitmap(traps[personas[contador].spriteT],(px+l)*50,(py+m)*50, 0);
                                                break;
                                            case 4 :
                                                al_draw_bitmap(solo,(px+l)*50,(py+m)*50, 0);
                                                break;
                                            case 5 :
                                                al_draw_bitmap(saida,(px+l)*50,(py+m)*50, 0);
                                                break;
                                            default :
                                                break;
                                            }
                                    }
                                }
                            }
                        }


                    for(l = 0; l < red.vida; l++)
                            al_draw_bitmap(life,(660+l*70),250, 0);


                    if(b == 3)
                        al_draw_bitmap(traps[pos_x_trap],TAFu.x*50,TAFu.y*50, 0);



                   for (contador = 0; contador < 4; contador++){
                    //sortearNas(contador);

                   if(contador != servidor)
                        al_draw_bitmap(sprites[personas[contador].spritel][personas[contador].spritec], personas[contador].x, personas[contador].y, flags);

                        al_draw_bitmap(sprites[red.direcaoS][red.sprite], red.x, red.y, flags);


                   }


        }
            else
        {
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

                red.x = (6*50) + (9);
                red.y = (6*50) + (5);
                al_draw_bitmap(sprites[0][0], red.x, red.y, flags);

                for (contador = 0; contador < 4; contador++){
                    if(contador != servidor)
                        al_draw_bitmap(sprites[personas[contador].spritel][personas[contador].spritec], personas[contador].x, personas[contador].y, flags);
                }
            }

        }

        al_flip_display();

      refresh = 0;

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

    // Flag que condicionará nosso looping
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

    fonte = al_load_font("C:/Users/denis.loliveira/Desktop/aspartam.ttf", 24, 0);
    if (!fonte)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return -1;
    }

    fontT = al_load_font("C:/Users/denis.loliveira/Desktop/aspartam.ttf", 50, 0);
    if (!fontT)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fontT.\n");
        return -1;
    }



    // Configura o título da janela
    al_set_window_title(janela, "Rotinas de Mouse - www.rafaeltoledo.net");

    //configurar textos
    char *texto1 = "Programa teste";
    char *texto2 = "Mutiplayer";
    char *texto3 = "Sair";
    char *titulo1 = "Riddle Story";
    char *titulo2 = " of ";
    char *titulo3 = "devil degree";
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Alocamos o retângulo central da tela
    area_central = al_create_bitmap(250, 50);
    if (!area_central)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return -1;
    }
    //botão multiplayer
    btt_mult = al_create_bitmap(250, 50);
    if (!btt_mult)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return -1;
    }



    // Alocamos o botão para fechar a aplicação
    botao_sair = al_create_bitmap(100, 50);
    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar botão de saída.\n");
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

    // Flag indicando se o mouse está sobre o retângulo central
    int na_area_central = 0;
    int no_btt_multi = 0;
    while (!sair)
    {
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            // Se o evento foi de movimentação do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                // Verificamos se ele está sobre a região do retângulo central
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
                if (evento.mouse.x >= WIDTHM - al_get_bitmap_width(botao_sair) - 10 &&
                    evento.mouse.x <= WIDTHM - 10 && evento.mouse.y <= HEIGHT - 10 &&
                    evento.mouse.y >= HEIGHTM - al_get_bitmap_height(botao_sair) - 10)
                {
                    sair = 1;


                }else{
                    if( evento.mouse.x >= 200 && evento.mouse.x <= 450 && evento.mouse.y >= 250 && evento.mouse.y <= 300){
                           al_destroy_bitmap(botao_sair);
                           al_destroy_bitmap(area_central);
                           al_destroy_bitmap(btt_mult);

                           al_destroy_display(janela);
                           al_destroy_event_queue(fila_eventos);


                           return 1;
                    }
                }
            }
        }

        // Limpamos a tela
       al_clear_to_color(al_map_rgb(0, 0, 0));

        // Colorimos o bitmap correspondente ao retângulo central,
        // com a cor condicionada ao conteúdo da flag na_area_central
        al_set_target_bitmap(area_central);
        if (!na_area_central)
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }
        //no segundo botão
        al_set_target_bitmap(btt_mult);
        if (!no_btt_multi)
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }


        // Colorimos o bitmap do botão de sair


        al_set_target_bitmap(botao_sair);
        al_clear_to_color(al_map_rgb(255, 0, 0));

        // Desenhamos os retângulos na tela
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

    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(area_central);
    al_destroy_bitmap(btt_mult);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}

int criaCliente(){
 //   int winsock;
    int clienteWinsock;
    // testando comunicação
    if(WSAStartup(MAKEWORD(2,0),&data)==SOCKET_ERROR)
    {
        printf("Erro ao inicializar o winsock\n");
        //return 0;
    }

    if((clienteWinsock = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)
    {
        printf("Erro ao criar socket\n");
        //return 0;
    }

    /*printf("Digite o ip do servidor:\n");
    gets(ip);*/

    sock.sin_family=AF_INET;
    sock.sin_port=htons(1235); //Numero da porta de rede
    sock.sin_addr.s_addr=inet_addr(/*"127.0.0.1"*/"10.135.160.22"/*ip*/);

    if(connect(clienteWinsock, (SOCKADDR*)&sock, sizeof(sock))==SOCKET_ERROR)
    {
        printf("Erro ao se conectar\n");
        //return 0;
    }
    return clienteWinsock;
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

    ALLEGRO_FONT *fonte = al_load_font("C:/Users/denis.loliveira/Desktop/NIv.ttf", 20, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");

    ALLEGRO_FONT *fonte2 = al_load_font("C:/Users/denis.loliveira/Desktop/NIv.ttf", 30, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");

    ALLEGRO_BITMAP *area_central = al_create_bitmap(650, 650);
    if (!area_central)
        error("Falha ao criar bitmap.");


    int saida = 1;
    int conf1, conf2, confT;
    int timerF;
    int ret; // retorno

    conf1 = 0;
    conf2 = 0;
    int confp[4];
    int i;
    for(i = 0; i<4; i++)
        confp[i] = 0;
    confT = 0;

    char *texto1 = "Voce  o player N";

    char *texto2 = "Aguardando mapa";
    char *texto21 = "Mapa carregado";

    char *texto3 = "Aguardando Player ";
    char *texto4 = "Player ";
    char *okok ="ok";

    char *texto5 = "Posicoes inicias definidas";

    char *texto6 = " Iniciando ";
    char *texto7 = " Esperando todas as condicoes ";

    char *titulo = "Riddle Story of devil degree";

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(timer_contador));

    timerF = 20;
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
                                if(confp[0] == 0){
                                //Player 1
                                    if(personas[0].x != 0 && personas[0].y != 0)
                                        confp[0] = 1;
                                }
                                if(confp[1] == 0){
                                //Player 2
                                   if(personas[1].x != 0 && personas[1].y != 0)
                                        confp[1] = 1;
                                }
                                if(confp[2] == 0){
                                //Player 3
                                    if(personas[2].x != 0 && personas[2].y != 0)
                                        confp[2] = 1;
                                }
                                if(confp[3] == 0){
                                //divinha
                                    if(personas[3].x != 0 && personas[3].y != 0)
                                        confp[3] = 1;
                                }
                                for(i = 0; i<4; i++){
                                    if(confp[i] == 0){
                                        conf2 = 0;
                                    }else{
                                        conf2 = 1;
                                    }
                                }

                            }
                            if (conf1 && conf2){
                                if (personas[posicaoServidor].inicia == 1){
                                    al_start_timer(timer_contador);
                                }
                            }/*else{
                                recv(descritorCliente, &personas, sizeof(personas),0);
                            }*/


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
                        if(confp[i] == 1){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s: %d", texto4, i);
                        }else{
                           al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s: %d", texto3, i);
                        }

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
                  if(i == posicaoServidor)  {
                      if(confp[i] == 1){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s: %d", texto1, i);
                        }else{
                           al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "Arguandando informacoes do serve");
                        }
                  }else{
                        if(confp[i] == 1){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s%d%s", texto4, i,okok);
                        }else{
                           al_draw_textf(fonte, al_map_rgb(140, 255, 0), 300, (150 +(i * 50)), ALLEGRO_ALIGN_CENTRE, "%s%d", texto3, i);
                        }
                  }
            }

            if(conf2 == 1)
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

    return 0;


}



int main(){
    HANDLE th[2];
    DWORD Ith;
//    struct sockaddr_in serv_addr;
    /*Tamanho da estrutura*/
//    unsigned int clntLen;
//    clntLen = sizeof (sock);
//    HANDLE th;
    /*Define o descritor cliente*/
    //int descritorCliente;
    descritorCliente = criaCliente();
    recv(descritorCliente, &posicaoServidor, sizeof(posicaoServidor),0);
    printf("%d\n", posicaoServidor);
    recv(descritorCliente, &mapa, sizeof(mapa),0);
    recv(descritorCliente, (void*)&personas, sizeof(personas),0);
    eu = personas[posicaoServidor];
    red.x = eu.x;
    red.y = eu.y;
    //zeraPersonagens();
    //printf("%d,\n%d\n", red[posicaoServidor].x,red[posicaoServidor].y);
    th[0] = CreateThread(NULL,0,recebeClientes,&posicaoServidor,0,&Ith);

    int qual = menu();
    send(descritorCliente, (void*)&eu, sizeof(eu),0);
    int q2;
    if(qual == 1){
        waitplayer();
        th[1] = CreateThread(NULL,0,enviaClientes,&posicaoServidor,0,&Ith);
        game(posicaoServidor);
    }

    return 0;
}
