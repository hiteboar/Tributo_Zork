#include "jugador.h"
#include <string>

Jugador::Jugador(){
	Personatge::vida = 100;
	Personatge::forca = 10;
	pos = 0;
}

std::list<int> Jugador::getInv(){
	return Jugador::inv;
}

void Jugador::setInv(std::list<int> inventari){
	Jugador::inv = inventari;
}

void Jugador::addInv(int obj){
	Jugador::inv.push_back(obj);
}

void Jugador::rmInv(int obj){
	Jugador::inv.remove(obj);
}

void Jugador::setPos(int posicio){
	Jugador::pos = posicio;
}

int Jugador::getPos(){
	return Jugador::pos;
}

std::string Jugador::getInfo(){

	std::string info = "Vida: " + std::to_string(Jugador::vida) + "\nForca: " + std::to_string(Jugador::forca);
	return info;
}

Jugador::~Jugador(){}