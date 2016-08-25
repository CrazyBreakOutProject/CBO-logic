
/* 
 * File:   Brick.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:57 PM
 */

#ifndef BARRADES_H
#define	BARRADES_H
#include "Constantes.h"
#include "Bola.h"

/**
 * clase que crea Bloques para destuir en pantalla.
 */
class Brick:public Constantes {
public:
    Brick(int pX, int pY, int pType);
    virtual ~Brick();
    void setDatas(int pX, int pY, int pType);
    bool checkForHit(int* pBallX, int* pBallY, Bola* pBall);
    int getType();
    int getHitLft();
    int getPosX();
    int getPosY();
    void impact();
private:
    int _Posx, _Posy;
    int _hitsLft;
    int _type;
};

#endif	/* BARRADES_H */

