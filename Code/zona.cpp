#include "zona.h"

void Zona::addObjecte(int id){
	Zona::objectes.push_back(id);
}

void Zona::rmObjecte(int id){
	Zona::objectes.remove(id);
}

std::list<int > Zona::getObjs(){
	return Zona::objectes;
}

void Zona::addZonaPropera(std::string direccio, int zona){
	properes.insert(std::pair<std::string, int>(direccio, zona));
}

bool Zona::getZona(std::string direccio, int& zona){
	std::map<std::string, int>::iterator it = properes.find(direccio);

	if (it != Zona::properes.end()){
		zona = it->second;
		return true;
	}
	else return false;
}

std::string Zona::getNom(){
	return Zona::nom;
}

std::string Zona::getDescripcio(){
	return Zona::descripcio;
}
