#include <list>

class Personatge{

protected:
	unsigned int forca = 0;
	unsigned int vida = 1;

public:

	void addDamage(unsigned int damage){ vida -= damage; }
	unsigned int getForca() { return forca; }
};