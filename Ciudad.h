/*
 * Ciudad.h
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_CIUDAD_H_
#define SRC_CIUDAD_H_
#define DISTANCIA_MAX 500

#include "Estacion.h"
#include "Archivo.h"
#include "util.h"
#include "Coordenadas.h"

class Ciudad
{

private:
	Lista<Estacion *> *estacionesTren;
	Lista<Estacion *> *bocasSubte;
	Lista<Estacion *> *estacionesColectivo;

	bool verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada,
							 Lista<Estacion *> *recorridoDirecto);

	bool buscarPuntoIntermedio(Lista<Estacion *> *estaciones, Estacion *llegada, Coordenadas puntoPartida,
							   Lista<Estacion *> *recorridoCombinado);

	void borrarDatos(Lista<Estacion *> *medioDeTransporte);

	void cargarEstacionesCercanas(Lista<Estacion *> *medioDeTransporte,
								  Lista<Estacion *> *datosCargados, Coordenadas ubicacion);

	void vincularPartidaLlegada(Lista<Estacion *> *estacionesPartida, Lista<Estacion *> *estacionesLlegada, Lista<Estacion *> *recorrido);

	/*post: Imprime algunos campos de Lista<Estacion*> *recorrido
		 * por ej: tipo de transporte|linea/ramal que corresponde|
		 * nombre de parada/estacion|coordenadas geograficas.*/

	void leerRecorrido(Lista<Estacion *> *recorrido);

	bool esMinimo(Lista<Estacion *> *minimo, Lista<Estacion *> &aEvaluar);

	float calcularLongitudRecorrido(Lista<Estacion *> *recorrido)
	{
		recorrido->iniciarCursor();
		float longitud = 0;

		Coordenadas primerPunto = recorrido->obtenerCursor()->verUbicacion();
		recorrido->avanzarCursor();
		Coordenadas segundoPunto = recorrido->obtenerCursor()->verUbicacion();

		longitud = primerPunto.distanciaMetros(segundoPunto);

		while (recorrido->avanzarCursor())
		{
			Coordenadas primerPunto = recorrido->obtenerCursor()->verUbicacion();
			recorrido->avanzarCursor();
			Coordenadas segundoPunto = recorrido->obtenerCursor()->verUbicacion();

			longitud += primerPunto.distanciaMetros(segundoPunto);
		}

		return longitud;
	}

public:
	/*post: crea ciudad con datos de transportes de archivos csv
		 */
	Ciudad();

	const Lista<Estacion *> *verEstacionesTren()
	{
		return this->estacionesTren;
	}
	const Lista<Estacion *> *verBocasSubte()
	{
		return this->bocasSubte;
	}
	const Lista<Estacion *> *verColectivos()
	{
		return this->estacionesColectivo;
	}

	void cargarDatos(Lista<Estacion *> *medioDeTransporte, Lista<std::string> datos, std::string tipoDeTransporte);
	/*pre: Coordenadas geograficas de caba
		 * post:imprime si existe un recorrido directo entre las coordenadas pedidas,
		 *  si no existe busca e imprime un recorrido con combinacion*/
	void verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada);
	/*pre: coordenadas geograficas no vacias y de caba
		 * post: busca e imprime un posible camino entre esos puntos cuando solamente los une un medio de transporte
		 * */
	void verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada);
	/*post: agrega en estacionesCercanas las estaciones/paradas con un rango de 250m a la ubicacionUsuario
		 * como pueden ser bocas de subte, paradas de colectivo, estaciones de tren.. */
	void obtenerEstacionesCercanas(Coordenadas ubicacionUsuario, Lista<Estacion *> *estacionesCercanas);

	~Ciudad();
};

#endif /* SRC_CIUDAD_H_ */
