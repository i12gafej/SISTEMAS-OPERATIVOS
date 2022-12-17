/*
 * c_cursos.h
 *
 *  Created on: 9 dic 2022
 *      Author: USUARIO
 */

#ifndef OBJETOS_C_CURSOS_C_CURSOS_H_
#define OBJETOS_C_CURSOS_C_CURSOS_H_


#include "../usuario/usuario.cpp"
#include "../usuario/usuario.h"
#include <string>

using namespace std;

class Ccurso : public Usuario{
	public:
	Ccurso(string, string);
	int modificarCurso();
	void paginaCcurso(int vez);
};
	void opcionMod();
	bool crearCurso();
	bool editarCurso(int ncur);
	bool eliminarCurso(int ncur);
	size_t comprobarExistencia(string c);//devuelve la posicion de la linea donde se encuentra el elemento existente y -1 si no existe
	string estudiosRequeridos();
	string fecha(int mod);
	vector<string> desglosar(string linea, int tipo);


#endif /* OBJETOS_C_CURSOS_C_CURSOS_H_ */
