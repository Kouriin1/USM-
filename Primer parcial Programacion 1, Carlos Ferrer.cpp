/* 1.- Elabore un programa que presente en pantalla los primeros veinte 20 números que:
a.- Que finalicen en uno (1). 
b.- Que sean divisibles exactamente entre veintiuno (21). 
c.- Que el resultado de su división entre veintiuno (21) al sacarle la raíz cuadrada de un numero entero que termine en uno (1).
El rango a revisar es desde 50000 hasta que consiga los veinte (20) números.
En la pantalla deberá presentarse el número, su división entre veintiuno (21) y la raíz cuadrada de ese resultado que termina en uno (1): 
Numero terminado en uno – División entre 21 – Raíz Cuadrada que termina en uno
54621 – 2601 - 51

	Universidad Santa Maria
Estudiante: Roger Montero
C.I: 30.679.063
Area: Programacion 1.
Prof: Carlos Ferrer
Fecha: 12/4/2023
*/


#include<iostream>
#include<cmath>
using namespace std;

int main(){
	//Declaro las variables
	
	int valor = 50000; //variable que iniciador solicitado por el profesor
	int contador = 0; // contador cuando encuentre los 20 digitos
	double divisor;  // la division que se va a realizar
	double raiz; // la raiz cuadrada que se realizara

	cout<<"Este programa conseguira los primeros 20 numeros que terminen en 1,"<<endl;
	cout<<" despues va hacer la division entre 21 que dara un numero entero que finalize en 1"<<endl;
	cout<<"por ultimo sacara la raiz cuadrada que sera entero y que termine en 1"<<endl<<endl;
	
	
	
	// contador que encuentra las 20 unidades
	while(contador < 20){
		// if para saber si ese numero termina en 1 y si es divisible entre 21
		if(valor%10 == 1 and valor%21 == 0){
			
			//si encuentra esos 2 valores procede lo siguiente
			
			
			divisor = valor/21; //divido el valor a 21
			
			raiz = sqrt(divisor); //saco la raiz cuadrada
			
			int redondeo = static_cast<int> (raiz);// codigo que hace redondear condigos doubles 
			//en enteros  para poder verificar el resultado de la raiz en  c++
			if(redondeo%10 == 1)//if para verificar si termina en 1
			{
			
			
			
			//Imprimo los resultados en pantalla		
			cout<<valor<<"-"<<divisor<<"-"<<redondeo<<endl;
			contador++; //cuenta por cada que llego hasta aqui
			}
			
		}
		
		valor++; //conteo y se repite el ciclo hasta de contador sea < 20
		
	}	
	cout<<"Realizado por Roger Montero, C.I: 30.679.063"<<endl;
	cout<<"Fecha: 12/4/2023";

}
