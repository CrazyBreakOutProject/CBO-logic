/* 
 * File:   Player.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:56 PM
 */

#include "Player.h"

/**
 * constructor que recibe un id para identificarlos
 * @param pId dato tipo entero.
 */
Player::Player(int pId) {
    _id=pId;
    _PosX=INIT_POS_X_PLY;
    _PosY=POS_Y_PLY;
    _size=BAR_LENG_X_SECTOR3;
}

Player::~Player() {
    
}

void Player::setDatas(int pID) {
    _id=pID;
    _PosX=INIT_POS_X_PLY;
    _PosY=POS_Y_PLY;
    _size=BAR_LENG_X_SECTOR3;
}

/**
 * metodo para verificar coliciones contra una paleta de jugador y una pelota.
 * @param pBallX referencia del desplazamiento actual de la pelota en X.
 * @param pBallY referencia del desplazamiento actual de la pelota en Y.
 * @param pBall referencia de la pelota contra la que estamos revizando.
 * @return retorna un true o false con respecto al impacto con la barra.
 */
bool Player::checkHit(int* pBallX, int* pBallY, Bola* pBall) {
    bool hitFlag=false;
    //colision con sector UNO de la barra
    if((pBall->getPy()+BALL_SIZE)==_PosY && (pBall->getPx()>=_PosX &&
            pBall->getPx()<=(_PosX+BAR_LENG_X_SECTOR1))){
        (*pBallX)=-UNO;
        (*pBallY)=-UNO;
        hitFlag=true;
    }
    //colision con sector DOS de la barra
    else if(pBall->getPy()+BALL_SIZE==_PosY && 
            (pBall->getPx()>=(_PosX+BAR_LENG_X_SECTOR1) &&
            pBall->getPx()<=(_PosX+BAR_LENG_X_SECTOR2))){
        (*pBallX)=CERO;
        (*pBallY)=-UNO;
        hitFlag=true;
    }
    //colision con sector UNO de la barra
    else if(pBall->getPy()+BALL_SIZE==_PosY && 
            (pBall->getPx()>=(_PosX+BAR_LENG_X_SECTOR2) &&
            pBall->getPx()<=(_PosX+BAR_LENG_X_SECTOR3))){
        (*pBallX)=UNO;
        (*pBallY)=-UNO;
        hitFlag=true;
    }
    return hitFlag;
}

/**
 * metodo que retorna la posicion en X de la paleta del 
 * cliente
 * @return retorna un dato tipo entero que es la posicion en 
 * X. 
 */
int Player::getPosX() {
    return _PosX;
}

/**
 * metodo que retorna la posicion en Y de la barra para 
 * hacer reviciones contra esta coordenada.
 * @return retorna un dato tipo entero que es la posicion 
 * en Y.
 */
int Player::getPosY() {
    return _PosY;
}

/**
 * metodo que obtiene el tamaño dela paleta del cliente.
 * @return retorna un dato entero que es el tamaño de la paleta
 * del cliente.
 */
int Player::getSize() {
    return _size;
}

/**
 * metodo para redimencionar el tamaño de la paleta del cliente.
 * @param pOP recibe un dato entero que indica si vamos a hacer un
 * decremento o incremento.
 * @return retorna un dato entero que es el tamaño de la barra.
 */
int Player::resize(int pOP) {
    if(pOP==DECREMENT)
        _size+=DECREMENT;
    _size+=INCREMENT;
}

/**
 * metodo para mover la paleta, actualiza su posicion en X
 * segun el tipo de mensaje que recibe.
 * @param pX recibe un dato tipo entero, este puede ser un 
 * positivo o negativo de hacia donde moverse.
 */
void Player::move(string Moviment) {
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(Moviment.c_str());
    if(!_JsonDocument.IsObject()){
        cout<<"falla, archivo no es tipo json en jugador"<<endl;
        return;
    }//obtenemos la operacion a realizar
    rapidjson::Value & data = _JsonDocument[MOVE];
    int move= data.GetInt();
    if(_PosX>CERO){
        if (move==DOS)
            _PosX+=PIXL_MOV_BAR;
    }
    if((_PosX+BAR_LENG_X_SECTOR3)<SCREEN_X){
        if (move==CERO)
            _PosX-=PIXL_MOV_BAR;
    }
}
