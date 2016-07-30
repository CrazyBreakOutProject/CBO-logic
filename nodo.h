/* 
 * File:   nodo.h
 * Author: ellioth
 *
 * Created on March 18, 2016, 3:14 PM
 */

#ifndef NODO_H
#define	NODO_H

class nodo {
public:
    nodo(int data);
    virtual ~nodo();
    void setNext(nodo* nodoNext);
    nodo* getNext();
    int getData();
private:
    int _dato;
    nodo* _next;
};

#endif	/* NODO_H */

