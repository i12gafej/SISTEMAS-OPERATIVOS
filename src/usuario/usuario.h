/*
 * usuario.h
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */

#ifndef USUARIO_H
#define USUARIO_H
#include <stdlib.h>
#include <string>
using namespace std;

class Usuario{
	private:
		string correo_;
		string contra_;
	public:

		Usuario(string, string);
		//setters
		inline void set_correo(string correo){correo_ = correo;}
		inline void set_contra(string contra){contra_ = contra;}
		//Getters
		inline string get_correo(){return correo_;}
		inline string get_contra(){return contra_;}
		//User's operations
		int iniciarSesion();
		int verPagina(int vez);
		bool registrarUsuario();
		int verListas();
};
bool comprobar_coincidencia(string cor, string con, int *rol);
bool comprobar_correo(string cor);
bool arroba(string cor);
void imprimir();
void menu();

bool distancia(string cor);
void registrar(string cor, string con);
int contarUsuarios();

int contarDocentes(string titulo);


#endif /* OBJETOS_USUARIO_USUARIO_H_ */
