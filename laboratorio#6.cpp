#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>  // Para manejar errores de entrada numérica

using namespace std;

struct Empleado {
    string CI;
    string nombre;
    double sueldo;
    string fechaIngreso;
    string fechaNacimiento;
    string fechaUltimoAscenso;
    Empleado* siguiente;
};

// Punteros globales
Empleado* primero = NULL;
Empleado* actual = NULL;
Empleado* anterior = NULL;
Empleado* nuevo = NULL;

// Función para extraer año, mes y día de una fecha en formato YYYY-MM-DD
void extraerFecha(const string& fecha, int& anio, int& mes, int& dia) {
    stringstream ss(fecha);
    char separador;
    ss >> anio >> separador >> mes >> separador >> dia;
}



void buscarPorRangoSalario(double salarioMin, double salarioMax) {
    if (salarioMin > salarioMax) {
        cout << "Error: El salario minimo no puede ser mayor que el salario maximo.\n";
        return;
    }

    bool encontrado = false;
    actual = primero;
    while (actual != NULL) {
        if (actual->sueldo >= salarioMin && actual->sueldo <= salarioMax) {
            cout << "Empleado: " << actual->nombre << ", Sueldo: " << actual->sueldo << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) cout << "No se encontraron empleados en ese rango de salarios.\n";
}




// Validación de formato y rango de fechas
bool esFechaValida(const string& fecha) {
    if (fecha.size() != 10 || fecha[4] != '-' || fecha[7] != '-') return false;

    int anio, mes, dia;
    extraerFecha(fecha, anio, mes, dia);

    if (mes < 1 || mes > 12) return false;

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

bool validarEdadLogica(const string& fechaNacimiento, const string& fechaIngreso) {
    int anioNac, mesNac, diaNac;
    int anioIng, mesIng, diaIng;
    extraerFecha(fechaNacimiento, anioNac, mesNac, diaNac);
    extraerFecha(fechaIngreso, anioIng, mesIng, diaIng);

    // Verifica que el año de nacimiento sea razonable
    if (anioNac < 1930) return false;

    // Calcula la edad exacta al momento de ingreso
    int edadAnios = anioIng - anioNac;
    int edadMeses = mesIng - mesNac;
    int edadDias = diaIng - diaNac;

    // Ajusta la edad en años si el mes o día del ingreso es anterior al de nacimiento
    if (edadMeses < 0 || (edadMeses == 0 && edadDias < 0)) {
        edadAnios--;
    }

    // Verifica que la edad sea de al menos 18 años
    return edadAnios >= 18;
}

// Validación de edad mínima de 18 años
bool validarEdad(const string& fechaNacimiento, const string& fechaIngreso) {
    int anioNac, mesNac, diaNac;
    int anioIng, mesIng, diaIng;

    extraerFecha(fechaNacimiento, anioNac, mesNac, diaNac);
    extraerFecha(fechaIngreso, anioIng, mesIng, diaIng);

    int edad = anioIng - anioNac;
    
    if (mesIng < mesNac || (mesIng == mesNac && diaIng < diaNac)) edad--;

    return edad >= 18;
}

// Validar que la CI no se repita
bool ciExiste(const string& ci) {
    actual = primero;
    while (actual != NULL) {
        if (actual->CI == ci) return true;
        actual = actual->siguiente;
    }
    return false;
}


bool esCINumeroValido(const string& ci) {
   
    for (char c : ci) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Verifica que la CI no esté vacía y no comience con '0'
    if (ci.empty() || ci[0] == '0') {
        return false;
    }

    return true;
}


void eliminarEmpleadoPorSalario(double salario) {
    bool encontrado = false;
    Empleado* anterior = NULL;
    actual = primero;

    while (actual != NULL) {
        if (actual->sueldo == salario) {
            encontrado = true;
            cout << "¿Desea eliminar a " << actual->nombre << " (CI: " << actual->CI << ")? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                if (anterior == NULL) primero = actual->siguiente;
                else anterior->siguiente = actual->siguiente;
                delete actual;
                cout << "Empleado eliminado.\n";
                return;
            }
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    if (!encontrado) cout << "No se encontro ningun empleado con ese salario.\n";
}


void eliminarEmpleadosEnRango(double salarioMin, double salarioMax) {
    if (primero == NULL) {
        cout << "La lista esta vacia. No hay empleados para borrar.\n";
        return;
    }
    
    Empleado* anterior = NULL;
    actual = primero;

    while (actual != NULL) {
        if (actual->sueldo >= salarioMin && actual->sueldo <= salarioMax) {
            cout << "¿Desea eliminar a " << actual->nombre << " (CI: " << actual->CI << ")? (s/n): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S') {
                if (anterior == NULL) {
                    primero = actual->siguiente;
                    delete actual;
                    actual = primero;
                } else {
                    anterior->siguiente = actual->siguiente;
                    delete actual;
                    actual = anterior->siguiente;
                }
                cout << "Empleado eliminado.\n";
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}


void insertarEmpleado(string ci, string nombre, double sueldo, string fechaIngreso,
                      string fechaNacimiento, string fechaUltimoAscenso) {
                      	
         	
	if (!validarEdadLogica(fechaNacimiento, fechaIngreso)) {
        cout << "Error: La fecha de nacimiento o ingreso es inconsistente.\n";
        return;
    }
	 
	                                    	
   	if (!esCINumeroValido(ci)) {
        cout << "Error: CI no valida.\n";
        return;
    }                   	
                      	
    if (!esFechaValida(fechaNacimiento) || !esFechaValida(fechaIngreso) || !esFechaValida(fechaUltimoAscenso)) {
        cout << "Error: Una o mas fechas ingresadas no son validas.\n";
        return;
    }

    if (ciExiste(ci)) {
        cout << "Error: La CI ya existe en el sistema.\n";
        return;
    }

    if (sueldo < 0) {
        cout << "Error: El sueldo no puede ser negativo.\n";
        return;
    }

    if (fechaIngreso <= fechaNacimiento) {
        cout << "Error: La fecha de ingreso no puede ser anterior o igual a la fecha de nacimiento.\n";
        return;
    }

    string fechaActual = "2024-10-28";
    if (fechaUltimoAscenso < fechaIngreso || fechaUltimoAscenso > fechaActual) {
        cout << "Error: La fecha del ultimo ascenso es invalida.\n";
        return;
    }

    if (!validarEdad(fechaNacimiento, fechaIngreso)) {
        cout << "Error: El empleado debe tener al menos edad de 18 years al momento de ingresar.\n";
        return;
    }


    nuevo = new Empleado{ci, nombre, sueldo, fechaIngreso, fechaNacimiento, fechaUltimoAscenso, NULL};

    if (primero == NULL || sueldo > primero->sueldo) {
        nuevo->siguiente = primero;
        primero = nuevo;
    } else {
        actual = primero;
        while (actual->siguiente != NULL && actual->siguiente->sueldo >= sueldo) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

void mostrarLista() {
    if (primero == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    actual = primero;
    cout << left << setw(12) << "CI" << setw(15) << "Nombre" << setw(10) << "Sueldo"
         << setw(15) << "F. Ingreso" << setw(15) << "F. Nacimiento" << "F. Ult. Ascenso\n";
    cout << string(75, '-') << endl;
    while (actual != NULL) {
        cout << setw(12) << actual->CI << setw(15) << actual->nombre << setw(10) << actual->sueldo
             << setw(15) << actual->fechaIngreso << setw(15) << actual->fechaNacimiento
             << actual->fechaUltimoAscenso << endl;
        actual = actual->siguiente;
    }
}

void buscarPorCI(const string& ci) {
    actual = primero;
    while (actual != NULL) {
        if (actual->CI == ci) {
            cout << "Empleado encontrado: " << actual->nombre << ", Sueldo: " << actual->sueldo << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontro ningun empleado con esa CI.\n";
}

void buscarPorRangoFechas(const string& inicio, const string& fin) {
    if (inicio > fin) {
        cout << "Error: La fecha de inicio no puede ser posterior a la fecha de fin.\n";
        return;
    }

    bool encontrado = false;
    actual = primero;
    while (actual != NULL) {
        if (actual->fechaIngreso >= inicio && actual->fechaIngreso <= fin) {
            cout << "Empleado: " << actual->nombre << ", Fecha de Ingreso: " << actual->fechaIngreso << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) cout << "No se encontraron empleados en ese rango de fechas.\n";
}

void borrarEmpleado(const string& criterio) {
    if (primero == NULL) {
        cout << "La lista esta vacia. No hay empleados para borrar.\n";
        return;
    }

    anterior = NULL;
    actual = primero;
    while (actual != NULL && actual->CI != criterio) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) {
        cout << "Empleado no encontrado.\n";
        return;
    }

    char confirmacion;
    cout << "¿Esta seguro de que desea eliminar al empleado con CI: " << criterio << "? (s/n): ";
    cin >> confirmacion;
    if (confirmacion != 's' && confirmacion != 'S') {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (anterior == NULL) {
        primero = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    delete actual;
    cout << "Empleado eliminado.\n";
}


void eliminarEmpleadosPorRangoFechas(const string& inicio, const string& fin) {
    if (inicio > fin) {
        cout << "Error: La fecha de inicio no puede ser posterior a la fecha de fin.\n";
        return;
    }

    if (primero == NULL) {
        cout << "La lista esta vacia. No hay empleados para borrar.\n";
        return;
    }

    Empleado* anterior = NULL;
    actual = primero;

    while (actual != NULL) {
        if (actual->fechaIngreso >= inicio && actual->fechaIngreso <= fin) {
            cout << "¿Desea eliminar a " << actual->nombre << " (Fecha de Ingreso: " << actual->fechaIngreso << ")? (s/n): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S') {
                if (anterior == NULL) {
                    primero = actual->siguiente;
                    delete actual;
                    actual = primero;
                } else {
                    anterior->siguiente = actual->siguiente;
                    delete actual;
                    actual = anterior->siguiente;
                }
                cout << "Empleado eliminado.\n";
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}


int main() {
    int opcion;
    string ci, nombre, fechaIngreso, fechaNacimiento, fechaUltimoAscenso;
    double sueldo;
    string inicio, fin;

    do {
        cout << "\n----- Menu -----\n";
        cout << "1. Insertar empleado\n";
        cout << "2. Mostrar lista de empleados\n";
        cout << "3. Buscar por CI\n";
        cout << "4. Buscar por rango de fechas\n";
        cout << "5. Buscar por rango de salario\n";
        cout << "6. Eliminar empleado por CI\n";
        cout << "7. Eliminar empleado por salario\n";
        cout << "8. Eliminar empleados en rango de salario\n";
        cout << "9. Eliminar empleados en rango de fechas de ingreso\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese CI: ";
                getline(cin, ci);
                cout << "Ingrese nombre: ";
                getline(cin, nombre);
                cout << "Ingrese sueldo: ";
                cin >> sueldo;
                cin.ignore();
                cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
                getline(cin, fechaIngreso);
                cout << "Ingrese fecha de nacimiento (YYYY-MM-DD): ";
                getline(cin, fechaNacimiento);
                cout << "Ingrese fecha del ultimo ascenso (YYYY-MM-DD): ";
                getline(cin, fechaUltimoAscenso);
                insertarEmpleado(ci, nombre, sueldo, fechaIngreso, fechaNacimiento, fechaUltimoAscenso);
                break;
            case 2:
                mostrarLista();
                break;
            case 3:
                cout << "Ingrese la CI a buscar: ";
                getline(cin, ci);
                buscarPorCI(ci);
                break;
            case 4:
                cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
                getline(cin, inicio);
                cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
                getline(cin, fin);
                buscarPorRangoFechas(inicio, fin);
                break;
            case 6:
                cout << "Ingrese la CI del empleado a eliminar: ";
                getline(cin, ci);
                borrarEmpleado(ci);
                break;
            case 5:
            	double salarioMin, salarioMax;
    			cout << "Ingrese el salario minimo: ";
    			cin >> salarioMin;
    			cout << "Ingrese el salario maximo: ";
    			cin >> salarioMax;
    			buscarPorRangoSalario(salarioMin, salarioMax);
    			break;
    		case 7:
    			cout << "Ingrese el salario exacto del empleado a eliminar: ";
                cin >> sueldo;
                eliminarEmpleadoPorSalario(sueldo);
    			break;
    		case 8:
    			cout << "Ingrese el salario minimo: ";
                cin >> salarioMin;
                cout << "Ingrese el salario maximo: ";
                cin >> salarioMax;
                eliminarEmpleadosEnRango(salarioMin, salarioMax);
                break;
			case 9:
    			cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
    			getline(cin, inicio);
    			cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
    			getline(cin, fin);
    			eliminarEmpleadosPorRangoFechas(inicio, fin);
    			break;
    
    					
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}


/*
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

struct Empleado {
    string CI;
    string nombre;
    double sueldo;
    string fechaIngreso;
    string fechaNacimiento;
    string fechaUltimoAscenso;
    Empleado* siguiente;
};

// Punteros globales
Empleado* primero = NULL;
Empleado* actual = NULL;
Empleado* anterior = NULL;
Empleado* nuevo = NULL;

void extraerFecha(const string& fecha, int& anio, int& mes, int& dia) {
    stringstream ss(fecha);
    char separador;
    ss >> anio >> separador >> mes >> separador >> dia;
}

bool esFechaValida(const string& fecha) {
    if (fecha.size() != 10 || fecha[4] != '-' || fecha[7] != '-') return false;
    int anio, mes, dia;
    extraerFecha(fecha, anio, mes, dia);
    if (mes < 1 || mes > 12) return false;
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) diasPorMes[1] = 29;
    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

bool validarEdadLogica(const string& fechaNacimiento, const string& fechaIngreso) {
    int anioNac, mesNac, diaNac;
    int anioIng, mesIng, diaIng;
    extraerFecha(fechaNacimiento, anioNac, mesNac, diaNac);
    extraerFecha(fechaIngreso, anioIng, mesIng, diaIng);

    // Verifica que el año de nacimiento sea lógico y que el empleado tenga al menos 18 años al ingresar
    if (anioNac < 1900 || (anioIng - anioNac < 18)) return false;

    return true;
}

void eliminarEmpleadoPorSalario(double salario) {
    bool encontrado = false;
    Empleado* anterior = NULL;
    actual = primero;

    while (actual != NULL) {
        if (actual->sueldo == salario) {
            encontrado = true;
            cout << "¿Desea eliminar a " << actual->nombre << " (CI: " << actual->CI << ")? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                if (anterior == NULL) primero = actual->siguiente;
                else anterior->siguiente = actual->siguiente;
                delete actual;
                cout << "Empleado eliminado.\n";
                return;
            }
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    if (!encontrado) cout << "No se encontró ningún empleado con ese salario.\n";
}

void eliminarEmpleadosEnRango(double salarioMin, double salarioMax) {
    if (primero == NULL) {
        cout << "La lista está vacía. No hay empleados para borrar.\n";
        return;
    }
    
    Empleado* anterior = NULL;
    actual = primero;

    while (actual != NULL) {
        if (actual->sueldo >= salarioMin && actual->sueldo <= salarioMax) {
            cout << "¿Desea eliminar a " << actual->nombre << " (CI: " << actual->CI << ")? (s/n): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S') {
                if (anterior == NULL) {
                    primero = actual->siguiente;
                    delete actual;
                    actual = primero;
                } else {
                    anterior->siguiente = actual->siguiente;
                    delete actual;
                    actual = anterior->siguiente;
                }
                cout << "Empleado eliminado.\n";
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

void insertarEmpleado(string ci, string nombre, double sueldo, string fechaIngreso,
                      string fechaNacimiento, string fechaUltimoAscenso) {
    if (!esFechaValida(fechaNacimiento) || !esFechaValida(fechaIngreso) || !esFechaValida(fechaUltimoAscenso)) {
        cout << "Error: Una o más fechas ingresadas no son válidas.\n";
        return;
    }

    if (!validarEdadLogica(fechaNacimiento, fechaIngreso)) {
        cout << "Error: La fecha de nacimiento o ingreso es inconsistente.\n";
        return;
    }

    nuevo = new Empleado{ci, nombre, sueldo, fechaIngreso, fechaNacimiento, fechaUltimoAscenso, NULL};

    if (primero == NULL || sueldo > primero->sueldo) {
        nuevo->siguiente = primero;
        primero = nuevo;
    } else {
        actual = primero;
        while (actual->siguiente != NULL && actual->siguiente->sueldo >= sueldo) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

void buscarPorRangoSalario(double salarioMin, double salarioMax) {
    if (salarioMin > salarioMax) {
        cout << "Error: El salario mínimo no puede ser mayor que el salario máximo.\n";
        return;
    }

    actual = primero;
    while (actual != NULL) {
        if (actual->sueldo >= salarioMin && actual->sueldo <= salarioMax) {
            cout << "Empleado: " << actual->nombre << ", Sueldo: " << actual->sueldo << endl;
        }
        actual = actual->siguiente;
    }
}

int main() {
    int opcion;
    string ci, nombre, fechaIngreso, fechaNacimiento, fechaUltimoAscenso;
    double sueldo, salarioMin, salarioMax;

    do {
        cout << "\n----- Menu -----\n";
        cout << "1. Insertar empleado\n";
        cout << "2. Mostrar lista de empleados\n";
        cout << "3. Buscar por CI\n";
        cout << "4. Eliminar empleado por salario\n";
        cout << "5. Eliminar empleados en rango de salario\n";
        cout << "6. Buscar por rango de salario\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese CI: ";
                getline(cin, ci);
                cout << "Ingrese nombre: ";
                getline(cin, nombre);
                cout << "Ingrese sueldo: ";
                cin >> sueldo;
                cin.ignore();
                cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
                getline(cin, fechaIngreso);
                cout << "Ingrese fecha de nacimiento (YYYY-MM-DD): ";
                getline(cin, fechaNacimiento);
                cout << "Ingrese fecha del ultimo ascenso (YYYY-MM-DD): ";
                getline(cin, fechaUltimoAscenso);
                insertarEmpleado(ci, nombre, sueldo, fechaIngreso, fechaNacimiento, fechaUltimoAscenso);
                break;
            case 4:
                cout << "Ingrese el salario exacto del empleado a eliminar: ";
                cin >> sueldo;
                eliminarEmpleadoPorSalario(sueldo);
                break;
            case 5:
                cout << "Ingrese el salario minimo: ";
                cin >> salarioMin;
                cout << "Ingrese el salario maximo: ";
                cin >> salarioMax;
                eliminarEmpleadosEnRango(salarioMin, salarioMax);
                break;
            case 6:
                cout << "Ingrese el salario minimo: ";
                cin >> salarioMin;
                cout << "Ingrese el salario maximo: ";
                cin >> salarioMax;
                buscarPorRangoSalario(salarioMin, salarioMax);
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}





*/

