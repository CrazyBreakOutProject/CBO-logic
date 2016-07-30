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
    _BarrsLeft=TOTAL_BRICKS;
    _barras=(BarraDes**)malloc(sizeof(BarraDes*)*TOTAL_BRICKS);
    int space=CERO;
    for(int j =CERO; j<ROW_BRICK; j++)
        for(int i=CERO; i<COL_BRICK;i++,space++){
            int fuerza= (rand()%TRES)+UNO;
            _barras[space]=(BarraDes*)malloc(sizeof(BarraDes));
            _barras[space]->setDatas(j*BAR_SIZE,(i*BAR_SIZE)+(CINCUENTA),fuerza);
        }
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
    if(_BarrsLeft>CERO){
        for(int i =CERO; i<_BarrsLeft; i++){
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
 * ciclo principal para revizar todo.
 */
void controlador::MainLoop(){
    int LoopCounter=CERO; //se usara para darle un pequeño retardo al juego para
    //que se pueda procesar todo enla GUI.
    _ply=(BarraPLY**)malloc(sizeof(BarraPLY*)*MAX_PLAYERS);
    while(true){
        if(_servidor->getTplyrs()>CERO){
            for(int i=CERO; i<_servidor->getTplyrs(); i++){
                //verificamos si los players son nulos para crearlos 
                if(_ply[i]==NULL)
                    _ply[i]=(BarraPLY*)malloc(sizeof(BarraPLY));
                    _ply[i]->setDatas(i);
                //obtenemos sus cambios y nos movemos por la pantalla.
                if(_servidor->getBoolPlyrs(i)){
                    _ply[i]->move(_servidor->getMSGPlyrs(i));
                    _servidor->setBoolPlyrs(i);
                }
            }
            //revisamos las coliciones
            checkColl();
            string msg;
            if(LoopCounter%SLEEP_TIME!=CERO)
                LoopCounter++;
            //revisamos de primero la condicion de terminacion.
            else if(_BallsLeft==CERO || _BarrsLeft==CERO){
                msg=_Json->create(NULL, _ply, NULL,_BallsLeft,
                        _servidor->getTplyrs(),-DOS);
                _servidor->sendMSG(msg.c_str(),msg.length());
                break;
            }
            else if(_BarrsHit==-UNO){
                msg=_Json->create(_pelota, _ply, NULL,_BallsLeft,
                        _servidor->getTplyrs(),_BarrsHit);
                _servidor->sendMSG(msg.c_str(),msg.length());
            }
            //en caso de que no seguimos normalmente
            else{
                msg=_Json->create(_pelota, _ply, _barras[_BarrsHit],
                    _BallsLeft,_servidor->getTplyrs(),_BarrsHit);
                _servidor->sendMSG(msg.c_str(),msg.length());
            }
        }   
    }
}

/**
 * metodo para ir revizando las coliciones de la pelota contra 
 * los objetos en campo.
 */
void controlador::checkColl() {
    _BarrsHit=-UNO;bool bandera= false;
    //bloque para verificar choques con limites de pantalla
    if(_pelota[CERO]->getPx()+BALL_SIZE==SCREEN_X)
        _MoveBallX=-UNO;
    else if(_pelota[CERO]->getPx()==CERO)
        _MoveBallX=UNO;
    if(_pelota[CERO]->getPy()==CERO)
        _MoveBallY=UNO;
    //verificacion para choque contra la paleta de cada jugador.
    
    for(int i =CERO; i<_servidor->getTplyrs(); i++)
        checkCollPly(i,&_MoveBallX,&_MoveBallY, &bandera);
    //verificaciones para colicion contra cada UNO de los bloques.
    for(int i=CERO; i<TOTAL_BRICKS; i++){
        checkCollBrr(i, &_MoveBallX, &_MoveBallY, &bandera);
        if(bandera)
            break;
    }
    //verificacion por si la pelota se sale del alcance del jugador
    if(_pelota[CERO]->getPy()>(POS_Y_PLY+PLAYER_LENGHT_Y)){
        _BallsLeft--;
        for(int i=CERO; i<_servidor->getTplyrs(); i++)
            _ply[i]->resize(DECREMENT);
        if(_BallsLeft==CERO){
            Bola * temp = _pelota[CERO];
            _pelota[CERO]= NULL;
            temp->~Bola();
            return;
        }
    }
    //movemos la pelota segun con los datos que hayamos cambiado.
    //solo se ejecuta la primera vez
    _pelota[CERO]->move(_MoveBallX,_MoveBallY);
}

/**
 * metodo para revizar una colicion contra un jugador
 * @param plyr dato tipo entero que es el numero de cliente contra el 
 * cual estamos revizando.
 * @param x dato tipo puntero entero que es el X de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 * @param y dato tipo puntero entero que es el Y de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 */
void controlador::checkCollPly(int plyr, int * x, int * y, bool *bandera) {
    //colision con sector UNO de la barra
    if(_pelota[CERO]->getPy()+BALL_SIZE==POS_Y_PLY && 
            (_pelota[CERO]->getPx()+BALL_SIZE)>=_ply[plyr]->getPosX() &&
            _pelota[CERO]->getPx()<=(_ply[plyr]->getPosX()+BAR_LENG_X_SECTOR1)){
        (*x)=-UNO;
        (*y)=-UNO;
        (*bandera)=true;
    }
    //colision con sector DOS de la barra
    else if(_pelota[CERO]->getPy()+BALL_SIZE==POS_Y_PLY && 
            _pelota[CERO]->getPx()>=(_ply[plyr]->getPosX()+BAR_LENG_X_SECTOR1) &&
            _pelota[CERO]->getPx()<=(_ply[plyr]->getPosX()+BAR_LENG_X_SECTOR2)){
        (*x)=CERO;
        (*y)=-UNO;
        (*bandera)=true;
    }
    //colision con sector UNO de la barra
    else if(_pelota[CERO]->getPy()+BALL_SIZE==POS_Y_PLY && 
            _pelota[CERO]->getPx()>=(_ply[plyr]->getPosX()+BAR_LENG_X_SECTOR2) &&
            _pelota[CERO]->getPx()<=(_ply[plyr]->getPosX()+BAR_LENG_X_SECTOR3)){
        (*x)=UNO;
        (*y)=-UNO;
        (*bandera)=true;
    }
}

/**
 * metodo para verificar coliciones contra barras
 * @param bar dato entero que es el espacio de la barra con la cual 
 * estamos revizando actualmente.
 * @param x dato tipo puntero entero que es el X de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 * @param y dato tipo puntero entero que es el Y de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 */
void controlador::checkCollBrr(int bar, int * x, int * y, bool * bandera) {
    //condicion por si revisamos contra una pelota que ya no existe.
    if(_barras[bar]==NULL)
        return;
    //choque de pelota en la parte inferior de la barra
    if(_pelota[CERO]->getPy()==_barras[bar]->getPosY()&&
            (_pelota[CERO]->getPx()+BALL_SIZE)>=_barras[bar]->getPosX()&&
            _pelota[CERO]->getPx()<=(_barras[bar]->getPosX()+BAR_SIZE)){
        (*y)=UNO;
        *bandera=true;
    }
    //choque de pelota en la parte superior de la barra
    else if(_pelota[CERO]->getPy()+BALL_SIZE==_barras[bar]->getPosY() &&
            (_pelota[CERO]->getPx()+BALL_SIZE)>=_barras[bar]->getPosX() &&
            _pelota[CERO]->getPx()<=(_barras[bar]->getPosX()+BAR_SIZE)){
        (*y)=-UNO;
        *bandera=true;
    }
    //choque de pelota en la parte izquierda de la barra
    else if((_pelota[CERO]->getPx()+BALL_SIZE)==_barras[bar]->getPosX() &&
            (_pelota[CERO]->getPy()+BALL_SIZE)>=_barras[bar]->getPosY() &&
            _pelota[CERO]->getPy()<=(_barras[bar]->getPosY()+BAR_SIZE)){
        (*x)=-UNO;
        *bandera=true;
    }
    //choque de pelota en la parte derecha de la barra
    else if(_pelota[CERO]->getPx()==(_barras[bar]->getPosX()+BAR_SIZE) &&
            (_pelota[CERO]->getPy()+BAR_SIZE)>=_barras[bar]->getPosY() &&
            _pelota[CERO]->getPy()<=(_barras[bar]->getPosY()+BAR_SIZE)){
        (*x)=UNO;
        *bandera=true;
    }
    /*verificacion para realizar una colicion y saber si se tieene que destruir
    el objeto*/
    if(*bandera){
        _BarrsHit=bar;
        _barras[bar]->impact();
        if(_barras[bar]->getHitLft()==CERO){
            _BarrsLeft--;
            destroyObj(bar);
        }
    }
        
}

/**
 * funcion para destruir un objeto.
 * @param pBarNum
 */
void controlador::destroyObj(int pBarNum) {
    BarraDes * temp = _barras[pBarNum];
    _barras[pBarNum]=NULL;
    temp->~BarraDes();
}

/**
 * funcion para disminuir el tamaño de la barra,
 * toDOS los jugadores se ven afectaDOS cuando se hace un resize.
 */
void controlador::resizeBar(int pTypeOP) {
    for(int i =0; i<_servidor->getTplyrs(); i++){
        _ply[i]->resize(pTypeOP);
    }
}