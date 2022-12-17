/*
 * participante.h
 *
 *  Created on: 6 dic 2022
 *      Author: USUARIO
 */



#include "../usuario/usuario.cpp"
#include "../usuario/usuario.h"
#include <string>




using namespace std;

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
vector<string> desglosa(string linea, int tipo);



