//programa elaborado por Enzo Ortiz y Roger Montero
//fecha 22/11/2023
#include<math.h> 
#include<iostream>
#include<locale.h>
#include<windows.h>

using namespace std;

//Creo la funcion gotoxy para utilizar coordenadas en mi introduccion al programa
void gotoxy(int x, int y){
	COORD coordenadas;
	coordenadas.X = x;
	coordenadas.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenadas);	
}

// hago un void para narrar la historia 
void narracion_history(){

//utilizacion de gotoxy eh imprima partes donde quiero que se imprima los dibujos y textos	
gotoxy(2,11);	cout<<"                      ____________            "; 
gotoxy(2,12);	cout<<"                      |          |           ";
gotoxy(2,13);	cout<<"                      | USM NAVY |           "; 
gotoxy(2,14);	cout<<"                      |__________|           "; 
gotoxy(2,15);	cout<<"                      |                      ";
gotoxy(2,16);	cout<<"          ____________|__________	        ";
gotoxy(2,17);   cout<<"       __/_______________________|__         ";
gotoxy(2,18);	cout<<"  ____/_____________________________|_____     ";
gotoxy(2,19);	cout<<"  |||||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦||||    ";
gotoxy(2,20);	cout<<"   ||||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦|||     ";
gotoxy(2,21);	cout<<"    |||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ||       ";
gotoxy(2,22);	cout<<"     ||____________________________||        ";
	
	
Beep(50,300);
//explicacion 	
gotoxy(1,1);cout<<"Hola comandante Ferrer, aqui nuestro informe de nuestro barco USM Navy"<<endl<<endl;

	Sleep(1000);
	Beep(50,300);
	
cout<<"Necesitamos desembarcar, pero el enemigo ha colocado un arma en la costa"<<endl<<endl;

	Sleep(1000);
	Beep(50,300);
	
cout<<"El enemigo dispone un potente misil mejor el de nuestra artilleria, lo cual es una gran desventaja para nosotros..."<<endl<<endl;

	Sleep(1000);
	Beep(50,300);
	
	cout<<"Lo que ellos no saben es que nuestros cientificos descrubrieron que tendremos la ventaja del viento."<<endl<<endl;
	
gotoxy(1,25);	system("pause"); // hago una pausa y despues limpio la pantalla para que le imprima otra vez el barco con otros textos
				system("cls");
				
				
				
gotoxy(2,11);	cout<<"                      ____________           "; 
gotoxy(2,12);	cout<<"                      |          |           ";
gotoxy(2,13);	cout<<"                      | USM NAVY |           "; 
gotoxy(2,14);	cout<<"                      |__________|           "; 
gotoxy(2,15);	cout<<"                      |                      ";
gotoxy(2,16);	cout<<"          ____________|__________	        ";
gotoxy(2,17);   cout<<"       __/_______________________|__         ";
gotoxy(2,18);	cout<<"  ____/_____________________________|_____   ";
gotoxy(2,19);	cout<<"  |||||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦||||   ";
gotoxy(2,20);	cout<<"   ||||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦|||    ";
gotoxy(2,21);	cout<<"    |||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ||       ";
gotoxy(2,22);	cout<<"     ||____________________________||        ";
	
			
// explicacion			
gotoxy(1,1);cout<<"Disponemos de un anemometro, comandante Ferrer, para medir la velocidad del viento y saber cuando tendremos ventaja!"<<endl<<endl;		
	
	Sleep(1000);
	Beep(50,300);
	

gotoxy(1,25);system("pause"); //pauso y limpio la pantalla para imprimir el arma enemiga
			 system("cls");		
			
			
			
gotoxy(2,11);cout<<"   _________                                          ";
gotoxy(2,12);cout<<"  |         |________________________                 ";
gotoxy(2,13);cout<<"  | ENEMIGO |_______________________|                 ";
gotoxy(2,14);cout<<"  |_________|____________|                            ";
gotoxy(2,15);cout<<"   |||||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦|||||                         ";
gotoxy(2,16);cout<<"     |||¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦|||                           ";
gotoxy(2,17);cout<<"      ||_____________|||                              ";
gotoxy(2,18);cout<<" _____OOOOOOOOOOOOOO_______                           ";
gotoxy(2,19);cout<<"|                         |";
gotoxy(2,20);cout<<"|                         |";
gotoxy(2,21);cout<<"|                         |";
gotoxy(2,22);cout<<"|                         |";
gotoxy(2,23);cout<<"|                         |";
gotoxy(2,24);cout<<"|                         |";
gotoxy(2,25);cout<<"|                         |";
gotoxy(2,26);cout<<"|                         |";
gotoxy(2,27);cout<<"|                         |";
gotoxy(2,28);cout<<"|                         |";
gotoxy(2,29);cout<<"|                         |";
gotoxy(2,30);cout<<"|_________________________|";


	//explicacion
	gotoxy(1,1);cout<<"Nuestro enemigo esta Ubicado a una torre a 100mts de altura, que es otra ventaja para ellos. Aumentando su alcanse horizontal."<<endl<<endl;
			
	Sleep(1000);
	Beep(50,300);	
			
	cout<<"Pero ellos no saben que por el efecto del viento la velocidad inicial de su disparo va a disminuir."<<endl<<endl;		
		
	Sleep(3000);
	Beep(50,300);
			
	string rogelio = "ES AHORA O NUNCA, ";
	for(int i = 0; i <= rogelio.length(); i++ ){
	Beep(300, 80);
	gotoxy(1+i,8);cout<<rogelio[i];
	
}		

//fin del void	
gotoxy(1,32);	system("pause");
	
}

main(){
	
	narracion_history(); //void que lleva a la narracion
	
	programa:
	
	system("cls");
	//declaramos variables
	double xene, xusm,tmaxene, tvene, tvusm, tmaxusm, ang=45, ang1, vv, vv1, voene=400, vousm=390, nudo, a, b, c, d=200;
	int caso;

    //hacemos la conversion de grados a radianes
	ang1=45*M_PI/180;
	//informamos a que velocidad del viento tenemos ventaja
	cout<<"Los cientificos identificaron que a una velocidad de viento mayor o igual a 32.21 m/seg "<<endl;
	cout<<"que vendran siendo 62.61 nudos, poseemos ventaja."<<endl<<endl;
	//solicitamos la velocidad del viento
	cout<<"El anemametro nos indica que la velocidad del viento en nudos para esta tarde es: "; cin>>nudo; cout<<endl; vv=nudo*0.514444;
	
	Sleep(500);
	Beep(70,90);
	//llevamos la velocidad del viento de nudos a metros sobre segundos
	cout<<"Lo cual sera "<<vv<<" m/seg aproximadamente"<<endl<<endl;
	//ubicamos los valores de la resolvente para hallar xmaxenemiga
	a=-4.9;
	b=282.84;
	c=100;
	
	tvene=(-b-(sqrt(pow(b,2)-(4*a*c))))/(2*a);
	//hallamos xmaxusm
	tvusm=(2*(vousm*(cos(ang1))))/9.8;
	xene=((voene*(cos(ang1)))-(vv/4))*tvene;
	xusm=((vousm*(cos(ang1)))+(vv/4))*tvusm;
	
	Sleep(500);
	Beep(70,90);
	//informamos la distancia de precaucion que debe tener el barco para no ser derribado
	cout<<"Antes de atacar, debemos tener en cuenta que nuestra nave debe tener precaucion y acercarse maximo: "<<xene+d<<" metros"<<endl<<endl;
	cout<<"De lo contrario nuesto nave podria ser derribado."<<endl;
	
	Sleep(500);
	Beep(70,90);
	//informamos alcance del enemigo
	cout<<endl<<"El alcance maximo del arma enemiga es: "<<xene<<" metros."<<endl<<endl;
	
	Sleep(500);
	Beep(70,90);
	//informamos alcance de nuestra arma
	cout<<endl<<"El alcance maximo de nuestra arma es: "<<xusm<<" metros."<<endl<<endl;
	
	//indicamos cuando es factible atacar verificando si el viento esta nos da ventaja o desventaja
	if(nudo>=62.61){
		cout<<"Sugerimos atacar de inmediato, debemos aprovechar nuestra ventaja"<<endl;
		cout<<"Recuerde que contamos con solo un disparo, debera ser muy exacto.";
	} else{
		cout<<"No atacar, mantener distancia de seguridad"<<endl;
	}
	
	cout<<endl<<endl;
	//opcion de iniciar de nuevo el programa
	cout<<"quieres volver utilizar el programa? "<<endl;
	cout<<"opcion = 1 para si"<<endl;
	cout<<"opcion = 0 para no"<<endl<<endl;
	cout<<"Opcion = ";cin>>caso;
	
	switch(caso){
		case 1:{
			system("cls");
			goto programa;
			break;
		}
		case 0: {
			return 0;
			break;
		}
		
		default:{
			return 0;
			break;
		}
	}
	
	
}
