#include <map>
#include "objecte.h"

class CjtObjectes{

private:
	std::map<int, Objecte*> objectes;
	bool existeixObj(int id);
	unsigned int creaCapsa(int id, std::string descr, std::string nom);
	unsigned int creaEstandard(int id, std::string descr, std::string nom, int forca);
	unsigned int creaConsumible(int id, std::string descr, std::string nom, int forca);

public:
	//enum tipus_obj {CAPSA, ESTANDARD, CONSUMIBLE};
	/// crea un nou objecte i en retorna l'identificador
	unsigned int creaObjecte(std::string descr, std::string nom, Objecte::tipus_obj tipus, int forca);
	std::string getNom(int id);
	std::string getDescripcio(int id);
	std::string getInfo(int id);
	int getForca(int id);
	bool posaObjACapsa(int capsa, int obj);
	bool accio_simple(int obj1, std::string accio);
	bool accio_composta(int obj1, std::string accio, int& obj2, std::string nom2);
};