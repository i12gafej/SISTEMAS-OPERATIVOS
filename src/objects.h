/*
 * objects.h
 *
 *  Created on: 11 dic 2022
 *      Author: USUARIO
 */

#ifndef OBJETOS_OBJECTS_H_
#define OBJETOS_OBJECTS_H_
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
struct Us{
    string correo, contra;
};

//FUNCIONES DE LA CLASE USUARIO
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
		bool iniciarSesion(string cor, string contra, int *role);
		int verPagina(int vez);
		bool registrarUsuario(string cor, string cotra);
		int verListas();
};
bool comprobar_coincidencia(string cor, string con, int **rol);
bool comprobar_correo(string cor);
bool arroba(string cor);
void imprimir();
void menu();
struct Us introducirUsuarioyContrasenia();

bool distancia(string cor);
void registrar(string cor, string con);
int contarUsuarios();

int contarDocentes(string titulo);

//CLASE VISITANTE
class Visitante: public Usuario{
	public:
		Visitante(string, string);


};

//FUNCIONES DE LA CLASE PARTICIPANTE
class Participante : public Usuario{
	private:
		string nombre_, dni_, estudios_, telefono_, nacimiento_, cmatriculados_;
	public:
		Participante(string, string, string, string, string, string, string, string);
		//setters
		inline void set_nombre(string nombre){nombre_ = nombre;}
		inline void set_dni(string dni){dni_ = dni;}
		inline void set_estudios(string estudios){estudios_ = estudios;}
		inline void set_telefono(string telefono){telefono_ = telefono;}
		inline void set_nacimiento(string nacimiento){nacimiento_ = nacimiento;}
		inline void set_cmatriculados(string cmatriculados){cmatriculados_ = cmatriculados;}
		//getters
		inline string get_nombre(){return nombre_;}
		inline string get_dni(){return dni_;}
		inline string get_estudios(){return estudios_;}
		inline string get_telefono(){return telefono_;}
		inline string get_nacimiento(){return nacimiento_;}
		inline string get_cmatriculados(){return cmatriculados_;}
		//funcionalidades
		bool matricularse();
		bool globalset(string cor);
		void paginaParticipante(int vez);

};
void menuParticipante();
bool opcionaMatricula();
bool buscarCurso(int curso, int ncursos);
bool comprobarFecha(string ahora, string date);
bool actualizarCursos(int p, int ncursos, int curso);
bool actualizarMatricula(string dni, string nombre);
string concatenar(vector<string> v, int n);
string estudiosPosibles();
string fechaPosible();
bool imprimirPerfilNuevo(string cor, string w[]);


//FUNCIONES DE LA CLASE COORDINADOR DE CURSO
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



#endif /* OBJETOS_OBJECTS_H_ */
