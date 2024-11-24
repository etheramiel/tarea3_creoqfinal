#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "pedido.hpp"
#include "registro.hpp"

void leer_archivo(std::string nombre_archivo, Plato *&platos, int &cant_platos){
    cant_platos = 0;
    std::ifstream archivo(nombre_archivo);

    if(archivo.is_open()){
        archivo>>cant_platos;
        archivo.ignore();
        platos = new Plato[cant_platos];    

        for(int i = 0; i<cant_platos; i++){
            std::string linea = "";
            std::string nombre = "";
            std::string guion;
            int precio = 0;
            std::getline(archivo, linea);
            std::stringstream ss(linea);
            std::getline(ss, nombre, '-');
            nombre.erase(nombre.find_last_not_of(" \t") + 1);
            ss>>precio;
            platos[i].nombre = nombre;
            platos[i].precio = precio;
        }
        archivo.close();
    }
    else{
        std::cout<<"No se pudo abrir el archivo"<<std::endl;
    }
    archivo.close();
};


int main(){
    int cant_platos;
    std::string comando, registrar1;
    Plato *platos;
    int cant_mesas;
    std::cin>>cant_mesas;
    Registro registro(cant_mesas);
    leer_archivo("platos.txt", platos, cant_platos);
    int contar_llevar = 1;

    while(comando != "cerrar"){
        Pedido pedido;
        Plato plato_temp;
        std::cin>>comando;
        if(comando == "registrar"){
            std::string tipo;
            int mesa, numero_pedido;
            bool servir;
            std::cin.ignore();
            std::cin>>tipo;
            if(tipo == "mesa"){
                std::cin>>mesa;
                servir = true;     
                registro.agregar_pedido(&pedido, true, mesa);
                numero_pedido = mesa;              
            }
            else{
                registro.agregar_pedido(&pedido, false, contar_llevar);
                numero_pedido = contar_llevar;
                contar_llevar++;
            }

            std::cin>>comando;
            std::string plato;
            
            while(comando == "agregar"){
                std::getline(std::cin, plato);
                plato.erase(0, plato.find_first_not_of(" "));

                for(int i = 0; i<cant_platos; i++){
                    if(platos[i].nombre == plato){
                        plato_temp = platos[i];
                    }
                }
                pedido.agregar_plato(&plato_temp);
                std::cin>>comando;  
                
                if(comando == "pedir"){
                    std::cout<<tipo<<" "<<numero_pedido<<" Registrado"<<std::endl;
                    break;
                }
            }
        }

         

        else if(comando == "info"){
            std::cout<<"info"<<std::endl;
            std::string tipo;
            int mesa;
            int n_pedido;
            bool servir;
            std::cin.ignore();
            std::cin>>tipo;
        
            if(tipo == "mesa"){
                std::cin>>mesa;
                
            }
            else{
                std::cin>>n_pedido;
            }

        }

        else if(comando == "pagar"){
            int id;
            bool tipo;
            std::string tipo1;
            std::cin>>tipo1;
            std::cin>>id;
            if(tipo1 == "mesa"){
                tipo = true;
                
            }
            else{
                tipo = false;
                
            } 
        }

    }

}