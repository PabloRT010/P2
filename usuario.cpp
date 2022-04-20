#include "usuario.hpp"
#include <cstring>
#include <random>
#include <map>
#include <unistd.h>

Clave::Clave(const char* contr){

    Cadena contrasenna(contr);

    if(contrasenna.length() < 5){
        throw Incorrecta(CORTA);
    }
    //ciframos la clave
    std::random_device rd; //elemento con el que generaremos un carácter aleatorio
    std::uniform_int_distribution<char> dis('0', 'z'); //0-9, A-Z, a-z
    const char salt[3] = {dis(rd),dis(rd),'\0'}; //generamos salt, la cual es una cadena de 2 caracteres aleatorios para generar un hash
    contrasenna_ = crypt(contr, salt);

    if(contrasenna_ == NULL){
        throw Incorrecta(ERROR_CRYPT);
    }

}

bool Clave::verifica(char* cad){

    return (strcmp(crypt(cad,contrasenna_.c_str()), contrasenna_.c_str()));
    
}

//Usuario 
Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& clave): id_(id), nom_(nom), apell_(apell), dir_(dir), clave_(clave){

    if(ID_.insert(id).second == false){ //un conjunto no admite elementos duplicados, este metodo devuelve un booleano de si esta o no en el conjunto
        throw Id_duplicado(id);
    }
    
}

void Usuario::es_titular_de(Tarjeta& t){ //ligamos a tarjeta
    T[t.numero()] = &t; //la tarjeta del usuario cuyo numero sea el de la tarjeta pasada
}

void Usuario::no_es_titular_de(Tarjeta& t){
    T.erase(t.numero());
}

void Usuario::compra(Articulo& art, int cant){
    if(cant == 0){
        A.erase(&art);
    }
    if(cant > 0){
        A[&art] = cant;
    }
}

int Usuario::n_articulos()const{
    return A.size();
}


std::ostream& operator << (std::ostream& os, const Usuario& u){

    os << u.id() << " ["<< u.clave_.clave() <<"] "<<u.nombre()<<" "<<u.apellidos()<<"\n"; //**devuelve contrasenna cifrada??
    os << u.direccion()<<"\n";
    os << "Tarjetas :"<<"\n";

    for(auto it = u.T.begin(); it != u.T.end(); it++){
        os << *(it->second) << "\n"; //mostramos la tarjeta 
    }

}

std::ostream& mostrar_carro(std::ostream& os, Usuario& u){

    os << "Carrito de compra de " << u.id() << " [Articulos:" << u.compra().size()<<"] " << std::endl;
    os << "===================================================================="<<std::endl;

    for (Usuario::Articulos::iterator it = u.compra().begin(); it != u.compra().end(); it++){
        os<<"\t" << it->second <<"\t"<< it->first << "\n";
    }
}




Usuario::~Usuario(){
    for (Usuario::Tarjetas::iterator it = T.begin(); it != T.end(); it++){
        it->second->anula_titular();
    }
}