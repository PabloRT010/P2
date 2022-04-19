#ifndef NUMERO_H
#define NUMERO_H
#include "cadena.hpp"
#include <iostream>

class Numero{
    public:
    Numero(Cadena& num);
    bool luhn(const Cadena& numero);
    enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto{
        public:
        Incorrecto(Razon r): r_(r){}
        const Razon& razon() const {return r_;} 

        private:
        Razon r_;
    };

    operator const char*() const; //constructor de conversion

    friend bool operator <(const Numero& a, const Numero& b);

    private:
    Cadena num_;
};




#endif