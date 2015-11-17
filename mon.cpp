#include "mon.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Mon::Mon(){
	creaNouMon();
}

void Mon::creaNouMon(){
	Mon::mapa.clear();
	Mon::carregaMapa();
}

bool Mon::accio(tipus_accions a, std::string accio_principal, std::string continuacio){
	switch (a){
	case A_OBJECTE:
		return tracta_accio_objecte(accio_principal, continuacio);
		break;
	case A_DESPL:
		if (tracta_accio_desplacament(accio_principal)){
			mostra_info_zona();
			return true;
		}
		else return false;
		break;
	case A_ZONA:
		return tracta_accio_zona(accio_principal, continuacio);
		break;
	case A_LLUITA:
		return tracta_accio_lluita(accio_principal, continuacio);
		break;
	case A_PERSONATGE:
		return tracta_accio_personatge(accio_principal, continuacio);
		break;
	}
}

void Mon::lecturaObjectes(std::istringstream& iss, int id_zona, std::ifstream& f_mapa, int capsa){
	std::string tipus, nom, descr;
	iss >> tipus >> nom >> descr;

	if (tipus.compare("Capsa") == 0){
		int num_obj;
		iss >> num_obj;
		int obj = cjtObj.creaObjecte(getDescr(descr), nom, Objecte::CAPSA, 0);
		if (capsa == -1) Mon::mapa.posaObjZona(id_zona, obj);
		else Mon::cjtObj.posaObjACapsa(capsa, obj);
		while (num_obj > 0){
			std::string line; 
			std::getline(f_mapa, line);
			std::istringstream iss2(line);
			lecturaObjectes(iss2, id_zona, f_mapa, obj);
			num_obj--;
		}
	}
	else if (tipus.compare("Estandard") == 0){
		int forca;
		iss >> forca;
		int obj = cjtObj.creaObjecte(getDescr(descr), nom, Objecte::ESTANDARD, forca);
		if (capsa == -1) Mon::mapa.posaObjZona(id_zona, obj);
		else Mon::cjtObj.posaObjACapsa(capsa, obj);
	}
	else if (tipus.compare("Consumible") == 0){
		int bonus;
		iss >> bonus;
		int obj = cjtObj.creaObjecte(getDescr(descr), nom, Objecte::CONSUMIBLE, bonus);
		if (capsa == -1) Mon::mapa.posaObjZona(id_zona, obj);
		else Mon::cjtObj.posaObjACapsa(capsa, obj);
	}
}

void Mon::carregaMapa(){
	std::ifstream f_mapa("mon.txt");
	std::string linia = ""; 
	int id_zona;

	while (std::getline(f_mapa, linia)){
		std::istringstream iss(linia);
		std::string paraula;
		while (iss >> paraula){
			if (paraula.compare("Zona") == 0){
				std::string zona_act, descr;
				iss >> zona_act >> descr;
				id_zona = Mon::mapa.creaZona(zona_act, getDescr(descr));
			}
			else if (paraula.compare("Objecte") == 0){
				lecturaObjectes(iss, id_zona, f_mapa); 
			}
			else{
				int zona_propera;
				iss >> zona_propera;
				Mon::mapa.enllacaZona(id_zona, paraula, zona_propera);
			}
		}
	}
	f_mapa.close();
}


std::string Mon::getDescr(std::string descr){
	for (int i = 0; i < descr.length(); ++i){
		if (descr[i] == '_') descr[i] = ' ';
	}
	return descr;
}

bool Mon::tracta_accio_desplacament(std::string accio){
	int zona_actual = Mon::jugador->getPos();
	int zona_desti;
	bool possible = Mon::mapa.desplacaZona(zona_actual, accio, zona_desti);
	if (possible) Mon::jugador -> setPos(zona_desti);
	return possible;
}

bool Mon::tracta_accio_objecte(std::string accio, std::string continuacio){
	std::string obj1;
	std::list<int> inv = Mon::jugador->getInv();
	if (accio.compare("posa") == 0){
		std::istringstream iss(continuacio);
		std::string obj2, paraula_enllac;
		iss >> obj2;
		iss >> paraula_enllac;
		if (paraula_enllac.compare("dins") == 0){
			iss >> obj1;
			int id1, id2;
			if (tradueixObj(obj1, inv, id1) && tradueixObj(obj2, inv, id2)){
				if (cjtObj.accio_composta(id1, accio, id2, obj2)){
					Mon::jugador->rmInv(id2);
					return true;
				}
			}
			else return false;
		}
		else return false;
	}
	else if (accio.compare("treu") == 0){ 
		std::istringstream iss(continuacio);
		std::string obj2, paraula_enllac;
		iss >> obj2;
		iss >> paraula_enllac;
		if (paraula_enllac.compare("de") == 0){
			iss >> obj1;
			int id1, id2;
			if (tradueixObj(obj1, inv, id1)){
				if (cjtObj.accio_composta(id1, accio, id2, obj2)){
					Mon::jugador->addInv(id2);
					return true;
				}
			}
			else return false;
		}
		else return false;
	}
	else if (accio.compare("mira") == 0){

		int id;
		if (tradueixObj(continuacio, inv, id)){
			std::cout << cjtObj.getInfo(id) << std::endl;
		}
		else return false;
	}
	else{
		int id;
		if (tradueixObj(obj1, inv, id)){
			return cjtObj.accio_simple(id, accio);
		}
		else return false;
	}
}

bool Mon::tracta_accio_zona(std::string accio, std::string continuacio){
	if (accio.compare("agafa") == 0){
		int zona = jugador->getPos();
		std::list<int> obj = mapa.getObjectes(zona);
		int id_obj;
		if (tradueixObj(continuacio, obj, id_obj)){
			mapa.llevaObjZona(zona, id_obj);
			jugador->addInv(id_obj);
			return true;
		}
		else return false;
	}
	else if (accio.compare("deixa") == 0){
		int zona = jugador->getPos();
		std::list<int> obj = jugador->getInv();
		int id_obj;
		if (tradueixObj(continuacio, obj, id_obj)){
			mapa.posaObjZona(zona, id_obj);
			jugador->rmInv(id_obj);
			return true;
		}
		else return false;
	}
	else if (accio.compare("aboca") == 0){
		if (continuacio.compare("Garrafa") == 0 && jugador->getPos() == 1){
			return true;
		}
		else if (continuacio.compare("Garrafa de benzina") == 0 && jugador->getPos() == 1){
			return true;
		}
		return false;
	}
}

bool Mon::tracta_accio_personatge(std::string accio, std::string continuacio){

	if (accio.compare("inventari") == 0){
		std::list<int> inv = jugador->getInv();
		std::cout << "Inventari:" << std::endl; 
		std::list<int>::iterator it = inv.begin();
		if (it == inv.end()){
			std::cout << "No hi ha res a l'inventari" << std::endl;
		}
		else{
			for (it; it != inv.end(); ++it){
				std::cout << cjtObj.getInfo(*it) << std::endl;
			}
		}
		return true;
	}
	else if (accio.compare("obre") == 0 || accio.compare("tanca") == 0){
		std::list<int> inv = jugador->getInv();
		int id;
		if (tradueixObj(continuacio, inv, id)){
			cjtObj.accio_simple(id, accio);
		}
		return true;
	}
	else if (accio.compare("consumeix") == 0){
		std::list<int> inv = jugador->getInv();
		int id;
		if (tradueixObj(continuacio, inv, id)){

			if (cjtObj.accio_simple(id, accio)){
				jugador->addDamage(cjtObj.getForca(id));
				jugador->rmInv(id);
				return true;
			}
			else return false;
		}
		return false;
	}
	else if (accio.compare("info") == 0){
		std::cout << jugador->getInfo() << std::endl;
		return true;
	}
	else return false;
}

bool Mon::tracta_accio_lluita(std::string accio, std::string continuacio){ return false; }

void Mon::mostra_info_zona(){
	int zona = Mon::jugador->getPos();
	std::cout << Mon::mapa.getNomZona(zona) << " " <<Mon::mapa.getDescrZona(zona) << std::endl;
	std::list<int> objectes = Mon::mapa.getObjectes(zona);
	if (objectes.size() > 0) std::cout << "Objectes a la vista: " << std::endl;
	for (std::list<int>::iterator it = objectes.begin(); it != objectes.end(); ++it){
		std::cout << cjtObj.getInfo(*it) << std::endl;
	}
}

bool Mon::tradueixObj(std::string nom, std::list<int> list, int& id){
	//comprovam a quin objecte es refereix el jugador
	std::list<int>::iterator it = list.begin();
	while (it != list.end()){
		std::string nom_obj = cjtObj.getNom(*it);
		if (nom.compare(nom_obj) == 0){
			id = *it;
			return true;
		}
		++it;
	}
	return false;
}
Mon::~Mon(){}