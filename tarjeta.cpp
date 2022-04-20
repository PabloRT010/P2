#include "tarjeta.hpp"
#include <cstddef>

Numero::Numero(Cadena& num){

    char aux[num.length() + 1];
    int i = 0;
    int j;
    for(j = 0; j < num.length(); j++){ //quitamos los espacios en blanco y guardamos en aux

        if (isdigit(num[j])){

            aux[i] = num[j];
            i++; 
        }
        else if(isalpha(num[j])){ //comprobamos si es una letra

            throw Incorrecto(DIGITOS);
        }
    }
    aux[i] = '\0';
    num = aux;

    if(num.length() < 13 || num.length() < 19){
        throw Incorrecto(LONGITUD);
    }

    if(!luhn(num)){
        throw Incorrecto(NO_VALIDO);
    }
    num_ = num;

}

bool luhn(const Cadena& numero){
  size_t n = numero.length();
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}

Numero::operator const char *() const{
    
    return num_.c_str();
}

bool operator <(const Numero& a, const Numero& b){

    return(a.num_ < b.num_);
}
//clase tarjeta
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
    
    if(numero_.num_[0] == '3'){ 
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
