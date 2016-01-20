#include "objecte.h"


using namespace std;

//// CAPSA ////
Capsa::Capsa(int id, std::string nom, std::string descr, tipus_obj t_obj){
	accions[0] = "obre";
	accions[1] = "tanca";
	accions[2] = "posa";
	accions[3] = "treu";
	accions[4] = "mira";
	Capsa::obert = false;
	Capsa::nom = nom;
	Capsa::descripcio = descr;
	Capsa::id = id;
	Capsa::tipus = t_obj;
}


void Capsa::addObjecte(Objecte* obj){
	Capsa::objectes.push_back(obj);
}

void Capsa::rmObjecte(Objecte* obj){
	Capsa::objectes.remove(obj); 
}

string Capsa::getInfo(){
	string info = Capsa::getNom() + " " + Capsa::getDescr();
	if (Capsa::obert) {
		info += "\nLa capsa conté:\n";
		for (list<Objecte* >::iterator it = Capsa::objectes.begin(); it != Capsa::objectes.end(); ++it){
			info +=" - " + (*it)->getInfo() + "\n";
		}
	}
	return info;
}

bool Capsa::accio_simple(std::string accio){
	int pos = 0;
	bool trobat = false;
	while (pos<5 && !trobat){
		if (Capsa::accions[pos].compare(accio) == 0) trobat = true;
		else ++pos;
	}
	if (trobat){
		switch (pos){
		case 0:
			if (Capsa::obert) return false;
			else Capsa::obert = true;
			break;
		case 1:
			if (!Capsa::obert) return false;
			else Capsa::obert = false;
			break;
		case 2:
		case 3:
			return false;
			break;
		case 4:
			if (!Capsa::obert) return false;
			break;
		}
	}
	return trobat;
}

bool Capsa::accio_composta(string accio, Objecte* obj){
	int pos = 0;
	bool trobat = false;
	while (pos<5 && !trobat){
		if (Capsa::accions[pos].compare(accio) == 0) trobat = true;
		else ++pos;
	}
	if (trobat){
		switch (pos){
		case 0:
		case 1:
		case 4:
			return false;
			break;
		case 2:
			if (Capsa::obert && !Capsa::conteObjecte(obj)){
				Capsa::objectes.push_back(obj);
			}
			else return false;
			break;
		case 3:
			if (Capsa::obert && Capsa::conteObjecte(obj)){
				Capsa::objectes.remove(obj);
			}
			else return false;
			break;
		}
	}
	return trobat;
}

bool Capsa::conteObjecte(Objecte* obj){
	list<Objecte*>::iterator it = Capsa::objectes.begin();
	bool trobat = false;
	while (it != Capsa::objectes.end() && !trobat){
		if (*it == obj) trobat = true;
		++it;
	}
	return trobat;
}


//// CONSUMIBLES ////

Consumible::Consumible(int id, std::string nom, std::string descr, int forca, tipus_obj tipus){
	Consumible::id = id;
	Consumible::nom = nom;
	Consumible::descripcio = descr;
	Consumible::plus_forca = forca;
	Consumible::tipus = tipus;
}

bool Consumible::accio_simple(std::string accio){
	if (accio.compare("consumeix") == 0){
		return true;
	}
	return false;
}


//// ESTANDARD ////
ObjEstandard::ObjEstandard(int id, std::string nom, std::string descr, int forca, tipus_obj t_obj){
	ObjEstandard::tipus = t_obj;
	ObjEstandard::id = id;
	ObjEstandard::nom = nom;
	ObjEstandard::descripcio = descr;
	ObjEstandard::plus_forca = forca;
}