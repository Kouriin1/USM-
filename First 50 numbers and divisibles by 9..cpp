/*Elabore un programa de almacene en un arreglo los primero 50 números
 DIVISIBLES entre 9 pero de dos en dos.
 El programa deberá trabajar en un rango cualquiera definido por el usuario por 
 ejemplo de 1 a 1.000.000.*/ 
 
 #include<iostream>
 #include<math.h>
 
 using namespace std;
 
 int main(){
 	int num[50]= {0};
 	int inicio = 0;
 	int final = 0;
 	int i;
 	int incremento= 0;
 	cout<<"Digite el rango inicial: ";
 	cin>>inicio;
 	cout<<"Digite el rango final: " ;
 	cin>>final;
 	
 	for(i= inicio; i <= final;i= i+2){
 		if(i%9 == 0){
 			num[incremento] = i;
 			incremento++;
		 }
 		
 		
	 }
	 
	  cout<<"Primeros 50 numeros divisibles entre 9 pero en 2 en 2."<<endl; 
	  for(incremento = 0; incremento < 50; incremento++){
	 	cout<<num[incremento]<<" "; 
	 }
	 
 }
