/* 
 * File:   servidor.cpp
 * Author: ellioth
 * 
 * Created on February 12, 2016, 2:26 PM
 */
#include "servidor.h"

/**
 * contructor de la clase que recibe un puerto para establecerlo
 * @param port es un dato tipo entero este es el puerto que usaremos
 * en el servidor.
 */
servidor::servidor(int port) {
    _portno= port;
    _Screens= new lista();
    pthread_t hiloServer;
    _Boolplyrs=(bool*)malloc(sizeof(bool)*MAX_PLAYERS);
    _plyMSG=(string*)malloc(sizeof(string)*MAX_PLAYERS);
    for(int i=0; i<MAX_PLAYERS; i++)
        _Boolplyrs[i]=false;
    //inicializar el mutex 
    if(pthread_mutex_init(&_lock,NULL)!=CERO)
        error("mutex falied at create");
    //creacion del hilo del server que escucha las conexiones al servidor.
    if(pthread_create(&hiloServer,NULL,&servidor::ServerLoopHelper,
            this)!=CERO)
        error("falla en creacion de hilo server: ");
}

servidor::~servidor() {
    pthread_mutex_lock(&_lock);
    _killSystem=true;
    pthread_mutex_unlock(&_lock);
    close(_sockfd);
    nodo* temp=_Screens->getHead();
    for(int i=0; i<_Screens->getSize();i++){
        close(temp->getData());
    }
}

/**
 * metodo que realiza el ciclo para escuchar a los clientes
 * que se quieren conectar.
 * @return no retorna nada, ese retorno se usa para la creacion 
 * de los pthread.
 */
void* servidor::ServerLoop() {
    _sockfd = socket(AF_INET, SOCK_STREAM, CERO);
    //resivision de si la conexion del socket 
    // fue positiva o fallida.
    if (_sockfd <CERO)
        error(error1);
    //se escibe 0s en la variables puesta.
    //esto garantiza que no se use memoria sucia.
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    //establecemos los datos que se van a utilizar 
    //en el socket.
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(_portno);
    if (bind(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr))<CERO)
        error(error2);
    //se pone a escuchar en el socket si hay nuevas conexiones.
    listen(_sockfd,CINCO);
    _clilen = sizeof(_cli_addr);
    _Tplayrs=CERO;
    bool flagForPlayer=false;
    while(true){
        _newsockfd = accept(_sockfd, (struct sockaddr*) &_cli_addr, &_clilen);
        if (_newsockfd < CERO)
            error(error3);
        //clasificacion del cliente, si es una pantalla o un control.
        ClasifiedClient(_newsockfd,&flagForPlayer);
        if(flagForPlayer){
            //bloque para crear datos para el cliente
            ThreadClienteData temp;
            temp.data=this;
            temp.playr=_Tplayrs-UNO;
            temp.sockFd=_newsockfd;
            //creacion del hilo para el cliente.
            pthread_t hiloCliente;
            if(pthread_create(&hiloCliente,NULL,
                    &servidor::ClienteLoopHelper,&temp)!=CERO)
                error(error4);
            flagForPlayer=false;
            }
        if(debug)
            printf("servidor: got connection from %s port %d\n",
                    inet_ntoa(_cli_addr.sin_addr), ntohs(_cli_addr.sin_port));
    }
    close(_sockfd);
    pthread_exit(NULL);
}

/**
 * metodo para botar todo el programa si existe algun fallo y 
 * evitar errores futuros.
 * @param msg dato char* que es el mensaje que corresponde a error 
 * probocado.
 */
void servidor::error(const char* msg) {
    perror(msg);
    exit(UNO);
}

/**
 * metodo para clasificar si lo que se conecta es una control de androir o
 * una pantalla.
 * @param pSockFd
 * @param pBandera
 */
void servidor::ClasifiedClient(int pSockFd, bool * pBandera) {
    char* almacenador= (char*)malloc(LENG_MSG);
    _n = recv(pSockFd,almacenador,LENG_MSG,0);
    if (_n < CERO)
        error(error6);
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(almacenador);
    if(!_JsonDocument.IsObject()){
        std::cout<<"falla, archivo no es tipo json"<<std::endl;
        return;
    }//obtenemos la operacion a realizar
    rapidjson::Value & data = _JsonDocument[TYPE_CONNECTION];
    int typeOfConnection= data.GetInt();
    if(typeOfConnection==CERO){
        _Screens->insert(pSockFd);
        if(debug)cout<<"se conecto una pantalla"<<endl;
    }
    else if(typeOfConnection==UNO){ 
        _Tplayrs++;
        if(debug)cout<<"se conecto un jugador"<<endl;
        *pBandera=true;
    }
        
}

/**
 * ciclo por cliente que escucha los datos recibidos por el cliente, ya tiene
 * el mutex.
 * @param pPlyr dato tipo entero que es el numero del cliente.
 * @param newsockfd dato entero que es el socket del cliente con el que
 * nos comunicamos.
 */
void* servidor::gettDatas(int pPlyr, int newsockfd) {
    void* almacenador= malloc(LENG_MSG+UNO);
    while(true){
        while(!getBoolPlyrs(pPlyr)){
            bzero(almacenador, LENG_MSG+UNO);
            _n = recv(newsockfd,almacenador,LENG_MSG,0);
            if (_n < CERO)
                error(error6);
            pthread_mutex_lock(&_lock);
            _plyMSG[pPlyr]=(char *)almacenador;
            _Boolplyrs[pPlyr]=true;
            pthread_mutex_unlock(&_lock);
        }
    }
    free(almacenador);
    pthread_exit(NULL);
}


/**
 * metodo para enviar los mensajes a la pantalla y alertar los cambios
 * @param msg dato tipo char* const, que es el mensaje que enviaremos.
 * @param lenght dato tipo entero, este es el largo del mensaje.
 */
void servidor::sendMSG(string msg, int lenght) {
    nodo* tempScreen=_Screens->getHead();
    //if(debug)cout<<_Screens->getSize()<<endl;
    char* tempMSG= (char*)malloc(lenght+UNO);
    memcpy(tempMSG, msg.c_str(),lenght);
    tempMSG[lenght]='\n';
    for(int i =0; i<_Screens->getSize(); i++){
        _n=send(tempScreen->getData(), tempMSG, lenght,CERO);
        if (_n < CERO) 
            error(error5);
        tempScreen=tempScreen->getNext();
    }
    //free(tempMSG);
}

/**
 * metodo para enviar un mensaje especifico a una pantalla, se usa para
 * cuando una nueva pantalla se conecta, se le debe de enviar el mensaje
 * de las posiciones y la informacion que debe de desplegar en pantalla
 * @param msg
 * @param lenght
 * @param pScreen
 */
void servidor::sendMSG(string msg, int lenght, int pScreen) {
    nodo* tempScreen=_Screens->getHead();
    //if(debug)cout<<_Screens->getSize()<<endl;
    char* tempMSG= (char*)malloc(lenght+UNO);
    memcpy(tempMSG, msg.c_str(), lenght);
    tempMSG[lenght]='\n';
    for(int i =0; i<pScreen; i++)
        tempScreen=tempScreen->getNext();
    
    _n=send(tempScreen->getData(), tempMSG, lenght,CERO);
        if (_n < CERO) 
            error(error5);
}


/**
 * metodo para hacer el observer y darse cuenta si ya hay
 * un mensaje de parte del cliente, ya tiene el mutex.
 * @param plyr recibe un entero que es el numero del cliente.
 * @return retorna un dato tipo bool.
 */
bool servidor::getBoolPlyrs(int plyr) {
    pthread_mutex_lock(&_lock);
    bool dato= _Boolplyrs[plyr];
    pthread_mutex_unlock(&_lock);
    return dato;
}

/**
 * metodo para establecer en falso el mensaje que recibimos del cliente 
 * y hacer que se pueda recibir un nuevo mensaje, ya tiene el mutex.
 * @param plyr dato tipo entero, este es el numero del jugador.
 */
void servidor::setBoolPlyrs(int plyr) {
    pthread_mutex_lock(&_lock);
    _Boolplyrs[plyr]=false;
    pthread_mutex_unlock(&_lock);
}

/**
 * metodo para obtener el mensaje que envia el cliente, ya tiene el mutex.
 * @param plyr recibe un dato tipo entero que es el numero de cliente
 * @return retorna un dato tipo string que es el mensaje del cliente
 */
string servidor::getMSGPlyrs(int plyr) {
    pthread_mutex_lock(&_lock);
    string dato= _plyMSG[plyr];
    pthread_mutex_unlock(&_lock);
    return dato;
}

/**
 * metodo para conocer la cantidad total de jugadores conectados
 * actualmente.
 * @return dato entero.
 */
int servidor::getTplyrs() {
    pthread_mutex_lock(&_lock);
    int var=_Tplayrs;
    pthread_mutex_unlock(&_lock);
    return var;
}

/**
 * metodo que nos indica la cantidad de pantalla que hay para enviarle 
 * los mensajes.
 * @return 
 */
int servidor::getScreens() {
    pthread_mutex_lock(&_lock);
    int var=_Screens->getSize();;
    pthread_mutex_unlock(&_lock);
    return var;
}

/**
 * metodo para retornar el estado del servidor.
 * @return 
 */
bool servidor::getServerState() {
    pthread_mutex_lock(&_lock);
    bool temp=_killSystem;
    pthread_mutex_unlock(&_lock);
    return temp;
}
