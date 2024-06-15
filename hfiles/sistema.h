#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
using namespace std;

#include "../ICollection/interfaces/ICollectible.h"
#include "../ICollection/interfaces/ICollection.h"
#include "../ICollection/interfaces/OrderedKey.h"
#include "../ICollection/interfaces/IKey.h"
#include "../ICollection/interfaces/IDictionary.h"
#include "../ICollection/interfaces/IIterator.h"
#include "../ICollection/collections/List.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/interfaces/OrderedKey.h"
#include "../ICollection/Integer.h"

class Sistema{
    private:
        IDictionary * usuarios;
        IDictionary * departamentos;
        IDictionary * propiedades;
    public:
        void iniciarSesion();
        void cerrarSesion();
        void altaInmobiliaria();
        void altaInteresado();
        void altaEdificio();
        void obtenerReporte();
        void altaPropiedad();
        void mensajeInteresado();
        void modificarPropiedad();
        void mensajeInmobiliaria();
        void consultarPropiedad();
        void eliminarPropiedad();
};

#endif