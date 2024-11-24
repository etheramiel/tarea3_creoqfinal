#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <iostream>
#include <fstream>
#include <string>
#include "pedido.hpp"

struct Plato {
std::string nombre ;
int precio ;
};


class Pedido {
private :
Plato *platos; // arreglo de platos en el pedido, tamaño inicial 25
bool servir; // true para servir, false para llevar
size_t cant_platos;


int estado; // 0 para nunca ocupado, 1 para ocupado, 2 para liberado
int id;
int id_llevar = 1;
int id_mesa = 1;
int precio_pedidos;

public:

Pedido ();
~ Pedido ();
void agregar_plato( Plato * plato ); // agrega un plato al pedido
int precio_total (); // retorna la suma del precio de todos los platos del pedido

int get_total();
void set_id_mesa(int id_enviado);
void set_id_llevar(int id_enviado);
int get_estado();
int get_id();
bool get_servir();
void set_estado(int estado2);


};

Pedido::Pedido(){
    platos = new Plato[25];
    cant_platos = 0;
    
}

Pedido::~Pedido (){
    delete[] platos;
}

void Pedido::agregar_plato(Plato *plato){
    
    if (cant_platos<25){
        platos[cant_platos] = *plato;
        cant_platos++;
    }
    else{
    std::cout<<"Cantidad máxima de platos alcanzada";
    }

}

int Pedido::precio_total() {
    int precio_pedidos = 0;
    for (int i = 0; i < cant_platos; i++) {
        precio_pedidos += platos[i].precio;
    }
    return precio_pedidos;
}

int Pedido::get_total(){
    return precio_pedidos;
}

void Pedido::set_id_mesa(int id_enviado){
    id_mesa = id_enviado;
}

void Pedido::set_id_llevar(int id_enviado){
    id_llevar = id_enviado;
}

int Pedido::get_estado(){
    return estado;
}

int Pedido::get_id(){
    return id;
}

bool Pedido::get_servir(){
    return servir;
}

void Pedido::set_estado(int estado2){
    estado = estado2;
}


#endif