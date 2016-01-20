#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include "mon.h"

using namespace std;

void acabaJoc(){
	cout << "Ehorabona, has trobat la benzina necessaria per arrancar el transbordador i tornar a la terra." << endl;
}

void minuscules(std::string& paraula){
	for (int i = 0; i < paraula.length(); ++i) paraula[i] = std::tolower(paraula[i]);
}

void incorrecte(){
	cout << "No es pot realitzar aquesta acció" << endl;
}

void fet(){
	cout << "Fet" << endl;
}

void main(){
	std::string entrada;
	Mon mon;
	cout << "Benvingut.\nEts un astronauta que es trobava en una base instalada a la Luna.\n" <<
		"Has sortit de la base per reconeixer la zona, però, quan has tornat has vist que la base havia sofert un atac.\n" <<
		"No veus a ningú pels voltants, necessites tornar a la terra per informar del que ha passat." << std::endl;
	cout << "Et trobes a: " << endl; 
	mon.mostra_info_zona();
	while (std::getline(cin, entrada)){
		std::istringstream iss(entrada);
		std::string paraula, continuacio;
		while (iss>>paraula){
			minuscules(paraula);
			if (paraula.compare("sortir") == 0) exit(0);
			else if (paraula.compare("nord") == 0 || paraula.compare("sud") == 0 || paraula.compare("est") == 0
				|| paraula.compare("oest") == 0 || paraula.compare("entra") == 0 || paraula.compare("surt") == 0){
				if (iss >> continuacio) incorrecte();
			    else mon.accio(Mon::A_DESPL, paraula, "");
			}
			else if (paraula.compare("mira") == 0){
				if (iss >> continuacio){
					std::string cont_total = continuacio;
					while (iss >> continuacio) cont_total += " " + continuacio;
					if (!mon.accio(Mon::A_OBJECTE, paraula, cont_total)) incorrecte();
				}
				else mon.mostra_info_zona();
			}
			else if (paraula.compare("posa") == 0 || paraula.compare("treu")==0){
				if (iss >> continuacio){
					std::string cont_total = continuacio;
					while (iss >> continuacio) cont_total += " " + continuacio;
					if (mon.accio(Mon::A_OBJECTE, paraula, cont_total)) fet();
					else incorrecte();
				}
				else incorrecte();
			}
			else if (paraula.compare("agafa") == 0 || paraula.compare("deixa") == 0){
				if (iss >> continuacio){
					std::string cont_total = continuacio;
					while (iss >> continuacio) cont_total += " " + continuacio;
					if (mon.accio(Mon::A_ZONA, paraula, cont_total)) fet();
					else incorrecte();
				}
				else std::cout << "Especifica el que vols agafar" << std::endl;
			}
			else if (paraula.compare("aboca") == 0){
				if (iss >> continuacio) {
					std::string cont_total = continuacio;
					while (iss >> continuacio) cont_total += " "+continuacio;
					if(!mon.accio(Mon::A_ZONA, paraula, cont_total)) incorrecte();
					else acabaJoc();
				}
				else incorrecte();
			}
			else if(paraula.compare("inventari") == 0){
				if (iss >> continuacio) incorrecte();
				else {
					if (!mon.accio(Mon::A_PERSONATGE, paraula, "")) incorrecte();
				}
			}
			else if (paraula.compare("obre") == 0 || paraula.compare("tanca") == 0){
				if (iss >> continuacio){
					if (mon.accio(Mon::A_PERSONATGE, paraula, continuacio)) fet();
					else incorrecte();
				}
				else incorrecte();
			}
			else if (paraula.compare("consumeix") == 0){
				if (iss >> continuacio){
					std::string cont_total = continuacio;
					while (iss >> continuacio) cont_total += " " + continuacio;
					if (mon.accio(Mon::A_PERSONATGE, paraula, cont_total)) fet();
					else incorrecte();
				}
				else incorrecte();
			}
			else if (paraula.compare("ataca") == 0){

			}
			else if (paraula.compare("info") == 0){
				if (iss >> continuacio) incorrecte();
				else {
					std::string cont_total = continuacio;
					while (iss >> continuacio) cont_total += " " + continuacio;
					if (!mon.accio(Mon::A_PERSONATGE, paraula, cont_total))incorrecte();
				}
			}
		}
	}
}