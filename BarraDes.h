/* 
 * File:   BarraDes.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:57 PM
 */

#ifndef BARRADES_H
#define	BARRADES_H
#include "Constantes.h"

/**
 * clase que crea Bloques para destuir en pantalla.
 */
class BarraDes:public Constantes {
public:
    BarraDes(int pX, int pY, int pType);
    virtual ~BarraDes();
    void setDatas(int pX, int pY, int pType);
    int getType();
    int getHitLft();
    int getPosX();
    int getPosY();
    void impact();
private:
    int _Posx, _Posy;
    int _hitsLft;
    int _type;
    bool _flag;
};

#endif	/* BARRADES_H */

