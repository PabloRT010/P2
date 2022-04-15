#ifndef CLAVE_HPP_
#define CLAVE_HPP_
#include "cadena.hpp"
#include <iostream>
#include <unistd.h>

class Clave{

    public:

    Clave(Cadena contr);
    const Clave& cifrar_clave(Cadena contr); //devuelve clave encriptada
    const Clave& clave() const; //devuelve clave 

    enum Razon{CORTA, ERROR_CRYPT};

    class Incorrecta{
        public:
        
        Incorrecta(Clave::Razon r): razon_(r){}
        Clave::Razon razon() const;

        private:
        Clave::Razon razon_;

    };
    
    private:
    Cadena contrasenna_;

};


















#endif