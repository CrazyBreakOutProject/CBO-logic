/* 
 * File:   JsonCreator.cpp
 * Author: ellioth
 * 
 * Created on February 17, 2016, 11:24 PM
 */

#include "JsonCreator.h"

JsonCreator::JsonCreator() {

}

JsonCreator::~JsonCreator() {
}

/**
 * metodo para crear el Json que se le enviara al cliente que tenga la pantalla
 * @param bola dato tipo puntero que es el arreglo de las bolas en el campo.
 * @param plyrs dato tipo puntero que es el arreglo que contiene a los 
 * clientes conectaDOS.
 * @param barrs dato tipo puntero que es el arreglo que contiene las barras o 
 * bloques restantes en el campo.
 * @param pBolas dato tipo entero que es la cantidad de bolas en el campo.
 * @param pPlyrs dato tipo entero que es la cantidad de jugadores en el campo.
 * @param pBarrs dato tipo entero que es el bloque que queremos decir que
 * recibio un golpe.
 * @return retorna un dato tipo string que es el Json creado.
 * {"players":{"p1":"000,000","p2":"000,000"...}, "brickH":{"id":00,"del":0}}
 */
string JsonCreator::create(Bola* bola[], BarraPLY* plyrs[], BarraDes* barrs, int pBolas, int pPlyrs, int pBarrs){
    string temp;
    rapidjson::StringBuffer JsonToWrite;
    rapidjson::Writer<rapidjson::StringBuffer> writer(JsonToWrite);
    writer.StartObject();
    //crea un mensaje que indica la terminacion del juego.
    if(pBolas==CERO || pBarrs==-DOS){
        temp="terminate";
        writer.String(temp.c_str());
        writer.String(temp.c_str());
        writer.EndObject();
        return JsonToWrite.GetString();
    }
    //bloque para los jugadores conectados
    writer.String(PLAYERS);
        writer.StartObject();
        string playerTempName;
        for(int i =0; i<pPlyrs; i++){
            playerTempName="p"+to_string(i);
            writer.String(playerTempName.c_str());
            string posPlayer= to_string(plyrs[i]->getPosX());
            posPlayer+=",";
            posPlayer+=to_string(plyrs[i]->getPosY());
            writer.String(posPlayer.c_str());
        }
        writer.EndObject();
    //bloque para los ladrillos que golpeamos 
    writer.String(BRICK_HIT);
        writer.StartObject();
        writer.String(ID);
        writer.String(to_string(pBarrs).c_str());
        if(barrs!=NULL){
            writer.String(BRICK_DEL);
            writer.String(to_string(barrs->getHitLft()).c_str());
        }
        writer.EndObject();
    //bloque para la pelota en el campo
    writer.String(BALL_POS);
        writer.StartObject();
        string ballTempName; 
        for(int i =0; i<pBolas; i++){
            ballTempName=POS+to_string(i);
            writer.String(ballTempName.c_str());
            string posBall= to_string(bola[i]->getPx());
            posBall+=",";
            posBall+=to_string(bola[i]->getPy());
            writer.String(posBall.c_str());
        }
        writer.EndObject();
    writer.EndObject();
    /*
    //agregamos al inicio del mensaje la cantidad de datos que van
    _mensaje="{"+to_string(pBolas)+","+ to_string(pPlyrs)
            +","+ to_string(pBarrs);
    //ciclo para agregar a las pelotas.
    for(int i=0; i<pBolas;i++){
        temp=";Bo:"+to_string(bola[i]->getPx())+
                ","+to_string(bola[i]->getPy());
        _mensaje.append(temp);
    }
    //ciclo para agregar a los jugadores.
    for(int i=0;i <pPlyrs; i++){
        temp=";Pl:"+to_string(plyrs[i]->getPosX())+","+
                to_string(plyrs[i]->getSize());
        _mensaje.append(temp);
    }
    //parte para agregar el bloque.
    if(barrs==NULL && pBarrs>=CERO){
        temp=";Bl:"+to_string(pBarrs)+","+to_string(CERO);
        _mensaje.append(temp);
    }
    else if(pBarrs>=CERO){
        temp=";Bl:"+to_string(pBarrs)+","+to_string(barrs->getHitLft());
        _mensaje.append(temp);
    }
    _mensaje.append(";}\0");*/
    return JsonToWrite.GetString();
}

