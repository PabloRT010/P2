#include "numero.hpp"
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
    numero_ = num;

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
    
    return numero_.c_str();
}

bool operator <(const Numero& a, const Numero& b){

    return(a.numero_ < b.numero_);
}
