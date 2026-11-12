#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class Estudiante {
private:
	string nombre;
	int anio;
	double gpa;
	double presupuesto;
	
public:
	Estudiante(string n="NN",int a=0, double g=0, double p=0) {
		nombre = n;
		anio = a;
		gpa = g;
		presupuesto = p;
	}
	string getNombre() { 
		return nombre; 
	}
	int getAnio() { 
		return anio; 
	}
	double getGpa() { 
		return gpa; 
	}
	double getPresupuesto() { 
		return presupuesto; 
	}
	
	double indiceUniversidad() {
		return fabs(gpa - 3)*presupuesto;
	}
};

class Gestor {
private:
	vector<Estudiante> estudiantes;
	double valor(Estudiante e, int criterio) {
		if (criterio == 1)
			return e.getAnio();
		if (criterio == 2) 
			return e.getGpa();
		if (criterio == 3) 
			return e.getPresupuesto();
		return e.indiceUniversidad();
	}
public:
		int cantidad() { 
			return estudiantes.size(); 
		}
		Estudiante obtener(int indice) {
			return estudiantes[indice];
		}
		void insertarAlFinal(Estudiante e) {
			estudiantes.push_back(e);
		}
		bool insertarEnIndice(int indice, Estudiante e) {
			if (indice < 0 || indice > cantidad()) 
				return false;
			estudiantes.insert(estudiantes.begin() + indice, e);
			return true;
		}
		bool eliminarUltimo() {
			if (cantidad() == 0) 
				return false;
			estudiantes.pop_back();
			return true;
		}
		bool eliminarEnIndice(int indice) {
			if (indice < 0 || indice >= cantidad()) return false;
			estudiantes.erase(estudiantes.begin() + indice);
			return true;
		}
		bool actualizar(int indice, Estudiante e) {
			if (indice < 0 || indice >= cantidad()) return false;
			estudiantes[indice] = e;
			return true;
		}
		void ordenar(int criterio) {
			for (int i = 0; i < cantidad() - 1; i++) {
				for (int j = 0; j < cantidad() - 1 - i; j++) {
					if (valor(estudiantes[j], criterio) > valor(estudiantes[j + 1], criterio)) {
						Estudiante temporal = estudiantes[j];
						estudiantes[j] = estudiantes[j + 1];
						estudiantes[j + 1] = temporal;
					}
				}
			}
		}
		string nombres() {
			string texto = "";
			for (int i=0;i<cantidad();i++) {
				texto =texto + estudiantes[i].getNombre()+ " ";
			}
			return texto;
		}
		void imprimir() {
			if (cantidad()==0) {
				cout << "  (vector vacio)" << endl;
				return;
			}
			for (int i = 0; i < cantidad(); i++) {
				cout << "  [" << i << "] "<< estudiantes[i].getNombre() << " | "
					<< estudiantes[i].getAnio() << " | "<< estudiantes[i].getGpa() << " | "
					<< estudiantes[i].getPresupuesto() << " | indice: "<< estudiantes[i].indiceUniversidad() <<endl;
			}
		}
};
Estudiante pedirDatos() {
	string nombre;
	int anio;
	double gpa, presupuesto;
	cout<< "Nombre: ";
	cin>> nombre;
	cout<< "Anio de nacimiento: ";
	cin>> anio;
	cout<< "Promedio GPA: ";
	cin>> gpa;
	cout<< "Presupuesto: ";
	cin>> presupuesto;
	return Estudiante(nombre, anio, gpa, presupuesto);
}
void mostrarEstudiante(Estudiante e) {
	cout << e.getNombre() << " | " << e.getAnio() << " | " << e.getGpa() << " | "
		<< e.getPresupuesto() << " | indice: " << e.indiceUniversidad() << endl;
}
int numeroPrueba = 0;
Gestor crearBase() {
	Gestor g;
	g.insertarAlFinal(Estudiante("Ana", 2001, 3.8, 1000));
	g.insertarAlFinal(Estudiante("Beto", 1999, 2.5, 3000));
	g.insertarAlFinal(Estudiante("Carla", 2003, 3.0, 2000));
	g.insertarAlFinal(Estudiante("Dario", 2000, 4.0, 500));
	return g;
}
void mostrarPrueba(string titulo, string entrada, string esperado, Gestor g) {
	numeroPrueba++;
	cout << endl << "Prueba " << numeroPrueba << ": " << titulo << endl;
	cout << "  Entrada : " << entrada << endl;
	cout << "  Esperado: " << esperado << endl;
	cout << "  Obtenido: " << g.nombres() << endl;
	g.imprimir();
	if (g.nombres() == esperado) cout << "  Resultado: PASA" << endl;
	else cout << "  Resultado: FALLA" << endl;
}
void pruebas() {
	numeroPrueba = 0;
	cout << endl << "PRUEBAS" << endl;
	
	Gestor g1;
	g1.insertarAlFinal(Estudiante());
	mostrarPrueba("Insertar sin datos", "vector vacio, insertar NN,0,0,0", "NN ", g1);
	
	Gestor g2;
	g2.insertarAlFinal(Estudiante("Ana", 2001, 3.8, 1000));
	g2.insertarAlFinal(Estudiante("Carla", 2003, 3.0, 2000));
	g2.insertarEnIndice(1, Estudiante("Beto", 1999, 2.5, 3000));
	mostrarPrueba("Insertar con datos en indice 1", "[Ana, Carla] + Beto en indice 1", "Ana Beto Carla ", g2);
	
	Gestor g3 = crearBase();
	g3.eliminarUltimo();
	mostrarPrueba("Eliminar el ultimo", "[Ana, Beto, Carla, Dario]", "Ana Beto Carla ", g3);
	
	Gestor g4 = crearBase();
	g4.eliminarEnIndice(1);
	mostrarPrueba("Eliminar con indice 1", "[Ana, Beto, Carla, Dario]", "Ana Carla Dario ", g4);
	
	Gestor g5;
	g5.eliminarUltimo();
	mostrarPrueba("No elimina si esta vacio", "vector vacio, eliminar ultimo", "", g5);
	
	Gestor g6 = crearBase();
	g6.actualizar(2, Estudiante("Carlos", 2002, 3.4, 2500));
	mostrarPrueba("Actualizar indice 2", "Carla pasa a Carlos 2002, 3.4, 2500", "Ana Beto Carlos Dario ", g6);
	
	Gestor g7 = crearBase();
	g7.ordenar(1);
	mostrarPrueba("Ordenar por anio", "Ana 2001, Beto 1999, Carla 2003, Dario 2000", "Beto Dario Ana Carla ", g7);
	
	Gestor g8 = crearBase();
	g8.ordenar(2);
	mostrarPrueba("Ordenar por GPA", "Ana 3.8, Beto 2.5, Carla 3.0, Dario 4.0", "Beto Carla Ana Dario ", g8);
	
	Gestor g9 = crearBase();
	g9.ordenar(3);
	mostrarPrueba("Ordenar por presupuesto", "Ana 1000, Beto 3000, Carla 2000, Dario 500", "Dario Ana Carla Beto ", g9);
	
	Gestor g10 = crearBase();
	g10.ordenar(4);
	mostrarPrueba("Ordenar por indice universidad", "Ana 800, Beto 1500, Carla 0, Dario 500", "Carla Dario Ana Beto ", g10);
}
void menu() {
	Gestor gestor = crearBase();
	int opcion = -1;
	cout << endl << "Estudiantes iniciales:" << endl;
	gestor.imprimir();
	while (opcion != 0) {
		cout<< endl << "MENU" << endl;
		cout<< "1. Insertar estudiante" << endl;
		cout<< "2. Eliminar estudiante" << endl;
		cout<< "3. Actualizar estudiante" << endl;
		cout<< "4. Ordenar" << endl;
		cout<< "5. Imprimir" << endl;
		cout<< "0. Salir" << endl;
		cout<< "Opcion: ";
		cin>> opcion;
		if (opcion == 1) {
			int donde, tipo;
			cout << endl << "Estudiantes antes de insertar:" << endl;
			gestor.imprimir();
			cout<< "(1. Al final  2. En un indice: )";
			cin>> donde;
			cout<< "(1. Por defecto (NN,0,0,0)  2. Con datos:) ";
			cin>> tipo;
			Estudiante e;
			if (tipo==2) e = pedirDatos();
			
			if (donde== 1) {
				int indice = gestor.cantidad();
				gestor.insertarAlFinal(e);
				cout << "Estudiante insertado en el indice " << indice << ": ";
				mostrarEstudiante(e);
				cout << endl << "Estudiantes despues de insertar:" << endl;
				gestor.imprimir();
			} else {
				int indice;
				cout<< "Indice (0 a " << gestor.cantidad() << "): ";
				cin>> indice;
				if (gestor.insertarEnIndice(indice, e)) {
					cout << "Estudiante insertado en el indice " << indice << ": ";
					mostrarEstudiante(e);
					cout << endl << "Estudiantes despues de insertar:" << endl;
					gestor.imprimir();
				}
				else {
					cout << "Indice invalido. Solo puedes insertar del 0 al " << gestor.cantidad() << "." << endl;
					cout << "Estudiantes que tienes:" << endl;
					gestor.imprimir();
				}
			}
		}
		else if (opcion == 2) {
			cout << endl << "Estudiantes antes de eliminar:" << endl;
			gestor.imprimir();
			if (gestor.cantidad() == 0) {
				cout << "El vector esta vacio, no se puede eliminar." <<endl;
			} else {
				int tipo;
				cout << "1. Eliminar el ultimo  2. Eliminar por indice: ";
				cin >>tipo;
				if (tipo == 1) {
					int indice = gestor.cantidad() - 1;
					Estudiante eliminado = gestor.obtener(indice);
					gestor.eliminarUltimo();
					cout<< "Estudiante eliminado del indice " << indice << ": ";
					mostrarEstudiante(eliminado);
					cout << endl << "Estudiantes despues de eliminar:" << endl;
					gestor.imprimir();
				} else {
					int indice;
					cout<< "Indice (0 a " << gestor.cantidad() - 1 << "): ";
					cin>> indice;
					if (indice >= 0 && indice < gestor.cantidad()) {
						Estudiante eliminado = gestor.obtener(indice);
						gestor.eliminarEnIndice(indice);
						cout << "Estudiante eliminado del indice " << indice << ": ";
						mostrarEstudiante(eliminado);
						cout << endl << "Estudiantes despues de eliminar:" << endl;
						gestor.imprimir();
					}
					else {
						cout << "Indice invalido. Solo puedes eliminar del 0 al " << gestor.cantidad() - 1 << "." << endl;
						cout << "Estudiantes que tienes:" << endl;
						gestor.imprimir();
					}
				}
			}
		}
		else if (opcion == 3) {
			int indice;
			cout << endl << "Estudiantes antes de actualizar:" << endl;
			gestor.imprimir();
			cout<< "Indice a actualizar: ";
			cin>> indice;
			if (indice >= 0 && indice < gestor.cantidad()) {
				Estudiante anterior = gestor.obtener(indice);
				gestor.actualizar(indice, pedirDatos());
				cout << "Estudiante actualizado en el indice " << indice << endl;
				cout << "Antes: ";
				mostrarEstudiante(anterior);
				cout << "Ahora: ";
				mostrarEstudiante(gestor.obtener(indice));
				cout << endl << "Estudiantes despues de actualizar:" << endl;
				gestor.imprimir();
			} else {
				cout << "Indice invalido." << endl;
				if (gestor.cantidad() == 0) cout << "No hay estudiantes para actualizar." << endl;
				else cout << "Solo puedes actualizar del 0 al " << gestor.cantidad() - 1 << "." << endl;
				cout << "Estudiantes que tienes:" << endl;
				gestor.imprimir();
			}
		}
		else if (opcion == 4) {
			int criterio;
			cout << endl << "Estudiantes antes de ordenar:" << endl;
			gestor.imprimir();
			cout<< "1. Anio  2. GPA  3. Presupuesto  4. Indice universidad: ";
			cin>> criterio;
			gestor.ordenar(criterio);
			cout<< "Lista ordenada."<< endl;
			cout << endl << "Estudiantes despues de ordenar:" << endl;
			gestor.imprimir();
		}
		else if (opcion == 5) {
			gestor.imprimir();
		}
		else if (opcion == 6) {
			pruebas();
		}
	}
	cout << "Hasta luego." << endl;
}
int main() {
	menu();
	return 0;
}

