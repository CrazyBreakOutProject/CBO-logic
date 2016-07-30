/* 
 * File:   lista.h
 * Author: ellioth
 *
 * Created on March 18, 2016, 3:14 PM
 */

#ifndef LISTA_H
#define	LISTA_H
#include <stddef.h>
#include "nodo.h"
#include "Constantes.h"

using namespace std;
class lista :public Constantes{
public:
    lista();
    virtual ~lista();
    void insert(int data);
    nodo* getHead();
    int getSize();
private:
    nodo* _head;
    int _size;
};

#endif	/* LISTA_H */

