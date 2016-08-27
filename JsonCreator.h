/* 
 * File:   JsonCreator.h
 * Author: ellioth
 *
 * Created on February 17, 2016, 11:24 PM
 */

#ifndef JASONCREATOR_H
#define	JASONCREATOR_H
#include <string>
#include <iostream>
#include "Brick.h"
#include "Player.h"
#include "Bola.h"
#include "Constantes.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace std;

/**
 * clase usada para crear el Json que se usara crear el mensaje que se enviara
 * al cliente que tenga pantalla.
 */

class JsonCreator: public Constantes {
public:
    JsonCreator();
    virtual ~JsonCreator();    
    string create(Bola* bola[], Player* plyrs[], Brick* Barrs,int pBolas,
    int pPlyrs, int pBarrs, int pScore);
    string firstMsg(Bola* bola[], Player* plyrs[], Brick* Barrs[],
    int pBolas, int pPlyrs, int pScore);
private:
};

#endif	/* JASONCREATOR_H */

