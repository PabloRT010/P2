#ifndef CLAVE_HPP_
#define CLAVE_HPP_
#include "cadena.hpp"
#include "articulo.hpp"
#include "numero.hpp"
#include "tarjeta.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>


class Clave{

    public:

    Clave(const char* contr);
   // void cifrar_clave(Cadena contr); //devuelve contrasenna encriptada
    const Cadena& clave() const {return contrasenna_;} //devuelve la contrasenna CIFRADA 
    bool verifica(char* cad);
    enum Razon{CORTA, ERROR_CRYPT};

    class Incorrecta{
        public:
        
        Incorrecta(Razon r): razon_(r){}
        const Razon& razon() const {return razon_;}

        private:
        Razon razon_;

    };
    
    private:
    Cadena contrasenna_;

};



class Usuario{
    public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& clave);
    Usuario(const Usuario& u) = delete; //impedimos que un usuario se construya en base aa otro
    Usuario& operator =(const Usuario& u) = delete;

    //consultoras
    const Cadena& id() const {return id_;}
    const Cadena& nombre() const {return nom_;}
    const Cadena& apellidos() const {return apell_;}
    const Cadena& direccion() const {return dir_;}
    const Tarjetas& tarjetas() const {return T;}
    const Articulos& compra() const {return A;}


    ~Usuario();

    class Id_duplicado{
        public:
        Id_duplicado(const Cadena& cad); //: idd_(cad) {}
        const Cadena& idd() const {return idd_;} 
        private:
        Cadena idd_;
    };

    private:
    const Cadena id_, nom_, apell_, dir_;
    Clave clave_;
    typedef std::unordered_set<Cadena> ID; //duplicidad de usuarios
    static ID ID_;
    Tarjetas T;
    Articulos A;

};









#endif