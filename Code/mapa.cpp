#include "mapa.h"




int Mapa::creaZona(std::string nom, std::string descripcio){
	Zona zona (nom, descripcio);
	Mapa::mapa.push_back(zona);
	return Mapa::mapa.size() - 1;
}

bool Mapa::enllacaZona(int zona1, std::string accio, int zona2){

	if (zona1 >= Mapa::mapa.size()) return false;
	Zona z1 = Mapa::mapa[zona1];
	z1.addZonaPropera(accio, zona2);
	Mapa::mapa[zona1] = z1;
	return true;
}

std::string Mapa::getNomZona(int id){
	if (id < Mapa::mapa.size()){
		Zona z = Mapa::mapa[id];
		return z.getNom();
	}
	else return "null";
}

std::string Mapa::getDescrZona(int id){
	if (id < Mapa::mapa.size()){
		Zona z = Mapa::mapa[id];
		return z.getDescripcio();
	}
	else return "null";
}

bool Mapa::desplacaZona(int zona1, std::string accio, int& zona2){
	if (zona1 >= Mapa::mapa.size()) return false;
	else{
		Zona zona = Mapa::mapa[zona1];
		if (zona.getZona(accio, zona2)) return true;
		else return false;
	}
}

std::list<int> Mapa::getObjectes(int zona){
	std::list<int> list_obj;
	if (zona < Mapa::mapa.size()){
		Zona z = Mapa::mapa[zona];
		list_obj = z.getObjs();
	}
	return list_obj;
}

void Mapa::posaObjZona(int zona, int obj){
	if (zona < Mapa::mapa.size()){
		Zona z = Mapa::mapa[zona];
		z.addObjecte(obj);
		Mapa::mapa[zona] = z;
	}
}

void Mapa::llevaObjZona(int zona, int obj){
	if (zona < Mapa::mapa.size()){
		Zona z = Mapa::mapa[zona];
		z.rmObjecte(obj);
		Mapa::mapa[zona] = z;
	}
}

int Mapa::getSize(){
	return Mapa::mapa.size();
}

void Mapa::clear(){
	Mapa::mapa.clear();
}
