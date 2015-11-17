#include <vector>
#include "zona.h"

class Mapa{

private:
	std::vector<Zona> mapa;

public:
	int creaZona(std::string nom, std::string descripcio); // crea zona i en retorna l'id
	bool enllacaZona(int zona1, std::string accio, int zona2); 
	std::string getNomZona(int id);
	std::string getDescrZona(int id);
	bool desplacaZona(int zona1, std::string accio, int& zona2); //desplaça d'una zona a una altra segons una acció, retorna false si no es pot
	std::list<int> getObjectes(int zona);
	void posaObjZona(int zona, int obj);
	void llevaObjZona(int zona, int obj);
	int getSize();
	void clear();
};