/*
 * usuario.cc
 *
 *  Created on: 5 dic 2022
 *      Author: JAVIER
 */
#include <fstream>
#include <iostream>
#include "usuario.h"
#include <stdlib.h>
#include <vector>
#include <string>



using namespace std;

Usuario::Usuario(string correo, string contra){
	correo_ = correo;
	contra_ = contra;
}
bool arroba(string cor){
	int c = 0, posi;
	for(int i = 0; i < cor.length(); i++){
		if(cor[i]=='@'){
			c++;
			posi = i;
		}
		else if(cor[i]=='.')
			c++;
	}
	//cout<<"Correo: "+ cor + " y substring " + cor.substr(posi, 7)<<endl;
	if(cor.substr(posi, 7) != "@uco.es"){
		cout<<"No es un correo de la uco"<<endl;
		return false;
	}
	if(c == 2){
		return true;
	}
	return false;
}
int Usuario::iniciarSesion(){
	string c, p;
	int rol;
	bool ccorr=false; //condicionadores para hacer un bucle por si falla el correo
	bool ccontra=false; //condicionadores para hacer un bucle por si falla la contraseña
	while(ccontra != true){ //si falla la contraseña se repite todo el bucle
		while(ccorr != true){ //si falla el correo se repite el bucle del correo
			cout<<"Introducir correo: "<<endl;
			cin>>c;
			cout<<endl;
			cout<<endl;
			cout<<endl;
			set_correo(c);
			bool al = arroba(c);
			if(comprobar_correo(c) == true){ //comprueba que el correo esté en el fichero
				if(al == true){
					cout<<"Correo valido"<<endl;
					ccorr = true; //se termina el while del correo
				}
			}
			else{
				cout<<"Correo erroneo, prueba de nuevo."<<endl;
			}
		}
		cout<<"Introducir contrasenya: "<<endl;
		cin>>p;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		set_contra(p);
		if(comprobar_coincidencia(c,p, &rol)==true){//comprobamos que la contraseña y el correo casan
			cout<<"Inicio en la sesion con exito"<<endl;
			cout<<endl;
			cout<<endl;
			cout<<endl;
			ccontra = true; //se termina el while grande
			return rol;
		}
		else{
			ccorr = false; //volvemos a dar como error el correo para que el usuario lo tenga que volver a escribir
			cout<<"No hay coincidencia entre la contrasenia y el correo proporcionados"<<endl;
		}
	}
	return 0;
}
bool comprobar_correo(string cor){
	ifstream fich;
	string linea;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;
		return false;
	}
	while(!fich.eof()){
		getline(fich, linea);
		if(linea == cor){
			return true;
		}
	}
	fich.close();
	return false;
}
bool comprobar_coincidencia(string cor, string con, int *rol){
	ifstream fich;
	int c = 0;
	string arriba, abajo, us;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;
		return false;
	}
	while(!fich.eof()){
		getline(fich, arriba);//hago esto porque la estructura de la base de datos va a ser linea de correo y la siguiente linea de contraseña
		getline(fich, abajo);
		getline(fich, us);
		if(arriba == cor && abajo == con){
			c++;
			*rol = stoi(us);
		}
	}
	if(c == 1){
		return true;
	}
	fich.close();
	return false;
}
void imprimir(){
	ifstream fich;
	string arriba, abajo;
	fich.open("logs.txt", ios::in);//abrimos en modo lectura
	if(fich.fail()){
		cout<<"Error al abrir fichero"<<endl;

	}
	while(!fich.eof()){
		getline(fich, arriba);//hago esto porque la estructura de la base de datos va a ser linea de correo y la siguiente linea de contraseña
		getline(fich, abajo);
		cout<<arriba<<" "<<abajo;
		cout<<endl;
	}
	fich.close();
}
int Usuario::verPagina(int vez){
	if(vez == 0){
		cout<<"BIENVENIDO A NUESTRA PAGINA WEB"<<endl;
		cout<<"-------------------------------------------------"<<endl;
	}
	int c, d = 0;
	cout<<"Que desea hacer?"<<endl;
	menu();
	cin>>c;
	//while(d == 0){
		switch(c){
		case 1:
			d = iniciarSesion();
			if(d == 1)
				return 1;//participante
			else if(d == 2)
				return 2;//coordinador de curso
			else
				return 0;
		break;
		case 2:
			verListas();
			verPagina(1);
		break;
		case 3:
			if(registrarUsuario() == true){
				return 1;
			}
		break;
		default:
			cout<<"Argumento no valido";
		}
	//}
	return 0;
}
void menu(){
	cout<<"1. Iniciar Sesion"<<endl;
	cout<<"2. Ver cursos de extension"<<endl;
	cout<<"3. Registrar Usuario"<<endl;
}

bool Usuario::registrarUsuario(){
	string c, p;
	int flag = 0;
		bool ccorr=false; //condicionadores para hacer un bucle por si falla el correo
		bool ccontra=false; //condicionadores para hacer un bucle por si falla la contraseña
		while(ccontra != true){ //si falla la contraseña se repite todo el bucle
			while(ccorr != true){ //si falla el correo se repite el bucle del correo
				if(flag == 0)
					cout<<"Introducir correo: "<<endl;
				else
					cout<<"Introducir correo, esta vez uno no registrado: "<<endl;
				cin>>c;
				cout<<endl;
				cout<<endl;
				cout<<endl;
				set_correo(c);
				bool al = arroba(c);
				if(al == true){ //comprueba que el correo tenga arroba y punto
					bool dis = distancia(c);
					if(dis == true){//comprueba que el dominio sea realista
						cout<<"Correo valido";
						if(comprobar_correo(c) == true){
							cout<<", pero ya esta registrado." <<endl;
							cout<<endl;
							cout<<endl;
							cout<<endl;
							flag = 1; //si el correo esta registrado, repites la introduccion de correo con otro mensaje
						}
						else{
							flag = 0;
							ccorr = true; //se termina el while del correo
						}
					}
				}
				else{
					cout<<"Correo no valido, prueba con otro correo."<<endl;
				}
			}
			cout<<endl;
			cout<<"Introducir contrasenya: "<<endl;
			cin>>p;
			set_contra(p);
			cout<<endl;
			cout<<endl;
			cout<<endl;
			cout<<"Contraseña valida"<<endl;
			cout<<endl;
			cout<<endl;
			cout<<endl;
			ccontra = true; //se termina el while grande
			registrar(c,p);
			return true;
		}
		return false;
}
bool distancia(string cor){
	int posi = 0, dot = 0, comprobantes = 0;
	for(int i = 0; i < cor.length(); i++){
		if(cor[i]=='@')
			posi = i;
		}
	for(int i = posi; i < cor.length(); i++){
		if(cor[i] == '.')
			dot = i;
	}
	if((dot - posi) > 4){
		cout<<"Dominio no válido"<<endl;
		return false;
	}
	if(cor.substr(posi, 7) != "@uco.es"){
		cout<<"Correo: "+ cor + " y substring " + cor.substr(posi, 7)<<endl;
		cout<<"No es un correo de la uco"<<endl;
		return false;
	}
	return true;
}

int contarUsuarios(){
	ifstream f;
	string linea;
	int c = 0;
	f.open("logs.txt", ios::in);
	if(f.fail()){
		cout<<"Error de abrir fichero"<<endl;
		return -1;
	}
	while(!f.eof()){
		getline(f, linea);
		c++;
	}
	f.close();
	return c/3;
}
void registrar(string cor, string con){
    int i = 0, n = contarUsuarios();
    ifstream re;
    ofstream wr;
    string a, b, rol;
    vector<string> v;
	re.open("logs.txt", ios::in);//abrimos en modo lectura
	if(re.fail()){
		cout<<"Error al abrir fichero de lectura"<<endl;
		exit(1);
	}
	while(!re.eof() && i < n){//hasta que no llegue al numero de usuarios no para
			getline(re, a);
	        getline(re, b);
	        getline(re, rol);
	        v.push_back(a);
	        v.push_back(b);
	        v.push_back(rol);
	        i++;
	}
	v.push_back(cor);
	v.push_back(con);
	v.push_back("1");
	n++; //aumenta uno porque añadimos a una persiona

	re.close();
	/*for(int i = 0; i < n*2; i++){
		cout<<v[i]<<endl;
	}*/
    wr.open("logs.txt", ios::out);//abrimos en modo escritura
    if(wr.fail()){
		cout<<"Error al abrir fichero de escritura"<<endl;
		exit(1);
	}
	i = 0;
    for(int j = 0; j < n*3; j++){//hasta que no llegue al numero de usuarios no para
    	if(j == n*3 -1)
    		wr<<v[j]; //en la ultima impresion no mete un enter de mas
    	else
    		wr<<v[j]<<endl;//fila a fila
    }
    wr.close();
}
int Usuario::verListas(){//cada curso ocupara varias lineas
	ifstream f;
	string id, titulo;//una linea paraid y otra pa titulo
	string descripcion;//una linea para desripcion
	string aforo;//linea para aforo
	int n = contarDocentes(titulo), times = 1;
	string docentes, contacto;//varias lineas para docentes:
							//una que pona los nombres
							//otra que muestre sus contactos
	string estudios;//estudios requeridos para acceder al curso
	string inicio, fin; //fechas de inicio y fin
	string participantes;
	f.open("open.txt", ios::in);
	if(f.fail()){
		cout<<"Error al abrir fichero de cursos"<<endl;
		exit(1);
	}
	cout<<"-------------------------------------------------"<<endl;
	while(!f.eof()){
		getline(f, id);//ID
		cout<<"ID: "<<id<<endl;
		getline(f, titulo);//nombre
		cout<<times<<". "<<titulo<<endl;
		getline(f, docentes);//Docentes
		cout<<"Docentes:"<<docentes<<endl;
		getline(f, contacto);//Contacto
		cout<<"Contacto de docentes"<<contacto<<endl;
		getline(f, descripcion);//Descripcion
		cout<<"Descripcion: "<<descripcion<<endl;
		getline(f, estudios);//estudios requeridoss
		cout<<"Estudios requeridos"<<estudios<<endl;
		getline(f, aforo);//Aforo
		cout<<"Aforo maximo: "<<aforo<<endl;
		getline(f,inicio);//Fecha de Inicio
		cout<<"Fecha de Inicio del Curso: "<<inicio<<endl;
		getline(f,fin);//Fecha de Final
		cout<<"Fecha de finalizacion del Curso: "<<fin<<endl;
		getline(f,participantes);//N participantes cursando
		cout<<"Participantes del curso: "<<participantes<<endl;
		cout<<"-------------------------------------------------"<<endl;
		times++;
	}
	return times - 1;
}
int contarDocentes(string titulo){
	ifstream d;
	string ausi;
	int c = 0;
	d.open("open.txt", ios::in);
	if(d.fail()){
		cout<<"Error al abrir fichero de cursos"<<endl;
		exit(1);
	}
	while(!d.eof()){
		getline(d, ausi);//lee todas las lineas hasta topar con el titulo
		if(ausi == titulo){
			getline(d, ausi);
		}
	}
	for(int i = 0 ; i < ausi.length() ; i++){
		if(ausi[i] == ',')
			c++;
	}
	d.close();
	c++;
	return c;
}
