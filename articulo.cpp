#include"articulo.hpp"

const Cadena& Articulo::referencia()const{
    return cod_ref_;
}

const Cadena& Articulo::titulo()const{
    return titulo_;
}

const Fecha& Articulo::f_publi()const{
    return fecha_pub_;
}

float Articulo::precio()const{
    return precio_;
}

float& Articulo::precio(){
    return precio_;
}

int Articulo::stock()const{
    return stock_;
}

int& Articulo::stock(){
    return stock_;
}

std::ostream& operator <<(std::ostream& os, Articulo& art){
    os << "["<< art.referencia() <<"] "<<'"'<<art.titulo()<<'"'<<", "<<art.f_publi()<<". "<<std::setprecision(2)<<art.precio()<<" €";
    return os;
}