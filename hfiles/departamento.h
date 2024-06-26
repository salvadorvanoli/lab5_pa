#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <iostream>
using namespace std;

#include "../ICollection/interfaces/ICollectible.h"
#include "../ICollection/interfaces/IDictionary.h"
#include "../ICollection/collections/List.h"
#include "../ICollection/interfaces/IKey.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/Integer.h"
#include "zona.h"
#include "dtdepartamento.h"
#include "dtzona.h"

class ICollectible;
class ICollection;
class Zona;
class DTZona;
class DTDepartamento;

class Departamento: public ICollectible {
    private:
        char * letra;
        string nombre;
        IDictionary * zonas;
        int cantZonas;
    public:
        Departamento(char *, string);
        ~Departamento();

        // Getters

        char * getLetra();
        string getNombre();
        int getCantZonas();
        IDictionary * getZonas();

        // Setters

        void setLetra(char *);
        void setNombre(string);
        void setCantZonas(int);

        // Agregar-Quitar (Creo que esta mal)

        void agregarZona(Zona *);
        void quitarZona(int);

        // Métodos de Departamento (DCD)

        DTDepartamento * getDTDepartamento();
        ICollection * listarZonasDepartamento();
        Zona * elegirZona(int);

        // Otras funciones
        int crearClaveZona();
};

#endif
