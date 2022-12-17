/*
 * c_cursos.cpp
 *
 *  Created on: 9 dic 2022
 *      Author: USUARIO
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "c_cursos.h"

using namespace std;

Ccurso::Ccurso(string correo, string contra):Usuario(correo, contra){}


int Ccurso::modificarCurso(){
	int m, n;
	while(1){
		n = verListas();
		opcionMod();
		cin>>m;
		switch(m){
		case 1:
			if(crearCurso() == true){
				return 1;
			}
			break;
		case 2:{
			if(editarCurso(n) == true){
				return 2;
			}
		}
		break;
		case 3:
			if(eliminarCurso(n) == true){
				return 3;
			}
			break;
		case 4:
			return 0;
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}
void Ccurso::paginaCcurso(int vez){
	int c, ope;
	if(vez == 1){
		cout<<"HOLA COORDINADOR DE CURSO"<<endl;
		cout<<"_-----------------------------------_"<<endl;
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"Que desea haces?"<<endl;
	cout<<"1. Modificar Curso"<<endl;
	cout<<"2. Salirse"<<endl;
	cin>>c;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	switch(c){
	case 1:
			ope = modificarCurso();
			if(ope == 1 || ope == 2 || ope == 3){
				if(ope == 1){
					cout<<"Creacion con exito"<<endl;
				}
				else if(ope == 2){
					cout<<"Edicion con exito"<<endl;
				}
				else if(ope == 3){
					cout<<"Eliminacion con exito"<<endl;
				}
			}
		paginaCcurso(1);
		break;
	case 2:
		cout<<"Hasta la proxima"<<endl;
		return;
		break;
	default:
		return;
		break;
	}
}
void opcionMod(){
	cout<<"Que quieres hacer?"<<endl;
	cout<<"1. Crear Curso"<<endl;
	cout<<"2. Editar Curso Existente"<<endl;
	cout<<"3. Eliminar Curso Existente"<<endl;
	cout<<"4. Salirte"<<endl;
}
bool crearCurso(){
	string curso[10];
	bool buc = false, docFlag = false;
	int x, n = 0, get = 0;
	vector<string> docentes;

	while(buc != true){
		cout<<"Como quiere que se llame el curso?"<<endl;
		cout<<"--> ";

		getline(cin, curso[1]);
		getline(cin, curso[1]);

		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"El curso se llamara <"+curso[1]+">"<<endl;
		cout<<"Sera este su nombre definitivo?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			if(comprobarExistencia(curso[1]) != -1){
				cout<<"Lo sentimos, este curso ya esta registrado."<<endl;
				cout<<"Intentelo de nuevo"<<endl;
			}
			else{
				buc = true;
			}
		}
	}
	buc = false;
	while(buc != true){
		cout<<"Id del curso: "<<endl;
		cout<<"--> ";
		cin>>curso[0];
		cout<<"El ID seria <"<<curso[0]<<">"<<endl;
		cout<<"Estas seguro"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			if(comprobarExistencia(curso[0]) != -1){
				cout<<"Lo sentimos, este ID ya esta siendo utilizado."<<endl;
				cout<<"Ingrese otro id"<<endl;
			}
			else{
				buc = true;
			}
		}
	}
	buc = false;
	bool encontrado = false;
	int ndoc = 0, ncon = 0, y;
	while(buc != true){
		cout<<"Ahora aniada los docentes que impartiran el curso: "<<endl;
		while(docFlag != true){
			cout<<"Introduzca el nombre del docente"<<endl;
				getline(cin, curso[2]);
				getline(cin, curso[2]);
			cout<<"El docente seria <"<<curso[2]<<">"<<endl;
			cout<<"Estas seguro"<<endl;
			cout<<"1. Si"<<endl;
			cout<<"2. No"<<endl;
			cout<<"--> ";
			cin>>x;
			if(x == 1){
				for(int i = 0 ; i < ndoc; i++){
					size_t found = docentes[i].find(curso[2]);//en found se guarda la posicion de encontrar
					if(found != string::npos){//si lo encuentra
						encontrado = true;
					}
				}
				if(encontrado == false){
					docentes.push_back(curso[2]);
					ndoc++;
					cout<<"Quiere aniadir a mas docentes?"<<endl;
					cout<<"1. Si"<<endl;
					cout<<"2. No"<<endl;
					cout<<"--> ";
					cin>>y;
					if(y == 2){
						docFlag = true;
					}
				}
				else{
					cout<<"El docente ya fue aniadido"<<endl;
					encontrado = false;
				}
			}
		}
		curso[2] = docentes[0];
		for(int i = 1; i < ndoc; i++){
			if(i == ndoc -1)
				curso[2] = curso[2] +" y " + docentes[i];
			else
				curso[2] = curso[2] +", "+ docentes[i];
		}
		buc = true;
	}
	cout<<curso[2]<<" son "<<ndoc<<" docentes."<<endl;
	buc = false;
	docFlag = false;
	encontrado = false;
	vector<string> contactos;
	while(buc != true){
		cout<<"Ahora vamos a introducir los contactos de los docentes"<<endl;
		for(int i = 0; i < ndoc; i++){
			docFlag = false;
			while(docFlag != true){
				cout<<"Cual va a ser el contacto de "<<docentes[i]<<" ?"<<endl;
					getline(cin, curso[3]);
					getline(cin, curso[3]);
				cout<<"El contacto de <"<<docentes[i]<<"> seria <"<<curso[3]<<">"<<endl;
				cout<<"Estas seguro"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cout<<"--> ";
				cin>>x;
				if(x == 1){//hay que ver que no sea el mismo que el de otra persona ya que es unico
					for(int j = 0 ; j < ncon; j++){
						cout<<"p1"<<endl;
						size_t found = contactos[j].find(curso[3]);//en found se guarda la posicion de encontrar
						if(found != string::npos){//si lo encuentra en el el vector actual
							encontrado = true;
						}
					}
					if(encontrado == false){
						//un profesor puede impartir varios cursos, entonces tenemos que comprobar
						//que si ese contacto está en la bbdd pertenezca al profesor
						//comprobamo la existencia del correo
						//si existe comprobamos la existencia del profesor
						//y calculamos relacion con [posicion de contacto = docente.length()+2(el : y el espacio) -1 (ya que es posicion y no tamanio)]
						//con lo que if(exiCon!=-1){if(exiCon == exiDoc + docentes[i] + 1 ){ corresponde}
						size_t exiCon = comprobarExistencia(curso[3]);
						size_t exiDoc = comprobarExistencia(docentes[i]);

						//cout<<"Posicion del contacto "<<exiCon<<" Posicion de docentes "<<exiDoc<<" Posicion relativa (si es == exiCon) "<< exiDoc + docentes[i].length() + 2<<endl;

						if(exiCon == -1){//el contacto no esta en la bbdd
							contactos.push_back(curso[3]);
							cout<<"Valido"<<endl;
							ncon++;
							docFlag = true;
						}
						else if(exiDoc != -1 && exiCon == -1){//el docente esta en bbdd pero con otro contacto
							contactos.push_back(curso[3]);
							cout<<"Valido"<<endl;
							ncon++;
							docFlag = true;
						}
						else if(exiCon != 1 && exiDoc != -1){//estan en la bbdd
							if(exiCon == (exiDoc + docentes[i].length() + 2)){//comprobamos si corresponde al docente
								cout<<"Esta en la base de datos pero es valida"<<endl;
								contactos.push_back(curso[3]);
								ncon++;
								docFlag = true;
							}
							else{
								cout<<"Este contacto no esta correspondiendo con el profesor"<<endl;
								encontrado = false;
							}
						}
					}
					else{//esta en el vector actual
						cout<<"El contacto lo acabas de aniadir, no se puede duplicar"<<endl;
						encontrado = false;
					}
				}
			}
		}
		buc = true;
	}
	curso[3] = docentes[0] + ": " + contactos[0];
		for(int i = 1; i < ndoc; i++){
			if(i == ndoc -1)
				curso[3] = curso[3] +" y " + docentes[i] +": "+ contactos[i]+",";
			else
				curso[3] = curso[3] +", "+ docentes[i] +": "+ contactos[i];
		}
	cout<<curso[3]<<endl;
	buc = false;
	y = 0;
	while(buc != true){
		if(y == 0)
			cout<<"Ahora vamos a introducir la descripcion del curso"<<endl;
		cout<<"Descricion del curso:"<<endl;
		getline(cin, curso[4]);
		getline(cin, curso[4]);
		cout<<"La descripcion del curso seria <"<<curso[4]<<">"<<endl;
		cout<<"Estas seguro"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			buc = true;
		}
		else{
			y = 1;
		}
	}
	cout<<curso[4]<<endl;
	buc = false;
	y = 0;
	while(buc != true){
		if(y == 0)
			cout<<"Ahora vamos a introducir aforo maximo"<<endl;
		cout<<"Aforo:"<<endl;
		getline(cin, curso[6]);
		getline(cin, curso[6]);
		cout<<"El aforo maximo del curso seria <"<<curso[6]<<">"<<endl;
		cout<<"Estas seguro"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cout<<"--> ";
		cin>>x;
		if(x == 1){
			buc = true;
		}
		else{
			y = 1;
		}
	}
	buc = false;
		cout<<"Ahora vamos a introducir los estudios requeridos"<<endl;
		curso[5] = estudiosRequeridos();
		cout<<curso[5]<<endl;
		cout<<"Ahora vamos a introducir la fecha de INICIO del curso"<<endl;
		curso[7] = fecha(0);
		cout<<curso[7]<<endl;
		cout<<"Ahora vamos a introducir la fecha de FIN del curso"<<endl;
		curso[8] = fecha(1);
		cout<<curso[8]<<endl;

	curso[9] = "0";//hay 0 participantes
	string linea;
	vector<string> lineas;
	ifstream re;
	int count = 0;
	re.open("open.txt", ios::in);
	if(re.fail()){
		cout<<"Error de lectura open"<<endl;
		return false;
	}
	while(!re.eof()){
		getline(re,linea);
		lineas.push_back(linea);
		count++;
	}
	re.close();
	ofstream wr;
	wr.open("open.txt", ios::out);
	if(wr.fail()){
		cout<<"Error de escritura open"<<endl;
		return false;
	}
	int punt = 0;
	while(punt <= count){
		if(punt == count)
            wr<<lineas[punt];
        else
            wr<<lineas[punt]<<endl;;
        punt++;
	}
	for(int b = 0; b < 10; b++){
		if(b == 9)
			wr<<curso[b];
		else
			wr<<curso[b]<<endl;
	}
	wr.close();

	return true;
}
bool editarCurso(int ncur){
	int curso, c = 1;
	string linea = "", id, datos[10][ncur];
	bool elec = false, buc = false;
	cout<<"Introduce el curso que quieres modificar: ";
	cin>>curso;
    ifstream re;
	if(curso <= ncur && curso > 0){//el curso que metamos tiene que estar ahi
		//accedemos por primera vez para ver si es ese curso el que queremos editar
		re.open("open.txt", ios::in);
		if(re.fail()){
			cout<<"Error de lectura"<<endl;
			return false;
		}
		while(!re.eof()){//escaneaamos toda la pagina
				for(int i = 0; i < 10; i++){
					getline(re, datos[i][c-1]);
                    //cout<<"DATO CAPTADO DE ["<<i<< "]["<< c-1<<"]="+datos[i][c-1]<<endl;
					if(c == curso && i == 0){
						id = datos[0][c-1]; //cuando topemos con el id lo guardamos en string id
                        cout<<"ID DEL CURSO ES "<<id<<endl;
                        //cout<<"DATO CAPTADO DE ["<<i<< "]["<< c-1<<"]="+datos[i][c-1]<<endl;
					}
				}
			c++;
		}
		re.close();
	}
	cout<<"Es el curso que quieres editar el que tiene este id <"<<id<<">?"<<endl;
	cout<<"1. Si"<<endl;
	cout<<"2. No"<<endl;
	int x, y;
	cin>>x;
	if(x != 1){
		return false;
	}
	string atribs[10];
    //accedemos una segunda vez para ir volcando en un vector los datos y cambiandolos por otros
	re.open("open.txt", ios::in);
	if(re.fail()){
		cout<<"Error de lectura"<<endl;
		return false;
	}
	c = 1;
	while(id != linea && c < curso){
			for(int i = 0; i < 10; i++){
				getline(re, linea);
			}
		c++;
	}
	if(c == curso){
		getline(re, atribs[0]);//id
		cout<<"El id es <" + atribs[0] + ">."<<endl;
		cout<<"Quieres modificar el id?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			while(buc != true){
				cout<<"Id del curso: "<<endl;
				cout<<"--> ";
				cin>>atribs[0];
				cout<<"El ID seria <"<<atribs[0]<<">"<<endl;
				cout<<"Estas seguro"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cout<<"--> ";
				cin>>x;
				if(x == 1){
					if(comprobarExistencia(atribs[0]) != -1){
						cout<<"Lo sentimos, este ID ya esta siendo utilizado."<<endl;
						cout<<"Ingrese otro id"<<endl;
					}
					else{
						buc = true;
					}
				}
			}
		}
		buc = false;
		getline(re, atribs[1]);//nombre
		cout<<"El nombre del curso es <"+atribs[1]+">."<<endl;
		cout<<"Quieres modificarlo?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			while(buc != true){
				cout<<"Nombre del curso: "<<endl;
				cout<<"--> ";
				cin>>atribs[1];
				cout<<"El nombre seria <"<<atribs[1]<<">"<<endl;
				cout<<"Estas seguro"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cout<<"--> ";
				cin>>x;
				if(x == 1){
					if(comprobarExistencia(atribs[1]) != -1){
						cout<<"Lo sentimos, este nombre ya esta siendo utilizado."<<endl;
						cout<<"Ingrese otro nombre"<<endl;
					}
					else{
						buc = true;
					}
				}
			}
		}
		buc = false;
		bool docFlag = false, encontrado = false, docsMod = false;
		int ndoc = 0, d, z;
		vector<string> docentes;
		getline(re, atribs[2]);//Docentes
		cout<<"Los docentes del curso son <"+atribs[2]+">."<<endl;
		cout<<"Quieres modificarlo?"<<endl;
		cout<<"1. Si (los eliminaras todos)"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			while(buc != true){
				while(docFlag != true){
					cout<<"Introduzca el nombre del docente"<<endl;
						getline(cin, linea);
						getline(cin, linea);
					cout<<"El docente seria <"<<linea<<">"<<endl;
					cout<<"Estas seguro"<<endl;
					cout<<"1. Si"<<endl;
					cout<<"2. No"<<endl;
					cout<<"--> ";
					cin>>y;
					if(y == 1){
						for(int i = 0 ; i < ndoc; i++){
							size_t found = docentes[i].find(linea);//en found se guarda la posicion de encontrar
							if(found != string::npos){//si lo encuentra
								encontrado = true;
							}
						}
						if(encontrado == false){
							docentes.push_back(linea);
							ndoc++;
							cout<<"Quiere aniadir a mas docentes?"<<endl;
							cout<<"1. Si"<<endl;
							cout<<"2. No"<<endl;
							cout<<"--> ";
							cin>>y;
							if(y == 2){
								docFlag = true;
							}
						}
						else{
							cout<<"El docente ya fue aniadido"<<endl;
							encontrado = false;
						}
					}
				}
				linea = docentes[0];
				for(int i = 1; i < ndoc; i++){
					if(i == ndoc -1)
						linea = linea +" y " + docentes[i] + ".";
					else
						linea = linea +", "+ docentes[i];
				}
				atribs[2] = linea;
				buc = true;
				docsMod = true;
			}
		}
		else if(x == 2){
			docentes = desglosar(atribs[2], 0);
		}
		buc = false;
		docFlag = false;
		encontrado = false;
		vector<string> contactos;
		int ncon = 0;
		getline(re, atribs[3]);
		if(docsMod == true){
			while(buc != true){
			cout<<"Ahora vamos a introducir los contactos de los docentes"<<endl;
			for(int i = 0; i < ndoc; i++){
				docFlag = false;
				while(docFlag != true){
					//cout<<"Ncons = "<<ncon<<endl;
					cout<<"Cual va a ser el contacto de "<<docentes[i]<<" ?"<<endl;
						getline(cin, atribs[3]);
						getline(cin, atribs[3]);
					cout<<"El contacto de <"<<docentes[i]<<"> seria <"<<atribs[3]<<">"<<endl;
					cout<<"Estas seguro"<<endl;
					cout<<"1. Si"<<endl;
					cout<<"2. No"<<endl;
					cout<<"--> ";
					cin>>x;
					if(x == 1){//hay que ver que no sea el mismo que el de otra persona ya que es unico
						for(int j = 0 ; j < ncon; j++){
							cout<<"p1"<<endl;
							size_t found = contactos[j].find(atribs[3]);//en found se guarda la posicion de encontrar
							if(found != string::npos){//si lo encuentra en el el vector actual
								encontrado = true;
							}
						}
						if(encontrado == false){
							//un profesor puede impartir varios cursos, entonces tenemos que comprobar
							//que si ese contacto está en la bbdd pertenezca al profesor
							//comprobamo la existencia del correo
							//si existe comprobamos la existencia del profesor
							//y calculamos relacion con [posicion de contacto = docente.length()+2(el : y el espacio) -1 (ya que es posicion y no tamanio)]
							//con lo que if(exiCon!=-1){if(exiCon == exiDoc + docentes[i] + 1 ){ corresponde}
							size_t exiCon = comprobarExistencia(atribs[3]);
							size_t exiDoc = comprobarExistencia(docentes[i]);

							//cout<<"Posicion del contacto "<<exiCon<<" Posicion de docentes "<<exiDoc<<" Posicion relativa (si es == exiCon) "<< exiDoc + docentes[i].length() + 2<<endl;
							cout<<"p2"<<endl;
							if(exiCon == -1){//el contacto no esta en la bbdd
								contactos.push_back(atribs[3]);
								cout<<"Valido"<<endl;
								ncon++;
								docFlag = true;
							}
							else if(exiDoc != -1 && exiCon == -1){//el docente esta en bbdd pero con otro contacto
								contactos.push_back(atribs[3]);
								cout<<"Valido"<<endl;
								ncon++;
								docFlag = true;
							}
							else if(exiCon != 1 && exiDoc != -1){//estan en la bbdd
								if(exiCon == (exiDoc + docentes[i].length() + 2)){//comprobamos si corresponde al docente
									cout<<"Esta en la base de datos pero es valida"<<endl;
									contactos.push_back(atribs[3]);
									ncon++;
									docFlag = true;
								}
								else{
									cout<<"Este contacto no esta correspondiendo con el profesor"<<endl;
									encontrado = false;
								}
							}
						}
						else{//esta en el vector actual
							cout<<"El contacto lo acabas de aniadir, no se puede duplicar"<<endl;
							encontrado = false;
						}
					}
				}
			}
			buc = true;
			}
		}
		else{
			contactos = desglosar(atribs[3], 1);
			cout<<"Quieres modificar los contactos"<<endl;
			cout<<"1. si"<<endl;
			cout<<"2. no"<<endl;
			cin>>x;
			string cp;
			buc = false;
			if(x == 1){
				while(buc != true){

					for(int l = 0; l < contactos.size(); l++){
						cout<<l+1<<". "+docentes[l] + ": "+contactos[l]<<endl;
					}
					//cout<<"Contactos size "<<contactos.size()<<endl;

					cout<<"Cual quieres cambiar?"<<endl;
					cin>>d;
					if(d > 0 && d <= contactos.size()){
						cout<<"Introduzca el contacto nuevo de " + docentes[d-1]<<endl;
						getline(cin, cp);
						getline(cin, cp);
						cout<<"Quieres que "+cp+" sea el nuevo contacto de "+ docentes[d-1]+"?"<<endl;
						cout<<"1. si"<<endl;
						cout<<"2. no"<<endl;
						cin>>y;
						if(y == 1){
							contactos[d-1] = cp;
							cout<<"quieres editar otro contacto mas?"<<endl;
							cout<<"1. si"<<endl;
							cout<<"2. no"<<endl;
							cin>>z;
							if(z != 1)
								buc = true;
						}
					}
				}
			}
		}
		ndoc = docentes.size();
		atribs[3] = docentes[0] + ": " + contactos[0];
		if(ndoc == 1){
			atribs[3] = atribs[3] + ",";
		}
		for(int i = 1; i < ndoc; i++){
			if(i == ndoc - 1){
				atribs[3] = atribs[3] +" y " + docentes[i] + ": "+contactos[i] + ",";
			}
			else
				atribs[3] = atribs[3] +", "+ docentes[i] +": " + contactos[i];
		}
		cout<<atribs[3]<<endl;
		buc = false;
		getline(re, atribs[4]);//descripcion
		cout<<"La descipcion del curso es <"+atribs[4]+">."<<endl;
		cout<<"Quieres modificarla?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			while(buc != true){
				cout<<"Descripcion: "<<endl;
				cout<<"--> ";
				cin>>atribs[1];
				cout<<"La descripcion seria <"<<atribs[4]<<">"<<endl;
				cout<<"Estas seguro"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cout<<"--> ";
				cin>>x;
				if(x == 1){
					if(comprobarExistencia(atribs[4]) != -1){
						cout<<"Lo sentimos, este nombre ya esta siendo utilizado."<<endl;
						cout<<"Ingrese otro nombre"<<endl;
					}
					else{
						buc = true;
					}
				}
			}
		}
		buc = false;
		y = 0;

		getline(re, atribs[5]);//grados
		getline(re, atribs[6]);//aforo
		cout<<"El aforo del curso es <"+atribs[6]+">."<<endl;
		cout<<"Quieres modificarlo?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>z;
		if(z == 1){
			while(buc != true){
				if(y == 0)
					cout<<"Ahora vamos a introducir aforo maximo"<<endl;
				cout<<"Aforo:"<<endl;
				getline(cin, atribs[6]);
				getline(cin, atribs[6]);
				cout<<"El aforo maximo del curso seria <"<<atribs[6]<<">"<<endl;
				cout<<"Estas seguro"<<endl;
				cout<<"1. Si"<<endl;
				cout<<"2. No"<<endl;
				cout<<"--> ";
				cin>>x;
				if(x == 1){
					buc = true;
				}
				else{
					y = 1;
				}
			}
		}
		buc = false;
		cout<<"Los estudios requeridos del curso son <"+atribs[5]+">."<<endl;
		cout<<"Quieres modificarlos?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			cout<<"Ahora vamos a introducir los estudios requeridos"<<endl;
			atribs[5] = estudiosRequeridos();
		}
		cout<<atribs[5]<<endl;
		getline(re, atribs[7]);//fecha inicio
		cout<<"La fecha de inicio del curso es <"+atribs[7]+">."<<endl;
		cout<<"Quieres modificarla?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			cout<<"Ahora vamos a introducir la fecha de INICIO del curso"<<endl;
			atribs[7] = fecha(0);
		}
		cout<<atribs[7]<<endl;
		buc = false;
		getline(re, atribs[8]);//fecha final
		cout<<"La fecha de final del curso es <"+atribs[8]+">."<<endl;
		cout<<"Quieres modificarla?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>x;
		if(x == 1){
			cout<<"Introduzca la fecha de FIN del curso"<<endl;
			while(buc != true){
				atribs[8] = fecha(1);
				if(stoi(atribs[7].substr(6,4)) >  stoi(atribs[8].substr(6,4))){
					cout<<"El curso debe terminar despues de la fecha de inicio(a)"<<endl;
				}
				else{
					if(stoi(atribs[7].substr(3,2)) >  stoi(atribs[8].substr(3,2))){
					cout<<"El curso debe terminar despues de la fecha de inicio(m)"<<endl;
					}
					else{
						if(stoi(atribs[7].substr(0,2)) >  stoi(atribs[8].substr(0,2))){
							cout<<"El curso debe terminar despues de la fecha de inicio(d)"<<endl;
						}
						else{
							buc = true;
						}
					}
				}
			}
		}
		cout<<atribs[8]<<endl;
		getline(re, atribs[9]);
		//me queda los contactos, que hay que meterlos todos de nuevo, y el resto de cosas

	}
	else{
		return false;
	}
	//ahora vamos a imprimir en la pagina
	c = 1;
	ofstream wr;
	wr.open("open.txt", ios::out);
	if(wr.fail()){
		cout<<"Error de escritura"<<endl;
		return false;
	}
	while(c < curso){
		for(int i = 0; i < 10; i++){
			wr<<datos[i][c-1]<<endl;

		}
		c++;
	}
	for(int i = 0; i < 10; i++){
		if(c == ncur && i == 9){//si es el ultimo curso no mete intro final
			wr<<atribs[9];
		}
		else{
			wr<<atribs[i]<<endl;
		}
	}
	c++;
	if(c <= ncur){//si siguen quedando cursos seguimos imprimiendo
		for(int i = c; i <= ncur; i++){
			for(int j = 0; j < 10; j++){
				if(i == ncur && j == 9){
					wr<<datos[j][i-1];
				}
				else{
					wr<<datos[j][i-1]<<endl;
				}
			}
		}
	}
	wr.close();
	return true;
}

bool eliminarCurso(int ncur){
	bool sel = false;
	int curso, c = 1, x, cont=0;
	vector<string> datos;
	string linea, id;
	cout<<"Introduce el curso que quieres modificar: ";
	cin>>curso;
	ifstream re;
	while(sel != true){
		if(curso <= ncur && curso > 0){//el curso que metamos tiene que estar ahi
			re.open("open.txt", ios::in);
			if(re.fail()){
				cout<<"Error de lectura"<<endl;
				return false;
			}
			while(!re.eof()){//escaneaamos toda la pagina
				getline(re, linea);
				datos.push_back(linea);
				//cout<<linea<<endl;
			}
			id = datos[(curso - 1)*10];
			re.close();
			sel = true;
		}
		else{
			cout<<"Escoge un curso que este disponible"<<endl;
		}
	}
	c = 1;

	cout<<"Es el curso con el id <"+id+"> el que quieres eliminar?"<<endl;
	cout<<"1. Si"<<endl;
	cout<<"2. No"<<endl;
	cin>>x;
	if(x != 1){
		cout<<"No se ha borrado el curso <"+id+">."<<endl;
		return false;
	}
	ofstream wr;
	wr.open("open.txt", ios::out);
	if(wr.fail()){
		cout<<"Error de escritura"<<endl;
		return false;
	}
	for(int i = 0; i < (curso - 1)*10; i++){
		if(i == (curso - 1)*10 - 1)
			wr<<datos[i];
		else
			wr<<datos[i]<<endl;
	}
	//por donde sigue despues
	for(int i = (curso - 1)*10 + 10; i < datos.size(); i++){
		if(i == datos.size() - 1)
			wr<<datos[i];
		else
			wr<<datos[i]<<endl;
	}
	return true;
}
size_t comprobarExistencia(string c){
	ifstream f;
	string linea;
	size_t found;
	f.open("open.txt", ios::in);
	if(f.fail()){
		cout<<"Error al abrir fichero de cursos"<<endl;
		exit(1);
	}
	while(!f.eof()){
		getline(f, linea);
		size_t found = linea.find(c);
		if(found != string::npos){
			return found;
		}
	}
	f.close();
	return -1;
}
string fecha(int mod){
		auto now = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(now);
		string aus = ctime(&end_time);
		string anoActual = aus.substr(aus.length()-5, 4);
		cout<<"Ano actual: "+ anoActual<<endl;
		int anoA = stoi(anoActual);
		//capto el anio actual para ver si el curso se esta creando en el pasado o en una fecha realista
	int ano = 0, anoFlag = 0, mesFlag=0, mes, dayFlag = 0, dia;
	int nmesA, ndiaA;
	string dicciMeses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //Diccionario meses
	string mesActual = aus.substr(4, 3);
	for(int i = 0; i < 12; i++){
		if(mesActual == dicciMeses[i]){
			nmesA = i+1;
			cout<<"Mes actual : "<<nmesA<<endl;
		}
	}
	string diaActual = aus.substr(8, 1);
	if(diaActual == " "){
		diaActual = aus.substr(9, 1);
	}
	else{
		diaActual = aus.substr(8, 2);
	}
	cout<<"El dia actual es: "+diaActual<<endl;
	ndiaA = stoi(diaActual);
	bool visiesto = false;
	string sano, smes, sdia;
	while(anoFlag == 0){
		if(ano == 0){
			if(mod == 0)
				cout<<"Introduce el anio de la fecha de inicio del curso: ";
			else
				cout<<"Introduce el anio de la fecha de final del curso";
		}
		else
			cout<<"Introduce de nuevo el anio: ";
		cin>>ano;
		if(ano < anoA ){ //que el curso sea el mismo anio de creacion o posterior
			cout<<"Fecha no valida"<<endl;
		}
		else{
			sano = to_string(ano);
			if(ano % 4 == 0){
				visiesto = true;
			}
			anoFlag = 1;
		}
	}
	//Mes
	while(mesFlag == 0){
		cout<<"Mes: "<<endl;
		cout<<"1. Enero"<<endl;
		cout<<"2. Febrero"<<endl;
		cout<<"3. Marzo"<<endl;
		cout<<"4. Abril"<<endl;
		cout<<"5. Mayo"<<endl;
		cout<<"6. Junio"<<endl;
		cout<<"7. Julio"<<endl;
		cout<<"8. Agosto"<<endl;
		cout<<"9. Septiembre"<<endl;
		cout<<"10. Octubre"<<endl;
		cout<<"11. Noviembre"<<endl;
		cout<<"12. Diciembre"<<endl;
		cout<<"Introduce el mes: ";
		cin>>mes;
		if(mes < nmesA && ano == anoA){
			cout<<"Fecha pasada, introduzca otra por favor"<<endl;
		}
		else{
			if(mes > 0 && mes < 13){
				switch(mes){
					case 1:
						mes = 1;
						smes = "01";
					break;
					case 2:
						mes = 2;
						smes = "02";
					break;
					case 3:
						mes = 3;
						smes = "03";
					break;
					case 4:
						mes = 4;
						smes = "04";
					break;
					case 5:
						mes = 5;
						smes = "05";
					break;
					case 6:
						mes = 6;
						smes = "06";
					break;
					case 7:
						mes = 7;
						smes = "07";
					break;
					case 8:
						mes = 8;
						smes = "08";
					break;
					case 9:
						mes = 9;
						smes = "09";
					break;
					case 10:
						mes = 10;
						smes = "10";
					break;
					case 11:
						mes = 11;
						smes = "11";
					break;
					case 12:
						mes = 12;
						smes = "12";
					break;
				}
				mesFlag = 1;
			}
			else{
				cout<<"Fecha no valida"<<endl;
			}
		}
	}

	while(dayFlag == 0){
		cout<<"DIA: "<<endl;
		cout<<"01  ";cout<<"02  ";cout<<"03  ";cout<<"04  ";cout<<"05  ";cout<<"06  ";	cout<<"07  "<<endl;
		cout<<"08  ";cout<<"09  ";cout<<"10  ";cout<<"11  ";cout<<"12  ";cout<<"13  ";	cout<<"14  "<<endl;
		cout<<"15  ";cout<<"16  ";cout<<"17  ";cout<<"18  ";cout<<"19  ";cout<<"20  ";	cout<<"21  "<<endl;
		cout<<"22  ";cout<<"23  ";cout<<"24  ";cout<<"25  ";cout<<"26  ";cout<<"27  ";	cout<<"28  "<<endl;
		cout<<"29  ";cout<<"30  ";cout<<"31  "<<endl;
		cout<<"Introduce el dia: ";
		cin>>dia;
		if(dia > 0 && dia < 32){ //dia valido
			if(nmesA == mes && dia <= ndiaA && ano == anoA){ //el curso ha de empezar un dia despues de su creacion como minimo
				cout<<"Fecha tardia, no es posible"<<endl;
			}
			else{
				if(mes == 2 && dia < 30){//si es febrero
					if(dia == 29 && visiesto == true){//es 29 y es visiesto
						cout<<"Dia 29 de febrero valido"<<endl;
						sdia = "29";
						dayFlag = 1;
					}
					else if(dia == 29 && visiesto != true){ //si es 29 y no es visiesto
						cout<<"No puede ser, no me la cuelas"<<endl;
					}
					else if(dia != 29){//si no es 29 y me da igual que sea visiesto
						cout<<"Dia valido"<<endl;
						sdia = to_string(dia);
						dayFlag = 1;
					}
				}
				else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
					if(dia == 31){
						cout<<"Error, este 31 no existe"<<endl;
					}
					else{
						cout<<"Dia valido"<<endl;
						sdia = to_string(dia);
						dayFlag = 1;
					}
				}
				else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
					cout<<"Dia valido"<<endl;
					sdia = to_string(dia);
					dayFlag = 1;
				}
				else{
					cout<<"Dia no valido porque no existe el 30 o 31 de febrero"<<endl;
				}
			}
		}
	}
	if(dayFlag == 1){
		if(sdia.length() == 1){
			return "0"+sdia +"/"+ smes+"/" + sano;
		}
		else
			return sdia +"/"+ smes+"/" + sano;
	}
	return "";
}
string estudiosRequeridos(){
	int flag = 0, i = 0, c;
	string value = "";
	while(flag != -1){
		cout<<"1. Grado en Administración y Dirección de Empresas"<<endl;
		cout<<"2. Grado en Biología"<<endl;
		cout<<"3. Grado en Bioquímica"<<endl;
		cout<<"4. Grado en Ciencias Ambientales"<<endl;
		cout<<"5.Grado en Ciencia y Tecnología de los Alimentos"<<endl;
		cout<<"6.Grado en Cine y Cultura"<<endl;
		cout<<"7.Grado en Derecho"<<endl;
		cout<<"8.Grado en Educación Infantil"<<endl;
		cout<<"9.Grado en Educación Infantil (Itinerario Bilingüe)"<<endl;
		cout<<"10.Grado en Educación Primaria"<<endl;
		cout<<"11.Grado en Educación Primaria (Itinerario Bilingüe)"<<endl;
		cout<<"12.Grado en Educación Social"<<endl;
		cout<<"13.Grado en Enfermería"<<endl;
		cout<<"14.Grado en Estudios Ingleses"<<endl;
		cout<<"15.Grado en Filología Hispánica"<<endl;
		cout<<"16.Grado en Física"<<endl;
		cout<<"17.Grado en Fisioterapia"<<endl;
		cout<<"18.Grado en Gestión Cultural"<<endl;
		cout<<"19.Grado en Historia"<<endl;
		cout<<"20.Grado en Historia del Arte"<<endl;
		cout<<"21.Grado en Psicología"<<endl;
		cout<<"22.Grado en Ingeniería Civil (2 tecnologías)"<<endl;
		cout<<"23.Grado en Ingeniería Eléctrica"<<endl;
		cout<<"24.Grado en Ingeniería Electrónica Industrial"<<endl;
		cout<<"25.Grado en Ingeniería Forestal"<<endl;
		cout<<"26.Grado en Ingeniería Informática"<<endl;
		cout<<"27.Grado en Ingeniería Mecánica"<<endl;
		cout<<"28.Grado en Veterinaria"<<endl;
		cout<<"29.Grado en Medicina"<<endl;
		cout<<"30.Grado en Química"<<endl;
		cout<<"31.Grado en Relaciones Laborales y Recursos Humanos"<<endl;
		cout<<"32.Grado en Traducción e Interpretación"<<endl;
		cout<<"33.Grado en Turismo"<<endl;
		cout<<"34.Grado en Ingeniería de Recursos Energéticos y Mineros"<<endl;
		cout<<"35.Grado en Ingeniería Agroalimentaria y del Medio Rural"<<endl;
		cout<<"---------------------------------------------------------"<<endl;
		if(flag == 0){
			cout<<"Que grado corresponde con los estudios requeridos?-->";
			cin>>c;
			flag++;
		}
		else{
			i = 0;
            cout<<"Llevas aniadido "<<value<<endl;
			cout<<"Otro grado que quieras aniadir?-->"<<endl;
			cout<<"1. Si"<<endl;
			cout<<"2. No"<<endl;
			cin>>i;
			if(i == 1){
				cout<<"Cual?-->";
				cin>>c;
			}
			else{
				flag = -1;
                return value;
			}
		}
		switch(c){
			case 1:
				value = value + "// " + "Grado en Administración y Dirección de Empresas";
			break;
			case 2:
				value = value + "// " + "Grado en Biología";
			break;
			case 3:
				value = value + "// " + "Grado en Bioquímica";
			break;
			case 4:
				value = value + "// " + "Grado en Ciencias Ambientales";
			break;
			case 5:
				value = value + "// " + "Grado en Ciencia y Tecnología de los Alimentos";
			break;
			case 6:
				value = value + "// " + "Grado en Cine y Cultura";
			break;
			case 7:
				value = value + "// " + "Grado en Derecho";
			break;
			case 8:
				value = value + "// " + "Grado en Educación";
			break;
			case 9:
				value = value + "// " + "Grado en Educación Infantil (Itinerario Bilingüe)";
			break;
			case 10:
				value = value + "// " + "Grado en Educación Primaria";
			break;
			case 11:
				value = value + "// " + "Grado en Educación Primaria (Itinerario Bilingüe)";
			break;
			case 12:
				value = value + "// " + "Grado en Educación Social";
			break;
			case 13:
				value = value + "// " + "Grado en Enfermería";
			break;
			case 14:
				value = value + "// " + "Grado en Estudios Ingleses";
			break;
			case 15:
				value = value + "// " + "Grado en Filología Hispánica";
			break;
			case 16:
				value = value + "// " + "Grado en Física";
			break;
			case 17:
				value = value + "// " + "Grado en Fisioterapia";
			break;
			case 18:
				value = value + "// " + "Grado en Gestión Cultural";
			break;
			case 19:
				value = value + "// " + "Grado en Historia";
			break;
			case 20:
				value = value + "// " + "Grado en Historia del Arte";
			break;
			case 21:
				value = value + "// " + "Grado en Psicología";
			break;
			case 22:
				value = value + "// " + "Grado en Ingeniería Civil";
			break;
			case 23:
				value = value + "// " + "Grado en Ingeniería Eléctrica";
			break;
			case 24:
				value = value + "// " + "Grado en Ingeniería Electrónica Industrial";
			break;
			case 25:
				value = value + "// " + "Grado en Ingeniería Forestal";
			break;
			case 26:
				value = value + "// " + "Grado en Ingeniería Informática";
			break;
			case 27:
				value = value + "// " + "Grado en Ingeniería Mecánica";
			break;
			case 28:
				value = value + "// " + "Grado en Veterinaria";
			break;
			case 29:
				value = value + "// " + "Grado en Medicina";
			break;
			case 30:
				value = value + "// " + "Grado en Química";
			break;
			case 31:
				value = value + "// " + "Grado en Relaciones Laborales y Recursos Humanos";
			break;
			case 32:
				value = value + "// " + "Grado en Traducción e Interpretación";
			break;
			case 33:
				value = value + "// " + "Grado en Turismo";
			break;
			case 34:
				value = value + "// " + "Grado en Ingeniería de Recursos Energéticos y Mineros";
			break;
			case 35:
				value = value + "// " + "Grado en Ingeniería Agroalimentaria y del Medio Rural";
			break;
			default:
				value = value + "";
                cout<<"No existe este";
			break;
		}
	}
    return value;
}
vector<string> desglosar(string linea, int tipo){
	int lastPos = 0, j = 0;
	bool coma = false, done = false;
	vector<string> v;
	if(tipo == 0){//docente
		for(int i = 0; i < linea.length(); i++){
			if(linea[i] == ','){
				v.push_back(linea.substr(lastPos, i - lastPos));
				//cout<<linea.substr(lastPos, i - lastPos)<<endl;
				lastPos = i + 2;
			}
			else if(linea[i] == 'y' && linea[i+1] == ' ' && linea[i-1] == ' '){
				v.push_back(linea.substr(lastPos, i - lastPos - 1));
				//cout<<linea.substr(lastPos, i - lastPos -1)<<endl;
				lastPos = i + 2;
			}
			else if(linea[i] == '.'){
				v.push_back(linea.substr(lastPos, i - lastPos));
				//cout<<linea.substr(lastPos, i - lastPos)<<endl;
			}
		}
	}
	else if(tipo == 1){//contactos
		while(j < linea.length()){
			if(linea[j] == ':'){
				lastPos = j + 2;
			}
			if(lastPos < j && linea[j] == ','){
				v.push_back(linea.substr(lastPos, j - lastPos));
				//cout<<linea.substr(lastPos, j - lastPos)<<"yeaaaah"<<endl;
			}
			else if(lastPos < j && linea[j] == 'y' && linea[j+1] == ' ' && linea[j-1] == ' '){
				v.push_back(linea.substr(lastPos, j - lastPos - 1));
				//cout<<linea.substr(lastPos, j - lastPos - 1)<<"yeaaah"<<endl;
			}
			j++;
		}
	}
	else if(tipo == 2){
		while(j < linea.length()){
			if(linea[j] == '/' && linea[j+1] =='/'){
				lastPos = j;
			}
			if(lastPos < j && linea[j + 1] == '/' && linea[j+2] =='/'){
				v.push_back(linea.substr(lastPos, j - lastPos+1));
				//cout<<linea.substr(lastPos, j - lastPos)<<"yeaaaah"<<endl;
			}
			else if(lastPos < j && j == linea.length()-1){
				v.push_back(linea.substr(lastPos, j - lastPos +1));
				//cout<<linea.substr(lastPos, j - lastPos - 1)<<"yeaaah"<<endl;
			}
			j++;
		}
	}
	return v;
}
