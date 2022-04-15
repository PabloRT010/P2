#ifndef ARTICULO_H_
#define ARTICULO_H_
#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>

class Articulo{

    public:

        Articulo(const Cadena& ref, const Cadena& tit, const Fecha& fech, float prec, int st = 0): cod_ref_(ref), titulo_(tit), fecha_pub_(fech), precio_(prec), stock_(st) {};

        //observadores
        const Cadena& referencia() const;
        const Cadena& titulo() const;
        const Fecha& f_publi() const;
        float precio() const; // 2 decimales
        float& precio(float p);
        int stock() const;
        int& stock(int s);
     
    private:

        const Cadena cod_ref_;
        const Cadena titulo_;
        const Fecha fecha_pub_;
        float precio_;
        int stock_;
};

std::ostream& operator <<(std::ostream& os, Articulo& art);



#endif