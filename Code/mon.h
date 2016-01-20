#include "cjtObjectes.h"
#include "mapa.h"
#include "jugador.h"

class Mon{

private:
	Mapa mapa;
	Jugador* jugador = new Jugador();
	CjtObjectes cjtObj;
	void carregaMapa();
	void lecturaObjectes(std::istringstream& iss, int id_zona, std::ifstream& f_mapa, int capsa = -1);
	std::string getDescr(std::string descr);
	int creaObjecte(std::string nom, std::string descr, std::string tipus, int forca);
	bool tradueixObj(std::string nom, std::list<int> list, int& id); //cerca l'id de l'objecte dins la llista
	bool tracta_accio_desplacament(std::string accio);
	bool tracta_accio_objecte(std::string accio, std::string continuacio);
	bool tracta_accio_zona(std::string accio, std::string continuacio);
	bool tracta_accio_personatge(std::string accio, std::string continuacio);
	bool tracta_accio_lluita(std::string accio, std::string continuacio);

public:
	Mon();
	enum tipus_accions { A_OBJECTE, A_DESPL, A_ZONA, A_LLUITA, A_PERSONATGE};
	void creaNouMon();
	bool accio(tipus_accions a, std::string accio_principal, std::string continuacio);
	void mostra_info_zona();
	~Mon();
};