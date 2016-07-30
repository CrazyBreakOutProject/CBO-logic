/* 
 * File:   BarraDes.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:57 PM
 */

#include "BarraDes.h"

/**
 * constructor de la clase, este constructor recibe los parametros mas 
 * importantes que son la posicion y el tipo.
 * @param pX dato tipo entero, esta es la posicion de la coordena en X.
 * @param pY dato tipo entero, esta es la posicion de la coordena en Y.
 * @param pType dato tipo entero, este el tipo al que pertenece el bloque.
 */
BarraDes::BarraDes(int pX, int pY, int pType) {
    _Posx=pX;
    _Posy=pY;
    _type=pType;
    _hitsLft=_type;
}

BarraDes::~BarraDes() {
}

void BarraDes::setDatas(int pX, int pY, int pType) {
    _Posx=pX;
    _Posy=pY;
    _type=pType;
    _hitsLft=_type;
}


/**
 * metodo para obtener la cantidad de golpes restantes en el bloque.
 * @return retorna un dato entero que es la cantidad de golpes restantes.
 */
int BarraDes::getHitLft() {
    return _hitsLft;
}

/**
 * metodo que retorna la poscion de la barra en la coordenada en X.
 * @return retorna un dato entero que es la coordenada en X.
 */
int BarraDes::getPosX() {
    return _Posx;
}

/**
 * metodo que retorna la poscion de la barra en la coordenada en Y.
 * @return retorna un dato entero que es la coordenada en Y.
 */
int BarraDes::getPosY() {
    return _Posy;
}

/**
 * metodo para obtener el tipo de bloque al que pertenece este mismo.
 * @return retorna un dato entero que es el tipo del bloque.
 */
int BarraDes::getType() {
    return _type;
}

/**
 * funcion que alerta un impacto al bloque y disminulle en su cantidad 
 * de golpes disponibles.
 */
void BarraDes::impact() {
    _hitsLft--;
}