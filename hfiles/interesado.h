#ifndef INTERESADO_H
#define INTERESADO_H

#include <iostream>
using namespace std;

#include "../ICollection/interfaces/ICollectible.h"
#include "../ICollection/interfaces/ICollection.h"
#include "../ICollection/interfaces/OrderedKey.h"
#include "../ICollection/interfaces/IKey.h"
#include "../ICollection/interfaces/IDictionary.h"
#include "../ICollection/interfaces/IIterator.h"
#include "usuario.h"

class DTDir;
class ICollectible;
class ICollection;
class IKey;
class IDictionary;
class IIterator;
class OrderedKey;
class Usuario;

class Interesado : public Usuario {
    private:
        string nombre;
        string apellido;
        int edad;
    public:
        Interesado(char*, string, string, int);

        //Setters
        void setNombre(string);
        void setApellido(string);
        void setEdad(int);

        //Getters
        string getNombre();
        string getApellido();
        int getEdad();
};

#endif