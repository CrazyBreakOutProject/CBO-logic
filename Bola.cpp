/* 
 * File:   Bola.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:55 PM
 */

#include "Bola.h"

/**
 * contructor que recibe la poscion en donde 
 * se va a ubicar.
 * @param x dato tipo entero, es la coordenada en X de la bola.
 * @param y dato tipo entero, es la coordenada en Y de la bola.
 */
Bola::Bola(int x, int y){
    _Posx=x;
    _Posy=y;
}

Bola::~Bola() {
    
}

void Bola::setPos(int x, int y) {
    _Posx=x;
    _Posy=y;
}


/**
 * funcion para otorgar un poder a la pelota.
 * @param type recibe un entero que seria el 
 * tipo de poder que se puede utilizar.
 */
void Bola::setPw(int type) {
    _pow=type;
}

/**
 * metodo para retornar la posicion en X de la 
 * pelota.
 * @return retorna un dato tipo entero. 
 */
int Bola::getPx() {
    return _Posx;
}

/**
 * metodo para retornar la posicion en Y de la 
 * pelota.
 * @return retorna una dato tipo entero. 
 */
int Bola::getPy() {
    return _Posy;
}

/**
 * funcion que realiza el movimiento de la 
 * pelota sobre el campo segun se le indique.
 * @param pX dato tipo entero, es la posicion en X.
 * @param pY dato tipo entero, es la posicion en Y.
 */
void Bola::move(int pX, int pY) {
    if (pX>CERO)
        _Posx+=PIXL_MOV_BALL;
    else if(pX<CERO)
        _Posx-=PIXL_MOV_BALL;
    if (pY>CERO)
        _Posy+=PIXL_MOV_BALL;
    else if(pY<CERO)
        _Posy-=PIXL_MOV_BALL;
    
}
