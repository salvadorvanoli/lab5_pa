all: String.o Integer.o ICollectible.o IKey.o IIterator.o OrderedKey.o ICollection.o IDictionary.o ListNode.o ListIterator.o List.o OrderedDictionaryEntry.o OrderedDictionary.o DTHora.o DTFecha.o DTDir.o DTChatProp.o DTDepartamento.o DTZona.o DTEdificio.o DTMensaje.o DTInmobiliaria.o DTPropiedad.o DTPropiedadDetallada.o DTLineaReporte.o DTReporte.o Usuario.o Administrador.o Interesado.o Mensaje.o Conversacion.o Propiedad.o Venta.o Alquiler.o Inmobiliaria.o Casa.o Apartamento.o Edificio.o Zona.o Departamento.o Sistema.o main.o
	g++ String.o Integer.o ICollectible.o IKey.o IIterator.o OrderedKey.o ICollection.o IDictionary.o ListNode.o ListIterator.o List.o OrderedDictionaryEntry.o OrderedDictionary.o DTHora.o DTFecha.o DTDir.o DTChatProp.o DTDepartamento.o DTZona.o DTEdificio.o DTMensaje.o DTInmobiliaria.o DTPropiedad.o DTPropiedadDetallada.o DTLineaReporte.o DTReporte.o Usuario.o Administrador.o Interesado.o Mensaje.o Conversacion.o Propiedad.o Venta.o Alquiler.o Inmobiliaria.o Casa.o Apartamento.o Edificio.o Zona.o Departamento.o Sistema.o main.o -o programa.exe

# No puse el archivo DTTipoProp ni DTEstadoProp

String.o:
	g++ -c ICollection/String.cpp

Ingeger.o:
	g++ -c ICollection/Integer.cpp

ICollectible.o:
	g++ -c ICollection/interfaces/ICollectible.cpp

IKey.o:
	g++ -c ICollection/interfaces/IKey.cpp

IIterator.o: ICollectible.o
	g++ -c ICollection/interfaces/IIterator.cpp

OrderedKey.o: IKey.o
	g++ -c ICollection/interfaces/OrderedKey.cpp

ICollection.o: IIterator.o
	g++ -c ICollection/interfaces/ICollection.cpp

IDictionary.o: ICollectible.o IKey.o IIterator.o
	g++ -c ICollection/interfaces/IDictionary.cpp

ListNode.o: ICollection.o
	g++ -c ICollection/collections/ListNode.cpp

ListIterator.o: ListNode.o
	g++ -c ICollection/collections/ListIterator.cpp

List.o: ListNode.o
	g++ -c ICollection/collections/List.cpp

OrderedDictionaryEntry.o: ICollectible.o OrderedKey.o
	g++ -c ICollection/collections/OrderedDictionaryEntry.cpp

OrderedDictionary.o: IDictionary.o ListNode.o OrderedDictionaryEntry.o
	g++ -c ICollection/collections/OrderedDictionary.cpp

DTHora.o:
	g++ -c cppfiles/DTHora.cpp

DTFecha.o: DTHora.o
	g++ -c cppfiles/DTFecha.cpp

DTDir.o:
	g++ -c cppfiles/DTDir.cpp

DTChatProp.o: ICollectible.o DTDir.o
	g++ -c cppfiles/DTChatProp.cpp

DTDepartamento.o: ICollectible.o
	g++ -c cppfiles/DTDepartamento.cpp

DTZona.o: ICollectible.o
	g++ -c cppfiles/DTZona.cpp

DTEdificio.o: ICollectible.o
	g++ -c cppfiles/DTEdificio.cpp

DTMensaje.o: ICollectible.o DTFecha.o
	g++ -c cppfiles/DTMensaje.cpp

DTInmobiliaria.o: ICollectible.o DTDir.o
	g++ -c cppfiles/DTInmobiliaria.cpp

DTPropiedad.o: ICollectible.o DTDir.o
	g++ -c cppfiles/DTPropiedad.cpp

DTPropiedadDetallada.o: DTPropiedad.o DTInmobiliaria.o
	g++ -c cppfiles/DTPropiedadDetallada.cpp

DTLineaReporte.o: ICollectible.o
	g++ -c cppfiles/DTLineaReporte.cpp

DTReporte.o: ICollectible.o IIterator.o ICollection.o DTInmobiliaria.o DTLineaReporte.o
	g++ -c cppfiles/DTReporte.cpp

Usuario.o: ICollectible.o
	g++ -c cppfiles/Usuario.cpp

Administrador.o: Usuario.o
	g++ -c cppfiles/Administrador.cpp

Interesado.o: Usuario.o
	g++ -c cppfiles/Interesado.cpp

Mensaje.o: ICollectible.o DTFecha.o DTMensaje.o
	g++ -c cppfiles/Mensaje.cpp

Conversacion.o: ICollectible.o IIterator.o ICollection.o DTMensaje Mensaje.o Interesado.o
	g++ -c cppfiles/Conversacion.cpp

Propiedad.o: Integer.o ICollectible.o IKey.o IIterator.o IDictionary.o DTDir.o
	g++ -c cppfiles/Propiedad.cpp

Venta.o: ICollectible.o Propiedad.o
	g++ -c cppfiles/Venta.cpp

Alquiler.o: ICollectible.o Propiedad.o
	g++ -c cppfiles/Alquiler.cpp

# ME QUEDE ACA

Inmobiliaria.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Inmobiliaria.cpp

Casa.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Casa.cpp

Apartamento.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Apartamento.cpp

Edificio.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Edificio.cpp

Zona.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Zona.cpp

Departamento.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Departamento.cpp

Sistema.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c cppfiles/Sistema.cpp

main.o:
	g++ -c main.cpp

clean:
	del /Q String.o Integer.o ICollectible.o IKey.o IIterator.o OrderedKey.o ICollection.o IDictionary.o ListNode.o ListIterator.o List.o OrderedDictionaryEntry.o OrderedDictionary.o DTHora.o DTFecha.o DTDir.o DTChatProp.o DTDepartamento.o DTZona.o DTEdificio.o DTMensaje.o DTInmobiliaria.o DTPropiedad.o DTPropiedadDetallada.o DTLineaReporte.o DTReporte.o Usuario.o Administrador.o Interesado.o Mensaje.o Conversacion.o Propiedad.o Venta.o Alquiler.o Inmobiliaria.o Casa.o Apartamento.o Edificio.o Zona.o Departamento.o Sistema.o main.o programa.exe

run:
	make clean
	make
	cls
	programa.exe