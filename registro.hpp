#ifndef REGISTRO_HPP
#define REGISTRO_HPP
#include <iostream>
#include <fstream>
#include <string>
#include "registro.hpp"

class Registro {
private :
Pedido *pedidos; // arreglo de pedidos , tamaño inicial n (cantidad de mesas)
size_t size;
void ajustar_arreglo (); // ajusta el tamaño de la tabla de hashing
int ganancias;



float carga_max = 0.8;
int ranuras_ocupadas = 0;
int ranuras;
float factor_de_carga = 0.0;
int id_para_llevar = 1;
Pedido *tabla;

public:
Registro ();
~ Registro ();
Registro (int n);

void agregar_pedido(Pedido *pedido, bool servir, int id);
Pedido *get_pedido(int id, bool tipo); // Retorna el pedido según id y tipo (servir true // llevar false )
Pedido *eliminar_pedido(int id, bool tipo); // Elimina el pedido según id y tipo

void cuenta(Pedido *pedido);
int calcular_ganancias(Pedido *pedido);
int hash(int id, bool servir);
int hash2(int index, int i);
float calcular_factor_de_carga();

};

int Registro::hash(int id, bool servir){
    int index;
    if (servir){
        index = id * 2 + 1;
    }
    else{
        index = id * 2;
    }
    return index % size;
}

int Registro::hash2(int index, int i){
    index = index * index + i;
    return index % size;
}


void Registro::ajustar_arreglo(){
    int nuevo_tamanio = size * 1.5;
    Pedido *nueva_tabla = new Pedido[nuevo_tamanio];
    for (int i=0; i<size; i++ ){
        nueva_tabla[i] = pedidos[i];
    }
    delete[] pedidos;
    
    pedidos = nueva_tabla;
    size = nuevo_tamanio;

    delete[] nueva_tabla;
}


Registro::Registro (int n) {
    pedidos = new Pedido[n];
    size = n;
    ranuras_ocupadas = 0;
    ganancias = 0;
    for (int i = 0; i < n; i++){
        pedidos[i].set_estado(0);
    }
}

Registro::~ Registro (){
 delete [] pedidos;
}

void Registro::agregar_pedido(Pedido *pedido , bool servir , int id){
    
    int i = 0;

    ranuras_ocupadas++;
    
    if(ranuras_ocupadas/size > carga_max){
        ajustar_arreglo();
    }
    

    int indice, indice_nuevo, indice_temp;
    indice = hash(id, servir);
    indice_temp = indice;


    while (pedidos[indice_temp].get_estado() == 1) {
        indice_temp = hash2(indice, i);
        i++;
    }
    indice = indice_temp;

    // if(pedidos[indice].get_estado() == 1){
    //     while(pedidos[indice_temp].get_estado() == 1){
    //         indice_nuevo = hash2(indice, i);
    //         indice_temp = indice_nuevo;
    //         i++;
    //     }
    //     indice = indice_nuevo;
    // }
    
    pedidos[indice] = *pedido;

    if(servir){
        pedidos[indice].set_id_mesa(id);
    }
    else{
        pedidos[indice].set_id_llevar(id_para_llevar);
        id_para_llevar++;
    }

    pedidos[indice].set_estado(1);

}


Pedido *Registro::get_pedido(int id , bool tipo){
    
    int i = 0;
    int indice;
    indice = hash(id, tipo);
    int indice_temp = indice;

    int max_iter = size;


    while(pedidos[indice_temp].get_estado() != 0 && i < max_iter){
        
        if(pedidos[indice_temp].get_id() == id && pedidos[indice_temp].get_servir() == tipo){
           // std::cout<<"id get_pedido: "<<pedidos[indice_temp].get_id()<<std::endl;
            //std::cout<<"servir get_pedido: "<<pedidos[indice_temp].get_servir()<<std::endl;
            //std::cout<<"cantplatos get_pedido: "<<pedidos[indice_temp].get_cant_platos()<<std::endl;
            return &pedidos[indice_temp];
        }
        
        indice_temp = hash2(indice, i);

        i++;
    }

    return nullptr;
}

// Pedido *Registro::get_pedido (int id, bool tipo ){
    
//     int index, i = 0;
//     index = hash(id, tipo);
//     std::cout<<pedidos[index].get_estado()<<std::endl;  

//     if(pedidos[index].get_id() == id && pedidos[index].get_servir() == tipo){
//         std::cout<<"id: "<<pedidos[index].get_id()<<std::endl;
//         return &pedidos[index];
//     }

//     while(pedidos[index].get_estado() != 0){
//         std::cout<<"entro a while get_pedido"<<std::endl;
//         if(pedidos[index].get_id() == id && pedidos[index].get_servir() == tipo){
//             std::cout<<"entró al if "<<std::endl;
//             return &pedidos[index];
//         }
//         i++;
//         index = hash2(index, i);

//         if(i >= size){
//             return nullptr;
//         }
//     }


//     return nullptr;
// }

Pedido *Registro::eliminar_pedido(int id, bool tipo){
    int index, i = 0;
    index = hash(id, tipo);
    Pedido pedido_temp;

    while(pedidos[index].get_estado() != 0){
        if(pedidos[index].get_id() == id && pedidos[index].get_servir() == tipo){
            pedido_temp = pedidos[index];
            pedidos[index].~Pedido();
            pedidos[index].set_estado(2);
            ranuras_ocupadas;
            return &pedido_temp;
        }
        i++;
        index = hash2(index, i);

        if(i >= ranuras){
            return nullptr;
        }

    }
    return nullptr;
}

void Registro::cuenta(Pedido *pedido){
    int total;
    total=pedido->get_total();
    std::cout<<"total: "<<total<<std::endl;
}

int Registro::calcular_ganancias(Pedido *pedido){
    ganancias=pedido->get_total()*1.1;
    return ganancias;
}

float Registro::calcular_factor_de_carga(){
    factor_de_carga=ranuras_ocupadas/ranuras;
    return factor_de_carga;
}
#endif