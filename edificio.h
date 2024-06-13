#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H
#include <iostream>
#include "ICollection/interfaces/ICollectible.h"
#include "apartamento.h"


using namespace std;

class Zona: public ICollectible {
    private:
        int codigo;
        string nombre;
        int cantPisos;
        int gastosComunes;
        ICollection * apartamentos;
        int cantApartamentos;
    public:
        Edificio(int, string);
        ~Edificio();

        // Getters

        int getCodigo();
        string getNombre();
        int getCantPisos();
        int getGastosComunes();
        int getCantApartamentos();
        Apartamento ** getApartamentos();

        // Setters

        void setCodigo(int);
        void setNombre(string);
        void setCantPisos(int);
        void setGastosComunes(int);
        void setCantApartamentos(int);

        // Agregar-Quitar (Creo que esta mal)

        void agregarApartamento(Apartamento *);
        void quitarApartamento(int);

        // Métodos del Edificio (DCD)

        Apartamento * crearApartamento(int, int, int, bool, DTDir, int);
};

#endif