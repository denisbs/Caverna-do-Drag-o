#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <windows.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define WIDTH 600
#define HEIGHT 400

#define TILE_SIZEH 600
#define TILE_SIZEV 400
#define SPRITE_SIZEH 48
#define SPRITE_SIZEV 64
#define NUM_SPRITES 5
#define FRAMES_PER_SHIFT 10
#define SPEED 1

#define FPS 60

WSADATA data; //Variíveis que recebem o valor da inicialização e criação do socket.
//SOCKET winsock; //Variíveis que recebem o valor da inicialização e criação do socket.
SOCKADDR_IN sock; //Variíveis que recebem o valor da inicialização e criação do socket.

typedef struct{
    int x;
    int y;
}dados;
dados personagens[3];

int descritorCliente;
int posicaoServidor;
char ip [1024];
int posicaoPersonagem[4][4];
//int byte;

void error(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);

  exit(EXIT_FAILURE);
}

void* recebeClientes(void* arg)
{
    int sockEntrada = (*(int *) arg);
    //printf("%d\n",sockEntrada);
    while(1)
    {

    	//int j;
    	//for (j = 0; j >= 3; j++)
    	//{
		recv(descritorCliente, (void*)&personagens, sizeof(personagens),0);
		printf("Posicao x %d\n",personagens[sockEntrada].x);
        printf("Posicao y %d\n",personagens[sockEntrada].y);
        //Sleep(1500);
        //Sleep(1000);
    	//}
    		//printf("%f\n", dadosClientes[0][1]);
    }
}

void* enviaClientes(void* arg){
    int sockEntrada = (*(int *) arg);
    while(1){
        //printf("%d\n",personagens[sockEntrada].x);
        //printf("%d\n",personagens[sockEntrada].y);
        if (personagens[sockEntrada].x != 0 || personagens[sockEntrada].y != 0){
            send(descritorCliente, (void*)&personagens[sockEntrada], sizeof(personagens[sockEntrada]),0);
        }
    }

}

void telaJogo(int servidor)
{
    printf("%d\n",servidor);
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

    ALLEGRO_BITMAP *tile = al_load_bitmap("ii.png");
    if(!tile)
        error("failed to load tile");

    al_draw_bitmap(tile,0,0, 0);

  //al_destroy_bitmap(tile);

  /**********/

    ALLEGRO_BITMAP *sheet = al_load_bitmap("images.png");
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

    while(running) {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        send(descritorCliente, &posicaoPersonagem, sizeof(posicaoPersonagem),0);
        switch(event.type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode) {
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
                    switch(event.keyboard.keycode) {
                        case ALLEGRO_KEY_LEFT:
                            if(direction == -1) {
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
                            if (directionV == -1){
                                shift = 0;

                                shiftb = 0;

                                directionV = 0;

                                refresh = 1;
                            }
                            break;

                        case ALLEGRO_KEY_RIGHT:
                            if(direction == 1) {
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
                    if(direction != 0) {
                        if(shift == 0) {
                            shift = 2;

                            frame = 0;
                        }else{
                            frame++;

                            if(frame == FRAMES_PER_SHIFT) {
                                frame = 0;

                                shift += arm;

                                if(shift != 2)
                                    arm = -arm;
                            }
                        }

                        x += direction * SPEED;
                        personagens[servidor].x = x;
                        //printf("%d\n",personagens[servidor].x);
                        //printf("%d\n",servidor);
                        refresh = 1;

                    }

                    if(directionV != 0) {
                        if(shift == 0) {
                            shift = 2;

                            frame = 0;
                        }else{
                            frame++;

                            if(frame == FRAMES_PER_SHIFT) {
                                frame = 0;

                                shift += arm;

                                if(shift != 2)
                                    arm = -arm;
                            }
                        }

                        y += directionV * SPEED;
                        personagens[servidor].y = y;
                        //printf("%d\n",personagens[servidor].y);
                        //printf("%d\n", servidor);
                        refresh = 1;


                    }

                    break;
                default:
                    printf("unknown event\n");
            }

        if(refresh) {

            al_draw_bitmap(tile,0,0, 0);

            al_draw_bitmap(sprites[shiftb][shift], x, y, flags);


            al_flip_display();

            refresh = 0;
        }
        printf("%d\n",personagens[servidor].x);
        printf("%d\n",personagens[servidor].y);
        //send(descritorCliente, (void*)&personagens[servidor], sizeof(personagens[servidor]),0);
    }

  /**********/

    al_stop_timer(timer);

    al_unregister_event_source(queue, al_get_timer_event_source(timer));
    al_unregister_event_source(queue, al_get_display_event_source(display));
    al_unregister_event_source(queue, al_get_keyboard_event_source());

    for(shift = 0; shift < NUM_SPRITES; shift++)
        for(shiftb = 0; shiftb < NUM_SPRITES; shiftb++)
            al_destroy_bitmap(sprites[shift][shiftb]);



    al_destroy_bitmap(sheet);
    al_destroy_bitmap(tile);


    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_uninstall_keyboard();
    al_uninstall_system();

    return EXIT_SUCCESS;
}

int criaCliente()
{
    int winsock;
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
/*
    printf("Digite o ip do servidor:\n");
    gets(ip);
*/
    sock.sin_family=AF_INET;
    sock.sin_port=htons(1235); //Numero da porta de rede
    sock.sin_addr.s_addr=inet_addr("127.0.0.1"/*ip*/);

    if(connect(clienteWinsock, (SOCKADDR*)&sock, sizeof(sock))==SOCKET_ERROR)
    {
        printf("Erro ao se conectar\n");
        //return 0;
    }
    return clienteWinsock;
}


int main()
{
    struct sockaddr_in serv_addr;
    /*Tamanho da estrutura*/
    unsigned int clntLen;
    clntLen = sizeof (sock);
    HANDLE th;
    /*Define o descritor cliente*/
    //int descritorCliente;
    descritorCliente = criaCliente();
    recv(descritorCliente, &posicaoServidor, sizeof(posicaoServidor),0);
    //CreateThread(NULL,0,recebeClientes,&posicaoServidor,0,NULL);
    CreateThread(NULL,0,enviaClientes,&posicaoServidor,0,NULL);
    printf("%d\n", posicaoServidor);
    telaJogo(posicaoServidor);

    /*while(1){

    }*/

    printf("Hello world!\n");
    return 0;
}
