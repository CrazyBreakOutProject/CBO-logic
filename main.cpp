/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:55 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Bola.h"
#include "BarraPLY.h"
#include "BarraDes.h"
#include <pthread.h>
#include <string.h>
#include <random>
#include "servidor.h"
#include "controlador.h"
#include "lista.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*
    ThreadData datos;
    datos._Tplyr=1234;
    datos._Tsockfd=5678;
    metodoPrueba(&datos);
     
    string dato="{2,1,64;Bo:200,300;Bo:100,500;Pl:200,10;}";
    string temp=dato;
    //cout<<dato.find(",")<<endl;
    int n=1,i,pos=dato.find(";");
    int pBola, pPlyrs, pBolcks;
    ----bloque para econtrar cantidad de datos----
    i=temp.find(",",n);
    pBola=stoi(dato.substr(n,i));
    cout<<pBola<<endl;
    n=i+1;
    i=temp.find(",",n);
    pPlyrs=stoi(dato.substr(n,i));
    cout<<pPlyrs<<endl;
    n=i+1;
    i=temp.find(";",n);
    pBolcks=stoi(dato.substr(n,i));
    cout<<pBolcks<<endl;
    n=i+1;
    
    ----bloque para encontrar datos de una bola----
    cout<<"---bola---"<<endl;
    for(int f=0; f<pBola; f++){
        n=dato.find(":",n)+1;
        i=dato.find(",",n);
        int x=stoi(dato.substr(n,i));
        n=i+1;
        i=dato.find(";",n);
        int y=stoi(dato.substr(n,i));
        cout<<x<<endl;
        cout<<y<<endl;
    }
    cout<<"---player----"<<endl;
    for(int f=0; f<pPlyrs; f++){
        n=dato.find(":",n)+1;
        i=dato.find(",",n);
        int x=stoi(dato.substr(n,i));
        n=i+1;
        i=dato.find(";",n);
        int y=stoi(dato.substr(n,i));
        cout<<x<<endl;
        cout<<y
    std::string item_name=;
std::string item_address;<<endl;
    }
    int i=temp.find(",");
    cout<<stoi(dato.substr(n,i))<<endl;
    n=i+1;*/
    /*
    /*prueba para server
    servidor * server= new servidor(5000);
    for(;;){
        if(server->getScreens()>0)
            ser
    std::string item_name=;
std::string item_address;ver->sendMSG("hola_mundo",10);
    }
    cin.ignore();*/
    //controlador * pruebaControlador = new controlador(5001);
    /*prueba de coliciones
    Bola * pBola= new Bola(180,150);
    BarraDes * pBloque = new BarraDes(130,160,1);
    int y=0,x=0;
    bool bandera;
    if(pBola->getPy()==(pBloque->getPosY()+50)&&
            (pBola->getPx()+20)>=pBloque->getPosX()&&
            pBola->getPx()<=(pBloque->getPosX()+50)){
        y=1;
        bandera=true;
    }
    //choque de pelota en la parte superior de la barra
    else if(pBola->getPy()+20==pBloque->getPosY() &&
            (pBola->getPx()+20)>=pBloque->getPosX() &&
            pBola->getPx()<=(pBloque->getPosX()+50)){
        y=-1;
        bandera=true;
    }
    //choque de pelota en la parte izquierda de la barra
    else if((pBola->getPx()+20)==pBloque->getPosX() &&
            (pBola->getPy()+20)>=pBloque->getPosY() &&
            pBola->getPy()<=(pBloque->getPosY()+50)){
        x=-1;
        bandera=true;
    }
    //choque de pelota en la parte derecha de la barra
    else if(pBola->getPx()==(pBloque->getPosX()+50) &&
            (pBola->getPy()+20)>=pBloque->getPosY() &&
            pBola->getPy()<=(pBloque->getPosY()+50)){
        x=1;
        bandera=true;
    }
    pBola->move(x,y);
    cout<<"posX: "<<pBola->getPx()<<endl;
    cout<<"posY: "<<pBola->getPy()<<endl;
     * */
    /*
    string item_name = "John";
    string item_address = "New York";

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartObject();
    writer.String("item");
        writer.StartObject();
        writer.String(item_name.c_str());
        writer.String(item_name.c_str());
        writer.String("address");
        writer.String(item_address.c_str());
        writer.EndObject();
    writer.String("item");
        writer.StartObject();
        writer.String("name");
        writer.String(item_name.c_str());
        writer.String("address");
        writer.String(item_address.c_str());
        writer.EndObject();
    writer.EndObject();
    

    std:cout << s.GetString() <<endl;
    void * pointer = malloc(14);
    cout<<(int*)pointer<<endl;
    free(pointer);*/
    
    
    srand(time(NULL));
    int POS_Y_PLY= 600-120;
    
    //Bola* _pelota[10];
    //BarraDes * _barras[15];
    //BarraPLY * _ply[2];
    Bola** _pelotaPrueba= (Bola**)malloc(sizeof(Bola*)*10);
    _pelotaPrueba[0]=(Bola*)malloc(sizeof(Bola));
    _pelotaPrueba[0]->setPos(800/2-20,POS_Y_PLY-(25));
    BarraPLY ** _ply=(BarraPLY**)malloc(sizeof(BarraPLY*)*2);
    _ply[0]=(BarraPLY*)malloc(sizeof(BarraPLY));
    _ply[0]->setDatas(0);
    _ply[1]=(BarraPLY*)malloc(sizeof(BarraPLY));
    _ply[1]->setDatas(1);
    BarraDes ** _barras= (BarraDes**)malloc(sizeof(BarraDes*)*15);
    JsonCreator* nuevoJson= new JsonCreator();
    //_pelota[0]= new Bola(800/2-20,POS_Y_PLY-(25));
    //_pelota[1]= new Bola(800/2-20,POS_Y_PLY-(25));
    //_ply[0]= new BarraPLY(0);
    //_ply[1]= new BarraPLY(1);
    int _BallsLeft=1;
    int _PlayersLeft=2;
    /*---------------------------------------------------------------------*/
    //incializacion de los bloques
    int _BarrsLeft=15;
    int space=0;
    for(int i=0; i<15;i++){
        int fuerza= (rand()%3)+1;
        _barras[i]=(BarraDes*)malloc(sizeof(BarraDes));
        _barras[i]->setDatas(i*50,(i*50)+(50),fuerza);
    }
    //prueba para pelota sin golpear--funciona
    string pruebaJson= nuevoJson->create(_pelotaPrueba, _ply,NULL, _BallsLeft,_PlayersLeft,-1);
    //prueba para pelota golpeada--funciona a medias 
    //_barras[1]->impact();
    //string pruebaJson= nuevoJson->create(_pelotaPrueba, _ply, _barras[1],_BallsLeft,_PlayersLeft,1);
    //prueba para terminar juego--funciona
    //string pruebaJson= nuevoJson->create(NULL, _ply, NULL, _BallsLeft,_PlayersLeft,-2);
    cout<<pruebaJson<<endl;
    return 0;
}

