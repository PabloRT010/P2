#include "tarjeta.hpp"


Tarjeta::Tarjeta(const Numero& num, Usuario& tit, const Fecha& fech): numero_(num), titular_(&tit), activa_(true){

    Fecha hoy;
    if(fech < hoy){

        throw Caducada(fech);
    }
    if(TAR_.insert(num).second == false){

        throw Num_duplicado(num);
    }

    const_cast<Usuario*>(titular_)-> es_titular_de(*this); //asociacion con usuario. const_cast desecha el const

}

const Tarjeta::Tipo Tarjeta::tipo()const{
    Tipo aux;
    
    if(numero_.num_[0] == '3'){ //consultora en la clase numero??
        if(numero_.num_[1] == '4' || numero_.num_[1] == '7'){
            aux = AmericanExpress;
        }
        else
            aux = JCB;
    }
    else if(numero_.num_[0] == '4'){
        aux = VISA;
    }
    else if(numero_.num_[0] == '5'){
        aux = Mastercard;
    }
    else if(numero_.num_[0] == '6'){
        aux = Maestro;
    }
    else
        aux = Otro;
    
    return aux;
}

void Tarjeta::anula_titular(){
    titular_ = nullptr;
    activa_ = false;
}



std::ostream& operator <<(std::ostream& os, const Tarjeta& tar){
    os << tar.tipo() << '\n';
    os << tar.numero() << '\n';
    os << tar.titular().nombre() << " ";
    os << tar.titular().apellidos() << '\n';
    os << "Caduca: " << std::setw(2) << std::setfill('0') << tar.caducidad().mes() << '/' << std::setw(2) << std::setfill('0') << tar.caducidad().anno() % 100;
    return os;
}

std::ostream &operator<<(std::ostream &os, Tarjeta::Tipo t){
    if (t == Tarjeta::Otro)
        os << "Otro";
    else if (t == Tarjeta::VISA)
        os << "VISA";
    else if (t == Tarjeta::Mastercard)
        os << "Mastercard";
    else if (t == Tarjeta::Maestro)
        os << "Maestro";
    else if (t == Tarjeta::JCB)
        os << "JCB";
    else if (t == Tarjeta::AmericanExpress)
        os << "AmericanExpress";

    return os;
}

bool operator <(Tarjeta& a, Tarjeta& b){
    return(a.numero_ < b.numero_);
}

Tarjeta::~Tarjeta(){
    const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
}
