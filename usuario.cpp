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

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& clave): nom_(nom), apell_(apell), dir_(dir), clave_(clave){

    if(ID_.insert(id).second == false){ //un conjunto no admite elementos duplicados, este metodo devuelve un booleano de si esta o no en el conjunto
        throw Id_duplicado(id);
    }
}
