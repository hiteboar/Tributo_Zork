#include "cjtObjectes.h"

#include <iostream>


bool CjtObjectes::existeixObj(int id){
	std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
	if (it != CjtObjectes::objectes.end()){
		return true;
	}
	else return false;
}

unsigned int CjtObjectes::creaObjecte(std::string descr, std::string nom, Objecte::tipus_obj tipus, int forca){
	int id = CjtObjectes::objectes.size();
	switch (tipus){
	case Objecte::CAPSA:
		return creaCapsa(id, descr, nom);
		break;
	case Objecte::ESTANDARD:
		return creaEstandard(id, descr, nom, forca);
		break;
	case Objecte::CONSUMIBLE:
		return creaConsumible(id, descr, nom, forca);
		break;
	}
	
}

unsigned int CjtObjectes::creaCapsa(int id, std::string descr, std::string nom){
	Capsa* obj = new Capsa(id, nom, descr, Objecte::CAPSA);
	std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
	CjtObjectes::objectes.insert(it, std::pair<int, Objecte*>(id, obj));
	return id;
}

unsigned int CjtObjectes::creaEstandard(int id, std::string descr, std::string nom, int forca){
	ObjEstandard* obj = new ObjEstandard(id, nom, descr, forca, Objecte::ESTANDARD);
	std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
	CjtObjectes::objectes.insert(it, std::pair<int, Objecte*>(id, obj));
	return id;
}

unsigned int CjtObjectes::creaConsumible(int id, std::string descr, std::string nom, int forca){
	Consumible* obj = new Consumible(id, nom, descr, forca, Objecte::CONSUMIBLE);
	std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
	CjtObjectes::objectes.insert(it, std::pair<int, Objecte*>(id, obj));
	return id;
}

std::string CjtObjectes::getNom(int id){
	std::string nom;
	if (existeixObj(id)){
		std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
		nom = (it->second)->getNom();
	}
	else{
		nom = "null";
	}
	return nom;
}
std::string CjtObjectes::getDescripcio(int id){
	std::string descr;
	if (existeixObj(id)){
		std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
		descr = (it->second)->getDescr();
	}
	else{
		descr = "null";
	}
	return descr;
}

std::string CjtObjectes::getInfo(int id){
	std::string descr;
	if (existeixObj(id)){
		std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
		descr = (it->second)->getInfo();
	}
	else{
		descr = "null";
	}
	return descr;
}

int CjtObjectes::getForca(int id){
	int forca;
	if (existeixObj(id)){
		std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(id);
		forca = (it->second)->getPlusForca();
	}
	else{
		forca = 0;
	}
	return forca;
}

bool CjtObjectes::posaObjACapsa(int capsa, int obj){
	std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(capsa);
	std::map<int, Objecte*>::iterator it2 = CjtObjectes::objectes.find(obj);
	Capsa* c = (Capsa* )it->second;
	c->addObjecte(it2->second);
	return true;
}

bool CjtObjectes::accio_simple(int obj1, std::string accio){
	if (existeixObj(obj1)){

		std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(obj1);
		if ((it->second)->getTipus() == Objecte::CAPSA){
			Capsa* c = (Capsa *)it->second;
			return c->accio_simple(accio);
		}
		else if ((it->second)->getTipus() == Objecte::CONSUMIBLE){
			Consumible* cons = (Consumible *)it->second;
			return cons->accio_simple(accio);
		}
		else if ((it->second)->getTipus() == Objecte::ESTANDARD){
			ObjEstandard* est = (ObjEstandard*)it->second;
			return est->accio_simple(accio);
		}
		else return false;
	}
	else return false;
}

bool CjtObjectes::accio_composta(int obj1, std::string accio, int& obj2, std::string nom2){
	if (existeixObj(obj1)){
		if (nom2.compare("") != 0){ // si hi ha un nom escrit, cercam el seu identificador
			std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.begin();
			bool trobat = false;
			while (!trobat && it != CjtObjectes::objectes.end()){
					if (nom2.compare((it->second)->getNom()) == 0){
						trobat = true;
						obj2 = (it->second)->getId();
					}
				++it;
			}
			if (!trobat) return false;
		}

		std::map<int, Objecte*>::iterator it = CjtObjectes::objectes.find(obj1);
		std::map<int, Objecte*>::iterator it2 = CjtObjectes::objectes.find(obj2);
		return (it->second)->accio_composta(accio, it2->second);
	}
	else return false;
}