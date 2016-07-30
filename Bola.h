/* 
 * File:   Bola.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:55 PM
 */

#ifndef BOLA_H
#define	BOLA_H
#include "Constantes.h"

/**
 * clase para crear objetos del tipo bola.
 */
class Bola: public Constantes {
    
public:
    Bola(int x, int y);
    virtual ~Bola();
    void setPos(int x, int y);
    void setPw(int type);
    void move(int pX, int pY);
    int getPx();
    int getPy();
private:
    int _Posx,_Posy,_pow;

};

#endif	/* BOLA_H */

