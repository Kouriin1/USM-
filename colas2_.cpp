#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <windows.h>
#include <conio.h>

const int max_value = 8;
typedef int cola[max_value]; // Definición del arreglo

using namespace std;

void printcola(cola q, int front, int rear) {
    if (front == -1) {
        cout << "La cola está vacía." << endl;
        return;
    }
    for (int i = front; i != rear; i = (i + 1) % max_value) {
        cout << "[" << q[i] << "] ";
    }
    cout << "[" << q[rear] << "]" << endl;
}

int main() {
    cola array;
    int front = -1, rear = -1;
    int var = 0;
	char op;
   
    srand(time(0));

    while (true) {
        system("cls");
        int random = rand() % 100;
        int random2 = rand() % 3;


        if (var < max_value) {
            if (front == -1) front = 0;
            rear = (rear + 1) % max_value;
            array[rear] = random;
            var++;
            cout << "Entro el usuario: " << random << endl;
        }

        cout << "Estado de la cola: ";
        printcola(array, front, rear);

        if (var == max_value) {
            cout << "La cola esta llena, no puede ingresar mas usuarios." << endl;
        }

        // Eliminar usuario de la cola
        if (front != -1 && random2 == 2) {
            cout << "Saliendo usuario: " << array[front] << endl;
            if (front == rear) {
                front = rear = -1; // La cola está vacía
            } else {
                front = (front + 1) % max_value;
            }
            var--;
        }
        
        
        if (kbhit() != 0) {
			op = getch();
			if (op == 's' || op == 'S')  break; //si la tecla presionada es s o S rompe el ciclo
				
		}
        
        

        Sleep(3000);
    }

    return 0;
}

