//elaborado por Roger Montero C.I: 30.679.063

#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;

//estruturas para las casillas
struct couta{
	float monto;
	float interes;
	int perido;
	float amortizacion;	
	
};

//funcion para sacar la couta
float fun_cuota(float a1, float a2, float a3){


	
float resultado = 0;
float trans;
float interes;

	
trans = a2/100;	
	
resultado =	(a1*trans)/(1-powf((trans+1),-a3));


return resultado;

}


//funcion para sacar el interes
float fun_interes(float e1,float e2){
	
	float interes;
	float trans;
	trans = e2/100;
	
	interes = e1*trans;
	
	return interes;
}






int main(){
	
	setlocale(LC_ALL, "spanish"); 
	inicio:
	//declaramos variables a utilizar
	int opcion;
	float aporte;
	float pendiente;
	int duracion = 1;
	float interes;
	float sum_interes2[48] = {0}; 
	float  sum_interes[48] = {0};
	float el_monto;
	struct couta coutas[48]; //arreglo tipo estructura
	int time;
	
	//Aqui el ingreso de los monto,interes,tiempo,amortizacion.... etc
	cout<<"Ingrese el monto: "; cin>>coutas[1].monto;
	
	el_monto = coutas[1].monto;
	
	interes:
	cout<<endl;

	cout<<"Ingrese el interes:  "; cin>>coutas[2].interes;
	if(coutas[2].interes < 0 or coutas[2].interes > 7.99){
		
		cout<<"No se puede ingresar interes mayor a 7% o menor a 0%";
		goto interes;
		
	}
	periodo:
		
	cout<<endl;
	
	cout<<"Ingrese el periodo:  "; cin>>coutas[3].perido;
	
	if(coutas[3].perido < 12){
		
		cout<<"Periodo minimo es de 12, porfavor intente otra vez.";
		
		goto periodo;
		
	}else if(coutas[3].perido > 48){
		
		cout<<"No puedes establecer un periodo mayor a 2 años";
		goto periodo;
		
	}
	cout<<endl<<endl;
	
	
	
	//pregunta si quiere amortizar
	cout<<"Desea aplicar amortizacion? "<<endl;
	cout<<"Presione 1 para aplicar amortizacion, cualquier numero para caso contrario.";
	cout<<endl<<endl;
	cout<<"Opcion: ";cin>>opcion;
	cout<<endl<<endl;
	
	
	
	//condicion si elige si quiere amortizar
	if(opcion == 1){
		
		//aqui introduce la amortizacion y a partir de que mes
		cout<<"Cuantos quieres amortizar?: ";cin>>coutas[4].amortizacion;
		
		hola:
		cout<<endl;
		
		cout<<"A partir de que mes quieres amortizar?: ";cin>>time;
		
		if(time > coutas[3].perido){
			cout<<"Ese periodo de tiempo no existe, porfavor ingrese uno correcto";
			goto hola;
			
		}
		
	system("cls");
	//procedimiento imprimiendo las variables
	cout<<"     **** Corrida de pagos de un prestamo por ="<<el_monto<<" dolares con una tasa de interes de ="<<coutas[2].interes<<"% \n";
	cout<<"          para ser pagado inicialmente en un periodo de = "<<coutas[3].perido<<" meses. ****";
		
	cout<<endl<<endl;
		
	cout<<"PRESTAMO = "<<el_monto<<endl;
	cout<<"Cuota = prestamo x interes / [1 - (interes + 1)^( - periodo)]";
	
	cout<<endl<<endl<<endl;
	
	
	
	
	//procedimiento de las casillas	
	float couta = fun_cuota(coutas[1].monto,coutas[2].interes,coutas[3].perido);
		
	cout<<"Mes  "<<"Couta"<<"     "<<"Interes"<<"      "<<"Aporte"<<"     "<<"Monto Pendiente";
	cout<<endl<<endl;
	while(duracion <= coutas[3].perido){
	
	interes = fun_interes(coutas[1].monto,coutas[2].interes);
	aporte = couta-interes;
	pendiente = coutas[1].monto - aporte;
	coutas[1].monto = pendiente;
	
	cout<<endl;
	
	
	if(time == duracion){
		
	coutas[1].monto  = coutas[1].monto-coutas[4].amortizacion;
	
	cout<<"("<<duracion<<")"<<" "<<fixed<<setprecision(2)<<couta<<"    "<<
	fixed<<setprecision(2)<<interes<<"       "<<
	fixed<<setprecision(2)<<aporte<<"      "<<
	fixed<<setprecision(2)<<coutas[1].monto<<"   Amortizacion de: "<<coutas[4].amortizacion;
	
	sum_interes[duracion] = interes;
	duracion++;	                 
	}
	
	else{
	
	
	
	if(coutas[1].monto == 0 or coutas[1].monto < 0){
		
		
		aporte = aporte+coutas[1].monto;
		couta = 0;
		couta = interes + aporte;
   		coutas[1].monto = 0;
   		cout<<"("<<duracion<<")"<<" "<<couta<<"    "<<interes<<"       "<<aporte<<"      "<<coutas[1].monto;
		break;
		
		
		}
	
	
	
	
	
	cout<<"("<<duracion<<")"<<" "<<fixed<<setprecision(2)<<
	couta<<"    "<<fixed<<setprecision(2)<<interes<<"        "<<
	fixed<<setprecision(2)<<aporte<<"      "<<coutas[1].monto;
	sum_interes[duracion] = interes;
	duracion++;
	
	
   }
   
   
   
   
}
for(int i = 1; i <= sum_interes[duracion-1]; i++){
	
sum_interes2[0] = sum_interes2[0]+sum_interes[i];


}

cout<<endl<<endl;
cout<<"Total de interes pagado: "<<sum_interes2[0]<<endl;
cout<<"Total Pagado: "<<el_monto<<" + "<<sum_interes2[0]<<" = "<<el_monto+sum_interes2[0];

	
		
	}
	
	
	
	else{
	
	
	system("cls");
		
	cout<<"     **** Corrida de pagos de un prestamo por ="<<el_monto<<" dolares con una tasa de interes de ="<<coutas[2].interes<<"% \n";
	cout<<"          para ser pagado inicialmente en un periodo de = "<<coutas[3].perido<<" meses. ****";
		
	cout<<endl<<endl;
		
	cout<<"PRESTAMO = "<<el_monto<<endl;
	cout<<"Cuota = prestamo x interes / [1 - (interes + 1)^( - periodo)]";
	
	cout<<endl<<endl<<endl;
	
	float couta = fun_cuota(coutas[1].monto,coutas[2].interes,coutas[3].perido);
	
	cout<<"Mes  "<<"Couta"<<"     "<<"Interes"<<"   "<<"Aporte"<<"    "<<"Monto Pendiente";
	cout<<endl<<endl;
	
	
	while(duracion <= coutas[3].perido){
	
	interes = fun_interes(coutas[1].monto,coutas[2].interes);
	aporte = couta-interes;
	pendiente = coutas[1].monto - aporte;
	coutas[1].monto = pendiente;
	

	cout<<endl;
	cout<<"("<<duracion<<")"<<" "<<fixed<<setprecision(2)<<couta<<"    "<<fixed<<setprecision(2)<<
	interes<<"    "<<fixed<<setprecision(2)<<aporte<<"      "<<
	fixed<<setprecision(2)<<pendiente;
	
	sum_interes[duracion] = interes;
	duracion++;
	if(pendiente == 0 or pendiente < 0){
		pendiente = 0;
		break;
	}

}
for(int i = 1; i <= sum_interes[duracion-1]; i++){
	
sum_interes2[0] = sum_interes2[0]+sum_interes[i];


   }

cout<<endl<<endl;
cout<<"Total de interes pagado: "<<sum_interes2[0]<<endl;
cout<<"Total Pagado: "<<el_monto<<" + "<<sum_interes2[0]<<" = "<<el_monto+sum_interes2[0];

 }
 
 cout<<endl<<endl<<endl;
 
 cout<<"Quiere volver a utilizar el programa?"<<endl;
 cout<<"Selecione 1 para volver, caso contrario presione cualquier numero."<<endl;
 cout<<"Opcion: ";cin>>opcion;
 
 
 
 if(opcion == 1){
 	system("cls");
 	goto inicio;
 }
 else{
 	return 0;
 }
 
}
