/*
 * Tablero.cpp
 *
 *  Created on: Jun 1, 2022
 *      Author: juli
 */

#include <iostream>
#include "Tablero.h"

Tablero :: Tablero(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo){
	if(xMaximo < 1 || zMaximo < 1 || yMaximo < 1){
		throw "Los valores ingresados no son validos";
	}
	this->casilleros = new Lista<Lista<Lista<Casillero*>*>*>;
	this->xMaximo = xMaximo;
	this->yMaximo = yMaximo;
	this->zMaximo = zMaximo;
	//int contador = 0;

	//define que parte del suelo es tierra y cual es agua.
	unsigned int tierra;
	if(yMaximo%2==0){
		tierra = yMaximo/2;
	} else {
		tierra = (yMaximo + 1)/2;
	}

	//esta función debería estar con la de abajo (que agrega los casilleros)
	casilleros->iniciarCursor();
	while(casilleros->avanzarCursor()){
		Lista<Lista<Casillero*>*> *ejeZ = new Lista<Lista<Casillero*>*>;
		ejeZ->iniciarCursor();
		while(ejeZ->avanzarCursor()){
			Lista<Casillero*> *ejeY = new Lista<Casillero*>;
			ejeY->iniciarCursor();
			while(ejeY->avanzarCursor()){
				Casillero* casillero = ejeY->obtenerCursor();
				for(unsigned int i = -1; i <= 1; i++){
					for(unsigned int j = -1; j <= 1; j++){
						for(unsigned int k = -1; k <= 1; k++){
							if(i != 0 && j != 0 && k != 0){
								Casillero* casilleroVecino = getCasillero(casillero->getPosicionEnX() + i, casillero->getPosicionEnY() + j, casillero->getPosicionEnZ() + k);
								casilleroVecino->setVecino(casilleroVecino, i, j, k);
							}
						}
					}
				}
			}
		}
	}


	for(unsigned int z=1; z <= zMaximo; z++){
		Lista<Lista<Casillero*>*> *ejeZ = new Lista<Lista<Casillero*>*>;

		for(unsigned int y=1; y<= yMaximo; y++){

			Lista<Casillero*> *ejeY = new Lista<Casillero*>;

			for(unsigned int x=1; x<= xMaximo; x++){
				if(z==1){
					if(y <= tierra){
						Casillero* nuevoCasillero = new Casillero(x, y, z, Tierra);
						ejeY->agregar(nuevoCasillero);
					} else {
						Casillero* nuevoCasillero = new Casillero(x, y, z, Agua);
						ejeY->agregar(nuevoCasillero);
					}
				} else {
					Casillero* nuevoCasillero = new Casillero(x, y, z, Aire);
					ejeY->agregar(nuevoCasillero);
				}

				//contador++;
			}

			ejeZ->agregar(ejeY);
		}
		this->casilleros->agregar(ejeZ);
	}
	//std::cout << contador << std::endl;
}

Lista<Casillero*>* Tablero :: obtenerCasillerosVecinos(int x, int y, int z){
	Casillero* casillero = this->getCasillero(x,y,z);
	Lista<Casillero*>* vecinos = new Lista<Casillero*>;
	Casillero* casilleroVecino;
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			for(int k = -1; k <= 1; k++){
				if(i != 0 || j != 0 || k != 0){
						int posX = casillero->getPosicionEnX() + i;
						int posY = casillero->getPosicionEnY() + j;
						int posZ = casillero->getPosicionEnZ() + k;
						casilleroVecino = this->getCasillero(posX, posY, posZ);
						vecinos->agregar(casilleroVecino);
					}
				}
			}
		}
		return vecinos;
}


Casillero* Tablero :: getCasillero(unsigned int x, unsigned int y, unsigned int z){
	if(!this->verificarValoresIngresados(x, y, z)){
		throw "Los valores ingresados no son validos";
	}
	return this->casilleros->obtener(z)->obtener(y)->obtener(x);
}


void Tablero :: setFicha(unsigned int x, unsigned int y, unsigned int z, Ficha* ficha){
	if(!this->verificarValoresIngresados(x, y, z)){
		throw "Los valores ingresados no son validos";
	}
	this->casilleros->obtener(z)->obtener(y)->obtener(x)->setFicha(ficha);
}

bool Tablero :: verificarValoresIngresados(unsigned int x, unsigned int y, unsigned int z){
	bool devolver = true;
	if(x < 1 || y < 1 || z < 1){
		devolver = false;
	}
	else if(x > this->xMaximo || y > this->yMaximo || z > this->zMaximo){
		devolver = false;
	}
	return devolver;
}


void Tablero :: imprimirMapa(){
	this->casilleros->iniciarCursor();
	unsigned int nivel = 1;
	while(this->casilleros->avanzarCursor()){
		std::cout << "nivel:" << nivel <<std::endl;
		Lista<Lista<Casillero*>*>* profundidad = this->casilleros->obtenerCursor();
		profundidad->iniciarCursor();
		while(profundidad->avanzarCursor()){
			Lista<Casillero*>* largo = profundidad->obtenerCursor();
			largo->iniciarCursor();
			while(largo->avanzarCursor()){
				if (largo->obtenerCursor()->getTipo() == Tierra){
					std:: cout << "|" << "Tierra"<<"|";
				} else if (largo->obtenerCursor()->getTipo() == Agua) {
					std:: cout << "|" << " Agua "<<"|";
				}else if (largo->obtenerCursor()->getTipo() == Aire){
					std:: cout << "|" << " Aire "<<"|";
				}
			}
			std::cout<<std::endl;
		}
		nivel++;
		std::cout<<std::endl;
	}
}

// esta funcion se implementa con el for para no mover el cursor de la lista
void Tablero :: eliminarJugador(Jugador* jugador, Lista<Jugador*>* jugadores){
	for (unsigned int i = 1; i <= jugadores->contarElementos(); i++){
		Jugador* jugadorDeLista = jugadores->obtener(i);
		if(jugadorDeLista->getNumeroDeJugador() == jugador->getNumeroDeJugador()){
			jugadores->remover(i);
		}
	}
}

//verificar que vuelve a iniciar el cursor de jugadores
void Tablero :: colocarFicha (unsigned int x, unsigned int y, unsigned int z, TipoDeFicha tipo,Jugador* jugador, Tablero* tablero, Lista<Jugador*>* jugadores){
	if(!this->verificarValoresIngresados(x, y, z)){
		throw "valores ingresados no validos";
	}

	//colocar ficha
	if(this->getCasillero(x, y, z)->getFicha()!=NULL){
		//se ocupa de la posicion del soldado que ocupa la casilla actualmente
		std::cout << "Esa casilla estaba ocupada" << std::endl;
		Ficha* ficha = this->getCasillero(x, y, z)->getFicha();
		if(ficha->getTipo() == Soldado){
			ficha->getJugador()->restarSoldado();
			if (ficha->getJugador()->getNumeroDeSoldados() < 1){
				this->eliminarJugador(jugador, jugadores);
			}

		} else  if (ficha->getTipo() == Avion){ // tipo de ficha no es soldado
			jugador->restarAvion();

		} else { // si es barco
			jugador->restarBarco();

		}
		delete ficha;
		//el jugador que se esta moviento (restar un soldao y/o eliminar)
		if (tipo == Soldado){
			jugador->restarSoldado();
			if (ficha->getJugador()->getNumeroDeSoldados() < 1){
				this->eliminarJugador(jugador, jugadores);
			}
		} else if (tipo == Avion){//en caso de avion
			jugador->restarAvion();
		} else { //en caso de barco
			jugador->restarBarco();
		}

		Ficha* fichaAux = NULL;
		this->getCasillero(x, y, z)->setFicha(fichaAux);
		this->getCasillero(x, y, z)->setEstado(Inactivo);

	} else { //si la casilla esta vacia
		if(this->getCasillero(x, y, z)->getTipo() == Tierra &&
				tipo != Soldado){
			throw "El soldado debe colocarse en la tierra";
		}
		if(this->getCasillero(x, y, z)->getTipo() == Agua &&
				tipo != Barco){
			throw "El barco debe estar en el agua";
		}
		if(this->getCasillero(x, y, z)->getTipo() == Aire &&
				tipo != Avion){
			throw "El avion debe estar en el aire";
		}

		Ficha* ficha = new Ficha(tipo, jugador);
		this->getCasillero(x, y, z)->setFicha(ficha);
		if(tipo == Soldado){
			jugador->sumarSoldado();
		} else if (tipo == Avion){//en caso de avion
			jugador->sumarAvion();
		} else { //en caso de barco
			jugador->sumarBarco();
		}
	}

}

Lista<Lista<Lista<Casillero *> *> *> * Tablero :: getCasilleros(){
	return this ->casilleros;
}


int Tablero :: getXMaximo(){
	return this->xMaximo;
}

int Tablero :: getYMaximo(){
	return this->yMaximo;
}

int Tablero :: getZMaximo(){
	return this->zMaximo;
}

Tablero :: ~Tablero(){

	for(unsigned int z = 1; z<= this->zMaximo; z++){
		for(unsigned int y = 1; y <= this->yMaximo; y++){
			for(unsigned int x = 1 ; x <= this->xMaximo; x++){
				delete this->casilleros->obtener(z)->obtener(y)->obtener(x);
			}
			delete this->casilleros->obtener(z)->obtener(y);
		}
		delete this->casilleros->obtener(z);
	}
	delete this->casilleros;

}



