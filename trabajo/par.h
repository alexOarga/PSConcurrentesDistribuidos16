#ifndef PAR_H
#define PAR_H

/* Tipo Abstracto de Datos que almacena el par
 * id, que tiene asociado un precio */

struct par{
private:
	int id;
	int precio;
public:
	friend void crear(par &p, int id, int precio);
	friend void modificarPar(par &p, int precio);
	friend int queId(const par &p);
	friend int quePrecio(const par &p);
	friend bool operator==(const par &p1, const par &p2);
	
};

#endif
