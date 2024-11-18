/*
ordena orden alfateco
a la de eliminar pregutntar


*/


#include <iostream>
#include <string>
#include <regex>
#include<windows.h>
using namespace std;


struct Contacto {
    string nombre;
    string telefono;
    string email;
    string direccion;
    string redesSociales;
    Contacto* sig;  // Apuntador al siguiente contacto
    Contacto* ant;  // Apuntador al contacto anterior
};


void gotoxy(int x, int y){
	COORD coordenadas;
	coordenadas.X = x;
	coordenadas.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenadas);
	
}

void imprimirCoordenadas(string palabra, int x, int y){
	for(int i = 0; i <= palabra.length(); i++){
		Beep(300, 40);
		gotoxy(x+i,y);cout<<palabra[i];	
	}
}

class ListaContactos {
private:
    Contacto* primero;
    Contacto* actual;

public:
    ListaContactos() : primero(nullptr), actual(nullptr) {}

	bool validarCampoNoVacio(const string& campo) {
		
    return !campo.empty() && campo.find_first_not_of(" ") != string::npos;
	}

	bool validarCorreo(const string& email) {
    	for (int i = 0; i < email.length(); i++) {  
        	if (email[i] == '@') {
            return true;  // Retorna verdadero si se encuentra @
        	}
    	}
    return false;  // Si termina el bucle sin encontrar @, retorna falso
}


	
bool contactoExistente(const string& nombre, const string& telefono, const string& email,
                       const string& direccion, const string& redesSociales) {
    actual = primero;
    while (actual != nullptr) {
        bool coinciden = true;

        if (!nombre.empty() && actual->nombre != nombre) coinciden = false;
        if (!telefono.empty() && actual->telefono != telefono) coinciden = false;
        if (!email.empty() && actual->email != email) coinciden = false;
        if (!direccion.empty() && actual->direccion != direccion) coinciden = false;
        if (!redesSociales.empty() && actual->redesSociales != redesSociales) coinciden = false;

        if (coinciden) {
            return true; 
        }
        actual = actual->sig;
    }
    return false;
}


    bool validarTelefono(const string& telefono) {
        return telefono.length() <= 11 && telefono.find_first_not_of("0123456789") == string::npos;
    }
    
    
    bool telefonoExistente(const string& telefono) {
        actual = primero;
        while (actual != nullptr) {
            if (actual->telefono == telefono) return true;
            actual = actual->sig;
        }
        return false;
    }
    
    
    

  
    void agregarContacto(string nombre, string telefono, string email, string direccion, string redesSociales) {
    	
    	
		if (telefonoExistente(telefono)) {
        	cout << "Error: Ya existe un contacto con el mismo numero de telefono.\n";
            return;
        }
		
		
		if (contactoExistente(nombre, telefono, email, direccion, redesSociales)) {
        cout << "Error: Ya existe un contacto con los mismos datos.\n";
        return;
    	}
        
		
		if (!validarTelefono(telefono)) {
            cout << "Error: El numero de telefono debe tener un maximo de 11 digitos y contener solo numeros.\n";
            return;
        }
        
        if (!validarCorreo(email)) {
            cout << "Error: Formato de correo electronico invalido.\n";
            return;
        }
        
        if(email == "@"){
        
        email = "";
        	
		}
        

	    if (!validarCampoNoVacio(nombre)) {
        cout << "Error: El nombre no puede estar vacio.\n";
        return;
    	}
    	if (!validarCampoNoVacio(telefono)) {
        cout << "Error: El numero de telefono no puede estar vacio.\n";
        return;
    	}
	
        Contacto* nuevo = new Contacto();
        nuevo->nombre = nombre;
        nuevo->telefono = telefono;
        nuevo->email = email;
        nuevo->direccion = direccion;
        nuevo->redesSociales = redesSociales;
        nuevo->sig = nullptr;
        nuevo->ant = nullptr;

            // Insertar en orden alfabético
        if (primero == nullptr || primero->nombre > nombre) {
            // Insertar al inicio si la lista está vacía o si el primer elemento es mayor
            nuevo->sig = primero;
            if (primero != nullptr) primero->ant = nuevo;
            primero = nuevo;
        } else {
            // Insertar en la posición correcta
            actual = primero;
            while (actual->sig != nullptr && actual->sig->nombre < nombre) {
                actual = actual->sig;
            }
            nuevo->sig = actual->sig;
            if (actual->sig != nullptr) actual->sig->ant = nuevo;
            actual->sig = nuevo;
            nuevo->ant = actual;
        }
        cout << "Contacto agregado: " << nombre << endl;
    }
    void buscarContacto(string criterio) {
        actual = primero;
        bool encontrado = false;

        while (actual != nullptr) {
            if (actual->nombre == criterio || actual->telefono == criterio || actual->email == criterio || actual->direccion == criterio) {
                cout << "Contacto encontrado:\n";
                cout << "Nombre: " << actual->nombre << endl;
                cout << "Telefono: " << actual->telefono << endl;
                cout << "Email: " << actual->email << endl;
                cout << "Direccion: " << actual->direccion << endl;
                cout << "Redes Sociales: " << actual->redesSociales << endl;
                encontrado = true;
                break;
            }
            actual = actual->sig;
        }

        if (!encontrado) {
            cout << "Contacto no encontrado con el criterio: " << criterio << endl;
        }
    }

    void mostrarContactos() {
        actual = primero;
        if (actual == nullptr) {
            cout << "La lista de contactos esta vacia." << endl;
            return;
        }

        cout << "Lista de contactos:\n";
        while (actual != nullptr) {
            cout << "Nombre: " << actual->nombre << ", Telefono: " << actual->telefono << ", Email: " << actual->email
                 << ", Direccion: " << actual->direccion << ", Redes Sociales: " << actual->redesSociales << endl;
            actual = actual->sig;
        }
    }


    void eliminarContacto(const string& criterio) {
        actual = primero;
        bool encontrado = false;

        while (actual != nullptr) {
            if (actual->nombre == criterio || actual->telefono == criterio || actual->email == criterio) {
                encontrado = true;
                cout << "¿Desea eliminar el contacto? (s/n):\n";
                cout << "Nombre: " << actual->nombre << ", Telefono: " << actual->telefono << ", Email: " << actual->email << endl;
                char respuesta;
                cin >> respuesta;

                if (respuesta == 's' || respuesta == 'S') {
                    Contacto* eliminar = actual;
                    if (actual == primero) {
                        primero = actual->sig;
                        if (primero != nullptr) primero->ant = nullptr;
                    } else {
                        actual->ant->sig = actual->sig;
                        if (actual->sig != nullptr) actual->sig->ant = actual->ant;
                    }
                    actual = actual->sig;
                    delete eliminar;
                    cout << "Contacto eliminado correctamente.\n";
                } else {
                    actual = actual->sig;
                }
            } else {
                actual = actual->sig;
            }
        }

        if (!encontrado) {
            cout << "Contacto no encontrado con el criterio: " << criterio << endl;
        }
    }


    ~ListaContactos() {
        actual = primero;
        while (actual != nullptr) {
            Contacto* siguiente = actual->sig;
            delete actual;
            actual = siguiente;
        }
    }
};

int main() {
    ListaContactos lista;
    int opcion;
    string nombre, telefono, email, direccion, redesSociales, criterio;
    char respuesta;

    do {
        cout << "\n----- Menu -----\n";
        cout << "1. Agregar un contacto\n";
        cout << "2. Buscar contacto\n";
        cout << "3. Lista de contactos\n";
        cout << "4. Eliminar contacto\n";
        cout << "0. Salir\n";
        //imprimirCoordenadas("Elige una opcion:", 3,6);
        cout << "Elige una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            cout << "Agrega un contacto:\n";
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Numero (maximo 11 digitos): ";
            getline(cin, telefono);

            cout << "¿Desea agregar un correo electronico? (s/n): ";
            cin >> respuesta;
            cin.ignore();
            if (respuesta == 's' || respuesta == 'S') {
            	
            	do{
				
                cout << "Correo: ";
                getline(cin, email);
                if (!lista.validarCampoNoVacio(email)) {
                    cout << "Error: El campo de correo no puede estar vacio.\n";
                }
                
            	}while(!lista.validarCampoNoVacio(email));
            	
            } else {
                email = "@";
            }

            cout << "¿Desea agregar una direccion? (s/n): ";
            cin >> respuesta;
            cin.ignore();
            if (respuesta == 's' || respuesta == 'S') {
            	
           		do{
				
                cout << "Direccion: ";
                getline(cin, direccion);
                if (!lista.validarCampoNoVacio(direccion)) {
                    cout << "Error: El campo de correo no puede estar vacio.\n";
                }
                
            	}while(!lista.validarCampoNoVacio(direccion));
                
                
            } else {
                direccion = "";
            }

            cout << "¿Desea agregar redes sociales? (s/n): ";
            cin >> respuesta;
            cin.ignore();
            if (respuesta == 's' || respuesta == 'S') {
            	
            	
            	do{
				
                cout << "Redes Sociales: ";
                getline(cin, redesSociales);
                if (!lista.validarCampoNoVacio(redesSociales)) {
                    cout << "Error: El campo de redes sociales no puede estar vacio.\n";
                }
                
            	}while(!lista.validarCampoNoVacio(redesSociales));
                
                
                
                
            } else {
                redesSociales = "";
            }

            lista.agregarContacto(nombre, telefono, email, direccion, redesSociales);
            break;

        case 2:
            cout << "Introduce el nombre, telefono o correo del contacto a buscar: ";
            getline(cin, criterio);
            lista.buscarContacto(criterio);
            break;

        case 3:
            lista.mostrarContactos();
            break;
            
        case 4:
         	cout << "Introduce el nombre, telefono o correo del contacto a eliminar: ";
    		getline(cin, criterio);
    		lista.eliminarContacto(criterio);
    		break;

        case 0:
            cout << "Saliendo del programa." << endl;
            break;

        default:
            cout << "Opcion no valida. Intenta de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}

