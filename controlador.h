/* 
 * File:   controlador.h
 * Author: ellioth
 *
 * Created on February 12, 2016, 3:50 PM
 */

#ifndef CONTROLER_H
#define	CONTROLER_H
#include "Bola.h"
#include "Brick.h"
#include "Player.h"
#include "Constantes.h"
#include "servidor.h"
#include "JsonCreator.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace std;
/**
 * clase para controlar toda la logica, en esta se realiza 
 * todo lo necesario de movimientos, revizar coliciones, etc.
 * @param Pport recibe el puerto por donde se van a conectar
 * las personas.
 */
class controlador: public Constantes{
friend class servidor;
public:
    controlador(int Pport);
    virtual ~controlador();
private:
    //pelota en el campo
    Bola** _pelota;
    //barras que se destruiran en el campo
    Brick ** _barras;
    //paleta de jugadores
    Player ** _ply;
    //server por el cual nos conectaremos contra la gente
    servidor * _servidor;
    //variable 
    JsonCreator * _Json;
    //booleano para saber cuando el juego se va a terminar
    bool _flagTerminate;
    //dato entero que es puerto por el cual van a acceder los clientes.
    int _port;
    int _dirrection;
    int _score;
    //variables para desplazar la pelota sobre la pantalla
    int _MoveBallX,_MoveBallY;
    /**
     * _BallsLeft-> dato que contiene la cantidad de pelotas en campo
     * _BarrsLeft-> dato que contiene la cantidad de barras restante en campo.
     */
    int _BallsLeft,_BrickHit,_BricksLeft;
    void MainLoop();
    void checkForMsgPlayers(int * pAmmountPLayers);
    void checkCondForMsg();
    void destroyObj(int BarNum);
    void resizeBar(int pTypeOP);
    void checkColl();
};

#endif	/* CONTROLER_H */

