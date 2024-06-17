#include "../hfiles/zona.h"
#include <iostream>
#include "../hfiles/edificio.h"
#include "../hfiles/propiedad.h"
#include "../hfiles/casa.h"
using namespace std;

Zona::Zona(int codigo, string nombre){
    this->codigo = codigo;
    this->nombre = nombre;
    this->edificios = new OrderedDictionary();
    this->propiedades = new OrderedDictionary();
    this->cantEdificios = 0;
    this->cantPropiedades = 0;
    // Falta especificar el ICollection
}

Zona::~Zona(){}

// Getters

int Zona::getCodigo(){
    return this->codigo;
}

string Zona::getNombre(){
    return this->nombre;
}

int Zona::getCantEdificios(){
    return this->cantEdificios;
}

int Zona::getCantPropiedades(){
    return this->cantPropiedades;
}

IDictionary * Zona::getEdificios(){
    return this->edificios; // Capaz no es asi
}

IDictionary * Zona::getPropiedades(){
    return this->propiedades; // Capaz no es asi
}

// Setters

void Zona::setCodigo(int codigo){
    this->codigo = codigo;
}

void Zona::setNombre(string nombre){
    this->nombre = nombre;
}

void Zona::setCantEdificios(int cantEdificios){
    this->cantEdificios = cantEdificios;
}

void Zona::setCantPropiedades(int cantPropiedades){
    this->cantPropiedades = cantPropiedades;
}

// Agregar-Quitar

void Zona::agregarEdificio(Edificio * edificio){
    
    IKey * nuevaKey = new Integer (edificio->getCodigo());
    if (!this->edificios->member(nuevaKey)){
        ICollectible * nuevoEdificio = (ICollectible *) edificio;
        this->edificios->add(nuevaKey, nuevoEdificio);
        this->cantEdificios++;
        cout << "El edificio fue agregado exitosamente!" << endl;
    } else {
        delete nuevaKey;
        throw invalid_argument("El edificio ya fue agregado con anterioridad");
    }

    // ES CON ICOLLECTION
}

void Zona::quitarEdificio(int codigoEdificio){

    IKey * clave = new Integer (codigoEdificio);
    if (this->edificios->member(clave)){
        this->edificios->remove(clave);
        this->cantEdificios--;
        delete clave;
        cout << "El edificio fue removido de manera exitosa!" << endl;
    } else {
        delete clave;
        throw invalid_argument("El edificio especificado no se encuentra en la zona actual");
    }
    // ES CON ICOLLECTION
}

void Zona::agregarPropiedad(Propiedad * propiedad){

    IKey * nuevaKey = new Integer (propiedad->getCodigo());
    if (!this->edificios->member(nuevaKey)){
        ICollectible * nuevaPropiedad = (ICollectible *) propiedad;
        this->propiedades->add(nuevaKey, nuevaPropiedad);
        this->cantPropiedades++;
        cout << "La propiedad fue agregado exitosamente!" << endl;
    } else {
        delete nuevaKey;
        throw invalid_argument("La propiedad ya fue agregado con anterioridad");
    }
    // ES CON ICOLLECTION
}

void Zona::quitarPropiedad(int codigoProp){

    IKey * clave = new Integer (codigoProp);
    if (this->propiedades->member(clave)){
        this->propiedades->remove(clave);
        this->cantPropiedades--;
        delete clave;
        cout << "La propiedad fue removida de manera exitosa!" << endl;
    } else {
        delete clave;
        throw invalid_argument("La propiedad especificada no se encuentra en la zona actual");
    }
    // ES CON ICOLLECTION
}

// Métodos de Zona (DCD)

DTZona * Zona::getDTZona(){
    return new DTZona(this->codigo, this->nombre);
}

ICollection * Zona::listarEdificios(){
    ICollection * edificios = new List();
    IIterator * it = this->edificios->getIterator();
    Edificio * edificio;
    ICollectible * item;
    while (it->hasCurrent()){
        edificio = (Edificio *) it->getCurrent();
        item = (ICollectible *) edificio->getDTEdifico();
        edificios->add(item);
        it->next();
    }
    delete it;
    return edificios;
    // ES CON ICOLLECTION
}

Edificio * Zona::seleccionarEdificio(int codigoEdificio){

    IKey * clave = new Integer (codigoEdificio);
    Edificio * edificio = (Edificio *) this->edificios->find(clave);
    delete clave;
    if (edificio != NULL){
        return edificio;
    } else {
        throw invalid_argument("El edificio especificado no se encuentra en la zona actual");
    }
    // ES CON ICOLLECTION
}

// ES LO MISMO QUE AGREGAR PROPIEDAD
void Zona::enlazarPropiedad(Propiedad * propiedad){
    
    IKey * nuevaKey = new Integer (propiedad->getCodigo());
    if (!this->edificios->member(nuevaKey)){
        ICollectible * nuevaPropiedad = (ICollectible *) propiedad;
        this->propiedades->add(nuevaKey, nuevaPropiedad);
        this->cantPropiedades++;
        cout << "La propiedad fue agregado exitosamente!" << endl;
    } else {
        delete nuevaKey;
        throw invalid_argument("La propiedad ya fue agregado con anterioridad");
    }
    // ES CON ICOLLECTION
}

Casa * Zona::crearCasa(int cantAmbientes, int cantDormitorios, int cantBanios, int m2Edificados, DTDir * dir, bool tieneGaraje, int m2Verdes){
    int codigo = crearClavePropiedad();
    return new Casa(codigo, cantAmbientes, cantDormitorios, cantBanios, m2Edificados, dir, tieneGaraje, this, m2Verdes);
}

// ES LO MISMO QUE QUITAR PROPIEDAD
void Zona::desvincularPropiedad(Propiedad * propiedad){

    IKey * clave = new Integer (propiedad->getCodigo());
    if (this->propiedades->member(clave)){
        this->propiedades->remove(clave);
        delete clave;
        cout << "La propiedad fue removida de manera exitosa!" << endl;
    } else {
        delete clave;
        throw invalid_argument("La propiedad especificada no se encuentra en la zona actual");
    }
    // ES CON ICOLLECTION
}

ICollection * Zona::listarChatPropiedad(char * email){
    IIterator * it = this->propiedades->getIterator();
    ICollection * lista = new List();
    Propiedad * prop;
    ICollectible * item;
    while (it->hasCurrent()){
        prop = (Propiedad *) it->getCurrent();
        item = (ICollectible *) prop->getDTChatProp(email);
        lista->add(item);
        it->next();
    }
    delete it;
    return lista;
    // ES CON ICOLLECTION
}

Propiedad * Zona::seleccionarPropiedad(int codigoProp){

    IKey * clave = new Integer (codigoProp);
    Propiedad * propiedad = (Propiedad *) this->propiedades->find(clave);
    delete clave;
    if (propiedad != NULL){
        return propiedad;
    } else {
        throw invalid_argument("La propiedad especificada no se encuentra en la zona actual");
    }
    // ES CON ICOLLECTION
}

// Esta mal
ICollection * Zona::getUltimosMensajes(){
    ICollection * lista = new List();
    IIterator * it = this->propiedades->getIterator();
    Mensaje * mensaje;
    ICollectible * item;
    int count = 0;
    while(it->hasCurrent() && count < 5){
        mensaje = (Mensaje *) it->getCurrent();
        item = (ICollectible *) mensaje->getDTMensaje();
        lista->add(item);
        it->next();
        count++;
    }
    delete it;
    return lista;
    // ES CON ICOLLECTION
}

int Zona::crearClavePropiedad(){
    IIterator * it = this->propiedades->getIterator();
    Propiedad * prop = NULL;
    while (it->hasCurrent()){
        prop = (Propiedad *) it->getCurrent();
        it->next();
    }
    delete it;
    if (prop != NULL){
        return prop->getCodigo()+1;
    }
    return 1;
}