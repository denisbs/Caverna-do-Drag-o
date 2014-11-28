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


#define WIDTH 650
#define HEIGHT 650

#define WIDTHM 500
#define HEIGHTM 450

#define mapa_sizeL 67
#define mapa_sizeC 71

#define TILE_SIZEH 50
#define TILE_SIZEV 50
#define SPRITE_SIZEH 32
#define SPRITE_SIZEV 40
#define NUM_SPRITES 5
#define FRAMES_PER_SHIFT 10
#define SPEED 3

#define worldWidth 3550
#define worldHeight 3350

#define realWieHei 650


#define FPS 60



WSADATA data; //Variíveis que recebem o valor da inicialização e criação do socket.
//SOCKET winsock; //Variíveis que recebem o valor da inicialização e criação do socket.
SOCKADDR_IN sock; //Variíveis que recebem o valor da inicialização e criação do socket.

int descritorCliente;
int posicaoServidor;
char ip [1024];
int posicaoPersonagem[4][4];
int saidaMapa;


// the camera's position
int cameraX = 0;
int cameraY = 0;

int posicaoS[6][3];

int vencedor;

int mapa[67][71];


struct pontoNas{
        int x[7];
        int y[7];
        int ativa[7];

};

struct pontoNas inicios;

void setI(){
    inicios.x[0] = 1;
    inicios.y[0] = 1;
    inicios.ativa[0] = 0;
    mapa[1][1] = 60;

    inicios.x[1] = 1;
    inicios.y[1] = 33;
    inicios.ativa[1] = 0;
    mapa[33][1] = 60;

    inicios.x[2] = 1;
    inicios.y[2] = 65;
    inicios.ativa[2] = 0;
    mapa[65][1] = 60;

    inicios.x[3] =35;
    inicios.y[3] = 1;
    inicios.ativa[3] = 0;
    mapa[1][35] = 60;


    inicios.x[4] = 35;
    inicios.y[4] = 65;
    inicios.ativa[4] = 0;
    mapa[65][35] = 60;

    inicios.x[5] = 69;
    inicios.y[5] = 1;
    inicios.ativa[5] = 0;
    mapa[1][69] = 60;

    inicios.x[6] = 69;
    inicios.y[6] = 65;
    inicios.ativa[6] = 0;
    mapa[65][69] = 60;

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

      int ataque;
      int frame;
      int arm;


      int chave;

};

struct Pdfora{
    int x;
    int y;

    int estado;

    int spritel;
    int spritec;

    int atacando;

    int trapX;
    int trapY;
    int Trapativa;
    int spriteT;
    int vida;

    int inicia;

    int chave;
};

struct relogio{
    int minutos;
    int segundos;
};

struct trapAtiva{
    int x;
    int y;
    int quale;

};

struct Reds red;
struct Pdfora personas[4];
struct Pdfora eu;
struct trapAtiva TAFu;
struct relogio reloginho;

void SetS(){
    posicaoS[0][0] = 12;
    posicaoS[0][1] = 18;
    posicaoS[0][2] = 71;

    posicaoS[1][0] = 14;
    posicaoS[1][1] = 44;
    posicaoS[1][2] = 72;

    posicaoS[2][0] = 20;
    posicaoS[2][1] = 43;
    posicaoS[2][2] = 73;


    posicaoS[3][0] = 47;
    posicaoS[3][1] = 62;
    posicaoS[3][2] = 74;

    posicaoS[4][0] = 46;
    posicaoS[4][1] = 23;
    posicaoS[4][2] = 75;

    posicaoS[5][0] = 68;
    posicaoS[5][1] = 22;
    posicaoS[5][2] = 76;

}


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
    	//red.b = personas[posicaoServidor].estado;
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
        eu.estado = red.b;

            Sleep(20);
            send(descritorCliente, (void*)&eu, sizeof(eu),0);
        //}
    }

}

void setmove(int lado){
    // 4 = down 1, 1 = esquerda -1, 2 = direita 1, 3 = cima-1 - mapa de sprites moves
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
   p = rand()%7;
   inicios.ativa[p] = identiP(inicios.x[p]*50, inicios.y[p]*50);


   while(C == 1){

        if(inicios.ativa[p] == 0){
            red.x = inicios.x[p]*50;
            red.y = inicios.y[p]*50;
            inicios.ativa[p] = 0;
            C=0;
        }else{
            p = rand()%7;
            inicios.ativa[p] = identiP(inicios.x[p]*50, inicios.y[p]*50);
        }
   }

}

void atualizaCAM(int x, int y){

    cameraX = (x)- realWieHei/2;
    cameraY = (y)- realWieHei/2;

    if (cameraX < 0)
        cameraX = 0;

    if (cameraY < 0)
        cameraY = 0;

    if (cameraX > (worldWidth - realWieHei))
        cameraX = worldWidth - realWieHei;

    if (cameraY > (worldHeight - realWieHei))
        cameraY = worldHeight - realWieHei;


}

int identiP(int x, int y){
    int coli = 0;
    int contador;

    for (contador = 0; contador < 4; contador++ ){
            if(contador != posicaoServidor){

                    if(personas[contador].x >= x && personas[contador].x <= (x+50))
                        if(personas[contador].y >= y && personas[contador].y <= (y+50))
                            coli = 1;

                    if((personas[contador].x+32) >= x && (personas[contador].x+32) <= (x+50))
                        if(personas[contador].y >= y && personas[contador].y <= (y+50))
                            coli = 1;

                    if(personas[contador].x >= x && personas[contador].x <= (x+50))
                        if((personas[contador].y+40) >= y && (personas[contador].y+40) <= (y+50))
                            coli = 1;

                    if((personas[contador].x+32) >= x && (personas[contador].x+32) <= (x+50))
                        if((personas[contador].y+40) >= y && (personas[contador].y+40) <= (y+50))
                            coli = 1;

                    if((personas[contador].x+16) >= x && (personas[contador].x+16) <= (x+50))
                        if((personas[contador].y+20) >= y && (personas[contador].y+20) <= (y+50))
                            coli = 1;
            }



    }

    return coli;
}

int ataque(int x, int y, int sentido){

    int coli = 5;
    int contador;
     // 4 = down 1, 1 = esquerda -1, 2 = direita 1, 3 = cima-1

    switch(sentido){
		case 4:
			y = y+41; //baixo
			for (contador = 0; contador < 4; contador++ ){
					if(contador != posicaoServidor){
                        /*
                        if((personas[contador].x+16) >= x && (personas[contador].x+16) <= (x+50))
                            if((personas[contador].y+20) >= y && (personas[contador].y+20) <= (y+50))
                                    coli =contador;
                        */

                        if((personas[contador].x+16)>= x){
                            if((personas[contador].x+16)<= x+50){
                                if((personas[contador].y+20)>= y){
                                    if((personas[contador].y+20)<= y+50)
                                    {
                                            coli =contador;
                                    }
                                }
                            }
                        }

					}
			}
		break;
		case 1://esquerda
			x = x - 50;
			for (contador = 0; contador < 4; contador++ ){
					if(contador != posicaoServidor){

						if((personas[contador].x+16)>= x){
                            if((personas[contador].x+16)<= x+50){
                                if((personas[contador].y+20)>= y){
                                    if((personas[contador].y+20)<= y+50)
                                    {
                                            coli =contador;
                                    }
                                }
                            }
                        }

					}
			}
			break;
		case 2://direita
			x = x + 33;
			for (contador = 0; contador < 4; contador++ ){
					if((personas[contador].y+20)>= y){
                            if((personas[contador].y+20)<= y+50)
                                 if((personas[contador].x+16)>= x){
                                    if((personas[contador].x+16)<= x+50){
                                    {
                                            coli =contador;
                                    }
                                }
                            }
                        }
			}
			break;
		case 3://cima
			y = y-51;
			for (contador = 0; contador < 4; contador++ ){
					if(contador != posicaoServidor){


                        if((personas[contador].y+20)>= y){
                            if((personas[contador].y+20)<= y+50)
                                 if((personas[contador].x+16)>= x){
                                    if((personas[contador].x+16)<= x+50){
                                    {
                                            coli =contador;
                                    }
                                }
                            }
                        }

					}
			}
			break;
			default:
			    coli = 5;
                break;
	}
    printf("%d\n",coli);
    return coli;
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

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;



                        //ponto de borda sprite 2
                        anaX = (px+32)/50;
                        anaY = (py/50);

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                        //ponto de borda sprite 3
                        anaX = (px+32)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                        if(mapa[anaY][anaX] > 100)
                            coli = 3;

                       // if(mapa[anaY][anaX] == 5)
                         //   coli = 5;

                        //ponto de borda sprite 4
                        anaX = (px)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                        if(mapa[anaY][anaX] > 100)
                            coli = 3;

                        //if(mapa[anaY][anaX] == 5)
                          //  coli = 5;





       }else {
                if(eixo == 2){
                            py += posiy * SPEED;
                                 //ponto de borda sprite 1

                        anaX = (px/50);
                        anaY = (py/50);

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                        //ponto de borda sprite 2
                        anaX = (px+32)/50;
                        anaY = (py/50);

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                        //ponto de borda sprite 3
                        anaX = (px+32)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                       if(mapa[anaY][anaX] > 100)
                            coli = 3;

                        // if(mapa[anaY][anaX] == 5)
                          //  coli = 5;

                        //ponto de borda sprite 4
                        anaX = (px)/50;
                        anaY = (py+40)/50;

                        if( mapa[anaY][anaX] >= 35 && mapa[anaY][anaX] <= 57 && mapa[anaY][anaX] != 60 )
                            coli = 1;

                        if(mapa[anaY][anaX] > 100)
                            coli = 3;

                         //if(mapa[anaY][anaX] == 5)
                        //    coli = 5;



                    }

       }


        //para o personagem
       int contador;

       for (contador = 0; contador < 4; contador++ ){
            if(contador != posicaoServidor){
                if(eixo == 1){
                        px += posix * SPEED;

                        if(px >= personas[contador].x && px<=(personas[contador].x+32) )
                            if(red.y >= personas[contador].y && red.y<=(personas[contador].y+40) )
                                coli =1;

                        if((px+32) >= personas[contador].x && (px+32)<=(personas[contador].x+32) )
                            if(red.y >= personas[contador].y && red.y<=(personas[contador].y+40) )
                                coli =1;

                        if((px) >= personas[contador].x && (px)<=(personas[contador].x+32) )
                            if((red.y+40) >= personas[contador].y && (red.y+40)<=(personas[contador].y+40) )
                                coli =1;

                        if((px+32) >= personas[contador].x && (px+32)<=(personas[contador].x+32) )
                            if((red.y+40) >= personas[contador].y && (red.y+40)<=(personas[contador].y+40) )
                                coli =1;




                        if((px+16) >= personas[contador].x && (px+16)<=(personas[contador].x+32) )
                            if(red.y >= personas[contador].y && red.y<=(personas[contador].y+40) )
                                coli =1;

                        if((px+16) >= personas[contador].x && (px+16)<=(personas[contador].x+32) )
                            if(red.y >= personas[contador].y && red.y<=(personas[contador].y+40) )
                                coli =1;

                        if((px+16) >= personas[contador].x && (px+16)<=(personas[contador].x+32) )
                            if((red.y+20) > personas[contador].y && (red.y+20)<(personas[contador].y+40) )
                                coli =1;

                        if((px+16) >= personas[contador].x && (px+16)<=(personas[contador].x+32) )
                            if((red.y+20) >= personas[contador].y && (red.y+20)<=(personas[contador].y+40) )
                                coli =1;


                }
                if(eixo == 2){
                     py += posiy * SPEED;
                    if(py >= personas[contador].y && py<=(personas[contador].y+40) )
                        if(red.x >= personas[contador].x && red.x<=(personas[contador].x+32) )
                            coli =1;

                    if((py+40) >= personas[contador].y && (py+40)<=(personas[contador].y+40) )
                        if((red.x+32) >= personas[contador].x && (red.x+32)<=(personas[contador].x+32) )
                            coli =1;

                    if(py >= personas[contador].y && py<=(personas[contador].y+40) )
                        if((red.x+32) >= personas[contador].x && (red.x+32)<=(personas[contador].x+32) )
                            coli =1;

                    if((py+40) >= personas[contador].y && (py+40)<=(personas[contador].y+40) )
                        if(red.x >= personas[contador].x && red.x<=(personas[contador].x+32) )
                            coli =1;


                    if((py+20) >= personas[contador].y && (py+20)<=(personas[contador].y+40) )
                        if(red.x >= personas[contador].x && red.x<=(personas[contador].x+32) )
                            coli =1;

                    if((py+20) >= personas[contador].y && (py+20)<=(personas[contador].y+40) )
                        if((red.x+16) >= personas[contador].x && (red.x+16)<=(personas[contador].x+32) )
                            coli =1;

                    if((py+20) >= personas[contador].y && (py+20)<=(personas[contador].y+40) )
                        if((red.x+16) >= personas[contador].x && (red.x+16)<=(personas[contador].x+32) )
                            coli =1;

                    if((py+20) >= personas[contador].y && (py+20)<=(personas[contador].y+40) )
                        if(red.x >= personas[contador].x && red.x <= (personas[contador].x+32) )
                            coli =1;




                }






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

            if(esta == 0 || esta == 5){
                red.x += red.moveH * SPEED;
                atualizaCAM(red.x, red.y);
            }
                if (esta == 3){


                    red.xA = red.x;
                    red.xA = red.xA/50;
                    red.xA = red.xA*50;
                    red.yA = red.y;
                    red.x += red.moveH * SPEED;
                    atualizaCAM(red.x, red.y);

                    red.moveH = 0;

                    TAFu.x = red.x/50;
                    TAFu.y = (red.y+40)/50;


                    int inia;
                    if (mapa[TAFu.y][TAFu.x] < 100){
                        inia = TAFu.x + 1;
                        if (mapa[TAFu.y][inia] < 100){
                            TAFu.x = TAFu.x -1;
                        }else{
                            TAFu.x = inia;
                        }

                    }
                    TAFu.quale = mapa[TAFu.y][TAFu.x] -101;
                    red.sprite = 0;

                }
                    if (cameraX < 0)
                        cameraX = 0;

                    if (cameraY < 0)
                        cameraY = 0;

                    if (cameraX > (worldWidth - realWieHei))
                        cameraX = worldWidth - realWieHei;

                    if (cameraY > (worldHeight - realWieHei))
                        cameraY = worldHeight - realWieHei;



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

            if(esta == 0 || esta == 5 ){
                red.y += red.moveV * SPEED;
                atualizaCAM(red.x, red.y);
            }else{
                if (esta == 3){

                    red.xA = red.x;
                    red.yA = red.y/50;
                    if(red.moveV == -1)
                        red.yA = red.yA + 1;

                    red.yA = (red.yA) * 50;
                    red.y += red.moveV * SPEED;
                    atualizaCAM(red.x, red.y);

                    red.moveV = 0;

                    TAFu.x =  (red.x)/50;
                    TAFu.y = (red.y+40)/50;


                    int inia;
                    if (mapa[TAFu.y][TAFu.x] < 100){
                        inia = TAFu.x + 1;
                        if (mapa[TAFu.y][inia] < 100){
                            TAFu.x = TAFu.x -1;
                        }else{
                            TAFu.x = inia;
                        }

                    }
                    TAFu.quale = mapa[TAFu.y][TAFu.x] -101;

                    red.sprite = 0;
                    //printf("trap\n\n");

                }

                }

                    if (cameraX < 0)
                        cameraX = 0;

                    if (cameraY < 0)
                        cameraY = 0;

                    if (cameraX > (worldWidth - realWieHei))
                        cameraX = worldWidth - realWieHei;

                    if (cameraY > (worldHeight - realWieHei))
                        cameraY = worldHeight - realWieHei;


        return esta;
}

void error(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);

  exit(EXIT_FAILURE);
}

void zeraPersonagens(){

        red.sprite = 0;
        red.direcaoS = 0;
        red.moveH = 0;
        red.moveV = 0;
        red.frame = 0;
        red.arm = -1;
}

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
  ALLEGRO_TIMER *timer_mudanca_de_posicao_na_imagem_da_trap = al_create_timer(0.12);
  ALLEGRO_TIMER *timer_contador = al_create_timer(1.0);
  ALLEGRO_TIMER *timer_ataque = al_create_timer(0.15);
  ALLEGRO_TIMER *timer_dano = al_create_timer(0.35);
  /**********//*
  ALLEGRO_BITMAP *area_central = al_create_bitmap(250, 650);
    if (!area_central)
        error("Falha ao criar bitmap.");
*/
// itens de informações de personagem Local
    ALLEGRO_BITMAP *life = al_load_bitmap("C:/Inclusos/heart.png");
    if(!life)
        error("faled to load life");

    ALLEGRO_BITMAP *sheet = al_load_bitmap("C:/Inclusos/Red.png");
    if(!sheet)
        error("failed to load sheet");

    ALLEGRO_FONT *fonte = al_load_font("C:/Inclusos/aspartam.ttf", 20, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");


    ALLEGRO_BITMAP *sprites[NUM_SPRITES+4][NUM_SPRITES];

    int shift, shiftb;

    for(shift = 0; shift < (NUM_SPRITES+4); shift++){
        for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++){
            sprites[shift][shiftb] = al_create_sub_bitmap(sheet, shiftb * SPRITE_SIZEH, shift * SPRITE_SIZEV, SPRITE_SIZEH, SPRITE_SIZEV);
        }
    }
// carregando imagens do mapa
  //imagens de solo
    ALLEGRO_BITMAP *i1 = al_load_bitmap("C:/Inclusos/mapa/1.png");
    if(!i1)
      error("failed to load 1");
    ALLEGRO_BITMAP *i2 = al_load_bitmap("C:/Inclusos/mapa/2.png");
    if(!i2)
      error("failed to load 2");
    ALLEGRO_BITMAP *i3 = al_load_bitmap("C:/Inclusos/mapa/3.png");
    if(!i3)
      error("failed to load 3");
    ALLEGRO_BITMAP *i4 = al_load_bitmap("C:/Inclusos/mapa/4.png");
    if(!i4)
      error("failed to load 4");
    ALLEGRO_BITMAP *i5 = al_load_bitmap("C:/Inclusos/mapa/5.png");
    if(!i5)
      error("failed to load 5");
    ALLEGRO_BITMAP *i6 = al_load_bitmap("C:/Inclusos/mapa/6.png");
    if(!i6)
      error("failed to load 6");
    ALLEGRO_BITMAP *i7 = al_load_bitmap("C:/Inclusos/mapa/7.png");
    if(!i7)
      error("failed to load 7");
    ALLEGRO_BITMAP *i8 = al_load_bitmap("C:/Inclusos/mapa/8.png");
    if(!i8)
      error("failed to load 8");
    ALLEGRO_BITMAP *i9 = al_load_bitmap("C:/Inclusos/mapa/9.png");
    if(!i9)
      error("failed to load 9");
    ALLEGRO_BITMAP *i10 = al_load_bitmap("C:/Inclusos/mapa/10.png");
    if(!i10)
      error("failed to load 10");
    ALLEGRO_BITMAP *i11 = al_load_bitmap("C:/Inclusos/mapa/11.png");
    if(!i11)
      error("failed to load 11");
    ALLEGRO_BITMAP *i12 = al_load_bitmap("C:/Inclusos/mapa/12.png");
    if(!i12)
      error("failed to load 12");
    ALLEGRO_BITMAP *i13 = al_load_bitmap("C:/Inclusos/mapa/13.png");
    if(!i13)
      error("failed to load 13");
    ALLEGRO_BITMAP *i14 = al_load_bitmap("C:/Inclusos/mapa/14.png");
    if(!i14)
      error("failed to load 14");
    ALLEGRO_BITMAP *i15 = al_load_bitmap("C:/Inclusos/mapa/15.png");
    if(!i15)
      error("failed to load 15");
    ALLEGRO_BITMAP *i16 = al_load_bitmap("C:/Inclusos/mapa/16.png");
    if(!i16)
      error("failed to load 16");
    ALLEGRO_BITMAP *i17 = al_load_bitmap("C:/Inclusos/mapa/17.png");
    if(!i17)
      error("failed to load 17");
    ALLEGRO_BITMAP *i18 = al_load_bitmap("C:/Inclusos/mapa/18.png");
    if(!i18)
      error("failed to load 18");
    ALLEGRO_BITMAP *i19 = al_load_bitmap("C:/Inclusos/mapa/19.png");
    if(!i19)
      error("failed to load 19");
    ALLEGRO_BITMAP *i20 = al_load_bitmap("C:/Inclusos/mapa/20.png");
    if(!i20)
      error("failed to load 20");
    ALLEGRO_BITMAP *i21 = al_load_bitmap("C:/Inclusos/mapa/21.png");
    if(!i21)
      error("failed to load 21");
    ALLEGRO_BITMAP *i22 = al_load_bitmap("C:/Inclusos/mapa/22.png");
    if(!i22)
      error("failed to load 22");
    ALLEGRO_BITMAP *i23 = al_load_bitmap("C:/Inclusos/mapa/23.png");
    if(!i23)
      error("failed to load 23");
    ALLEGRO_BITMAP *i24 = al_load_bitmap("C:/Inclusos/mapa/24.png");
    if(!i24)
      error("failed to load 24");
    ALLEGRO_BITMAP *i25 = al_load_bitmap("C:/Inclusos/mapa/25.png");
    if(!i25)
      error("failed to load 25");
    ALLEGRO_BITMAP *i26 = al_load_bitmap("C:/Inclusos/mapa/26.png");
    if(!i26)
      error("failed to load 26");
    ALLEGRO_BITMAP *i27 = al_load_bitmap("C:/Inclusos/mapa/27.png");
    if(!i27)
      error("failed to load 27");
    ALLEGRO_BITMAP *i28 = al_load_bitmap("C:/Inclusos/mapa/28.png");
    if(!i28)
      error("failed to load 28");
    ALLEGRO_BITMAP *i29 = al_load_bitmap("C:/Inclusos/mapa/29.png");
    if(!i29)
      error("failed to load 29");
    ALLEGRO_BITMAP *i30 = al_load_bitmap("C:/Inclusos/mapa/30.png");
    if(!i30)
      error("failed to load 30");
    ALLEGRO_BITMAP *i31 = al_load_bitmap("C:/Inclusos/mapa/31.png");
    if(!i31)
      error("failed to load 31");
    ALLEGRO_BITMAP *i32 = al_load_bitmap("C:/Inclusos/mapa/32.png");
    if(!i32)
      error("failed to load 32");
    ALLEGRO_BITMAP *i33 = al_load_bitmap("C:/Inclusos/mapa/33.png");
    if(!i33)
      error("failed to load 33");
    ALLEGRO_BITMAP *i34 = al_load_bitmap("C:/Inclusos/mapa/34.png");
    if(!i34)
      error("failed to load 34");

    //paredes
    ALLEGRO_BITMAP *i35 = al_load_bitmap("C:/Inclusos/mapa/35.png");
    if(!i35)
      error("failed to load 35");
    ALLEGRO_BITMAP *i36 = al_load_bitmap("C:/Inclusos/mapa/36.png");
    if(!i36)
      error("failed to load 36");
    ALLEGRO_BITMAP *i37 = al_load_bitmap("C:/Inclusos/mapa/37.png");
    if(!i37)
      error("failed to load 37");
    ALLEGRO_BITMAP *i38 = al_load_bitmap("C:/Inclusos/mapa/38.png");
    if(!i38)
      error("failed to load 38");
    ALLEGRO_BITMAP *i39 = al_load_bitmap("C:/Inclusos/mapa/39.png");
    if(!i39)
      error("failed to load 39");
    ALLEGRO_BITMAP *i40 = al_load_bitmap("C:/Inclusos/mapa/40.png");
    if(!i40)
      error("failed to load 40");
    ALLEGRO_BITMAP *i41 = al_load_bitmap("C:/Inclusos/mapa/41.png");
    if(!i41)
      error("failed to load 41");
    ALLEGRO_BITMAP *i42 = al_load_bitmap("C:/Inclusos/mapa/42.png");
    if(!i42)
      error("failed to load 42");
    ALLEGRO_BITMAP *i43 = al_load_bitmap("C:/Inclusos/mapa/43.png");
    if(!i43)
      error("failed to load 43");
    ALLEGRO_BITMAP *i44 = al_load_bitmap("C:/Inclusos/mapa/44.png");
    if(!i44)
      error("failed to load 44");
    ALLEGRO_BITMAP *i45 = al_load_bitmap("C:/Inclusos/mapa/45.png");
    if(!i45)
      error("failed to load 45");
    ALLEGRO_BITMAP *i46 = al_load_bitmap("C:/Inclusos/mapa/46.png");
    if(!i46)
      error("failed to load 46");
    ALLEGRO_BITMAP *i47 = al_load_bitmap("C:/Inclusos/mapa/47.png");
    if(!i47)
      error("failed to load 47");
    ALLEGRO_BITMAP *i48 = al_load_bitmap("C:/Inclusos/mapa/48.png");
    if(!i48)
      error("failed to load 48");
    ALLEGRO_BITMAP *i49 = al_load_bitmap("C:/Inclusos/mapa/49.png");
    if(!i49)
      error("failed to load 49");
    ALLEGRO_BITMAP *i50 = al_load_bitmap("C:/Inclusos/mapa/50.png");
    if(!i50)
      error("failed to load 50");
    ALLEGRO_BITMAP *i51 = al_load_bitmap("C:/Inclusos/mapa/51.png");
    if(!i51)
      error("failed to load 51");
    ALLEGRO_BITMAP *i52 = al_load_bitmap("C:/Inclusos/mapa/52.png");
    if(!i52)
      error("failed to load 52");
    ALLEGRO_BITMAP *i53 = al_load_bitmap("C:/Inclusos/mapa/53.png");
    if(!i53)
      error("failed to load 53");
    ALLEGRO_BITMAP *i54 = al_load_bitmap("C:/Inclusos/mapa/54.png");
    if(!i54)
      error("failed to load 54");
    ALLEGRO_BITMAP *i55 = al_load_bitmap("C:/Inclusos/mapa/55.png");
    if(!i55)
      error("failed to load 55");
    ALLEGRO_BITMAP *i56 = al_load_bitmap("C:/Inclusos/mapa/56.png");
    if(!i56)
      error("failed to load 56");
    ALLEGRO_BITMAP *i57 = al_load_bitmap("C:/Inclusos/mapa/57.png");
    if(!i57)
      error("failed to load 57");
    //saidas
    ALLEGRO_BITMAP *s60 = al_load_bitmap("C:/Inclusos/exit.png");
    if(!s60)
      error("failed to load exit");


  //armadilhas
    ALLEGRO_BITMAP *t1 = al_load_bitmap("C:/Inclusos/mapa/trap1.png");
    if(!t1)
      error("failed to load trap 1");
    ALLEGRO_BITMAP *t2 = al_load_bitmap("C:/Inclusos/mapa/trap2.png");
    if(!t2)
      error("failed to load trap 2");
    ALLEGRO_BITMAP *t3 = al_load_bitmap("C:/Inclusos/mapa/trap3.png");
    if(!t3)
      error("failed to load trap 3");
    ALLEGRO_BITMAP *t4 = al_load_bitmap("C:/Inclusos/mapa/trap4.png");
    if(!t4)
      error("failed to load trap 4");
    ALLEGRO_BITMAP *t5 = al_load_bitmap("C:/Inclusos/mapa/trap5.png");
    if(!t5)
      error("failed to load trap 5");
    ALLEGRO_BITMAP *t6 = al_load_bitmap("C:/Inclusos/mapa/trap6.png");
    if(!t6)
      error("failed to load trap 6");
    ALLEGRO_BITMAP *t7 = al_load_bitmap("C:/Inclusos/mapa/trap7.png");
    if(!t7)
      error("failed to load trap 7");
    ALLEGRO_BITMAP *t8 = al_load_bitmap("C:/Inclusos/mapa/trap8.png");
    if(!t8)
      error("failed to load trap 8");
    ALLEGRO_BITMAP *t9 = al_load_bitmap("C:/Inclusos/mapa/trap9.png");
    if(!t9)
      error("failed to load trap 9");
    ALLEGRO_BITMAP *t10 = al_load_bitmap("C:/Inclusos/mapa/trap10.png");
    if(!t10)
      error("failed to load trap 10");
    ALLEGRO_BITMAP *t11 = al_load_bitmap("C:/Inclusos/mapa/trap11.png");
    if(!t11)
      error("failed to load trap 11");
    ALLEGRO_BITMAP *t12 = al_load_bitmap("C:/Inclusos/mapa/trap12.png");
    if(!t12)
      error("failed to load trap 12");
    ALLEGRO_BITMAP *t13 = al_load_bitmap("C:/Inclusos/mapa/trap13.png");
    if(!t13)
      error("failed to load trap 13");
    ALLEGRO_BITMAP *t14 = al_load_bitmap("C:/Inclusos/mapa/trap14.png");
    if(!t14)
      error("failed to load trap 14");
    ALLEGRO_BITMAP *t15 = al_load_bitmap("C:/Inclusos/mapa/trap15.png");
    if(!t15)
      error("failed to load trap 15");
    ALLEGRO_BITMAP *t16 = al_load_bitmap("C:/Inclusos/mapa/trap16.png");
    if(!t16)
      error("failed to load trap 16");
    ALLEGRO_BITMAP *t17 = al_load_bitmap("C:/Inclusos/mapa/trap17.png");
    if(!t17)
      error("failed to load trap 17");
    ALLEGRO_BITMAP *t18 = al_load_bitmap("C:/Inclusos/mapa/trap18.png");
    if(!t18)
      error("failed to load trap 18");
    ALLEGRO_BITMAP *t19 = al_load_bitmap("C:/Inclusos/mapa/trap19.png");
    if(!t19)
      error("failed to load trap 19");
    ALLEGRO_BITMAP *t20 = al_load_bitmap("C:/Inclusos/mapa/trap20.png");
    if(!t20)
      error("failed to load trap 20");
    ALLEGRO_BITMAP *t21 = al_load_bitmap("C:/Inclusos/mapa/trap21.png");
    if(!t21)
      error("failed to load trap 21");
    ALLEGRO_BITMAP *t22 = al_load_bitmap("C:/Inclusos/mapa/trap22.png");
    if(!t22)
      error("failed to load trap 22");
    ALLEGRO_BITMAP *t23 = al_load_bitmap("C:/Inclusos/mapa/trap23.png");
    if(!t23)
      error("failed to load trap 23");
    ALLEGRO_BITMAP *t24 = al_load_bitmap("C:/Inclusos/mapa/trap24.png");
    if(!t24)
      error("failed to load trap 24");
    ALLEGRO_BITMAP *t25 = al_load_bitmap("C:/Inclusos/mapa/trap25.png");
    if(!t25)
      error("failed to load trap 25");
    ALLEGRO_BITMAP *t26 = al_load_bitmap("C:/Inclusos/mapa/trap26.png");
    if(!t26)
      error("failed to load trap 26");
    ALLEGRO_BITMAP *t27 = al_load_bitmap("C:/Inclusos/mapa/trap27.png");
    if(!t27)
      error("failed to load trap 27");
    ALLEGRO_BITMAP *t28 = al_load_bitmap("C:/Inclusos/mapa/trap28.png");
    if(!t28)
      error("failed to load trap 28");
    ALLEGRO_BITMAP *t29 = al_load_bitmap("C:/Inclusos/mapa/trap29.png");
    if(!t29)
      error("failed to load trap 29");
    ALLEGRO_BITMAP *t30 = al_load_bitmap("C:/Inclusos/mapa/trap30.png");
    if(!t30)
      error("failed to load trap 30");
    ALLEGRO_BITMAP *t31 = al_load_bitmap("C:/Inclusos/mapa/trap31.png");
    if(!t31)
      error("failed to load trap 31");
    ALLEGRO_BITMAP *t32 = al_load_bitmap("C:/Inclusos/mapa/trap32.png");
    if(!t32)
      error("failed to load trap 32");
    ALLEGRO_BITMAP *t33 = al_load_bitmap("C:/Inclusos/mapa/trap33.png");
    if(!t33)
      error("failed to load trap 33");
    ALLEGRO_BITMAP *t34 = al_load_bitmap("C:/Inclusos/mapa/trap34.png");
    if(!t34)
      error("failed to load trap 34");


    // carregar armadilha sprites
    ALLEGRO_BITMAP *traps[35][5];
    int trapshift;

    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[0][trapshift]= al_create_sub_bitmap(t1, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[1][trapshift]= al_create_sub_bitmap(t2, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[2][trapshift]= al_create_sub_bitmap(t3, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[3][trapshift]= al_create_sub_bitmap(t4, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[4][trapshift]= al_create_sub_bitmap(t5, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[5][trapshift]= al_create_sub_bitmap(t6, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[6][trapshift]= al_create_sub_bitmap(t7, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[7][trapshift]= al_create_sub_bitmap(t8, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[8][trapshift]= al_create_sub_bitmap(t9, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[9][trapshift]= al_create_sub_bitmap(t10, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }

    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[10][trapshift]= al_create_sub_bitmap(t11, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[11][trapshift]= al_create_sub_bitmap(t12, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[12][trapshift]= al_create_sub_bitmap(t13, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[13][trapshift]= al_create_sub_bitmap(t14, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[14][trapshift]= al_create_sub_bitmap(t15, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[15][trapshift]= al_create_sub_bitmap(t16, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[16][trapshift]= al_create_sub_bitmap(t17, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[17][trapshift]= al_create_sub_bitmap(t18, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[18][trapshift]= al_create_sub_bitmap(t19, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[19][trapshift]= al_create_sub_bitmap(t20, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[20][trapshift]= al_create_sub_bitmap(t21, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[21][trapshift]= al_create_sub_bitmap(t22, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[22][trapshift]= al_create_sub_bitmap(t23, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[23][trapshift]= al_create_sub_bitmap(t24, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[24][trapshift]= al_create_sub_bitmap(t25, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[25][trapshift]= al_create_sub_bitmap(t26, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[26][trapshift]= al_create_sub_bitmap(t27, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[27][trapshift]= al_create_sub_bitmap(t28, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[28][trapshift]= al_create_sub_bitmap(t29, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[29][trapshift]= al_create_sub_bitmap(t30, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[30][trapshift]= al_create_sub_bitmap(t31, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[31][trapshift]= al_create_sub_bitmap(t32, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[32][trapshift]= al_create_sub_bitmap(t33, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    for(trapshift = 0; trapshift < 5; trapshift++){
        traps[33][trapshift]= al_create_sub_bitmap(t34, trapshift * 49, 0, TILE_SIZEH, TILE_SIZEV);
    }
    //definido pontos inicias
    setI();
    int l,m;

    int px;
    int py;


    px = cameraX/50;
    py = cameraY/50;
    //subindo mapa pela primeira vez + demorado
        for(l = 0; l < mapa_sizeC; l++){
            for(m = 0; m < mapa_sizeL; m++){
              switch(mapa[m][l]){
                  case 60 :
                     al_draw_bitmap(s60,(l*50)-cameraX,(m*50)-cameraY, 0);
                     break;
                  case 1 :
                     al_draw_bitmap(i1,(l*50)-cameraX,(m*50)-cameraY, 0);
                     break;
                                            case 2 :
                                                al_draw_bitmap(i2,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 3 :
                                                al_draw_bitmap(i3,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 4 :
                                                al_draw_bitmap(i4,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 5 :
                                                al_draw_bitmap(i5,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 6 :
                                                al_draw_bitmap(i6,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 7 :
                                                al_draw_bitmap(i7,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 8 :
                                                al_draw_bitmap(i8,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 9 :
                                                al_draw_bitmap(i9,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 10 :
                                                al_draw_bitmap(i10,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 11 :
                                                al_draw_bitmap(i11,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 12 :
                                                al_draw_bitmap(i12,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 13 :
                                                al_draw_bitmap(i13,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 14 :
                                                al_draw_bitmap(i14,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 15 :
                                                al_draw_bitmap(i15,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 16 :
                                                al_draw_bitmap(i16,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 17 :
                                                al_draw_bitmap(i17,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 18 :
                                                al_draw_bitmap(i18,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 19 :
                                                al_draw_bitmap(i19,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 20 :
                                                al_draw_bitmap(i20,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 21 :
                                                al_draw_bitmap(i21,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 22 :
                                                al_draw_bitmap(i22,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 23 :
                                                al_draw_bitmap(i23,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 24 :
                                                al_draw_bitmap(i24,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 25 :
                                                al_draw_bitmap(i25,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 26 :
                                                al_draw_bitmap(i26,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 27 :
                                                al_draw_bitmap(i27,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 28 :
                                                al_draw_bitmap(i28,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 29 :
                                                al_draw_bitmap(i29,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 30 :
                                                al_draw_bitmap(i30,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 31 :
                                                al_draw_bitmap(i31,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 32 :
                                                al_draw_bitmap(i32,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 33 :
                                                al_draw_bitmap(i33,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 34 :
                                                al_draw_bitmap(i34,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 35 :
                                                al_draw_bitmap(i35,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 36 :
                                                al_draw_bitmap(i36,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 37 :
                                                al_draw_bitmap(i37,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 38 :
                                                al_draw_bitmap(i38,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 39 :
                                                al_draw_bitmap(i39,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 40 :
                                                al_draw_bitmap(i40,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 41 :
                                                al_draw_bitmap(i41,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 42 :
                                                al_draw_bitmap(i42,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 43 :
                                                al_draw_bitmap(i43,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 44 :
                                                al_draw_bitmap(i44,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 45 :
                                                al_draw_bitmap(i45,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 46 :
                                                al_draw_bitmap(i46,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 47 :
                                                al_draw_bitmap(i47,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 48 :
                                                al_draw_bitmap(i48,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 49 :
                                                al_draw_bitmap(i49,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 50 :
                                                al_draw_bitmap(i50,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 51 :
                                                al_draw_bitmap(i51,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 52 :
                                                al_draw_bitmap(i52,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 53 :
                                                al_draw_bitmap(i53,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 54 :
                                                al_draw_bitmap(i54,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 55 :
                                                al_draw_bitmap(i55,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 56 :
                                                al_draw_bitmap(i56,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 57 :
                                                al_draw_bitmap(i57,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 101 :
                                                al_draw_bitmap(traps[0][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 102 :
                                                al_draw_bitmap(traps[1][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 103 :
                                                al_draw_bitmap(traps[2][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 104 :
                                                al_draw_bitmap(traps[3][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 105 :
                                                al_draw_bitmap(traps[4][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 106 :
                                                al_draw_bitmap(traps[5][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 107 :
                                                al_draw_bitmap(traps[6][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 108 :
                                                al_draw_bitmap(traps[7][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 109 :
                                                al_draw_bitmap(traps[8][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 110 :
                                                al_draw_bitmap(traps[9][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 111 :
                                                al_draw_bitmap(traps[10][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 112 :
                                                al_draw_bitmap(traps[11][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 113 :
                                                al_draw_bitmap(traps[12][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 114 :
                                                al_draw_bitmap(traps[13][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 115 :
                                                al_draw_bitmap(traps[14][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 116 :
                                                al_draw_bitmap(traps[15][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 117 :
                                                al_draw_bitmap(traps[16][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 118 :
                                                al_draw_bitmap(traps[17][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 119 :
                                                al_draw_bitmap(traps[18][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 120 :
                                                al_draw_bitmap(traps[19][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 121 :
                                                al_draw_bitmap(traps[20][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 122 :
                                                al_draw_bitmap(traps[21][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 123 :
                                                al_draw_bitmap(traps[22][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 124 :
                                                al_draw_bitmap(traps[23][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 125 :
                                                al_draw_bitmap(traps[24][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 126 :
                                                al_draw_bitmap(traps[25][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 127 :
                                                al_draw_bitmap(traps[26][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 128 :
                                                al_draw_bitmap(traps[27][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 129 :
                                                al_draw_bitmap(traps[28][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 130 :
                                                al_draw_bitmap(traps[29][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 131 :
                                                al_draw_bitmap(traps[30][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 132 :
                                                al_draw_bitmap(traps[31][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 133 :
                                                al_draw_bitmap(traps[32][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 134 :
                                                al_draw_bitmap(traps[33][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            default :
                                                break;
              }
            }
            }


    //al_set_target_bitmap(area_central);
    //al_clear_to_color(al_map_rgb(255, 255, 255));
    //al_draw_bitmap(area_central, 650,0,0);
  /**********/
  // 0 = down, 1 = esquerda, 2 = direita, 3 = cima
    int b; //condição de colisão com trsap
    int ai;

    eu.atacando = 5;
    int alguemganhou = 0;   //se algum player achar e alcancar a saida
    int flags = 0;
    int pos_x_trap = 0;
    int flag_trap = 0;

    int pos_dano = 0;
    int pos_ataq = 0;




    int atuaS = 0;

    red.frame = 0;
    eu.spriteT = 0;
    red.arm = -1;

    red.b = 0;
    eu.estado = 0;

    red.vida = 3;

    vencedor = 0;




    reloginho.segundos = 0;
    reloginho.minutos = 0;
/*cameraY = red.y - realWieHei/2;

*/


  /************/
  //Gerando personagens na tela
  int contador;
  /*for (contador = 0; contador < 4; contador++){
        //sortearNas(contador);
       //if(contador != servidor)
            personas[contador].spriteT = 0;
  }*/
  /**********/

  al_flip_display();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_timer_event_source(timer_mudanca_de_posicao_na_imagem_da_trap));
  al_register_event_source(queue, al_get_timer_event_source(timer_contador));
  al_register_event_source(queue, al_get_timer_event_source(timer_ataque));
  al_register_event_source(queue, al_get_timer_event_source(timer_dano));
  /**********/

  int running = 1;

    int paraporra = 0;

    int refresh = 0;
    red.sprite = 0;

    al_start_timer(timer);
    al_start_timer(timer_contador);

  while(running) {
    // estado < 3 anda normal, 3 amardilha, 4 ffim por tempo, 6 atacando, 7 atacado

    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_KEY_DOWN:
      switch(event.keyboard.keycode) {
      case ALLEGRO_KEY_LEFT:
        if(red.b < 3 && personas[servidor].estado != 7 && alguemganhou == 0){
            setmove(1 );
            flags = 0;
            refresh = 1;
        }
        break;

      case ALLEGRO_KEY_DOWN:
                if(red.b < 3 && personas[servidor].estado != 7 && alguemganhou == 0){
                    setmove(4);
                    flags = 0;
                    refresh = 1;
                }
            break;

      case ALLEGRO_KEY_UP:
            if(red.b < 3 && personas[servidor].estado != 7 && alguemganhou == 0){
                setmove(3);
                flags = 0;
                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_RIGHT:
            if(red.b < 3 && personas[servidor].estado != 7 && alguemganhou == 0){
                setmove(2);
                flags = 0;
                refresh = 1;
            }
        break;
      /*case ALLEGRO_KEY_SPACE:
            if(red.b < 3 && personas[servidor].estado != 7 && alguemganhou == 0){
                    setmove(0);
                    red.b = 6;
                    eu.atacando = ataque(red.x, red.y, red.direcaoS);
                    al_start_timer(timer_ataque);
                    red.direcaoS += 4;
                    flags = 0;
                    refresh = 1;
                }
            break;*/

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
        if(red.moveH == -1 && red.b != 7) {
          setmove(0);
          refresh = 1;
        }
        break;


      case ALLEGRO_KEY_DOWN:
            if(red.moveV == 1 && red.b != 7){
                setmove(0);
                refresh = 1;
            }
            break;

      case ALLEGRO_KEY_UP:
          if (red.moveV == -1 && red.b != 7){
            setmove(0);
            refresh = 1;
          }
            break;

      case ALLEGRO_KEY_RIGHT:
        if(red.moveH == 1 && red.b != 7) {
          setmove(0);
          refresh = 1;
        }
        break;
      /*case ALLEGRO_KEY_SPACE:
          if(red.b != 6 && red.b != 7) {
          setmove(0);
          refresh = 1;
        }
        break;*/

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
                if(red.b == 7){
                    red.sprite = 0;
                    if(paraporra == 0){
                        setmove(0);
                         if(red.vida > 1)
                         {
                            red.vida -= 1;
                            al_start_timer(timer_dano);
                         }else{
                             sortearNas();
                             red.b = 0;
                             al_stop_timer(timer_dano);
                         }

                        paraporra = 1;
                    }
                }


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
                    eu.estado = red.b;
                    refresh = 1;

        }

        if(event.timer.source == timer_mudanca_de_posicao_na_imagem_da_trap)
        {
            if(red.vida < 1){
                sortearNas();
            }

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

                    eu.trapX = TAFu.x;
                    eu.trapY = TAFu.y;
                    eu.spriteT = pos_x_trap;
                    refresh = 1;
            }

        if(event.timer.source == timer_contador)
            {
                    maisumseg();
                    if(reloginho.segundos == 15 && reloginho.minutos == 0 ){
                        mapa[6][6] = 5;
                        atuaS = 1;
                    }

                    if( reloginho.minutos == 6 && reloginho.segundos == 30){
                        al_stop_timer(timer_contador);
                        al_stop_timer(timer_dano);
                        al_stop_timer(timer_ataque);
                        al_stop_timer(timer_mudanca_de_posicao_na_imagem_da_trap);

                        red.b = 4;
                        eu.estado = 4;
                        personas[servidor].estado = 4;
                    }
            }

         if(event.timer.source == timer_ataque)
         {
             eu.atacando = 5;
            if(red.sprite < 2 && pos_ataq == 0)
            {
                red.sprite++;
            }
            else
            {
                pos_ataq = 1;
                red.sprite--;

                if(red.sprite == 0)
                    {
                        al_stop_timer(timer_ataque);
                        red.b = 0;
                        red.direcaoS -= 4;
                        pos_ataq = 0;
                        eu.atacando = 5;
                    }
            }


         }

         if(event.timer.source == timer_dano)
         {

                if(pos_dano < 4){
                    red.direcaoS++;
                    pos_dano++;
                    if(red.direcaoS >= 3){
                        red.direcaoS = 0;
                    }

                }else{
                    al_stop_timer(timer_dano);
                    red.b = 0;
                    eu.estado = 0;
                    paraporra = 0;
                    personas[contador].estado = 0;
                }
                eu.estado = red.b;
         }
            break;
        default:
            printf("");
        }

    if(refresh) {
        //send(descritorCliente, (void*)&red, sizeof(red),0);
        //recv(descritorCliente, (void*)&red, sizeof(red),0);

            for(contador = 0; contador <4; contador++){
                if(personas[contador].estado == 5){
                        vencedor = contador;
                        alguemganhou = 1;

                }
            }

            if(red.b != 5 && alguemganhou != 1)
                {
                         //al_set_target_bitmap(al_get_backbuffer(display));


                          //al_draw_bitmap(area_central, 651, 0, 0);



                            px = cameraX/50;
                            py = cameraY/50;

                           		for(l = px; l < px+15  ; l++){
                                    for(m = py; m < py+15; m++){
                                      switch(mapa[m][l]){
                                            case 60 :
                                                al_draw_bitmap(s60,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 1 :
                                                al_draw_bitmap(i1,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 2 :
                                                al_draw_bitmap(i2,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 3 :
                                                al_draw_bitmap(i3,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 4 :
                                                al_draw_bitmap(i4,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 5 :
                                                al_draw_bitmap(i5,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 6 :
                                                al_draw_bitmap(i6,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 7 :
                                                al_draw_bitmap(i7,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 8 :
                                                al_draw_bitmap(i8,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 9 :
                                                al_draw_bitmap(i9,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 10 :
                                                al_draw_bitmap(i10,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 11 :
                                                al_draw_bitmap(i11,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 12 :
                                                al_draw_bitmap(i12,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 13 :
                                                al_draw_bitmap(i13,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 14 :
                                                al_draw_bitmap(i14,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 15 :
                                                al_draw_bitmap(i15,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 16 :
                                                al_draw_bitmap(i16,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 17 :
                                                al_draw_bitmap(i17,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 18 :
                                                al_draw_bitmap(i18,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 19 :
                                                al_draw_bitmap(i19,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 20 :
                                                al_draw_bitmap(i20,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 21 :
                                                al_draw_bitmap(i21,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 22 :
                                                al_draw_bitmap(i22,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 23 :
                                                al_draw_bitmap(i23,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 24 :
                                                al_draw_bitmap(i24,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 25 :
                                                al_draw_bitmap(i25,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 26 :
                                                al_draw_bitmap(i26,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 27 :
                                                al_draw_bitmap(i27,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 28 :
                                                al_draw_bitmap(i28,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 29 :
                                                al_draw_bitmap(i29,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 30 :
                                                al_draw_bitmap(i30,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 31 :
                                                al_draw_bitmap(i31,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 32 :
                                                al_draw_bitmap(i32,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 33 :
                                                al_draw_bitmap(i33,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 34 :
                                                al_draw_bitmap(i34,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 35 :
                                                al_draw_bitmap(i35,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 36 :
                                                al_draw_bitmap(i36,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 37 :
                                                al_draw_bitmap(i37,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 38 :
                                                al_draw_bitmap(i38,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 39 :
                                                al_draw_bitmap(i39,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 40 :
                                                al_draw_bitmap(i40,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 41 :
                                                al_draw_bitmap(i41,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 42 :
                                                al_draw_bitmap(i42,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 43 :
                                                al_draw_bitmap(i43,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 44 :
                                                al_draw_bitmap(i44,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 45 :
                                                al_draw_bitmap(i45,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 46 :
                                                al_draw_bitmap(i46,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 47 :
                                                al_draw_bitmap(i47,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 48 :
                                                al_draw_bitmap(i48,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 49 :
                                                al_draw_bitmap(i49,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 50 :
                                                al_draw_bitmap(i50,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 51 :
                                                al_draw_bitmap(i51,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 52 :
                                                al_draw_bitmap(i52,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 53 :
                                                al_draw_bitmap(i53,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 54 :
                                                al_draw_bitmap(i54,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 55 :
                                                al_draw_bitmap(i55,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 56 :
                                                al_draw_bitmap(i56,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 57 :
                                                al_draw_bitmap(i57,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 101 :
                                                al_draw_bitmap(traps[0][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 102 :
                                                al_draw_bitmap(traps[1][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 103 :
                                                al_draw_bitmap(traps[2][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 104 :
                                                al_draw_bitmap(traps[3][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 105 :
                                                al_draw_bitmap(traps[4][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 106 :
                                                al_draw_bitmap(traps[5][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 107 :
                                                al_draw_bitmap(traps[6][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 108 :
                                                al_draw_bitmap(traps[7][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 109 :
                                                al_draw_bitmap(traps[8][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 110 :
                                                al_draw_bitmap(traps[9][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 111 :
                                                al_draw_bitmap(traps[10][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 112 :
                                                al_draw_bitmap(traps[11][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 113 :
                                                al_draw_bitmap(traps[12][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 114 :
                                                al_draw_bitmap(traps[13][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 115 :
                                                al_draw_bitmap(traps[14][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 116 :
                                                al_draw_bitmap(traps[15][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 117 :
                                                al_draw_bitmap(traps[16][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 118 :
                                                al_draw_bitmap(traps[17][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 119 :
                                                al_draw_bitmap(traps[18][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 120 :
                                                al_draw_bitmap(traps[19][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 121 :
                                                al_draw_bitmap(traps[20][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 122 :
                                                al_draw_bitmap(traps[21][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 123 :
                                                al_draw_bitmap(traps[22][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 124 :
                                                al_draw_bitmap(traps[23][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 125 :
                                                al_draw_bitmap(traps[24][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 126 :
                                                al_draw_bitmap(traps[25][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 127 :
                                                al_draw_bitmap(traps[26][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 128 :
                                                al_draw_bitmap(traps[27][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 129 :
                                                al_draw_bitmap(traps[28][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 130 :
                                                al_draw_bitmap(traps[29][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 131 :
                                                al_draw_bitmap(traps[30][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 132 :
                                                al_draw_bitmap(traps[31][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 133 :
                                                al_draw_bitmap(traps[32][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 134 :
                                                al_draw_bitmap(traps[33][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            default :
                                                break;
                                      }
                                    }
                                  }

                    for(l = 0; l < red.vida; l++)
                            al_draw_bitmap(life,(0+l*70),0, 0);




                    if(red.b == 3){
                        printf("\ntafu X:%d\ntafu Y:%d\nTafu valor: %d\n", TAFu.x, TAFu.y, TAFu.quale);
                        al_draw_bitmap(traps[TAFu.quale][pos_x_trap],(TAFu.x*50)-cameraX,(TAFu.y*50)-cameraY, 0);

                    }


                    if(reloginho.segundos < 10){
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 450, 0, ALLEGRO_ALIGN_CENTRE, "0%d : 0%d", reloginho.minutos, reloginho.segundos);
                          }else{
                            al_draw_textf(fonte, al_map_rgb(140, 255, 0), 450, 0, ALLEGRO_ALIGN_CENTRE, "0%d : %d", reloginho.minutos, reloginho.segundos);
                          }

                    if(red.b == 4)
                        al_draw_textf(fonte, al_map_rgb(0, 0, 0), 325, 325, ALLEGRO_ALIGN_CENTRE, "Fim de jogo");


                    for(contador = 0;contador<4; contador++){
                            if(contador != servidor){
                                 if(px < ((personas[contador].x-cameraX)/50) && px+15 > ((personas[contador].x-cameraX)/50) ){
                                    if(py < ((personas[contador].y-cameraY)/50) && py+15 > ((personas[contador].y-cameraY)/50) )
                                  {
                                      if(personas[contador].estado == 3){
                                        al_draw_bitmap(traps[(personas[contador].Trapativa)][personas[contador].spriteT],personas[contador].trapX*50-cameraX,personas[contador].trapY*50-cameraY, 0);
                                      }
                                  }
                                }



                            }
                    }

                   for (contador = 0; contador < 4; contador++){
                    //sortearNas(contador);
                           if(contador != servidor){
                                //if(cameraX < personas[contador].x-cameraX && cameraX+realWieHei > personas[contador].x-cameraX ){
                                  //  if(cameraY < personas[contador].y-cameraY && cameraY+realWieHei > personas[contador].y-cameraY )
                                  //{
                                      al_draw_bitmap(sprites[personas[contador].spritel][personas[contador].spritec], personas[contador].x-cameraX, personas[contador].y -cameraY, flags);
                                  //}
                                //}

                           }

                            al_draw_bitmap(sprites[red.direcaoS][red.sprite], red.x -cameraX, red.y -cameraY, flags);


                   }


        }
            else
        {

            if(red.b == 5){
                red.x += (9);
                red.y += (5);
                //al_draw_textf(fonte, al_map_rgb(0, 0, 0), 800, 135, ALLEGRO_ALIGN_CENTRE, "Fim de jogo");
                //al_draw_textf(fonte, al_map_rgb(0, 0, 0), 770, 400, ALLEGRO_ALIGN_CENTRE, "Você venceu");
            }/*else{
                al_draw_textf(fonte, al_map_rgb(0, 0, 0), 800, 135, ALLEGRO_ALIGN_CENTRE, "Fim de jogo");
                al_draw_textf(fonte, al_map_rgb(0, 0, 0), 770, 400, ALLEGRO_ALIGN_CENTRE, "O jogador venceu %d", vencedor);

            }*/



            cameraX = (red.x)- realWieHei/2;
            cameraY = (red.y)- realWieHei/2;

                   px = cameraX/50;
                   py = cameraY/50;

                           		for(l = px; l < px+15  ; l++){
                                    for(m = py; m < py+15; m++){
                                      switch(mapa[m][l]){
                                            case 60 :
                                                al_draw_bitmap(s60,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 1 :
                                                al_draw_bitmap(i1,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 2 :
                                                al_draw_bitmap(i2,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 3 :
                                                al_draw_bitmap(i3,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 4 :
                                                al_draw_bitmap(i4,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 5 :
                                                al_draw_bitmap(i5,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 6 :
                                                al_draw_bitmap(i6,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 7 :
                                                al_draw_bitmap(i7,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 8 :
                                                al_draw_bitmap(i8,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 9 :
                                                al_draw_bitmap(i9,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 10 :
                                                al_draw_bitmap(i10,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 11 :
                                                al_draw_bitmap(i11,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 12 :
                                                al_draw_bitmap(i12,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 13 :
                                                al_draw_bitmap(i13,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 14 :
                                                al_draw_bitmap(i14,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 15 :
                                                al_draw_bitmap(i15,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 16 :
                                                al_draw_bitmap(i16,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 17 :
                                                al_draw_bitmap(i17,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 18 :
                                                al_draw_bitmap(i18,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 19 :
                                                al_draw_bitmap(i19,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 20 :
                                                al_draw_bitmap(i20,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 21 :
                                                al_draw_bitmap(i21,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 22 :
                                                al_draw_bitmap(i22,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 23 :
                                                al_draw_bitmap(i23,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 24 :
                                                al_draw_bitmap(i24,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 25 :
                                                al_draw_bitmap(i25,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 26 :
                                                al_draw_bitmap(i26,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 27 :
                                                al_draw_bitmap(i27,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 28 :
                                                al_draw_bitmap(i28,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 29 :
                                                al_draw_bitmap(i29,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 30 :
                                                al_draw_bitmap(i30,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 31 :
                                                al_draw_bitmap(i31,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 32 :
                                                al_draw_bitmap(i32,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 33 :
                                                al_draw_bitmap(i33,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 34 :
                                                al_draw_bitmap(i34,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 35 :
                                                al_draw_bitmap(i35,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 36 :
                                                al_draw_bitmap(i36,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 37 :
                                                al_draw_bitmap(i37,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 38 :
                                                al_draw_bitmap(i38,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 39 :
                                                al_draw_bitmap(i39,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 40 :
                                                al_draw_bitmap(i40,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 41 :
                                                al_draw_bitmap(i41,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 42 :
                                                al_draw_bitmap(i42,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 43 :
                                                al_draw_bitmap(i43,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 44 :
                                                al_draw_bitmap(i44,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 45 :
                                                al_draw_bitmap(i45,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 46 :
                                                al_draw_bitmap(i46,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 47 :
                                                al_draw_bitmap(i47,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 48 :
                                                al_draw_bitmap(i48,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 49 :
                                                al_draw_bitmap(i49,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 50 :
                                                al_draw_bitmap(i50,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 51 :
                                                al_draw_bitmap(i51,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 52 :
                                                al_draw_bitmap(i52,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 53 :
                                                al_draw_bitmap(i53,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 54 :
                                                al_draw_bitmap(i54,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 55 :
                                                al_draw_bitmap(i55,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 56 :
                                                al_draw_bitmap(i56,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 57 :
                                                al_draw_bitmap(i57,(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 101 :
                                                al_draw_bitmap(traps[0][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 102 :
                                                al_draw_bitmap(traps[1][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 103 :
                                                al_draw_bitmap(traps[2][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 104 :
                                                al_draw_bitmap(traps[3][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 105 :
                                                al_draw_bitmap(traps[4][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 106 :
                                                al_draw_bitmap(traps[5][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 107 :
                                                al_draw_bitmap(traps[6][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 108 :
                                                al_draw_bitmap(traps[7][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 109 :
                                                al_draw_bitmap(traps[8][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 110 :
                                                al_draw_bitmap(traps[9][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 111 :
                                                al_draw_bitmap(traps[10][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 112 :
                                                al_draw_bitmap(traps[11][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 113 :
                                                al_draw_bitmap(traps[12][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 114 :
                                                al_draw_bitmap(traps[13][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 115 :
                                                al_draw_bitmap(traps[14][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 116 :
                                                al_draw_bitmap(traps[15][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 117 :
                                                al_draw_bitmap(traps[16][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 118 :
                                                al_draw_bitmap(traps[17][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 119 :
                                                al_draw_bitmap(traps[18][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 120 :
                                                al_draw_bitmap(traps[19][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 121 :
                                                al_draw_bitmap(traps[20][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 122 :
                                                al_draw_bitmap(traps[21][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 123 :
                                                al_draw_bitmap(traps[22][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 124 :
                                                al_draw_bitmap(traps[23][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 125 :
                                                al_draw_bitmap(traps[24][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 126 :
                                                al_draw_bitmap(traps[25][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 127 :
                                                al_draw_bitmap(traps[26][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 128 :
                                                al_draw_bitmap(traps[27][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 129 :
                                                al_draw_bitmap(traps[28][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 130 :
                                                al_draw_bitmap(traps[29][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 131 :
                                                al_draw_bitmap(traps[30][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 132 :
                                                al_draw_bitmap(traps[31][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 133 :
                                                al_draw_bitmap(traps[32][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            case 134 :
                                                al_draw_bitmap(traps[33][0],(l*50)-cameraX,(m*50)-cameraY, 0);
                                                break;
                                            default :
                                                break;
                                      }
                                    }
                                  }




                for (contador = 0; contador < 4; contador++){
                    if(contador != servidor){
                        if(cameraX < personas[contador].x-cameraX && cameraX+realWieHei > personas[contador].x-cameraX ){
                            if(cameraY < personas[contador].y-cameraY && cameraY+realWieHei > personas[contador].y-cameraY )
                            {
                                al_draw_bitmap(sprites[personas[contador].spritel][personas[contador].spritec], personas[contador].x -cameraX, personas[contador].y -cameraY, flags);
                            }
                        }
                    }else{
                         al_draw_bitmap(sprites[0][0], red.x, red.y, flags);
                    }
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


  al_destroy_bitmap(i1);
  al_destroy_bitmap(i2);
  al_destroy_bitmap(i3);
  al_destroy_bitmap(i4);
  al_destroy_bitmap(i5);
  al_destroy_bitmap(i6);
  al_destroy_bitmap(i7);
  al_destroy_bitmap(i8);
  al_destroy_bitmap(i9);
  al_destroy_bitmap(i10);
  al_destroy_bitmap(i12);
  al_destroy_bitmap(i13);
  al_destroy_bitmap(i14);
  al_destroy_bitmap(i15);
  al_destroy_bitmap(i16);
  al_destroy_bitmap(i17);
  al_destroy_bitmap(i18);
  al_destroy_bitmap(i19);
  al_destroy_bitmap(i20);
  al_destroy_bitmap(i21);
  al_destroy_bitmap(i22);
  al_destroy_bitmap(i23);
  al_destroy_bitmap(i24);
  al_destroy_bitmap(i25);
  al_destroy_bitmap(i26);
  al_destroy_bitmap(i27);
  al_destroy_bitmap(i28);
  al_destroy_bitmap(i29);
  al_destroy_bitmap(i30);
  al_destroy_bitmap(i31);
  al_destroy_bitmap(i32);
  al_destroy_bitmap(i33);
  al_destroy_bitmap(i34);
  al_destroy_bitmap(i35);
  al_destroy_bitmap(i36);
  al_destroy_bitmap(i37);
  al_destroy_bitmap(i38);
  al_destroy_bitmap(i39);
  al_destroy_bitmap(i40);
  al_destroy_bitmap(i41);
  al_destroy_bitmap(i42);
  al_destroy_bitmap(i43);
  al_destroy_bitmap(i44);
  al_destroy_bitmap(i45);
  al_destroy_bitmap(i46);
  al_destroy_bitmap(i47);
  al_destroy_bitmap(i48);
  al_destroy_bitmap(i49);
  al_destroy_bitmap(i50);
  al_destroy_bitmap(i51);
  al_destroy_bitmap(i52);
  al_destroy_bitmap(i53);
  al_destroy_bitmap(i54);
  al_destroy_bitmap(i55);
  al_destroy_bitmap(i56);
  al_destroy_bitmap(i57);


  al_destroy_bitmap(t1);
  al_destroy_bitmap(t2);
  al_destroy_bitmap(t3);
  al_destroy_bitmap(t4);
  al_destroy_bitmap(t5);
  al_destroy_bitmap(t6);
  al_destroy_bitmap(t7);
  al_destroy_bitmap(t8);
  al_destroy_bitmap(t9);
  al_destroy_bitmap(t10);
  al_destroy_bitmap(t12);
  al_destroy_bitmap(t13);
  al_destroy_bitmap(t14);
  al_destroy_bitmap(t15);
  al_destroy_bitmap(t16);
  al_destroy_bitmap(t17);
  al_destroy_bitmap(t18);
  al_destroy_bitmap(t19);
  al_destroy_bitmap(t20);
  al_destroy_bitmap(t21);
  al_destroy_bitmap(t22);
  al_destroy_bitmap(t23);
  al_destroy_bitmap(t24);
  al_destroy_bitmap(t25);
  al_destroy_bitmap(t26);
  al_destroy_bitmap(t27);
  al_destroy_bitmap(t28);
  al_destroy_bitmap(t29);
  al_destroy_bitmap(t30);
  al_destroy_bitmap(t31);
  al_destroy_bitmap(t32);
  al_destroy_bitmap(t33);
  al_destroy_bitmap(t34);





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

    fonte = al_load_font("C:/Inclusos/aspartam.ttf", 24, 0);
    if (!fonte)
    {
        al_destroy_display(janela);if(ALLEGRO_EVENT_DISPLAY_CLOSE){}
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return -1;
    }

    fontT = al_load_font("C:/Inclusos/aspartam.ttf", 50, 0);
    if (!fontT)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fontT.\n");
        return -1;
    }


    ALLEGRO_FONT *fonte3 = al_load_font("C:/Inclusos/aspartam.ttf", 17, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");


    // Configura o título da janela
    al_set_window_title(janela, "Rotinas de Mouse - www.rafaeltoledo.net");

    //configurar textos
    char *texto1 = "Programa teste";
    char *texto2 = "Sabe de nada Inocente";
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
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
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

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                            al_destroy_bitmap(botao_sair);
                           al_destroy_bitmap(area_central);
                           al_destroy_bitmap(btt_mult);

                           al_destroy_display(janela);
                           al_destroy_event_queue(fila_eventos);

                    sair = 1;
            }

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
        al_draw_textf(fonte3, al_map_rgb(0, 0, 0), 220, 340, ALLEGRO_ALIGN_CENTRE, "%s", texto2);

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
    sock.sin_addr.s_addr=inet_addr("127.0.0.1"/*"10.135.160.22"/*ip*/);

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

    ALLEGRO_FONT *fonte = al_load_font("C:/Inclusos/NIv.ttf", 20, 0);
    if (!fonte)
        error("Falha ao carregar fonte.");

    ALLEGRO_FONT *fonte2 = al_load_font("C:/Inclusos/NIv.ttf", 30, 0);
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

    char *texto1 = "Voce  o player: ";

    char *texto2 = "Aguardando mapa";
    char *texto21 = "Mapa carregado";

    char *texto3 = "Aguardando Player ";
    char *texto4 = "Player ";
    char *okok =" OK";

    char *texto5 = "Posicoes inicias definidas";

    char *texto6 = " Iniciando ";
    char *texto7 = " Esperando todas as condicoes ";

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
                                if(mapa[0][0] >= 1)
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

    return ret;


}

int main(){

    mapa[0][0] = 0;

    HANDLE th[2];
    DWORD Ith;

    setI();
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

    personas[posicaoServidor].x = 0;
    personas[posicaoServidor].y = 0;
    //recv(descritorCliente, &saidaMapa, sizeof(saidaMapa),0);
    recv(descritorCliente, (void*)&personas, sizeof(personas),0);


    if (recv(descritorCliente, &mapa, sizeof(mapa),0) < 0){
        printf("Error");
        return 0;
    }

    eu = personas[posicaoServidor];
    red.x = eu.x;
    red.y = eu.y;

    printf("x: %d\ny: %d", red.x,red.y);

    atualizaCAM(red.x, red.y);

    eu.atacando = 5;
    //zeraPersonagens();
    //printf("%d,\n%d\n", red[posicaoServidor].x,red[posicaoServidor].y);
    th[0] = CreateThread(NULL,0,recebeClientes,&posicaoServidor,0,&Ith);

    int qual = 3;
    int q2 = 0;
    //while(qual != 0){
        qual = menu();
        send(descritorCliente, (void*)&eu, sizeof(eu),0);

        if(qual == 1){
            q2 = waitplayer();
            th[1] = CreateThread(NULL,0,enviaClientes,&posicaoServidor,0,&Ith);
            if(q2 == 1){
                game(posicaoServidor);
            }
        }
    //}
    return 0;
}

