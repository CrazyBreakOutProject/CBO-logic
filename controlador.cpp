/* 
 * File:   controlador.cpp
 * Author: ellioth
 * 
 * Created on February 12, 2016, 3:50 PM
 */

#include "controlador.h"

controlador::controlador(int Pport) {
    srand(time(NULL));
    _port=Pport;
    //arrancar server
    _servidor= new servidor(_port);
    //inicializar pelota
    _pelota=(Bola**)malloc(sizeof(Bola*)*MAX_BALLS);
    _pelota[CERO]= (Bola*)malloc(sizeof(Bola));
    _pelota[CERO]->setPos(SCREEN_X/DOS-BALL_SIZE,POS_Y_PLY-(BALL_SIZE+CINCO));
    _BallsLeft++;
    /*--bloque para establecer el movimiento de la pelota sobre el campo---*/
    _dirrection=(rand()%TRES)+UNO;
    if(_dirrection==UNO)
        _MoveBallX=-UNO;
    else if(_dirrection==DOS)
        _MoveBallX=CERO;
    else if(_dirrection==TRES)
        _MoveBallX=UNO;
    _MoveBallY=-UNO;
    /*---------------------------------------------------------------------*/
    //incializacion de los bloques
    _BricksLeft=TOTAL_BRICKS;
    _barras=(Brick**)malloc(sizeof(Brick*)*TOTAL_BRICKS);
    int space=CERO;
    for(int j =CERO; j<ROW_BRICK; j++)
        for(int i=CERO; i<COL_BRICK;i++,space++){
            int fuerza= (rand()%TRES)+UNO;
            _barras[space]=(Brick*)malloc(sizeof(Brick));
            _barras[space]->setDatas(j*BRICK_SIZE,(i*BRICK_SIZE)+(CINCUENTA),fuerza);
        }
    _flagTerminate=false;
    //entramos al hilo principal
    if(debug)cout<<"juego iniciado"<<endl;
    MainLoop();
    if(debug)cout<<"juego terminado"<<endl;
}

controlador::~controlador() {
    if(_BallsLeft>CERO){
        for(int i =CERO; i<_BallsLeft; i++){
            free(_pelota[i]);
        }
        free(_pelota);
    }
    if(_BricksLeft>CERO){
        for(int i =CERO; i<_BricksLeft; i++){
            free(_barras[i]);
        }
        free(_barras);
    }
    if(_servidor->getTplyrs()>CERO){
        for(int i =CERO; i<_servidor->getTplyrs(); i++){
            free(_ply[i]);
        }
        free(_ply);
    }
}

/**
 * ciclo principal para revisar todo.
 */
void controlador::MainLoop(){
    int ids=0, temp=0;
    _ply=(Player**)malloc(sizeof(Player*)*MAX_PLAYERS);
    while(true){
        if(_servidor->getTplyrs()>CERO){
            checkForMsgPlayers(&ids);
            //revisamos las coliciones
            _BrickHit=-UNO;
            checkColl();
            checkCondForMsg();
            if(_flagTerminate){
                break;
            }
            sleep_(SLEEP_TIME);
        }
    }
}

/**
 * metodo para verificar que los jugadores nuevos conectados, han enviado 
 * un cambio en la posicion.
 * @param pAmmountPLayers indice que le va a dar un id unico al jugador
 * nuevo conectado.
 */
void controlador::checkForMsgPlayers(int* pAmmountPLayers) {
    for(int i=CERO; i<_servidor->getTplyrs(); i++){
        //verificamos si los players son nulos para crearlos 
        if(_ply[i]==NULL){
            if(debug)cout<<"jugador conectado"<<endl;
            _ply[i]=(Player*)malloc(sizeof(Player));
            _ply[i]->setDatas(*pAmmountPLayers);
            (*pAmmountPLayers)++;
        }
        //obtenemos sus cambios y nos movemos por la pantalla.
        if(_servidor->getBoolPlyrs(i)){
            _ply[i]->move(_servidor->getMSGPlyrs(i));
            _servidor->setBoolPlyrs(i);
        }
    }
}

/**
 * revisa que tipo de mensaje en formato de Json debe de enviar a las
 * pantallas segun el cambio realizado.
 */
void controlador::checkCondForMsg() {
    string msg;
    //revisamos de primero la condicion de terminacion.
    if(_BallsLeft==CERO || _BricksLeft==CERO){
        //if(debug)cout<<"terminando juego"<<endl;
        msg=_Json->create(NULL, _ply, NULL,_BallsLeft,
                _servidor->getTplyrs(),-DOS);
        _servidor->sendMSG(msg,msg.length());
        //if(debug)cout<<msg<<endl;
        _flagTerminate=true;
        return;
    }
    else if(_BrickHit==-UNO){
        //if(debug)cout<<"ladrillo no golpeado"<<endl;
        msg=_Json->create(_pelota, _ply, NULL,_BallsLeft,
                _servidor->getTplyrs(),_BrickHit);
        _servidor->sendMSG(msg.c_str(),msg.length());
        //if(debug)cout<<msg<<endl;
    }
    //en caso de que no seguimos normalmente
    else{
        //if(debug)cout<<"ladrillo golpeado"<<endl;
        msg=_Json->create(_pelota, _ply, _barras[_BrickHit],
            _BallsLeft,_servidor->getTplyrs(),_BrickHit);
        _servidor->sendMSG(msg.c_str(),msg.length());
        //if(debug)cout<<msg<<endl;
    }
}

/**
 * metodo para ir revizando las coliciones de la pelota contra 
 * los objetos en campo.
 */
void controlador::checkColl() {
    bool bandera= false;
    
    //bloque para verificar choques con limites de pantalla
    if(_pelota[CERO]->getPx()+BALL_SIZE==SCREEN_X)
        _MoveBallX=-UNO;
    else if(_pelota[CERO]->getPx()==CERO)
        _MoveBallX=UNO;
    if(_pelota[CERO]->getPy()==CERO)
        _MoveBallY=UNO;
    
    //verificacion por si la pelota se sale del alcance del jugador
    if(_pelota[CERO]->getPy()>POS_Y_PLY){
        _BallsLeft--;
        for(int i=CERO; i<_servidor->getTplyrs(); i++)
            _ply[i]->resize(DECREMENT);
        if(_BallsLeft==CERO){
            Bola*  temp= _pelota[CERO];
            free(temp);
            _pelota[CERO]=NULL;
            return;
        }
    }
    
    //verificacion para choque contra la paleta de cada jugador.
    for(int i =CERO; i<_servidor->getTplyrs(); i++){
        bandera=_ply[i]->checkHit(&_MoveBallX, &_MoveBallY, _pelota[CERO]);
        if(bandera)
            break;
    }
    //verificaciones para colicion contra cada UNO de los bloques.
    for(int i=CERO; i<TOTAL_BRICKS; i++){
        if(_barras[i]!=NULL)
            bandera=_barras[i]->checkForHit(&_MoveBallX, &_MoveBallY, _pelota[CERO]);
        
        if(bandera && _barras[i]->getHitLft()==CERO){
            _BrickHit=i;
            _BricksLeft--;
            destroyObj(i);
            
        }else if(bandera){
            _BrickHit=i;
            _BricksLeft--;
            break;
        }
    }
    
    //movemos la pelota segun con los datos que hayamos cambiado.
    //solo se ejecuta la primera vez
    _pelota[CERO]->move(_MoveBallX,_MoveBallY);

}

/**
 * funcion para destruir un objeto.
 * @param pBarNum
 */
void controlador::destroyObj(int pBarNum) {
    Brick* temp = _barras[pBarNum];
    free(temp);
    _barras[pBarNum]=NULL;
}

/**
 * funcion para disminuir el tamaño de la barra,
 * toDOS los jugadores se ven afectaDOS cuando se hace un resize.
 */
void controlador::resizeBar(int pTypeOP) {
    for(int i =0; i<_servidor->getTplyrs(); i++){
        if(_ply[i]==NULL);
        else if(_ply[i]!=NULL)
            _ply[i]->resize(pTypeOP);
        else if(_ply[i]->getSize()==CERO){
            Player* temp = _ply[i];
            free(temp);
            _ply[i]=NULL;
        }
    }
}