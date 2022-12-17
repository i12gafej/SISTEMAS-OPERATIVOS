/*
 * participante.cpp
 *
 *  Created on: 6 dic 2022
 *      Author: USUARIO
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "participante.h"

using namespace std;


Participante::Participante(string correo,
		string contra,
		string nombre = "null",
		string dni = "null",
		string estudios = "null",
		string telefono = "null",
		string nacimiento = "null",
		string cmatriculados = "null"):Usuario(correo, contra){}
bool Participante::globalset(string cor){
	ifstream f, g;
	string linea, atribs[5], a,b,rol;
	vector<string> v;
	v.push_back("");
	int ncmat = 0, iters, flag = 0;
	f.open("matriculas.txt", ios::in);
	g.open("logs.txt", ios::in);
	if(f.fail() || g.fail()){
		cout<<"Error al obtener datos en fichero matricula."<<endl;
		return false;
	}
	while(!f.eof()){
		getline(f, linea);//escanea cada linea hasta dar con el correo
		if(linea == cor){
			flag++;
			for(int i = 0 ; i < 5 ; i++){
				getline(f, linea);//escaneamos dni, nombre, estudios, telefono y nacimiento
				atribs[i] = linea;
			}
			getline(f, linea); //escaneamos los cursos
			bool tri = false;
			while(tri != true){//o si hay guion no escanea nada
				if(linea != "-"){
					v.push_back(linea);
					getline(f, linea);
				}
				else
					tri = true;
			}
		}
	}
	if(flag == 0){
		while(!g.eof()){
			getline(g, a);
			getline(g, b);
			getline(g, rol);
			if(cor == a){
				if(rol == "2"){//si tenemos a un coordinador de curso pasamos de aniadir sus datos
					flag = 1;
				}
			}
		}
	}
	f.close();
	g.close();
	if(flag == 0){//no se ha encontrado el correo en los perfiles, no esta registrado
		cout<<"No tienes datos en la base de datos"<<endl;
		cout<<"Vas a introducir tus datos personales"<<endl;
		//dni
		cout<<"Introduce tu DNI: ";
		cin>>atribs[0];
		cout<<endl;
		cout<<"Introduce Tu nombre completo: ";
		getline(cin,atribs[1]);
		getline(cin,atribs[1]);
		cout<<endl;
		cout<<"Elige tus estudios: ";
		atribs[2] = estudiosPosibles() ;
		cout<<endl;
		cout<<"Introduce numero de telefono: ";
		cin>>atribs[3];
		cout<<endl;
		cout<<"Seleccione su Fecha de nacimiento: ";
		atribs[4] = fechaPosible();
	}
	iters = v.size();
	set_dni(atribs[0]);
	set_nombre(atribs[1]);
	set_estudios(atribs[2]);
	set_telefono(atribs[3]);
	set_nacimiento(atribs[4]);
	if(flag != 0){
		string cursos;
		cursos = concatenar(v, iters-1);
		cout<<"ESTA MATRICULAO EN "<<cursos<<endl;
		set_cmatriculados(cursos);
		return true;
	}
	else if(flag == 0){
		if(imprimirPerfilNuevo(cor, atribs)==true){
			cout<<"Registrado con exito"<<endl;
			return true;
		}
	}
	return true;
}
//FUNCIONES DE PARTICIPANTE
bool imprimirPerfilNuevo(string cor, string w[]){
	ifstream re;
	vector<string> v;
	string linea;
	int lines = 0;
	re.open("matriculas.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
	while(!re.eof()){
		getline(re, linea);
		v.push_back(linea);
		lines++;
	}
	if(v[v.size()-1] != "-"){ //Si no es un gion el ulitmo elemento del fichero eliminamos el ultimo elemento del vector para no crear espacios en blanco
		v.pop_back();
	}
	cout<<"Numero de lineas: "<<lines<<endl;
	cout<<"Numero de elementos de v: "<<v.size()<<endl;
	re.close();
	ofstream wr;
	wr.open("matriculas.txt", ios::out);//machaca matriculas con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	int i = 0;
	while(i < v.size()){
		wr<<v[i]<<endl;
		i++;
	}
	wr<<cor<<endl;
	wr<<w[0]<<endl;
	wr<<w[1]<<endl;
	wr<<w[2]<<endl;
	wr<<w[3]<<endl;
	wr<<w[4]<<endl;;
	wr<<"-";

	wr.close();
	return true;
}
string fechaPosible(){
	//Ano
	int ano = 0, anoFlag = 0, mesFlag=0, mes, dayFlag = 0, dia;
	bool visiesto = false;
	string sano, smes, sdia;
	while(anoFlag == 0){
		if(ano == 0)
			cout<<"Introduce el anio de tu nacimiento: ";
		else
			cout<<"Introduce de nuevo tu anio de nacimiento: ";
		cin>>ano;
		if(ano < 1915 || ano > 2013){ //Ni mas de 107 ni menos de 9 anios xd
			cout<<"Fecha de nacimiento no valida"<<endl;
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
		cout<<"Introduce el mes de tu nacimiento: ";
		cin>>mes;
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
	if(dayFlag == 1){
		if(sdia.length() == 1){
			return "0"+sdia + smes + sano;
		}
		else
			return sdia + smes + sano;
	}
	return "";
}
string estudiosPosibles(){
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
			cout<<"Cual es tu grado?-->";
			cin>>c;
			flag++;
		}
		else{
			i = 0;
            cout<<"Llevas seleccionados los siguientes grados: "<<value<<endl;
			cout<<"Otro grado al que pertenezcas o tengas?-->"<<endl;
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
                cout<<"No existe este"<<endl;
			break;
		}
	}
    return value;
}
//funcion recursiva que concatena los nombres de los cursos matriculados
string concatenar(vector<string> v, int n){
	string resul;
    if(n < 0){
		return resul;
	}
    else if(n == 0)
        resul = v[n] +  concatenar(v, n-1);
    else{
        resul = v[n] + " // " + concatenar(v, n-1);
    }
    return resul;
}
bool Participante::matricularse(){
	bool valid = false;
	string aforo, date, estudios, linea, participantes, nombre;
	int cual, curso, ticks = 0, partips, afor;
	while(valid != true){
		cual = Usuario::verListas();
		cout<<"En que curso de extension de los "<<cual<<" desea matricularse?"<<endl;
		cin>>curso;
		if(curso < 1 || curso > cual){
			cout<<"Curso no valido, prueba de nuevo."<<endl;
		}
		else{
			if(buscarCurso(curso, cual) == true){ //el curso existe
				cout<<"EN PROCESO DE IMPRESION"<<endl;
				//tenemos que hacer 4 comprobaciones,
				//1. antes que nada ver si el alumno esta matriculado ya
				//2. si el curso tienee aforo
				//3. si se tienen los estudios requeridos
				//4. si es antes de la fecha de inicio
				ifstream f;
				f.open("open.txt", ios::in);
				if(f.fail()){
					cout<<"Error al leer fichero open"<<endl;
					exit(1);
				}
				for(int i = 1; i < curso; i++){//recorre cursos
					for(int l = 0; l < 10; l++){//recorre atributos de cada curso
						getline(f, linea);
					}
				}
				for(int i = 0; i < 5; i++){
					//recorre de ID a descripcion
					if(i == 1){
						getline(f, nombre);
					}
					else
						getline(f, linea);
				}

				string cmat = get_cmatriculados();
				cout<<endl;
				size_t found = cmat.find(nombre);//en found se guarda la posicion de encontrar
				if(found != string::npos){
					cout<<"Este alumno ya esta registrado en el curso. //"<<found<<endl;
					return false;
				}
				getline(f, estudios);//capta estudios
				string cestudios = get_estudios();

				vector<string> studis = desglosa(cestudios, 2);
				int nestcontaos = 0;
				while(nestcontaos <= studis.size() - 1){
					found = estudios.find(studis[nestcontaos]);
					if(found != string::npos){//3. si se tienen los estudios requeridos
						cout<<"ESTUDIOS VALIDOS"<<endl;
						ticks++;
						nestcontaos = studis.size();
					}
					else{
						nestcontaos++;
					}
				}
				getline(f, aforo);//aforo
				getline(f, date);//fecha inicio
				auto now = chrono::system_clock::now();//semilla reloj activa
				time_t end_time = chrono::system_clock::to_time_t(now);//semilla parada y guarda hora
				string aus = ctime(&end_time); //guardamos fecha en ahora
				string ahora = aus.substr(4);//quitamos parte del string
				if(comprobarFecha(ahora, date)==true){//4. si es antes de la fecha de inicio
					ticks++;
					cout<<"FECHA VALIDA"<<endl;
				}
				getline(f, linea);//fecha fin
				getline(f, participantes);//participantes
				partips = stoi(participantes);
				//cout<<"Hay "<<partips<<" participantes ";
				afor = stoi(aforo);
				//cout<<"para un aforo de "<<afor<<" estudiantes"<<endl;
				if(partips < afor){//2. si el curso tienee aforo
					ticks++;
					cout<<"AFORO VALIDO"<<endl;
				}
				else{
					cout<<"Aforo completo"<<endl;
				}

				f.close();
				if(ticks == 3){
					if(actualizarCursos(partips, cual, curso)==true){
						cout<<"Base de datos actualizada."<<endl;
						if(actualizarMatricula(get_dni(), nombre)==true){
							cout<<"Base de datos de matriculas acctuaalizada."<<endl;
							valid = true;
							return true;
						}
						else{
							cout<<"Error al actualizar base de datos de matriculas."<<endl;
							return false;
						}
					}
					else{
						cout<<"Error al actualizar base de datos de cursos."<<endl;
						return false;
					}

				}
				else{
					cout<<"No puedes matricularte en este curso, ya que no se cumplen los requerimientos posibles para ello."<<endl;
					return false;
				}

			}
			else{
				cout<<"No te matriculas en nada."<<endl;
				valid = true;
			}
		}
	}
	return false;
}
bool actualizarMatricula(string dni, string nombre){
	ifstream re;
	int posi = 0, lines = 0;
	vector<string> v;
	string linea;
	re.open("matriculas.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
	while(!re.eof()){
		getline(re, linea);
        v.push_back(linea);
		if(linea == dni){
			posi = lines; //guardamos la posicion del dni del alumno matriculado
            //cout<<"Posicion de la linea del dni que buscamos aqui <"<<posi<<">"<<endl;
		}
        //cout<<"v["<<lines<<"]= "<<linea<<endl;
		lines++;
	}
    if(v[v.size()-1] != "-"){ //Si no es un gion el ulitmo elemento del fichero eliminamos el ultimo elemento del vector para no crear espacios en blanco
        v.pop_back();
    }
    //cout<<"Numero de lineas: "<<lines<<endl;
    //cout<<"Numero de elementos de v: "<<v.size()<<endl;
	re.close();
	ofstream wr;
	wr.open("matriculas.txt", ios::out);//machaca open con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	int i = 0, flag = 0, iter = 0;
	while(i < v.size()){
		if(i == posi + 5 && flag == 0){		//si estamos en 5 posiciones del dni
			wr<<nombre<<endl;   //escribimos el curso al que se ha matriculado
            //cout<<"v["<<iter<<"]= "<<nombre<<endl;
            flag++;
            iter++;
        }
		else{
			wr<<v[i]<<endl;
            //cout<<"v["<<i<<"]= "<<v[i]<<endl;
            i++;
            iter++;
        }
	}
	wr.close();
	return true;
}
bool actualizarCursos(int p, int ncursos, int curso){
	//bolcar datos en vector e imprimirlos en open.txt
	string a[10][ncursos], ausi;
    curso--;
	ifstream re;
	int c = 0, lines = 0;
	re.open("open.txt", ios::in);
	if(re.fail()){
		cout<<"Error de abrir fichero de lectura."<<endl;
		return false;
	}
    string participantes = to_string(p+1);
	while(!re.eof() && c < ncursos){
		for(int i = 0 ; i < 10 ; i++){
			if(i == 9 && c == curso){
				a[9][c] = participantes;
                //cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;
                getline(re, ausi);
            }
			else{
				getline(re, a[i][c]);
                //cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;

            }
            lines++;
		}
		c++;
        //cout<<"c = "<<c<<endl;
	}

    c = 0;
	re.close();
	ofstream wr;
	wr.open("open.txt", ios::out);//machaca open con los datos actualizados
	if(wr.fail()){
		cout<<"Error de abrir fichero de escritura."<<endl;
		return false;
	}
	while(!wr.eof() && c < ncursos){
		for(int i = 0 ; i < 10 ; i++){
			if(i == 9 && c == ncursos - 1){
                wr<<a[i][c];
                //cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;
            }
            else{
                wr<<a[i][c]<<endl;
                //cout<<"a["<<i<<"]["<<c<<"] = "<<a[i][c]<<endl;
            }
		}
		c++;
	}
	wr.close();
	return true;
}
bool comprobarFecha(string ahora, string date){//traduce la fecha chrono a la de la bbdd
	//Comparar año
	int yearA, yearB, checks = 0;
	string anoActual = ahora.substr(ahora.length()-4, 4);
	string anoInicio = date.substr(6,4);
	yearA = stoi(anoActual);
	yearB = stoi(anoInicio);
	if(yearA == yearB){ //Si el año es el mismo años tenemos que averiguar el mes y el dia
		checks++;
		//Comparar Mes
		int nmesA, nmesB;
		string dicciMeses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //Diccionario meses
		string mesActual = ahora.substr(0, 3);
		string mesInicio = date.substr(3,2);
		for(int i = 0; i < 12; i++){//pasamos los meses a numeros
			if(mesActual == dicciMeses[i])
				nmesA = i;
			else if(mesInicio == dicciMeses[i])
				nmesB = i;
		}
		if(nmesA == nmesB){//si estamos antes(<) o en el mismo mes (=) estamos bien
			checks++;
			//Comparar Dia
			int dayA, dayB;
			string diaActual;
			if(ahora[6] == ' '){
					diaActual = "0"+ ahora.substr(5,1);
				}
				else{
					diaActual = ahora.substr(5,2);
				}
			string diaInicio = date.substr(9,9);
			dayA = stoi(diaActual);
			dayB = stoi(diaInicio);
			if(dayA < dayB){//si nos matriculamos un dia antes si podemos
				checks++;
			}
			else{
				cout<<"Este curso ya ha empezado(d)."<<endl;
				return false;
			}
		}
        else if(nmesA < nmesB) //si es el mismo año pero el mes de matricula es menor estamos bien
            return true;
		else{
			cout<<"Este curso ya ha empezado(m)."<<endl;
			return false;
		}
	}
    else if(anoActual < anoInicio)//si el año actual es menos que el inicial, directamente estamos en la fecha
        return true;
	else{
		cout<<"Este curso ya ha empezado(a)."<<endl;
		return false;

	}
	if(checks == 3){
		cout<<"!!!FECHA CORRECTA!!!"<<endl;
		return true;
	}
	else if(checks == 2){
		cout<<"LLEGAS UNOS DIAS TARDE"<<endl;
		return false;
	}
	else if(checks == 1){
		cout<<"LLEGAS UNOS MESES TARDE"<<endl;
		return false;
	}
	else if(checks == 0){
			cout<<"LLEGAS UNOS ANHITOS TARDE"<<endl;
			return false;
	}
	return false;
}
bool buscarCurso(int curso, int ncursos){
	int i = 1, c;
	string linea,nombre;
	ifstream fichero;
	fichero.open("open.txt", ios::in);
	if(fichero.fail()){
		cout<<"Error al acceder al fichero de cursos"<<endl;
		exit(1);
	}
	while(i < curso && i < ncursos){
		for(int j = 0; j < 10 ; j++){
			getline(fichero, linea);//escaneamos un curso completo
			//cout<<linea<<endl;
		}							//hasta llegar al que queremos
			i++;
	}
	if(i == curso && i <= ncursos){//si la posicion está en el curso y no supera los ncursos estamos bien
		getline(fichero, nombre);//nombre del curso que queremos
		fichero.close();
		cout<<"Es <"<<nombre<<"> el curso donde te quieres matricular?"<<endl;
		cout<<"1. Si"<<endl;
		cout<<"2. No"<<endl;
		cin>>c;
		if(c == 1)
			return true;
		else
			return false;

	}
	else if(fichero.eof()){
		cout<<"No se ha podido acceder al curso(f)"<<endl;
		return false;
	}
	else{
		cout<<"No se ha podido acceder al curso(otro)"<<endl;
		return false;
	}
	return false;
}
void Participante::paginaParticipante(int vez){
	cout<<endl;
	cout<<endl;
	cout<<endl;
	if(vez == 0){ //Si es la primera vez que entra pone vienbenido
		cout<<"BIENVENIDO <"<<get_nombre()<<">."<<endl;
		cout<<"-------------------------------------------------"<<endl;
	}
	int c;
	bool mat;
	cout<<"Que desea hacer?"<<endl;
	menuParticipante();
	cin>>c;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	switch(c){
	case 1:
		verListas();
		if(opcionaMatricula() == true){
			mat = matricularse();
			if(mat == false || mat == true){
				if(mat == true){
					cout<<"Inscripcion con exito"<<endl;
					globalset(get_correo());
				}
				cout<<endl;
				cout<<endl;
				cout<<endl;
				paginaParticipante(1);
			}

		}
		else{
			paginaParticipante(1);
		}
	break;
	case 2:
		exit(1);
	default:
		cout<<"Argumento no valido";
		cout<<endl;
		cout<<endl;
		cout<<endl;
	}
}
void menuParticipante(){
	cout<<"1. Ver cursos de extension"<<endl;
	cout<<"2. Salirse"<<endl;
}
bool opcionaMatricula(){
	int c;
	cout<<"Desea matricularse en algun curso?"<<endl;
	cout<<"1. Si"<<endl;
	cout<<"2. No"<<endl;
	cin>>c;
	switch(c){
	case 1:
		return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}
vector<string> desglosa(string linea, int tipo){
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
