#include <string>
#include <list>

class Objecte{

public:
	enum tipus_obj  { CAPSA, CONSUMIBLE, ESTANDARD, OBJECTE };

protected:
	unsigned int id;
	std::string descripcio = "";
	std::string nom;
	int plus_forca = 0;
	tipus_obj tipus = OBJECTE;

public:
	Objecte(){};
	virtual ~Objecte(){};
	int getId() { return id; }
	std::string getDescr() { return descripcio; }
	std::string getNom(){ return nom; }
	int getPlusForca(){ return plus_forca; }
	tipus_obj getTipus(){ return tipus; }
	virtual std::string getInfo(){return nom + " " + descripcio;} // dona informació del contingut de l'objecte
	virtual bool accio_simple(std::string accio){return false;} // fa una accio sobre l'bjecte. Retorna true si s'ha pogut fer
	virtual bool accio_composta(std::string accio, Objecte* obj){ return false; } // idem anterior pero relacionat amb un altre objecte
};

class Capsa : public Objecte{

private:
	bool obert = false;
	std::string accions[5];
	std::list<Objecte*> objectes;
	bool conteObjecte(Objecte* obj);

public:
	Capsa(int id, std::string nom, std::string descr, tipus_obj t_obj);
	~Capsa(){}
	std::string getInfo();
	void addObjecte(Objecte* obj);
	void rmObjecte(Objecte* obj);
	bool accio_simple(std::string accio); // fa una accio sobre l'bjecte. Retorna true si s'ha pogut fer
	bool accio_composta(std::string accio, Objecte* obj); // idem anterior pero relacionat amb un altre objecte
};

class Consumible : public Objecte {
public:
	Consumible(int id, std::string nom, std::string descr, int forca, tipus_obj t_obj);
	~Consumible(){}
	int getForca();
	std::string getInfo() {return nom + " " + descripcio;}
	bool accio_simple(std::string accio);// fa una accio sobre l'bjecte. Retorna true si s'ha pogut fer
	bool accio_composta(std::string accio, Objecte* obj){ return false; } // idem anterior pero relacionat amb un altre objecte
};

class ObjEstandard : public Objecte{

public:
	ObjEstandard(int id, std::string nom, std::string descr, int forca, tipus_obj t_obj);
	~ObjEstandard(){}
	std::string getInfo(){
		return nom + " " + descripcio;
	}
	bool accio_simple(std::string accio){ return false; } // fa una accio sobre l'bjecte. Retorna true si s'ha pogut fer
	bool accio_composta(std::string accio, Objecte* obj){ return false; } // idem anterior pero relacionat amb un altre objecte
};