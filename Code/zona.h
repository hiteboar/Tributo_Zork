#include <list>
#include <map>

class Zona{

private:
	std::list<int> objectes;
	std::map<std::string, int> properes;
	std::string nom;
	std::string descripcio;

public:
	Zona(std::string nom1, std::string descripcio1){ nom = nom1; descripcio = descripcio1; }
	void addObjecte(int id);
	void rmObjecte(int id);
	void addZonaPropera(std::string direccio, int zona);
	bool getZona(std::string direccio, int& zona);
	std::string getNom();
	std::string getDescripcio();
	std::list<int> getObjs();
};