/* 
 * File:   Brick.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:57 PM
 */

#include "Brick.h"

/**
 * constructor de la clase, este constructor recibe los parametros mas 
 * importantes que son la posicion y el tipo.
 * @param pX dato tipo entero, esta es la posicion de la coordena en X.
 * @param pY dato tipo entero, esta es la posicion de la coordena en Y.
 * @param pType dato tipo entero, este el tipo al que pertenece el bloque.
 */
Brick::Brick(int pX, int pY, int pType) {
    _Posx=pX;
    _Posy=pY;
    _type=pType;
    _hitsLft=_type;
}

Brick::~Brick() {
}

void Brick::setDatas(int pX, int pY, int pType) {
    _Posx=pX;
    _Posy=pY;
    _type=pType;
    _hitsLft=_type;
}

/**
 * metodo para verificar coliciones contra un ladrillo y pelota
 * @param pBallX direccion actual de X para la pelota para saber si va a 
 * cambiar producto a la colision.
 * @param pBallY direccion actual de Y para la pelota para saber si va a
 * cambiar producto a la colision.
 * @param pBall puntero de la pelota con la cual estamos revizando.
 * @return retorna un true o false por si se golpeo la pelota.
 */
bool Brick::checkForHit(int* pBallX, int* pBallY, Bola* pBall) {
    bool hitFlag=false;
    //choque de la pelota en la seccion inferior
    if(pBall->getPy()==(_Posy+BRICK_SIZE) && (pBall->getPx()>=_Posx &&
            pBall->getPx()<=(_Posx+BRICK_SIZE))){
        (*pBallY)=UNO;
        hitFlag=true;
    }
    //choque de pelota en la parte superior de la barra
    else if(pBall->getPy()+BALL_SIZE==_Posy && 
            (pBall->getPx()>=_Posx && 
            pBall->getPx()<=(_Posx+BRICK_SIZE))){
        (*pBallY)=-UNO;
        hitFlag=true;
    }
    //choque de pelota en la parte izquierda de la barra
    else if((pBall->getPx()+BALL_SIZE)==_Posx && 
            (pBall->getPy()>=_Posy &&
            pBall->getPy()<=(_Posy+BRICK_SIZE))){
        (*pBallX)=-UNO;
        hitFlag=true;
    }
    //choque de pelota en la parte derecha de la barra
    else if(pBall->getPx()==(_Posx+BRICK_SIZE) && 
            (pBall->getPy()>=_Posy &&
            pBall->getPy()<=(_Posy+BRICK_SIZE))){
        (*pBallX)=UNO;
        hitFlag=true;
    }
    if(hitFlag)
        impact();
    return hitFlag;
}

/**
 * metodo para obtener la cantidad de golpes restantes en el bloque.
 * @return retorna un dato entero que es la cantidad de golpes restantes.
 */
int Brick::getHitLft() {
    return _hitsLft;
}

/**
 * metodo que retorna la poscion de la barra en la coordenada en X.
 * @return retorna un dato entero que es la coordenada en X.
 */
int Brick::getPosX() {
    return _Posx;
}

/**
 * metodo que retorna la poscion de la barra en la coordenada en Y.
 * @return retorna un dato entero que es la coordenada en Y.
 */
int Brick::getPosY() {
    return _Posy;
}

/**
 * metodo para obtener el tipo de bloque al que pertenece este mismo.
 * @return retorna un dato entero que es el tipo del bloque.
 */
int Brick::getType() {
    return _type;
}

/**
 * funcion que alerta un impacto al bloque y disminulle en su cantidad 
 * de golpes disponibles.
 */
void Brick::impact() {
    _hitsLft--;
}