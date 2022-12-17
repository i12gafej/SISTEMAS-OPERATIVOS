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
#include <list>
using namespace std;
struct Us{
    string correo, contra;
};
//FUNCIONES DE LA CLASE CURSO
class Curso{
	private:
		string id_, nombre_, docentes_, contactos_, descripcion_, estudios_, aforo_, inicio_, fin_, participantes_;
	public:
		Curso(string, string, string, string, string, string, string, string, string, string); 
		//setters
		inline void set_id(string id){id_ = id;};
		inline void set_nombre(string nombre){nombre_ = nombre;};
		inline void set_docentes(string docentes){docentes_ = docentes;};
		inline void set_contactos(string contactos){contactos_ = contactos;};
		inline void set_descripcion(string descripcion){descripcion_ = descripcion;};
		inline void set_estudios(string estudios){estudios_ = estudios;};
		inline void set_aforo(string aforo){aforo_ = aforo;};
		inline void set_inicio(string inicio){inicio_ = inicio;};
		inline void set_fin(string fin){fin_ = fin;};
		inline void set_participantes(string participantes){participantes_ = participantes;};
		//getters
		inline string get_id(){return id_;};
		inline string get_nombre(){return nombre_;};
		inline string get_docentes(){return docentes_;};
		inline string get_contactos(){return contactos_;};
		inline string get_descripcion(){return descripcion_;};
		inline string get_estudios(){return estudios_;};
		inline string get_aforo(){return aforo_;};
		inline string get_inicio(){return inicio_;};
		inline string get_fin(){return fin_;};
		inline string get_participantes(){return participantes_;};
		//funcionalidades
};
list<Curso> listaCursos();
void imprimirListas(list<Curso> listas);
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
		int verPagina(int vez, list<Curso> listas);
		bool registrarUsuario(string cor, string cotra);
		void verListas(list<Curso> listas);
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

int contarlineas();

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
		bool matricularse(int curso, int cuantos);
		bool globalset(string cor);
		void paginaParticipante(int vez, list<Curso> listas);
		bool comprobaciones(int curso, int cual);

};
void seleccionarCurso(int *curso, int *cual);
void menuParticipante();
bool opcionaMatricula();
bool buscarCurso(int **curso, int **ncursos);
bool comprobarFecha(string ahora, string date);
bool actualizarCursos(int p, int ncursos, int curso);
bool actualizarMatricula(string dni, string nombre);
string concatenar(vector<string> v, int n);
string estudiosPosibles();
string fechaPosible();
bool imprimirPerfilNuevo(string cor, string w[]);


//FUNCIONES DE LA CLASE COORDINADOR DE CURSO
class Ccurso : public Usuario{
	private:
	list<Curso> listas_;
	public:
	Ccurso(string, string, list<Curso>);
	//setter
	inline void set_listas(list<Curso> listas){listas_ = listas;};
	//getters
	inline list<Curso> get_listas(){return listas_;};
	int modificarCurso();
	void paginaCcurso(int vez);
	bool crearCurso(Curso c1);
	bool editarCurso();
	bool eliminarCurso(int curso);
};
	void opcionMod();
	vector<string> atributos();
	
	size_t comprobarExistencia(string c);//devuelve la posicion de la linea donde se encuentra el elemento existente y -1 si no existe
	string estudiosRequeridos();
	string fecha(int mod);
	vector<string> desglosar(string linea, int tipo);


#endif /* OBJETOS_OBJECTS_H_ */
