#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

using namespace std;

string tema, contenido;

// Nombre del directorio o carpeta
const string directorio = "Sistema de Flashcards";

int n = 0, i, id;

string* nombresMazos = nullptr;

string ruta(string nombreArchivo){
	return (directorio + "/" + nombreArchivo);
}

void escribir();
void lectura();
void aniadir();

void menuCartas();
void crearMazo();
void mostrarMazos(bool soloLectura);
void renombrarMazo();
void eliminarMazo();
void crearCarta();
void mostrarCartas();
void editarCarta();
void eliminarCarta();


int main() {
	string opcion;
	
	// Crear el directorio  o carpeta
	if (_mkdir(directorio.c_str())) {
		cout << "Ha ocurrido un error en la creación de la carpeta";
	}
	
	do{
		// Mostramos el menú de opciones del contenedor
		cout << "\nCONTENEDOR DE FLASHCARDS\n";
		cout << "\nMenú de opciones:\n";
        cout << "1. Crear mazo\n";
        cout << "2. Mostrar mazos\n";
        cout << "3. Renombrar mazo\n";
        cout << "4. Eliminar mazo\n";
        cout << "0. Salir\n";
        
        // Solicitamos la opción al usuario
		fflush(stdin);
		cout << "Seleccione una opción: ";
		getline(cin, opcion);
		
		// Limpiamos la pantalla
		system("cls");
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opcion[0]) {
			case '1': {
				crearMazo();
				break;
			}
			case '2': {
				mostrarMazos(false);
				break;
			}
			case '3': {
				renombrarMazo();
				break;
			}
			case '4': {
				eliminarMazo();
				break;
			}
			case '0': {
				cout << "Saliendo del programa..." << endl;
				system("pause");
				break;
			}
			default: {
				cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
				system("pause");
				break;
			}
		}
		system("cls");
	} while (opcion[0] != '0');
}

void menuCartas() {
	int opcion;
	
	do{
		// Mostramos el menú de opciones del contenedor
		cout << "\nFLASHCARDS\n";
		cout << "\nMenú de opciones:\n";
        cout << "1. Crear flashcards\n";
        cout << "2. Mostrar flashcards\n";
        cout << "3. Editar flashcards\n";
        cout << "4. Eliminar flashcard\n";
        cout << "0. Salir\n";
        
        
        // Solicitamos la opción al usuario
		cout << "Seleccione una opción: "; cin >> opcion;
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opcion) {
			case 1: {
				crearCarta();
				break;
			}
			case 2: {
				mostrarCartas();
				break;
			}
			case 3: {
				editarCarta();
				break;
			}
			case 4: {
				eliminarCarta();
				break;
			}
			default: {
				cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
				break;
			}
		}
	} while (opcion != 0);
}

void crearMazo() {
	string nombreMazo;
	
	fflush(stdin);
	cout << "Nombre del mazo: "; getline(cin, nombreMazo);
	
	// Crea un archivo en una carpeta
	ofstream archivo(ruta(nombreMazo));
	
	if(archivo.fail()) {
		cout << "No se pudo crear el mazo" << endl;
	}
	
	archivo.close();
}

void mostrarMazos(bool soloLectura) {
	// Almacena la informacion de un archivo
	_finddata_t archivo;
	
	// Crea un verificador que comprueba si hay archivos .txt
	intptr_t verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
	
	// Verifica si la busqueda fue exitosa
	if (verificador != -1) {
		
		//Hallar la cantidad de mazos
		do {
			n++;	
		} while (_findnext(verificador, &archivo) == 0);
		
		_findclose(verificador);
		
		// Define el vector global nombresMazos
		nombresMazos = new string [n];
		// Almacena en el vector los nombres de los mazos y los muestra
		verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
		
		i=0;
		do {
			nombresMazos[i] = archivo.name;
			cout << i << ' ' << nombresMazos[i] << endl;
			i++;
		} while (_findnext(verificador, &archivo) == 0);
		_findclose(verificador);
		
		if (soloLectura == false) {
			menuCartas();
		} 	
	} else {
		cout << "No se encontraron mazos en el directorio" << endl;
	}
}

void renombrarMazo() {
	mostrarMazos(true);
	string nuevoNombre;
	
	fflush(stdin);
	cout << "ID del mazo que desea renombrar: "; cin >> id;
	// Extrae el nombre del mazo a partir del id
	fflush(stdin);
	cout << "Nuevo nombre del mazo: "; getline(cin, nuevoNombre);
	
	if (rename (ruta(nombresMazos[id]).c_str(), ruta(nuevoNombre + ".txt").c_str() ) != 0) {
        cout << "Error al renombrar el mazo." << endl;
    } else {
    	cout << "El nombre del mazo se ha cambiado correctamente" << endl;
	}
	system("pause");
    
}

void eliminarMazo() {
	mostrarMazos(true);
	int id;
	
	fflush(stdin);
	cout << "ID del mazo que desea eliminar: "; cin >> id;
	
	if (remove( ruta(nombresMazos[id]).c_str() ) != 0) {
        cout << "Error al eliminar el mazo." << endl;
    } else {
    	cout << "El mazo se ha eliminado correctamente" << endl;
	}
}

void crearCarta() {
	string nombreMazo;
	bool continuar;
	
	mostrarMazos(true);
	
	fflush(stdin);
	cout << "ID del mazo: "; cin >> id;
	
	ofstream mazo;
	mazo.open( ruta(nombresMazos[id]), ios::app );
	
	if(mazo.fail()){
		cout<<"No se pudo abrir el mazo"<<endl;
		return;
	}
	
	do {
		fflush(stdin);
		cout << "Tema: "; getline(cin, tema);
		cout << "Contenido: "; getline(cin, contenido);
		mazo << "t:: " << tema << endl << "c:: " << contenido << endl << endl;
		cout << "Desea agregar más flashcards (Sí = 1) (No = 0): ";
		cin >> continuar;
	} while (continuar);
	
	mazo.close();
}

void mostrarCartas() {
	
}

void editarCarta() {
	
}

void eliminarCarta() {
	
}

//ELIMianRARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

void lectura(){
	ifstream archivo; //-----Escribir texto
	string texto;
	
	archivo.open("flashcards.txt",ios::in); //Abrir el archivo en modo lectura
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		return;
	}
	
	while(getline(archivo, texto)){ //Mientras el archivo no esté en el final
		cout<<texto<<endl;
	}
	
	archivo.close();
}

void aniadir(){
	ofstream archivo; //Abrir el archivo para escritura
	string texto;
	
	 //Abrimos el archivo en modo añadir
	
	
	
	cout<<"Digite el texto que quiere añadir: ";
	getline(cin, texto);
	
	archivo<<texto<<endl;
	
	archivo.close(); //Cerramos el archivo
}