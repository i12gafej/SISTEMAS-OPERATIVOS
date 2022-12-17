/*
 * main.cpp
 *
 *  Created on: 6 dic 2022
 *      Author: USUARIO
 */
/*#include "participante/participante.h"
//#include "participante/participante.cpp"
#include "c_cursos/c_cursos.h"
//#include "c_cursos/c_cursos.cpp"
#include <iostream>
#include <stdlib.h>
#include <string>


using namespace std;

int main(){
	int user;
	string correo, contra;
	Usuario uno = Usuario("","");
	//Participante tres = Participante("","","","","","","","");
	Ccurso cuatro = Ccurso("","");
	user = uno.verPagina(0);
	cout<<"Orden de usuario: "<<user<<endl;
	if(user == 1){
		correo = uno.get_correo();
		contra = uno.get_contra();
		tres = Participante(correo, contra,"","","","","","");
		tres.globalset(correo);
		tres.paginaParticipante(0);
	}
	if(user == 2){
		correo = cuatro.get_correo();
		contra = cuatro.get_contra();
		cuatro = Ccurso(correo, contra);
		cuatro.paginaCcurso(0);
	}
}*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include "objects.h"

using namespace std;

int main(){
	int user;
	string correo, contra;
	Usuario uno = Usuario("","");
	Participante tres = Participante("","","","","","","","");
	list<Curso> listas = listaCursos();
	Ccurso cuatro = Ccurso("","", listas);
	user = uno.verPagina(0, listas);
	if(user == 1){
		tres = Participante(uno.get_correo(), uno.get_contra(), "","","","","","");
		tres.globalset(correo);
		tres.paginaParticipante(0, listas);
	}
	if(user == 2){
		
		cuatro = Ccurso(uno.get_correo(), uno.get_contra(), listas);
		cuatro.set_listas(listas);
		//ver por que ahi hay error(no muestra listas)
		cuatro.paginaCcurso(0);
	}
	/*if(imprimirListas(listas) == true){
		cout<<"ACTUALIDACION BBDD"<<endl;
		return 0;
	}
	else{
		cout<<"NO ACTUALIZACION DE BBDD"
	}*/
}



