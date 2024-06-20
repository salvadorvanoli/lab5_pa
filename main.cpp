#include <iostream>
using namespace std;

#include "hfiles/sistema.h"
#include "hfiles/sistemafactory.h"
#include <string> 
#include <ctime>



void imprimirZonasDepto(ICollection * col){
    IIterator * it = col->getIterator();
    DTZona * zona;
    int i = 1;
    while (it->hasCurrent()){
        zona = (DTZona *) it->getCurrent();
        cout << "[ZONA " << i << ']' << endl << zona << endl;
        i++;
        it->next();
    }
    delete it;
}


void imprimirDepto(ICollection * col){
    IIterator * it = col->getIterator();
    DTDepartamento * departamento;
    int i = 1;
    while (it->hasCurrent()){
        departamento = (DTDepartamento *) it->getCurrent();
        cout << "[DEPARTAMENTO " << i << ']' << endl << departamento << endl;
        i++;
        it->next();
    }
    delete it;
}

void imprimirEdificios(ICollection * col){
    IIterator * it = col->getIterator();
    DTEdificio * edificio;
    int i = 1;
    while (it->hasCurrent()){
        edificio = (DTEdificio *) it->getCurrent();
        cout << "[EDIFICIO " << i << ']' << endl << edificio << endl;
        i++;
        it->next();
    }
    delete it;
}

void imprimirProps(ICollection * col){
    IIterator * it = col->getIterator();
    DTPropiedad * prop;
    int i = 1;
    while (it->hasCurrent()){
        prop = (DTPropiedad *) it->getCurrent();
        cout << "[PROPIEDAD " << i << ']' << endl << prop << endl;
        i++;
        it->next();
    }
    delete it;
}

void imprimirPropsDetalladas(ICollection * col){
    IIterator * it = col->getIterator();
    DTPropiedadDetallada * propDetallada;
    while (it->hasCurrent()){
        propDetallada = (DTPropiedadDetallada *) it->getCurrent();
        cout << propDetallada << endl;
        it->next();
    }
    delete it;
}

void imprimirDTChatProps(IDictionary * col){
    IIterator * it = col->getIterator();
    DTChatProp * dtchatprop;
    DTPropiedad * prop;
    while (it->hasCurrent()){
        prop = dynamic_cast<DTPropiedad *> (it->getCurrent());
        if (prop != NULL){
            cout << "---PROPIEDAD---" << endl << prop << endl;
        } else {
            dtchatprop = dynamic_cast<DTChatProp *> (it->getCurrent());
            cout << "------CHAT------" << endl << dtchatprop << endl;
        }
        it->next();
    }
    delete it;
}

void imprimirDTMensajes(ICollection * col){
    IIterator * it = col->getIterator();
    DTMensaje * dtmensaje;
    int i = 1;
    while (it->hasCurrent()){
        dtmensaje = dynamic_cast<DTMensaje *> (it->getCurrent());
        cout << "[MENSAJE " << i << ']' << endl << dtmensaje << endl;
        i++;
        it->next();
    }
    delete it;
}

DTFecha * getDTFechaActual(){
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    // Obtener el día, mes y año actuales
    int dia = now->tm_mday;
    int mes = now->tm_mon + 1; // Los meses van de 0 a 11, por eso se suma 1
    int anio = now->tm_year + 1900; // El año se cuenta desde 1900, por eso se suma 1900

    // Obtener la hora, minuto y segundo actuales
    int hora = now->tm_hour;
    int minuto = now->tm_min;
    int segundo = now->tm_sec;

    DTHora * dthora = new DTHora(hora, minuto, segundo);
    
    return new DTFecha(dia, mes, anio, dthora);
}

bool manejarIniciarSesion(ISistema * sistema){
    system("cls");
    char* email = new char[100];
    bool emailCorrecto;
    do{
        cout << "Inicie sesión con una cuenta" << endl << endl;
        cout << "Ingrese email" << endl << endl;
        cin >> email;
        try {
            sistema->iniciarSesion(email);
            emailCorrecto = true;
        } catch (const exception& e){
            system("cls");
            cout << "Error de ejecución: " << e.what() << endl;
            system("pause");
            emailCorrecto = false;
            system("pause");
        }
    } while(!emailCorrecto);
    if(sistema->getLoggeado()->getPrimeraVez() == true){
        try{
            system("cls");
            string pwd1;
            string pwd2;
            cout << "Es su primera vez iniciando sesión" << endl;
            cout << "Establezca una contraseña segura de más de 8 caracteres" << endl << endl;
            cin >> pwd1;
            cout << "Repita la contraseña" << endl << endl;
            cin >> pwd2;
            sistema->crearContrasenia(pwd1, pwd2);
        } catch (const exception& e){
            system("cls");
            cout << "Error de ejecución: " << e.what() << endl;
            system("pause");
            return false;
        }
    }
    system("cls");
    string pwd;
    cout << "Inicie sesión con su contraseña" << endl << endl;
    cin >> pwd;
    try{
        sistema->ingresarContrasenia(pwd);
        cout << "Sesión iniciada con éxito";
        return true;
    } catch (const exception& e) {
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return false;
    }
}

void manejarAltaInmobiliaria(ISistema * sistema){
    system("cls");
    char* email = new char[100];
    string nombre;
    DTDir* dir;
    string calle;
    int numero;
    string ciudad;
    cout << "Va a ingresar un usuario inmobiliaria en el sistema" << endl << endl;
    cout << "Ingrese el email" << endl << endl;
    cin >> email;
    IKey * key = new String(email);
    if(sistema->getUsuarios()->member(key)){
        cout << "Ya existe un usuario con ese correo" << endl;
        return;
    }
    system("cls");

    cout << "Ingrese ahora un nombre para la inmobiliaria" << endl << endl;
    cin >> nombre;

    system("cls");

    cout << "Ingrese calle" << endl << endl;
    cin >> calle;

    system("cls");

    cout << "Ingrese numero" << endl << endl;
    cin >> numero;

    system("cls");

    cout << "Ingrese ciudad" << endl << endl;
    cin >> ciudad;

    dir = new DTDir(calle, numero, ciudad);

    try{
        sistema->altaInmobiliaria(nombre, email, dir);
    } catch (const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
}


void manejarAltaInteresado(ISistema * sistema){
    system("cls");
    char* email = new char[100];
    string nombre;
    string apellido;
    int edad;
    cout << "Va a ingresar un usuario interesado en el sistema" << endl << endl;
    cout << "Ingrese el email" << endl << endl;
    cin >> email;
    IKey * key = new String(email);
    if(sistema->getUsuarios()->member(key)){
        cout << "Ya existe un usuario con ese correo" << endl;
        return;
    }
    system("cls");

    cout << "Ingrese ahora un nombre para el interesado" << endl << endl;
    cin >> nombre;

    system("cls");

    cout << "Ingrese un apellido" << endl << endl;
    cin >> apellido;

    do {
        system("cls");
        cout << "Ingrese la edad" << endl << endl;
        cin >> edad;
    } while(edad <= 0);

    try{
        sistema->altaInteresado(email, nombre, apellido, edad);
    } catch (const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
}

void manejarAltaEdificio(ISistema * sistema){
    system("cls");
    string nombre;
    int cantPisos;
    int gastosComunes;
    Zona* zona;

    char* opt = new char[100];

    cout << "Elija uno de los departamentos listados debajo" << endl;
    imprimirDepto(sistema->listarDepartamentos());
    cin >> opt;
    try{
        sistema->elegirDepartamento(opt);
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
   
    cout << "Elija una de las zonas listadas debajo" << endl;
    imprimirZonasDepto(sistema->listarZonasDepartamento()); // Valentin cambió esto
    
    int optint;

    cin >> optint;

    try{
        sistema->elegirZona(optint);
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    cout << "Va a ingresar un edificio en el sistema" << endl << endl;
    cout << "Ingrese ahora un nombre para el edificio" << endl << endl;
    cin >> nombre;

    do {
        system("cls");
        cout << "Ingrese la cantidad de pisos" << endl << endl;
        cin >> cantPisos;
    } while(cantPisos <= 0);

    do {
        system("cls");
        cout << "Ingrese los gastos comunes" << endl << endl;
        cin >> gastosComunes;
    } while(gastosComunes <= 0);

    try{
        sistema->altaEdificio(nombre, cantPisos, gastosComunes);
        sistema->setDepartamentoActual(NULL);
        sistema->setZonaActual(NULL);

    } catch (const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
}

void manejarAltaPropiedad(ISistema * s){
    system("cls");

    
   //chequear usuario
    if(s->getLoggeado() == NULL){
        system("cls");
        throw runtime_error("No hay un usuario en el sistema");
    }
    Inmobiliaria * inmo = (Inmobiliaria*) s->getLoggeado();
    if(inmo == NULL){
        system("cls");
        throw runtime_error("El usuario ingresado no es Inmobiliaria");
    }

    //elegir departamento
    imprimirDepto(s->listarDepartamentos());
    char* opt = new char[100];
    cout << "Eliga un departamento:" << endl;
    cin >> opt;
    try{
        s->elegirDepartamento(opt);
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
    system("cls");
   

    //elegir zona
    imprimirZonasDepto(s->listarZonasDepartamento()); 
    cout << "Ingresar identificación de la zona:" << endl;
    int numZona;
    cin >> numZona;
    try{
        s->elegirZona(numZona);
    } catch(const exception& e){
        system("cls");
        s->setDepartamentoActual(NULL);
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    cout << "Ingrese tipo de propiedad" << endl;
    cout << "1. Casa" << endl;
    cout << "2. Apartamento" << endl;
    int opcion;
    cin >> opcion;
    system("cls");

    //si es apartamento
    if (opcion == 2) {
        imprimirEdificios(s->listarEdificio());
        cout << "¿Desea seleccionar un nuevo edificio?" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        opcion = 0;
        cin >> opcion;


        //agrega edificio
        if (opcion == 1) {
            system("cls");
            string nombre;
            int pisos, gastosC;
            cout << "Ingrese nombre del edificio" << endl;
            cin >> nombre;
            system("cls");
            do {
                system("cls");
                cout << "Ingrese la cantidad de pisos" << endl << endl;
                cin >> pisos;
            } while(pisos <= 0);

            do {
                system("cls");
                cout << "Ingrese los gastos comunes" << endl << endl;
                cin >> gastosC;
            } while(gastosC <= 0);
            system("cls");
            s->altaEdificio(nombre, pisos, gastosC);         
        }

        else if (opcion == 2) {
            //seleccionar edificio
            system("cls");
            imprimirEdificios(s->listarEdificio());
            cout << "Ingresar identificación del edificio:" << endl;
            int numEdificio;
            cin >> numEdificio;
        
            try{
                s->seleccionarEdificio(numEdificio); 
            } catch(const exception& e) {
                system("cls");
                cout << "Error de ejecución: " << e.what() << endl;
                system("pause");
                s->setDepartamentoActual(NULL);
                s->setZonaActual(NULL);
                return;
            }
        }
        int cantAmb, cantBanos, cantDorm, numero;
        float m2t;
        string calle, ciudad;
        bool garage = false;
        int opcion;
        cout << "Ingresar calle:" << endl;
        cin >> calle; 
        system("cls");
        cout << "Ingresar numero:" << endl;
        cin >> numero;
        system("cls");
        cout << "Ingresar ciudad:" << endl;
        cin >> ciudad;
        system("cls");
        DTDir* dir = new DTDir(calle, numero, ciudad);
       do {
                system("cls");
                cout << "Ingrese la cantidad de ambientes" << endl << endl;
                cin >> cantAmb;
            } while(cantAmb <= 1);
        
        do {
                system("cls");
                cout << "Ingrese la cantidad de banos" << endl << endl;
                cin >> cantBanos;
            } while(cantBanos <= 0);
        do {
                system("cls");
                cout << "Ingrese la cantidad de dormitorios" << endl << endl;
                cin >> cantDorm;
            } while(cantDorm <= 0);
        system("cls");
        cout << "Ingresar si tiene garage:" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        cin >> opcion;
        system("cls");
        if (opcion == 1) 
            garage = true;
            do {
                system("cls");
                cout << "Ingrese metros cuadrados edificados" << endl << endl;
                cin >> m2t;
            } while(m2t <= 0);
            system("cls");
            s->especificacionesApartamento(cantAmb, cantBanos, cantDorm, m2t, garage, dir, s->getEdificioActual(), s->getZonaActual());
        }

        //si es casa
        else if (opcion == 1) {
            int cantAmb, cantBanos, cantDorm, numero;
            float m2v, m2e;
            string ciudad, calle;
            bool garage = false;
            int opcion;
            cout << "Ingresar calle:" << endl;
            cin >> calle;
            system("cls");
            cout << "Ingresar numero:" << endl;
            cin >> numero;
            system("cls");
            cout << "Ingresar ciudad:" << endl;
            cin >> ciudad;
            system("cls");
            DTDir* dir = new DTDir(calle, numero, ciudad);
            do {
                system("cls");
                cout << "Ingrese la cantidad de ambientes" << endl << endl;
                cin >> cantAmb;
            } while(cantAmb <= 1);
        
            do {
                system("cls");
                cout << "Ingrese la cantidad de banos" << endl << endl;
                cin >> cantBanos;
            } while(cantBanos <= 0);

            do {
                system("cls");
                cout << "Ingrese la cantidad de dormitorios" << endl << endl;
                cin >> cantDorm;
            } while(cantDorm <= 0);

            system("cls");
            cout << "Ingresar si tiene garage:" << endl;
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            cin >> opcion;
            system("cls");
            if (opcion == 1) 
                garage = true;

            do {
                system("cls");
                cout << "Ingrese metros cuadrados edificados" << endl << endl;
                cin >> m2e;
            } while(m2e <= 0);

            do {
                system("cls");
                cout << "Ingrese metros cuadrados verdes" << endl << endl;
                cin >> m2v;
            } while(m2v < 0);
                system("cls");
                s->especificacionesCasa(cantAmb, cantDorm, cantBanos, garage, dir, m2e, s->getZonaActual(), m2v);
            }


            cout << "1. Poner en venta" << endl;
            cout << "2. Poner en alquiler" << endl;
            cout << "3. Poner en venta y alquiler" << endl;
            int option;
            cin >> option;
            system("cls");
            if (option == 1) {
                float valorV;
                cout << "Ingrese valor de la venta" << endl;
                cin >> valorV;
                system("cls");
                s->ponerEnVenta(valorV);
                cout << "La propiedad ha sido ingresada exitosamente, su codigo de propiedad es "<< s->getPropiedadActual()->getCodigo() << endl;
                return;
            }
            if (option == 2) {
                float valorA;
                cout << "Ingrese valor del alquiler" << endl;
                cin >> valorA;
                system("cls");
                s->ponerEnAlquiler(valorA);
                cout << "La propiedad ha sido ingresada exitosamente, su codigo de propiedad es "<< s->getPropiedadActual()->getCodigo() << endl;
                return;
            }
            if (option == 3) {
                float valorA;
                float valorV;
                cout << "Ingrese valor de la venta" << endl;
                cin >> valorV;
                system("cls");
                cout << "Ingrese valor del alquiler" << endl;
                cin >> valorA;
                s->ponerEnAlquiler(valorA);
                s->ponerEnVenta(valorV);
                cout << "La propiedad ha sido ingresada exitosamente, su codigo de propiedad es "<< s->getPropiedadActual()->getCodigo() << endl;
                return;
            }
           
    s->setPropiedadActual(NULL);
    s->setDepartamentoActual(NULL);
    s->setZonaActual(NULL);
    s->setEdificioActual(NULL);
}

void manejarConsultarPropiedad(ISistema * sistema){
    system("cls");
    char* opt = new char[100];

    cout << "Elija uno de los departamentos listados debabajo" << endl;
    imprimirDepto(sistema->listarDepartamentos());
    cout << "Ingrese la letra correspondiente: ";
    cin >> opt;
    
    try{
        sistema->elegirDepartamento(opt);
    } catch(const exception& e){
        cout << "Error de ejecución: " << e.what() << endl;
        return;
    }

    system("cls");
   
    cout << "Elija una de las zonas listadas debajo" << endl;
    imprimirZonasDepto(sistema->listarZonasDepartamento());
    
    string optstr;
    int optint;

    while (true){
        cout << "Ingrese el código de la zona: ";
        cin >> optstr;
        try {
            optint = stoi(optstr);
            break;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingrese un código de zona válido" << endl;
        }
    }

    try{
        sistema->elegirZona(optint);
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    system("cls");

    cout << "Elija una de las propiedades listadas debajo" << endl;
    
    try{
        imprimirProps(sistema->listarPropiedades());
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    cout << "Ingrese el codigo de la propiedad: ";
    cin >> optint;

    system("clear");

    try{
        cout << "---Propiedad Detallada---" << endl << endl;
        cout << sistema->verDetallesPropiedad(optint);
        system("pause");
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    system("cls");

}


void manejarModificarPropiedad(ISistema * sistema){
    //vale
    system("cls");

    cout << "Selecciona una de las siguientes propiedades para modificarla" << endl;
    
    try{
        imprimirProps(sistema->listarPropiedadesInmo());
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    string optstr;
    int codigoProp;

    while (true){
        cout << "Ingresa el código de la propiedad: ";
        cin >> optstr;
        try {
            codigoProp = stoi(optstr);
            break;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingrese un código de propiedad válido" << endl;       
        }
    }

    try{
        sistema->seleccionarPropiedadInmobiliaria(codigoProp);
    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

    DTTipoProp tipoProp = sistema->getDTTipoProp();

    int cantAmbientes, cantDormitorios, cantBanios;
    bool tieneGaraje;

    // Para la dirección
    DTDir * direccion;
    string calle, ciudad;
    int numero;


    system("cls");

    while (true){
        cout << "Ingresa la cantidad de ambientes: ";
        cin >> optstr;
        try {
            cantAmbientes = stoi(optstr);
            if (cantAmbientes >= 1){
                break;
            }
            cout << endl << "Por favor, ingresa una cantidad de ambientes válida (mayor a 0)" << endl;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingresa una cantidad numérica" << endl;
        }
    }

    system("cls");

    while (true){
        cout << "Ingresa la cantidad de dormitorios: ";
        cin >> optstr;
        try {
            cantDormitorios = stoi(optstr);
            if (cantDormitorios >= 0){
                break;
            }
            cout << endl << "Por favor, ingresa una cantidad de dormitorios válida (0 o más)" << endl;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingresa una cantidad numérica" << endl;
        }
    }

    system("cls");

    while (true){
        cout << "Ingresa la cantidad de baños: ";
        cin >> optstr;
        try {
            cantBanios = stoi(optstr);
            if (cantBanios >= 0){
                break;
            }
            cout << endl << "Por favor, ingresa una cantidad de baños válida (0 o más)" << endl;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingresa una cantidad numérica" << endl;
        }
    }

    system("cls");

    while (true){
        cout << "Indica a continuación si la propiedad tiene garaje" << endl << "1 - No tiene garaje" << endl << "2 - Tiene Garaje" << endl << endl << "Ingresa tu opción: ";
        cin >> optstr;
        try {
            tieneGaraje = stoi(optstr)-1;
            if (tieneGaraje == 0 || tieneGaraje == 1){
                break;
            }
            cout << endl << "Por favor, ingresa una opción válida (1 o 2)" << endl;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingresa un valor numérico" << endl;
        }
    }

    system("cls");

    cout << "Dirección de la propiedad" << endl << "Especifica la ciudad: ";
    do{
        cin.ignore();
        getline(cin, ciudad);
    } while(ciudad == "");

    cout << endl << "Especifica la calle: ";
    do{
        cin.ignore();
        getline(cin, calle);
    } while(calle == "");

    cout << endl;

    while (true){
        cout << "Especifica el número: ";
        cin >> optstr;
        try {
            numero = stoi(optstr);
            if (numero > 0){
                break;
            }
            cout << endl << "Por favor, ingresa un valor válido (mayor a 0)" << endl;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingresa un valor numérico" << endl;
        }
    }

    direccion = new DTDir(calle, numero, ciudad);

    system("cls");

    if (tipoProp == DTTipoProp::apartamento){
        float m2Totales;
        
        while (true){
            cout << "Introduce los m2Totales: ";
            cin >> optstr;
            try {
                m2Totales = stof(optstr);
                if (m2Totales > 0){
                    break;
                }
                cout << endl << "Por favor, ingresa un valor válido (mayor a 0)" << endl;
            } catch(const exception& e) {
                cout << endl << "Por favor, ingresa una cantidad numérica" << endl;
            }
        }

        try{
            sistema->modificarApartamento(cantAmbientes, cantDormitorios, cantBanios, tieneGaraje, direccion, m2Totales);
        } catch(const exception& e){
            system("cls");
            cout << "Error de ejecución: " << e.what() << endl;
            system("pause");
            return;
        }

        cout << "Apartamento modificado de manera exitosa!" << endl;

    } else {
        float m2Edificados, m2Verdes;

        while (true){
            cout << "Introduce los m2Edificados: ";
            cin >> optstr;
            try {
                m2Edificados = stof(optstr);
                if (m2Edificados > 0){
                    break;
                }
                cout << endl << "Por favor, ingresa un valor válido (mayor a 0)" << endl;
            } catch(const exception& e) {
                cout << endl << "Por favor, ingresa una cantidad numérica" << endl;
            }
        }

        system("cls");

        while (true){
            cout << "Introduce los m2Verdes: ";
            cin >> optstr;
            try {
                m2Verdes = stof(optstr);
                if (m2Verdes >= 0){
                    break;
                }
                cout << endl << "Por favor, ingresa un valor válido (mayor o igual a 0)" << endl;
            } catch(const exception& e) {
                cout << endl << "Por favor, ingresa una cantidad numérica" << endl;
            }
        }

        try{
            sistema->modificarCasa(cantAmbientes, cantDormitorios, cantBanios, tieneGaraje, direccion, m2Edificados, m2Verdes);
        } catch(const exception& e){
            system("cls");
            cout << "Error de ejecución: " << e.what() << endl;
            system("pause");
            return;
        }

        cout << "Casa modificada de manera exitosa!" << endl;

    }
}

void manejarEliminarPropiedad(ISistema * sistema){
    system("cls");

    try {
            imprimirProps(sistema->listarPropiedadesInmo());
        } catch(const exception& e) {
            system("cls");
            cout << "Error: " << e.what() << endl;
            system("pause");
            return;
        }
    
    cout << "¿Qué propiedad te gustaría eliminar?" << endl << endl;
    string codigoProp;
    int codigoNumerico;

    while (true){
        cout << "Ingresa el código de la misma: ";
        cin >> codigoProp;
        try {
            codigoNumerico = stoi(codigoProp);
            break;
        } catch(const exception& e) {
            cout << endl << "Por favor, ingresa un código numérico" << endl;
        }
    }
    
    try {
        sistema->eliminarPropiedad(codigoNumerico);
        system("cls");
        cout << "La propiedad fue removida exitosamente!" << endl;
        system("pause");
    } catch(const exception& e) {
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
}

void manejarEnviarMensajeInteresado(ISistema * sistema){
    system("cls");
    try {

        imprimirDepto(sistema->listarDepartamentos()); // Antes hacía un try-catch con esto

        char * letraDepa = new char[100];
        cout << "Ingrese la letra del Departamento: ";
        cin >> letraDepa;

        sistema->elegirDepartamento(letraDepa); // Antes hacía un try-catch con esto

        system("cls");

        imprimirZonasDepto(sistema->listarZonasDepartamento()); // Antes hacía un try-catch con esto

        string opcion;
        int numZona;

        while (true){
            cout << "Ingrese el codigo de la Zona: ";
            cin >> opcion;
            try {
                numZona = stoi(opcion);
                break;
            } catch(const exception& e) {
                cout << endl << "Por favor, ingrese un código de Zona válido" << endl;
            }
        }

        system("cls");

        sistema->elegirZona(numZona); // Antes hacía un try-catch con esto

        imprimirDTChatProps(sistema->listarChatProp()); // Antes hacía un try-catch con esto

        int codProp;

        while (true){
            cout << "Ingrese el codigo de la Propiedad: ";
            cin >> opcion;
            try {
                codProp = stoi(opcion);
                break;
            } catch(const exception& e) {
                cout << endl << "Por favor, ingrese un código de Propiedad válido" << endl;
            }
        }
        
        sistema->seleccionarPropiedad(codProp); // Antes hacía un try-catch con esto

        Conversacion * conver;

        conver = sistema->getConversacionInteresado(); // Antes hacía un try-catch con esto
        
        if (conver == NULL){
            sistema->nuevoChat();
        }

        system("cls");

        ICollection * mensajes = sistema->getUltimosMensajes();

        if (mensajes->isEmpty()){
            cout << "Aún no hay mensajes en esta conversación." << endl << "Sé el primero en participar!" << endl;
        } else {
            cout << "---Ultimos mensajes---" << endl;
            imprimirDTMensajes(mensajes);
        }

        string mensaje;
        do{
            cin.ignore();
            cout << "Ingrese un Mensaje no vacio" << endl;
            getline(cin, mensaje);
        } while(mensaje == ""); //agregar bucle en caso de q el mensaje sea vacio

        DTFecha * FECHA = getDTFechaActual();
        
        sistema->nuevoMensaje(mensaje, FECHA);

        system("cls");
        cout << "El mensaje se envió de manera exitosa!" << endl;
        system("pause");

        // sistema->setConversacionActual(NULL); // No es necesario
        // sistema->setDepartamentoActual(NULL);
        // sistema->setEdificioActual(NULL);
        // sistema->setPropiedadActual(NULL);
        // sistema->setZonaActual(NULL);

    } catch(const std::exception& e) {
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

}


void manejarEnviarMensajeInmobiliaria(ISistema * sistema){
    //feli
    try{
        system("cls");

        imprimirDTChatProps(sistema->listarChatsInmo());
    
        string respuesta;
        int codigo;

        while (true){
            cout << "Ingrese el código de la conversación que desee seleccionar: ";
            cin >> respuesta;
            try {
                codigo = stoi(respuesta);
                break;
            } catch(const exception& e) {
                cout << endl << "Por favor, ingrese un código de conversación válido" << endl;
            }
        }

        system("cls");

        sistema->seleccionarConversacionInmo(codigo);

        cout << "---Ultimos mensajes---" << endl;
        imprimirDTMensajes(sistema->getUltimosMensajes());

        cout << "Ingresa el contenido del Mensaje: " << endl;
        do{
            cin.ignore();
            cout << "Ingrese un Mensaje no vacio" << endl;
            getline(cin, respuesta);
        } while(respuesta == ""); //agregar bucle en caso de q el mensaje sea vacio

        DTFecha * fecha = getDTFechaActual();
        sistema->nuevoMensaje(respuesta, fecha);

        system("cls");
        cout << "El mensaje fue agregado de manera exitosa!" << endl;
        system("pause");

    } catch(const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }

}

void manejarReporte(ISistema * sistema){
    system("cls");
    ICollection * reportes;
    try {
        reportes = sistema->obtenerReporte();
    } catch (const exception& e){
        system("cls");
        cout << "Error de ejecución: " << e.what() << endl;
        system("pause");
        return;
    }
    int i = 1;
    IIterator * it = reportes->getIterator();
    while(it->hasCurrent()){
        DTReporte * reporte = (DTReporte*) it->getCurrent();
        cout << "[REPORTE " << i << "]" << endl;
        // cout << reporte << endl << endl;
        cout << "Inmobiliaria: " << reporte->getInmo() << endl << endl;
        IIterator * it2 = reporte->getLineas()->getIterator();
        while(it2->hasCurrent()){
            DTLineaReporte * linea = (DTLineaReporte*) it2->getCurrent();
            // cout << linea << endl << endl;
            cout << "Departamento: " << linea->getLetraDep() << endl;
            cout << "Código de la zona: " << linea->getCodigoZona() << endl;
            cout << "Cantidad de casas: " << linea->getCantCasas() << endl;
            cout << "Cantidad de apartamentos: " << linea->getCantApartamentos() << endl << endl;
            it2->next();
        }
        i++;
        it->next();
    }
}

void menu(ISistema * sistema){
    string opt;
    do{

        do{
            opt = "";
            sistema->setConversacionActual(NULL);
            sistema->setDepartamentoActual(NULL);
            sistema->setEdificioActual(NULL);
            sistema->setPropiedadActual(NULL);
            sistema->setZonaActual(NULL);
            system("cls");
            cout << "Necesita iniciar sesión en el sistema" << endl << endl;
            cout << "1-Iniciar sesión" << endl;
            cout << "exitsystem-Salir del sistema" << endl << endl;
            cin >> opt;
        } while (opt != "1" && opt != "exitsystem");

        if(opt != "exitsystem"){
            bool sesionCorrecta;
            do{
                sesionCorrecta = manejarIniciarSesion(sistema);
                system("pause");
            } while(!sesionCorrecta);

            if(sesionCorrecta){
                Inmobiliaria * inmo = dynamic_cast<Inmobiliaria*>(sistema->getLoggeado());
                Administrador * admin = dynamic_cast<Administrador*>(sistema->getLoggeado());
                Interesado* interesado = dynamic_cast<Interesado*>(sistema->getLoggeado());

                if(admin != NULL){
                    do{
                        do{
                            system("cls");
                            opt = "";
                            sistema->setConversacionActual(NULL);
                            sistema->setDepartamentoActual(NULL);
                            sistema->setEdificioActual(NULL);
                            sistema->setPropiedadActual(NULL);
                            sistema->setZonaActual(NULL);
                            cout << "Elija una función del sistema" << endl << endl;
                            cout << "1-Cerrar sesión" << endl;
                            cout << "2-Alta inmobiliaria" << endl;
                            cout << "3-Alta interesado" << endl;
                            cout << "4-Obtener reporte de inmobiliaria" << endl << endl;
                            cin >> opt;
                        } while(opt != "1" && opt != "2" && opt != "3"  && opt != "4");

                        if(opt == "1"){
                            sistema->cerrarSesion();
                            continue;
                        } else if(opt == "2"){
                            manejarAltaInmobiliaria(sistema);
                            system("pause");
                        } else if (opt == "3"){
                            manejarAltaInteresado(sistema);
                            system("pause");
                        } else if (opt == "4"){
                            manejarReporte(sistema);
                            system("pause");
                        } else {
                            throw invalid_argument("No se encontró una opción válida");
                        }
                    } while(opt != "1");
                } else if(inmo != NULL) {
                    do{
                        do{
                            system("cls");
                            opt = "";
                            sistema->setConversacionActual(NULL);
                            sistema->setDepartamentoActual(NULL);
                            sistema->setEdificioActual(NULL);
                            sistema->setPropiedadActual(NULL);
                            sistema->setZonaActual(NULL);
                            cout << "Elija una función del sistema" << endl << endl;
                            cout << "1-Cerrar sesión" << endl;
                            cout << "2-Alta edificio" << endl;
                            cout << "3-Alta propiedad" << endl;
                            cout << "4-Consultar propiedad" << endl;
                            cout << "5-Modificar propiedad" << endl;
                            cout << "6-Eliminar propiedad" << endl;
                            cout << "7-Enviar mensaje inmobiliaria" << endl << endl;
                            cin >> opt;
                        } while(opt != "1" && opt != "2" && opt != "3" && opt != "4" && opt != "5" && opt != "6" && opt != "7");

                        if (opt == "1"){
                            sistema->cerrarSesion();
                            continue;
                        } else if(opt == "2"){
                            manejarAltaEdificio(sistema);
                            system("pause");
                        } else if (opt == "3"){
                            manejarAltaPropiedad(sistema);
                            system("pause");
                        } else if (opt == "4"){
                            manejarConsultarPropiedad(sistema);
                            system("pause");
                        } else if (opt == "5"){
                            manejarModificarPropiedad(sistema);
                            system("pause");
                        } else if (opt == "6"){
                            manejarEliminarPropiedad(sistema);
                            system("pause");
                        } else if (opt == "7"){
                            manejarEnviarMensajeInmobiliaria(sistema);
                        } else {
                            throw invalid_argument("No se encontró una opción válida");
                        }
                    } while(opt != "1");
                } else if (interesado != NULL){
                    do{
                        do{
                            system("cls");
                            opt = "";
                            sistema->setConversacionActual(NULL);
                            sistema->setDepartamentoActual(NULL);
                            sistema->setEdificioActual(NULL);
                            sistema->setPropiedadActual(NULL);
                            sistema->setZonaActual(NULL);
                            cout << "Elija una función del sistema" << endl << endl;
                            cout << "1-Cerrar sesión" << endl;
                            cout << "2-Consultar propiedad" << endl;
                            cout << "3-Enviar mensaje interesado" << endl << endl;
                            cin >> opt;
                        } while(opt != "1" && opt != "2" && opt != "3");

                        if(opt == "1"){
                            sistema->cerrarSesion();
                            continue;
                        } else if(opt == "2"){
                            manejarConsultarPropiedad(sistema);
                            system("pause");
                        } else if (opt == "3"){
                            manejarEnviarMensajeInteresado(sistema);
                            system("pause");
                        } else {
                            throw invalid_argument("No se encontró una opción válida");
                        }
                    }while(opt != "1");
                }
            }
        }
    } while(opt != "exitsystem");
}


int main() {

    ISistema * sistema = (new Factory())->getISistema();
    

    // DTs
    // string calle, int numero, string ciudad
    DTDir * dir1 = new DTDir("Rivera", 8, "Santa Lucia");
    DTDir * dir2 = new DTDir("Sarandi", 232, "Santa Lucia");
    DTDir * dir3 = new DTDir("Treinta y Tres", 403, "Canelones");
    DTDir * dir4 = new DTDir("18 de Julio", 123, "Santa Lucia");
    DTDir * dir5 = new DTDir("Rocha", 654, "Montevideo");
    DTDir * dir6 = new DTDir("Miranda", 666, "Canelones");
    DTDir * dir7 = new DTDir("Brum", 42, "Juanico");
    DTDir * dir8 = new DTDir("Herrera", 69, "Durazno");
    // USUARIOS

    // ADMINISTRADORES
    char* email1 = "a";
    Administrador * nuevoAdmin = new Administrador(email1, "abc");
    ICollectible * nuevo = (ICollectible*) nuevoAdmin;

    IKey * key = new String(nuevoAdmin->getCorreoEletronico());

    sistema->getUsuarios()->add(key, nuevo);

    // INMOBILIARIAS
    char * email2 = "inmo1";
    char * email3 = "inmo2";
    Inmobiliaria * inmo1 = new Inmobiliaria(email2, "Salva Enterprise", dir6);
    Inmobiliaria * inmo2 = new Inmobiliaria(email3, "Tesla", dir7);

    IKey * keyusr2 = new String(inmo1->getCorreoEletronico());
    IKey * keyusr3 = new String(inmo2->getCorreoEletronico());

    ICollectible * usr2 = (ICollectible*) inmo1;
    ICollectible * usr3 = (ICollectible*) inmo2;

    sistema->getUsuarios()->add(keyusr2, usr2);
    sistema->getUsuarios()->add(keyusr3, usr3);
    
    // INTERESADOS
    char * email4 = "int1";
    char * email5 = "int2";
    Interesado * int1 = new Interesado(email4, "Nadia", "Gorría", 42);
    Interesado * int2 = new Interesado(email5, "José", "Soto", 13);

    IKey * keyusr4 = new String(int1->getCorreoEletronico());
    IKey * keyusr5 = new String(int2->getCorreoEletronico());

    ICollectible * usr4 = (ICollectible*) int1;
    ICollectible * usr5 = (ICollectible*) int2;

    sistema->getUsuarios()->add(keyusr4, usr4);
    sistema->getUsuarios()->add(keyusr5, usr5);

    // DEPARTAMENTOS
    Departamento * dep1 = new Departamento("A", "Canelones");
    Departamento * dep2 = new Departamento("S", "Montevideo");
    Departamento * dep3 = new Departamento("M", "San Jose");

    // ZONAS
    // Zonas de dep1
    Zona* zona1 = new Zona(1, "Santa Lucia", "A");
    Zona* zona2 = new Zona(2, "Canelones", "A");
    Zona* zona3 = new Zona(3, "Juanico", "A");

    // Zonas de dep2
    Zona* zona4 = new Zona(4, "Malvin Norte", "S"); // Vacio
    Zona* zona5 = new Zona(5, "Prado", "S"); // Vacio
    Zona* zona6 = new Zona(6, "Ciudad Vieja", "S"); // Vacio

    // Zonas de dep3
    Zona* zona7 = new Zona(7, "Rodriguez", "M"); // Vacio
    Zona* zona8 = new Zona(8, "Prado", "M"); // Vacio
    Zona* zona9 = new Zona(9, "Ciudad Vieja", "M"); // Vacio

    ICollectible * zonacol1 = (ICollectible*) zona1;
    ICollectible * zonacol2 = (ICollectible*) zona2;
    ICollectible * zonacol3 = (ICollectible*) zona3;
    ICollectible * zonacol4 = (ICollectible*) zona4;
    ICollectible * zonacol5 = (ICollectible*) zona5;
    ICollectible * zonacol6 = (ICollectible*) zona6;
    ICollectible * zonacol7 = (ICollectible*) zona7;
    ICollectible * zonacol8 = (ICollectible*) zona8;
    ICollectible * zonacol9 = (ICollectible*) zona9;

    IKey * keyzona1 = new Integer(1);
    IKey * keyzona2 = new Integer(2);
    IKey * keyzona3 = new Integer(3);
    IKey * keyzona4 = new Integer(4);
    IKey * keyzona5 = new Integer(5);
    IKey * keyzona6 = new Integer(6);
    IKey * keyzona7 = new Integer(7);
    IKey * keyzona8 = new Integer(8);
    IKey * keyzona9 = new Integer(9);

    dep1->getZonas()->add(keyzona1, zona1);
    dep1->getZonas()->add(keyzona2, zona2);
    dep1->getZonas()->add(keyzona3, zona3);
    dep2->getZonas()->add(keyzona4, zona4);
    dep2->getZonas()->add(keyzona5, zona5);
    dep2->getZonas()->add(keyzona6, zona6);
    dep3->getZonas()->add(keyzona7, zona7);
    dep3->getZonas()->add(keyzona8, zona8);
    dep3->getZonas()->add(keyzona9, zona9);

    IKey * keydepa1 = new String(dep1->getLetra());
    IKey * keydepa2 = new String(dep2->getLetra());
    IKey * keydepa3 = new String(dep3->getLetra());

    sistema->getDepartamentos()->add(keydepa1, dep1);
    sistema->getDepartamentos()->add(keydepa2, dep2);
    sistema->getDepartamentos()->add(keydepa3, dep3);

    // Creamos edificios
    // int codigo, string nombre, int cantPisos, int gastosComunes, Zona* zona
    Edificio* edi1 = new Edificio(1, "Hotel California", 10, 20000, zona1);
    Edificio* edi2 = new Edificio(2, "Hotel Lamas", 2, 10000, zona1); // Vacio
    Edificio* edi3 = new Edificio(1, "Motel Oasis", 3, 7500, zona2);
    Edificio* edi4 = new Edificio(2, "Hotel Disney", 40, 100000, zona2); // Vacio
    Edificio* edi5 = new Edificio(3, "Empire State", 100, 50000, zona2); // Vacio
    Edificio* edi6 = new Edificio(1, "Luna y Mar", 9, 50000, zona3); // Vacio

    zona1->agregarEdificio(edi1);
    zona1->agregarEdificio(edi2);
    zona2->agregarEdificio(edi3);
    zona2->agregarEdificio(edi4);
    zona2->agregarEdificio(edi5);
    zona3->agregarEdificio(edi6);

    // int _codigo, int _cantAmbiente, int _cantDormitorios, int _cantBanios, float _m2Edificios, DTDir * dir, bool _tieneGaraje, Zona * _zona, float _m2Verdes)

    Casa * casa1 = zona1->crearCasa(2, 1, 1, 50, dir1, true, 20, inmo1);

    zona1->enlazarPropiedad(casa1);

    Casa * casa2 = zona1->crearCasa(4, 2, 2, 100, dir2, false, 40, inmo1);

    zona1->enlazarPropiedad(casa2);

    Casa * casa3 = zona2->crearCasa(3, 1, 2, 70, dir3, true, 30, inmo2);

    zona2->enlazarPropiedad(casa3);

    // int _codigo, int _cantAmbiente, int _cantDormitorios, int _cantBanios, float _m2Edificios, DTDir * dir, bool _tieneGaraje, Zona * _zona, Edificio * _edificio

    Apartamento * ap1 = edi1->crearApartamento(2, 3, 2, 90, dir4, false, inmo1);

    zona1->enlazarPropiedad(ap1);
    edi1->enlazarPropiedad(ap1);

    Apartamento * ap2 = edi1->crearApartamento(3, 2, 1, 70, dir8, false, inmo2);

    zona1->enlazarPropiedad(ap2);
    edi1->enlazarPropiedad(ap2);

    Apartamento * ap3 = edi3->crearApartamento(1, 1, 1, 20, dir5, true, inmo2);
    
    zona2->enlazarPropiedad(ap3);
    edi3->enlazarPropiedad(ap3);

    inmo1->agregarPropiedad(casa1);

    inmo1->agregarPropiedad(casa2);

    inmo2->agregarPropiedad(casa3);

    inmo1->agregarPropiedad(ap1);

    inmo2->agregarPropiedad(ap2);

    inmo2->agregarPropiedad(ap3);


    menu(sistema);

    system("pause");
    return 0;
}