#ifndef CLAVE_HPP_
#define CLAVE_HPP_
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include<utility>

class Tarjeta;
class Numero;
class Articulo;
class Clave{

    public:

    Clave(const char* contr);
   // void cifrar_clave(Cadena contr); //devuelve contrasenna encriptada
    Cadena clave() const {return contrasenna_;} //devuelve la contrasenna CIFRADA 
    bool verifica(const char* cad) const;
    enum Razon{CORTA, ERROR_CRYPT};

    class Incorrecta{
        public:
        
        Incorrecta(Razon r): razon_(r){}
        Razon razon() const {return razon_;}

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
    Cadena id() const {return id_;}
    Cadena nombre() const {return nom_;}
    Cadena apellidos() const {return apell_;}
    Cadena direccion() const {return dir_;}
    const Tarjetas& tarjetas() const {return T;}
    const Articulos& compra() const {return A;}
    //asociaciones
    void es_titular_de(Tarjeta& t);
    void no_es_titular_de(Tarjeta& t);
    void compra(Articulo& art, int cant = 1);
    int n_articulos()const;

    ~Usuario();
    friend std::ostream& operator << (std::ostream& os, const Usuario& u);//aqui lo hago friend porque hay varias clases en el fichero

    class Id_duplicado{
        public:
        Id_duplicado(const Cadena& cad): idd_(cad) {}
        Cadena idd() const {return idd_;} 
        private:
        Cadena idd_;
    };

    private:
    Cadena id_, nom_, apell_, dir_;
    Clave clave_;
    typedef std::unordered_set<Cadena> ID; //duplicidad de usuarios
    static ID ID_;
    Tarjetas T; //tarjetas a las que esta asociado
    Articulos A; //articulos de su carrito

};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u);

#endif