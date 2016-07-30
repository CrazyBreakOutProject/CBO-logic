/* 
 * File:   BarraPLY.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:56 PM
 */

#ifndef BARRAPLY_H
#define	BARRAPLY_H
#include "Constantes.h"
#include <string>
#include <string.h>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace std;

/**
 * clase para crear los objetos de los bloques.
 */
class BarraPLY: public Constantes {
public:
    BarraPLY(int pId);
    virtual ~BarraPLY();
    void setDatas(int pID);
    int getSize();
    int resize(int pOP);
    int getPosX();
    int getPosY();
    void move(string Moviment);
private:
    int _id;
    int _PosX,_PosY;
    int _size;

};

#endif	/* BARRAPLY_H */

