/* 
 * File:   Constantes.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 2:43 PM
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H
#include <iostream>
#include <ctime>
#include <chrono>
/**
 * Datos internos para las constantes que se usaran en 
 * el proyecto.
 */
class Constantes {
private:
    /* constante usada para definir el tamaño estandar de la paleta*/
    static const int BAR_LENG_X=100;
public:
    /*tamaño de la pantalla en X*/
    static const int SCREEN_X=800;
    /*tamaño de la pantalla en Y*/
    static const int SCREEN_Y=600;
    /*variable para validar los prints en pantalla*/
    static const bool debug=true;
    /*largo del mensaje que se espera recibir*/
    static const int LENG_MSG=50;
    /*cantidad maxima de recepcion de jugadores*/
    static const int MAX_PLAYERS=10;
    
    /*-----------jugador-------------*/
    /*largo de la paleta del jugador en X*/
    static const int PLAYER_LENGHT=100;
    /*largo de la paleta del jugador en Y*/
    static const int PLAYER_LENGHT_Y=20;
    /*pos inicial de la paleta en X*/
    static const int INIT_POS_X_PLY=(SCREEN_X/2)-(PLAYER_LENGHT/2);
    /*posicion fija en Y*/
    static const int POS_Y_PLY=SCREEN_Y-(PLAYER_LENGHT_Y+100);
    /*constante para disminuir el tamaño de la barra*/
    static const int DECREMENT=-5;
    /*constante para aumentar el tamaño de la barra*/
    static const int INCREMENT=5;
    /*cantidad de movimiento en pixeles*/
    static const int PIXL_MOV_BAR=10;
    
    /*--------------bola-----------------*/
    /*espacio del choque con el primer sector de la barra para cambiar su 
     direccion*/
    static const int BAR_LENG_X_SECTOR1=BAR_LENG_X*(1/3);
    /*espacio del choque con el segundo sector de la barra para cambiar su 
     direccion*/
    static const int BAR_LENG_X_SECTOR2=BAR_LENG_X*(2/3);
    /*espacio del choque con el tercer sector de la barra para cambiar su 
     direccion*/
    static const int BAR_LENG_X_SECTOR3=BAR_LENG_X;
    /*tamaño de la pelota*/
    static const int BALL_SIZE=20;
    /*tamaño de la pelota, como es cuadrada solo se ocupa una constante*/
    static const int PIXL_MOV_BALL=1;
    /*cantidad maxima de pelotas permitidas*/
    static const int MAX_BALLS=1;
    
    /*--------------bloques-------------*/
    /*cantidad total de bloques con lo que trabajaremos*/
    static const int TOTAL_BRICKS=64;
    /*cantidad total de bloques por columna*/
    static const int COL_BRICK=4;
    /*cantidad total de bloques por fila*/
    static const int ROW_BRICK=16;
    /*tamaño del bloque*/
    static const int BRICK_SIZE=50;
    
    //constantes varias
    static const int CERO=0;
    static const int UNO=1;
    static const int DOS=2;
    static const int TRES=3;
    static const int CUATRO=4;
    static const int CINCO=5;
    static const int SEIS=6;
    static const int SIETE=7;
    static const int DIEZ=10;
    static const int CINCUENTA=50;
    static const double SLEEP_TIME;
    
    /*------constantes para los archivos tipos Json-------*/
    static const char* TYPE_CONNECTION;
    static const char* ID;
    static const char* MOVE;
    static const char* PLAYERS;
    static const char* BRICK_HIT;
    static const char* BRICKS;
    static const char* BRICK_DEL;
    static const char* SCORE;
    static const char* BALL_POS;
    static const char* POWER;
    static const char* POS;
    
    /*-------errores por parte del server------*/
    static const char* error1;
    static const char* error2;
    static const char* error3;
    static const char* error4;
    static const char* error5;
    static const char* error6;
    
    void sleep_(double pSeconds){
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds;
        while(pSeconds>elapsed_seconds.count()){
            end = std::chrono::system_clock::now();
            elapsed_seconds= end-start;
        }
        //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    };
    
};

#endif	/* CONSTANTES_H */

