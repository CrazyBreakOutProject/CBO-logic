/* 
 * File:   lista.cpp
 * Author: ellioth
 * 
 * Created on March 18, 2016, 3:14 PM
 */

#include "lista.h"

lista::lista() {
    _head=NULL;
}

lista::~lista() {
}

/**
 * metodo para insertar datos en una lista.
 * @param data recibe un dato tipo entero, este se va a guardar 
 * en la lista empaquetado por un nodo.
 */
void lista::insert(int data) {
    if(_head== NULL){
        _head= new nodo(data);
        _size++;
    }
    else{
        nodo* temp=_head;
        if(temp->getData()==data)
            return;
        for(int i =0; i<_size-UNO; i++)
            temp=temp->getNext();
        nodo* newNodo= new nodo(data);
        temp->setNext(newNodo);
        _size++;
    }
}

/**
 * metodo que nos retorna la cabeza de la lista 
 * @return retorna un dato tipo nodo* que este es el puntero 
 * al nodo.
 */
nodo* lista::getHead() {
    return _head;
}

/**
 * nos retorna el largo de la lista permitiendonos hacer el
 * recorrido de esta misma de una manera mas sencilla.
 * @return retorna una dato tipo entero que es el tamaño 
 * de la lista.
 */
int lista::getSize() {
    return _size;
}
