/* 
 * File:   nodo.cpp
 * Author: ellioth
 * 
 * Created on March 18, 2016, 3:14 PM
 */

#include "nodo.h"

/**
 * constructor que recibe un dato para guaradarlo
 * @param dato
 */
nodo::nodo(int dato) {
    _dato=dato;
}

/**
 * destructor de la clase.
 */
nodo::~nodo() {
    delete _next;
}

/**
 * metodo que retorna el nodo que le sigue
 * @return retorna un dato tipo Nodo, este es un 
 * puntero.
 */
nodo* nodo::getNext() {
    return _next;
}

/**
 * metodo que establece el nodo siguiente a este 
 * @param nodoNext recibe un dato tipo Nodo*, este es el 
 * puntero del nodo.
 */
void nodo::setNext(nodo* nodoNext) {
    _next=nodoNext;
}

int nodo::getData() {
    return _dato;
}
