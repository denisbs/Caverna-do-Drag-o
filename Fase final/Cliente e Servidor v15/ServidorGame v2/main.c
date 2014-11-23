#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <windows.h>

#define mapa_size 13

WSADATA data; //Variíveis que recebem o valor da inicialização e criação do socket.
//SOCKET winsock; //Variíveis que recebem o valor da inicialização e criação do socket.
SOCKADDR_IN sock; //Variíveis que recebem o valor da inicialização e criação do socket

typedef struct{
    int x; // x do personagem
    int y; // y do personagem
    int estado;
    int spritel; // imagem atual do personagem
    int spritec;
    int atacando;
    int trapX;
    int trapY;
    int spriteT;
    int vida;
    int inicia;
}dados;


typedef struct {
        int x[8];
        int y[8];
        int ativa[8];

}pontoNas;

dados personagens[4];
pontoNas inicios;

HANDLE MeuMutex;

int cont = 0;
int iniciar = 0;
int clientes[4];
int posicaoPersonagem[4][4];
int saidaMapa;
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
};   // mapa base

void Servidor(void* arg){
    int sockEntrada = (*(int *) arg);
    int EstadoAtual;
    dados armazena;
    /*if (sockEntrada < 0){
        sockEntrada = sockEntrada + 1;
    }*/
    printf("%d\n", sockEntrada);
    printf("%d\n", clientes[sockEntrada]);
    printf("---------------------------------------\n");
    if (send(clientes[sockEntrada], &sockEntrada, sizeof(sockEntrada),0) < 0){
        puts("Send failed\n");
        return 1;
    }
    send(clientes[sockEntrada], &mapa, sizeof(mapa),0);
    send(clientes[sockEntrada], &saidaMapa, sizeof(saidaMapa),0);
    sortearNas(sockEntrada);
    send(clientes[sockEntrada], (void*)&personagens, sizeof(personagens),0);
    while(1){
        //printf("oi oio io ioi o io i");EstadoAtual = WaitForSingleObject(MeuMutex, INFINITE);

        if (cont > 0 ){
            recv(clientes[sockEntrada], (void*)&armazena, sizeof(armazena),0);
            WaitForSingleObject(MeuMutex, INFINITE);
            if (iniciar < 4){
                iniciar++;
                //printf("%d\n",iniciar);
            }else{
                if (armazena.atacando < 5){
                    personagens[armazena.atacando].estado = 7;
                }
                personagens[sockEntrada] = armazena;
            }
            ReleaseMutex(MeuMutex);


            //printf("%d\n", personagens[sockEntrada].x);
            //printf("%d\n", personagens[sockEntrada].y);
            //send(clientes[sockEntrada], (void*)&personagens, sizeof(personagens),0);
        }
            //Sleep(2000);
        /*printf("Posicao x %d\n",posicaoPersonagem[0][sockEntrada]);
        printf("Posicao y %d\n",posicaoPersonagem[1][sockEntrada]);*/
    }
}

void enviaClientes(){
    int k;
    while(1){
        Sleep(20);
        if(iniciar != 4){
            for(k = 0; k < 4; k++){
                if (k < cont){
                    send(clientes[k], (void*)&personagens, sizeof(personagens),0);
                }
            }
        }else{
            for(k = 0; k < 4; k++){
                personagens[k].inicia = 1;
                //printf("adcionei\n");
            }
            iniciar++;
        }
    }
}

void sortearNas(int n){


   int p, C;
   personagens[n].vida = 3;
   C = 1;
   srand((unsigned)time(NULL));
   while(C == 1){

        p = rand()%8;
        if(inicios.ativa[p] != 1 ){
            personagens[n].x = inicios.x[p]*50;
            personagens[n].y = inicios.y[p]*50;
            personagens[n].estado = 0;
            personagens[n].atacando = 5;
            //printf("%d,\n%d\n", inicios.x[p],inicios.y[p]);
            //send(clientes[n], (void*)&personagens[n], sizeof(personagens[n]),0);

            inicios.ativa[p] = 1;
            C=0;
        }
   }

}

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
                printf(" trap em: %d - %d\n", nL, nC);
            }else{
                nL = rand()%mapa_size;
                nC = rand()%mapa_size;
            }
        }
        C = 0;

    }
}

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

int criaServidor(){
    int winsock;
    struct sockaddr_in serverAddr; /*Declaracao da estrutura*/
    if(WSAStartup(MAKEWORD(2,0),&data)==SOCKET_ERROR)
    {
        printf("Erro ao inicializar o winsock");
        //return 0;
    }
    if((winsock = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)
    {
        printf("Erro ao criar socket");
        //return 0;
    }

    memset(&serverAddr, 0, sizeof (serverAddr));/*Zera a estrutura*/
    sock.sin_family=AF_INET; //tipo de familia
    sock.sin_port=htons(1235); //Numero da porta de rede

    if(bind(winsock,(SOCKADDR*)&sock,sizeof(sock))==SOCKET_ERROR)
    {
        printf("Erro colocar utilizar a funcao BIND");
        //return 0;
    }

    if (listen(winsock,5) < 0)
    {
        printf("Erro no Socket\n");
        exit(1);
    }

    /*while((winsock = accept(winsock,0,0))==SOCKET_ERROR)
    {
        Sleep(1);
    }*/
    return winsock;
}

int main(){
    HANDLE th[5];
    DWORD Ith;

    MeuMutex = CreateMutex(NULL, FALSE, NULL);
    if(MeuMutex == NULL){
        printf("Erro na funcao CreateMutex:%d\n",GetLastError());
        return 0;
    }

    setI();
    sorteaA();
    int i = 0;
    struct sockaddr_in clienteAddr;
    int winsock = criaServidor();


    while(1)
    {
        /*tamanho da estrutura*/
        unsigned int clntLen;
        clntLen = sizeof (clienteAddr);

        /*Fica no aguardo da conexao do cliente*/
        clientes[cont] = accept(winsock, (struct sockaddr *) & clienteAddr, &clntLen);
        if (clientes[cont] < 0)
        {
            Sleep(1);
      		/*printf("Erro no Socket\n");
      		exit(1);*/
        }else{

            /*Inicializa a thread*/
            //th[i] = CreateThread(th[i],0,Servidor,0,0,&clientes[cont]);
            printf("%d\n", clientes[cont]);
            printf("%d\n",cont);
            th[cont] = CreateThread(NULL,0,Servidor,&cont,0,&Ith);
            if (th[cont] == NULL)
            {
                printf("Erro na Thread\n",GetLastError());
                return 0;
            }
            Sleep(1000);
            cont++;
            if (cont == 1){
                //Sleep(1000);
                th[4] = CreateThread(NULL,0,enviaClientes,0,0,NULL) == 0;
            }

            //cont++;
            i++;
        }
    }
    printf("Hello world!\n");
    return 0;
}
