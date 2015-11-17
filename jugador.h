#include "personaje.h"

class Jugador : public Personatge{

private:
	int pos = -1;
	std::list<int> inv;

public:
	Jugador(); 

	std::list<int> getInv();
	void setInv(std::list<int> inventari);
	void rmInv(int obj);
	void addInv(int obj);
	void setPos(int pos);
	std::string getInfo();
	int getPos();

	~Jugador();
};