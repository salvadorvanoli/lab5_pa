#include "../hfiles/mensaje.h"
#include <iostream>
using namespace std;

Mensaje::Mensaje(int codigo, DTFecha * fecha, string texto){
    this->codigoMen = codigo;
    this->fecha = fecha;
    this->texto = texto;
}

Mensaje::~Mensaje(){
    delete this->fecha;
}

int Mensaje::getCodigo(){
    return this->codigoMen;
}

DTFecha * Mensaje::getFecha(){
    return this->fecha;
}

string Mensaje::getTexto(){
    return this->texto;
}

void Mensaje::setFecha(DTFecha * fecha){
    this->fecha = fecha;
}

void Mensaje::setTexto(string texto){
    this->texto = texto;
}

DTMensaje * Mensaje::getDTMensaje(){
    return new DTMensaje(this->texto, this->fecha);
}