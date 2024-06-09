#ifndef DTREPORTE_H
#define DTREPORTE_H

#include <iostream>
using namespace std;

#include "ICollection/interfaces/ICollectible.h"
#include "dtinmobiliaria.h"
#include "dtlineareporte.h"

class ICollectible;
class DTInmobiliaria;
class DTLineaReporte;

class DTReporte {
    private:
        DTInmobiliaria * inmo;
        ICollection * lineas;
    public:
        DTReporte(DTInmobiliaria *, ICollection * );
        ~DTReporte();
        
        // Getters

        DTInmobiliaria * getInmo();
        DTLineaReporte ** getLineas();
};





#endif