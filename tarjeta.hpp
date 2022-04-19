#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "usuario.hpp"
#include "numero.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>
#include <set>
#include <iomanip>

class Tarjeta{
    public:
    enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

    Tarjeta(const Numero& num, Usuario& tit, const Fecha& fech);
    Tarjeta(const Tarjeta& t) = delete;
    Tarjeta& operator =(const Tarjeta& t) = delete;
    //observadoras
    const Numero& numero()const {return numero_;}
    const Usuario& titular()const{return *titular_;}
    const Fecha& caducidad()const {return caducidad_;}
    const bool activa()const{return activa_;}
    const Tipo tipo() const;

    bool activa(bool par = true);
    void anula_titular();
    friend bool operator <(Tarjeta& a, Tarjeta& b);
    class Caducada{
        public:
        Caducada(const Fecha& f):f_caducada_(f){}
        const Fecha& cuando()const{return f_caducada_;}

        private:
        Fecha f_caducada_;
    };

    class Num_duplicado{
        public:
        Num_duplicado(const Numero& num): num_(num){}
        const Numero& que() const {return num_;}

        private:
        Numero num_;
    };

    class Desactivada;

    ~Tarjeta();
    private:
    const Numero numero_;
    const Usuario* titular_;
    const Fecha caducidad_;
    bool activa_;
    typedef std::set<Numero> TAR; //duplicidad de tarjeta
    static TAR TAR_;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& tar);
std::ostream& operator<<(std::ostream &os, Tarjeta::Tipo t);

bool Tarjeta::activa(bool par){
    activa_ = par;
    return activa_;
}

#endif