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
int get_cant_platos();
void imprimir_platos();
void reiniciar();


};


Pedido::Pedido(){
    platos = new Plato[25];
    precio_pedidos = 0;
}

Pedido::~Pedido (){
    delete[] platos;
}

void Pedido::agregar_plato(Plato *plato) {
    if (cant_platos < 25) {
        platos[cant_platos].nombre = plato->nombre;  // Copia explícita del nombre
        platos[cant_platos].precio = plato->precio;  // Copia explícita del precio
        //std::cout << "Plato agregado: " << platos[cant_platos].nombre << std::endl;
        cant_platos++;
    } else {
        std::cout << "Cantidad máxima de platos alcanzada" << std::endl;
    }
}

// void Pedido::agregar_plato(Plato *plato){
    
//     if (cant_platos<25){
//         platos[cant_platos] = *plato;
//         std::cout<<"plato agregado: "<<platos[cant_platos].nombre<<std::endl;
//         cant_platos++;
//     }
//     else{
//     std::cout<<"Cantidad máxima de platos alcanzada"<<std::endl;
//     }

// }

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

void Pedido::set_id_mesa(int id_enviado) {
    id = id_enviado;
    servir = true; 
}

void Pedido::set_id_llevar(int id_enviado) {
    id = id_enviado;
    servir = false;
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

void Pedido::imprimir_platos(){
    int precio_pedido = 0;
   for(int i = 0; i<cant_platos; i++){
        std::cout<<platos[i].nombre<<std::endl;
    }
    for(int i = 0; i<cant_platos; i++){
        precio_pedido += platos[i].precio;
    }
    std::cout<<"precio total: "<<precio_pedido<<std::endl;
}



int Pedido::get_cant_platos(){
    return cant_platos;
}


void Pedido::reiniciar() {
    cant_platos = 0;
    precio_pedidos = 0;
    servir = false;
    estado = 0;
    id = 0;
}
#endif