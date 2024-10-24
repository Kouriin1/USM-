/*
Imaginenos que un restaurante (cualquiera) tiene un total de "N" platos. 
Suponiendo que hay platos de 3 colores, y que alguien está lavando platos y los coloca uno sobre otro y 
que los mesoneros toman de los platos para servirlos. 

Escriba en pseudocodigo que muestre el proceso de lavar y de servir platos y que muestre
en un momento determinado que tipo de platos hay, cuantos hay, y de que color hay en un 
momento disponible, usando pilas.

Estudiantes: 

Roger Montero
Efraín Arreaza 

*/

#include <windows.h>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <conio.h>
#include <ctime>  

using namespace std;

// Declarando una estructura para usar los valores 
struct Platos {
    int plato_rojo;
    int plato_azul;    
    int plato_verde;
};

// Función para cambiar el color de la consola según el color deseado
void cambiarColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Función para imprimir el color y restablecer al color por defecto (blanco)
void imprimirPlatoConColor(string color) {
    if (color == "Rojo" || color == "Rojos") {
        cambiarColor(4);  // Rojo
        cout << "Rojo";
    } else if (color == "Azul" || color == "Azules") {
        cambiarColor(1);  // Azul
        cout << "Azul";
    } else if (color == "Verde" || color == "Verdes") {
        cambiarColor(2);  // Verde
        cout << "Verde";
    }
    cambiarColor(7);  // Restablecer a blanco 
}  
   
   const int MAX_CAPACIDAD = 10; // Capacidad máxima de la pila
   int random_action;

int main() {
    stack<string> pila;
    Platos p;
    char op;
    // Inicializar la semilla de los números aleatorios
    srand(time(0));
    
    cout << "Bienvenidos al Restaurante!" << endl;
    cout << "Para poder atender a los comensales necesitamos tener un buen flujo de entrada y salida de platos." << endl;
    cout << "A continuacion se nos da un vistazo de dicho flujo desde la cocina: " << endl <<endl;
    
    system("pause");
    // Asignación aleatoria de platos
    p.plato_rojo = rand() % 30 + 1;
    p.plato_azul = rand() % 30 + 1;
    p.plato_verde = rand() % 30 + 1;

    while (true) {
        int random_action = rand() % 4; // Generar un número aleatorio entre 0 y 3 para decidir la acción
        
        if (random_action == 0 && p.plato_rojo > 0) {
            pila.push("Rojo");				//ingresar valor en la pila
            cout << "Entrando y lavando plato de color "; 
            imprimirPlatoConColor("Rojo"); 
            cout << endl;
            p.plato_rojo--;
        } else if (random_action == 1 && p.plato_azul > 0) {
            pila.push("Azul");				//ingresar valor en la pila
            cout << "Entrando y lavando plato de color ";
            imprimirPlatoConColor("Azul");
            cout << endl;
            p.plato_azul--;
        } else if (random_action == 2 && p.plato_verde > 0) {
            pila.push("Verde");				//ingresar valor en la pila
            cout << "Entrando y lavando plato de color ";
            imprimirPlatoConColor("Verde");
            cout << endl;
            p.plato_verde--;
            Sleep(200);
        } else if (random_action == 3 && !pila.empty()) {
            string plato = pila.top();
            //si el top de la pila de es un plato de x color sumale 1 (es decir se sirvio y se ensucio el plato, hay que lavarlo)
            if(pila.top() == "Rojo"){
            	p.plato_rojo++;
			}else if(pila.top() == "Azul"){
				p.plato_azul++;
			}else if(pila.top() == "Verde"){
				p.plato_verde++;
			}
            
            pila.pop();			//sacar valor de la pila
            cout << "Sirviendo y saliendo de la cocina un plato de color ";
            imprimirPlatoConColor(plato);
            cout << endl;
            Sleep(200);
        }
        
        	
		if (kbhit() != 0) {
			op = getch();
			if (op == 's' || op == 'S')  break; //si la tecla presionada es s o S rompe el ciclo
				
		}
		
        
        Sleep(1150);
    }  

    return 0;
}

