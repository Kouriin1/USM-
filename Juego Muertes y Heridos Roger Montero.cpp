// Task: Elabore un juego de Muerte y Heridos

#include<time.h>
#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

using namespace std;

// definniendo las coordendas
void gotoxy(int x, int y){
	COORD coordenadas;
	coordenadas.X = x;
	coordenadas.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenadas);
	
	
}

// una funcion de autor
void autor(){
	system("cls");
	
	
gotoxy(2,1); cout<<"-------------------------------------------Autor------------------------------------------------";

	
	string rogelio = "Elaborado por Roger Montero, C.I: 30.679.063";
	for(int i = 0; i <= rogelio.length(); i++ ){
	Beep(300, 30);
	gotoxy(1+i,3);cout<<rogelio[i];
	

}
Sleep(1700);



cout<<endl<<endl<<endl<<endl;
system("pause");

}

// funcion de instrucciones
void intruction(){
	system("cls");
	char op1;
gotoxy(2,1); cout<<"-------------------------------------------Instrucciones------------------------------------------------";
	// declaro una variable string y con esa variable hago un ciclo for sacando la anchura y que me imprima letra por letra
	
	//asi sucesivamente hasta terminar las instrucciones 
	string intrucion = "Bienvenidos al juego de Muertes y Heridos, en esta parte procederemos a explicar de que trata el juego y cuales son sus reglas.";
	
	
for(int i = 0; i <= intrucion.length(); i++ ){
	Beep(300, 40);
	gotoxy(1+i,3);cout<<intrucion[i];
	

}
string mensaje = "ADVERTENCIA"; 
for(int i = 0; i <= mensaje.length(); i++ ){
	Beep(900, 100);
	gotoxy(47+i,6);cout<<mensaje[i];
	
}

string mensaje2 = "Las intrucciones avaces pueden ser largas y tediosas, si usted ya vio las intrucciones por favor precione la tecla 1, si no precione cualquier tecla.";
for(int i = 0; i <= mensaje2.length(); i++ ){
	Beep(400,30);
	gotoxy(0+i,8);cout<<mensaje2[i];
	
}

string mensaje3 = "Opcion: ";
for(int i = 0; i <= mensaje3.length(); i++ ){
	Beep(400,30);
	gotoxy(0+i,10);cout<<mensaje3[i];
	
}
do{

gotoxy(8,10); op1 = getche();



switch(op1){
	case '1':{
		goto intro;
		break;
	}
	default:{
		return;
		break;
	}
	
 }
}while(1);
intro:



system("cls");
gotoxy(2,1); cout<<"-------------------------------------------Instrucciones------------------------------------------------";



string intrucio2 = "El juego Muertes y Heridos es un juego de deduccion logica para dos o mas jugadores";
for(int i = 0; i <= intrucio2.length(); i++){
	Beep(300,40);
	gotoxy(1+i,3);cout<<intrucio2[i];
}



string intrucio3 = "Pero en este caso jugaras tu contra la maquina.";
for(int i = 0; i <= intrucio3.length(); i++){
	Beep(300,40);
	gotoxy(1+i,4);cout<<intrucio3[i];
}
cout<<endl<<endl;
system("pause");

string intrucio4 = "El juego consiste que va a generar un numero aleatorio de 4 digitos diferentes, tu objetivo sera deducir cual es el numero que genero y en la posicion exacta de esos numeros,";
for(int i = 0; i <= intrucio4.length(); i++){
	Beep(300,40);
	gotoxy(1+i,8);cout<<intrucio4[i];
}

string intrucio5 = "es decir si la maquina genero el numero: 5432, tu objetivo sera deducir ese numero y en el orden correcto de los numeros.";
for(int i = 0; i <= intrucio5.length(); i++){
	Beep(300,40);
	gotoxy(1+i,10);cout<<intrucio5[i];
}
cout<<endl<<endl;
system("pause");

string intrucio6 = "Los numeros a decifrar se tendran que poner en una casillas de este estilo: [ ] [ ] [ ] [ ]";
for(int i = 0; i <= intrucio6.length(); i++){
	Beep(300,40);
	gotoxy(1+i,15);cout<<intrucio6[i];
}

string intrucio7 = "Cada casilla representa el numero que usted va a colocar.";
for(int i = 0; i <= intrucio7.length(); i++){
	Beep(300,40);
	gotoxy(1+i,16);cout<<intrucio7[i];
}


cout<<endl<<endl;

system("pause");

string intrucio8 = "Ahora procederemos a explicar que consiste las muertes y los heridos.";
for(int i = 0; i <= intrucio8.length(); i++){
	Beep(300,40);
	gotoxy(1+i,20);cout<<intrucio8[i];
}
cout<<endl<<endl;
system("pause");

system("cls");

gotoxy(2,1); cout<<"-------------------------------------------Instrucciones------------------------------------------------";

string intrucio9 = "El juego se va a representar de la siguiente manera:";
for(int i = 0; i <= intrucio9.length(); i++){
	Beep(300,40);
	gotoxy(1+i,3);cout<<intrucio9[i];
}


gotoxy(3,5); Beep(500,40);cout<<"  _______________________________________________________________________________ ";
gotoxy(3,6);Beep(500,40); cout<<"  |                                                    |                        |";
gotoxy(3,7);Beep(500,40); cout<<"  |                 MUERTES Y HERIDOS                  |       Jugador          |";
gotoxy(3,8); Beep(500,40);cout<<"  |____________________________________________________|________________________|" ;   
gotoxy(3,9); Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,10);Beep(500,40);cout<<"  |                                                    |________________________|";
gotoxy(3,11);Beep(500,40);cout<<"  |                 Numero Generado                    |                        |";
gotoxy(3,12);Beep(500,40);cout<<"  |                                                    |   Numero Insertado     |";
gotoxy(3,13);Beep(500,40);cout<<"  |                      ****                          |                        |";
gotoxy(3,14);Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,15);Beep(500,40);cout<<"  |                                                    |________________________|";
gotoxy(3,16);Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,17);Beep(500,40);cout<<"  |                 Numero a Buscar                    |                        |";
gotoxy(3,18);Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,19);Beep(500,40);cout<<"  |                 [ ] [ ] [ ] [ ]                    |  Muertes      Heridos  |";
gotoxy(3,20);Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,21);Beep(500,40);cout<<"  |                                                    |     -            -     |";
gotoxy(3,22);Beep(500,40);cout<<"  |                                                    |________________________|";
gotoxy(3,23);Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,24);Beep(500,40);cout<<"  |                                                    |         Vidas          |";
gotoxy(3,25);Beep(500,40);cout<<"  |                                                    |                        |";
gotoxy(3,26);Beep(500,40); cout<<" _______________________________________________________________________________";
 
 string intrucio10 = "Donde aqui estan el Numero a decifrar";
 for(int i = 0; i <= intrucio10.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio10[i];
}

gotoxy(2,19); Beep(1000,600);cout<<"==>";

    Sleep(2000);
    
  gotoxy(2,19); cout<<"   ";
  gotoxy(1,28);cout<<"                                                    ";
  
   string intrucio11 = "Aqui las muertes y los heridos";
   
 for(int i = 0; i <= intrucio11.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio11[i];
}

gotoxy(85,21); Beep(1000,600);cout<<"<==";

    Sleep(2000);
    
gotoxy(85,21); cout<<"   ";    
gotoxy(1,28);cout<<"                                                    ";



  string intrucio12 = "El numero aleatorio que se va a generar";
  for(int i = 0; i <= intrucio12.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio12[i];
}  
 gotoxy(2,13); Beep(1000,600);cout<<"==>";   
    
     Sleep(2000);
     
    gotoxy(2,13); Beep(1000,600);cout<<"   ";
    gotoxy(1,28);cout<<"                                                    ";
    
    
     string intrucio13 = "El nombre del jugador. Se va a pedir un nombre en especifico para jugar";
  for(int i = 0; i <= intrucio13.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio13[i];
}  
     gotoxy(85,9); Beep(1000,600);cout<<"<=="; 
    
       Sleep(2000);
       
     gotoxy(85,9);cout<<"   "; 
     gotoxy(1,28);cout<<"                                                                         ";
    
string intrucio14 = "Por ultimo las vidas, que quiere decir las oportunidades que tendras, que seran un total de 7 oportunidades que usted dispone. Por cada apuesta que usted ponga se le restara una vida.";
  for(int i = 0; i <= intrucio14.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio14[i];
} 
gotoxy(85,25); Beep(1000,600);cout<<"<=="; 
    
    Sleep(1000);
    
    for(int i = 0;i <= 6; i++){
    	gotoxy(67+i,25);Beep(500,90);printf("%c",3);
	}
    
    Sleep(2000);
    
   gotoxy(1,31); system("pause");
   gotoxy(1,31); cout<<"                                                                              ";
    gotoxy(1,28);cout<<"                                                                                                                                            ";
    gotoxy(1,29);cout<<"                                                                               ";
    gotoxy(85,25);cout<<"   ";
    
    string intrucio15 = "Las Muertes representan los digitos que pertenecen a la respuesta y se encuentran en la posicion correcta, los heridos son los digitos que pertenecen a la respuesta y se encuentran en una posicion incorrecta,        Por ejemplo ";
    for(int i = 0; i <= intrucio15.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio15[i];
} 
 gotoxy(1,31); system("pause");
 gotoxy(1,31); cout<<"                                            ";

  gotoxy(1,28);cout<<"                                                                                                                                  ";
  gotoxy(1,29);cout<<"                                                                                                                                  ";
  gotoxy(1,30);cout<<"                                                                                                                                  ";
  
  string intrucio16 = "Imaginemos que el numero que genero la maquina sea 4325";
   for(int i = 0; i <= intrucio16.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio16[i];
} 
  gotoxy(30,13);for(int i = 0;i < 3 ; ){
    	gotoxy(28,13);Beep(400,800);cout<<"4";
    	i++;
    	gotoxy(29,13);Beep(400,800);cout<<"3";
    	i++;
    	gotoxy(30,13);Beep(400,800);cout<<"2";
    	i++;
    	gotoxy(31,13);Beep(400,800);cout<<"5";
    	gotoxy(31,13);Beep(400,800);
	}
	
Sleep(1000);
	
gotoxy(1,28);cout<<"                                                                                                                                  ";
	
string intrucio17 = "Obviamente usted no puede ver ese numero pero nos sirve para que entienda el ejemplo";
	for(int i = 0; i <= intrucio17.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio17[i];
	}
	
	Sleep(1500);
	
	gotoxy(1,28);cout<<"                                                                                                                                  ";
	string intrucio18 = "Digamos que nuestra apuesta es el numero 4235";
	for(int i = 0; i <= intrucio18.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio18[i];
	}
	
	  for(int i = 0;i < 3 ; ){
    	gotoxy(24,19);Beep(400,800);cout<<"4";
    	i++;
    	gotoxy(28,19);Beep(400,800);cout<<"2";
    	i++;
    	gotoxy(32,19);Beep(400,800);cout<<"3";
    	i++;
    	gotoxy(36,19);Beep(400,800);cout<<"5";
    	gotoxy(36,19);Beep(400,800);
	}



Sleep(1500);


gotoxy(64,21);cout<<"2";
gotoxy(77,21);cout<<"2";
gotoxy(1,28);cout<<"                                                                                                                                  ";

string intrucio19 = "El sistema aviso que obtuviste 2 Muertes y 2 Heridos";
for(int i = 0; i <= intrucio19.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio19[i];
	}
	
gotoxy(73,25);Beep(500,90);cout<<" ";

Sleep(2000);
gotoxy(1,28);cout<<"                                                                                                                                  ";
string intrucio20 = "Por que usted acerto 2 numeros en la posicion correcta y acerto 2 numeros que pertenencen a la respuesta pero no en la casilla correcta";
for(int i = 0; i <= intrucio20.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio20[i];
	}

Sleep(1500);

gotoxy(1,28);cout<<"                                                                                                                                  ";
gotoxy(1,29);cout<<"                                                                                                                                  ";

string intrucio21 = "Los numeros de la posicion correcta son: 4 y el 5 que son las muertes. ";
for(int i = 0; i <= intrucio21.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio21[i];
	}

string intrucio22 = "Los numero acertados pero en posicion incorrecta son: 2 y 3 que son los heridos.";
for(int i = 0; i <= intrucio22.length(); i++){
	Beep(300,40);
	gotoxy(1+i,29);cout<<intrucio22[i];
	}	
	
	Sleep(2000);
gotoxy(24,19);cout<<" ";
gotoxy(28,19);cout<<" ";
gotoxy(32,19);cout<<" ";
gotoxy(36,19);cout<<" ";	
gotoxy(64,21);cout<<" ";
gotoxy(77,21);cout<<" ";
gotoxy(1,28);cout<<"                                                                                                                                  ";
gotoxy(1,29);cout<<"                                                                                                                                  ";
string intrucio23 = "Intentemos ahora con otra apuesta, vamos a apostar el numero 1325.";
for(int i = 0; i <= intrucio23.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio23[i];
	}
	
	  for(int i = 0;i < 3 ; ){
    	gotoxy(24,19);Beep(400,800);cout<<"1";
    	i++;
    	gotoxy(28,19);Beep(400,800);cout<<"3";
    	i++;
    	gotoxy(32,19);Beep(400,800);cout<<"2";
    	i++;
    	gotoxy(36,19);Beep(400,800);cout<<"5";
    	gotoxy(36,19);Beep(400,800);
	}

Sleep(1500);
gotoxy(64,21);cout<<"3";
gotoxy(77,21);cout<<"0";
gotoxy(72,25);cout<<" ";	
gotoxy(1,28);cout<<"                                                                                                                                  ";
string intrucio24 = "El sistema aviso que usted acerto 3 muertos y 0 herido";	
	for(int i = 0; i <= intrucio24.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio24[i];
	}
	
	Sleep(1200);
	
	gotoxy(1,28);cout<<"                                                                                                                                  ";
	
string intrucio25 = "Las muertes son los numeros: 3, 2 y 5 que son los numeros que acerto con exito.";
	for(int i = 0; i <= intrucio25.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio25[i];
	}
	Sleep(1900);
	gotoxy(1,28);cout<<"                                                                                                                                  ";	
	gotoxy(1,29);cout<<"                                                                                                                                  ";
	
string intrucio26 = "Heridos no hay, por que el numero (1) ingresado no pertenece a ninguna respuesta.";
	for(int i = 0; i <= intrucio26.length(); i++){
	Beep(300,40);
	gotoxy(1+i,29);cout<<intrucio26[i];
	}
	gotoxy(1,31); system("pause");
   gotoxy(1,31); cout<<"                                                                              ";
	gotoxy(1,29);cout<<"                                                                                                                                  ";
	
	string intruciop1 = "Ganara el juego cuando acierte los 4 muertos. Perdera el juego si se le acaba las vidas";
	for(int i = 0; i <= intruciop1.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intruciop1[i];
	}
	
	Sleep(2000);
	gotoxy(1,28);cout<<"                                                                                                                                  ";
	
	
	string intrucio27 = "Con esto finalizamos la explicacion del juego";
	for(int i = 0; i <= intrucio27.length(); i++){
	Beep(300,40);
	gotoxy(1+i,28);cout<<intrucio27[i];
	}
	
gotoxy(1,35);system("pause");

system("cls");

gotoxy(2,1); cout<<"-------------------------------------------Instrucciones------------------------------------------------";

string intrucio28 = "Acciones que usted no debe cometer a la hora de jugar";
for(int i = 0; i <= intrucio28.length(); i++){
	Beep(300,40);
	gotoxy(1+i,3);cout<<intrucio28[i];
}
Sleep(2000);
string intrucio29 = "1) No meta mas de 2 digitos en una casilla, automaticamente es game over.";
for(int i = 0; i <= intrucio29.length(); i++){
	Beep(300,40);
	gotoxy(1+i,5);cout<<intrucio29[i];
}
Sleep(1900);
string intrucio30 = "2) No ingrese numeros iguales en las casillas, por ejemplo [2] [2] [3] [1].";
for(int i = 0; i <= intrucio30.length(); i++){
	Beep(300,40);
	gotoxy(1+i,7);cout<<intrucio30[i];
}
Sleep(1900);
string intrucio31 = "3) No ingrese caracteres en las casillas, solamente numericas, si usted lo hace automaticamente no podra jugar mas el  juego hasta que lo cierre.";
for(int i = 0; i <= intrucio31.length(); i++){
	Beep(300,40);
	gotoxy(1+i,9);cout<<intrucio31[i];
}

Sleep(2000);

string intrucio32 = "Con esto finalizamos las instrucciones, espero que disfrute el juego :)";
for(int i = 0; i <= intrucio32.length(); i++){
	Beep(300,40);
	gotoxy(1+i,12);cout<<intrucio32[i];
}


cout<<endl<<endl<<endl<<endl;
system("pause");





}

// funcion si pierde el juego
void game_over(){
	system("cls");
	  // Reproduce un sonido de 800 Hz durante 100 ms
    Beep(800, 100);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 700 Hz durante 150 ms
    Beep(700, 150);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 600 Hz durante 200 ms
    Beep(600, 200);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 500 Hz durante 250 ms
    Beep(500, 250);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 400 Hz durante 300 ms
    Beep(400, 300);
	
	gotoxy(30,9);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,10);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,11);cout<<"|----------------PERDISTE---------------|"<<endl;
	gotoxy(30,12);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,13);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,14);cout<<"|---------------------------------------|"<<endl;

	Sleep(1500);
	
	gotoxy(25,17);cout<<"Precione cualquier tecla para continuar. . . . ";
	getch();
	
	
}





// funcion si gana
void victory(){
	system("cls");
 // Reproduce un sonido de 400 Hz durante 300 ms
    Beep(400, 300);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 500 Hz durante 250 ms
    Beep(500, 250);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 600 Hz durante 200 ms
    Beep(600, 200);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 700 Hz durante 150 ms
    Beep(700, 150);
    // Espera 50 ms
    Sleep(50);
    // Reproduce un sonido de 800 Hz durante 100 ms
    Beep(800, 100);
    // Espera 50 ms
    Sleep(50);

	gotoxy(30,9);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,10);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,11);cout<<"|----------------GANASTE----------------|"<<endl;
	gotoxy(30,12);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,13);cout<<"|---------------------------------------|"<<endl;
	gotoxy(30,14);cout<<"|---------------------------------------|"<<endl;

	Sleep(1500);
	
	gotoxy(25,17);cout<<"Precione cualquier tecla para continuar. . . . ";
	getch();	
}


// el juego

void play(){
	system("cls"); // para borrar el main
int Muertes = 0;// heridos
int num[4] = {0};
int Heridos = 0; //muertes
int vidas = 7; // las vidas

string User = ""; //nombre del jugador
	
	 // Declarar las frecuencias de las notas musicales
  const int doo = 262;
  const int re = 294;
  const int mi = 330;
  const int fa = 349;
  const int sol = 392;
  const int la = 440;
  const int si = 494;
  
  // Declarar la duración de las notas musicales
  const int negra = 500; // Milisegundos
  const int blanca = negra * 2;

gotoxy(40,6); cout<<"                                          "<<endl;
gotoxy(40,7); cout<<"                                          "<<endl;
gotoxy(40,8); cout<<"                                          "<<endl;
gotoxy(40,9);cout<<"                                           "<<endl;
gotoxy(40,10);cout<<"                                          "<<endl<<endl;	

gotoxy(40,12);cout<<"      "; 
 cout<<endl;		
	
  
	
	user:
gotoxy(40,8); cout<<"Introduzca Nombre de usuario: "<<endl<<endl;
gotoxy(47,10);getline(cin,User);
gotoxy(40,8); cout<<"                                "<<endl<<endl;
gotoxy(47,10);cout<<"                                 ";


if(User.length() == 0){
gotoxy(30,10);cout<<"Debes insertar un nombre"<<endl;
	gotoxy(30,10); cout<<"                                                        ";
	gotoxy(30,12); cout<<"                                                        ";
goto user;
	
}

for(int i = 0; i <= User.length(); i++){
	if(i > 15){
		cout<<endl<<endl;
		gotoxy(30,10);cout<<"el nombre de usuario no debe tener mas de 15 caracteres"<<endl;
		gotoxy(30,12);	system("pause");
		gotoxy(30,10); cout<<"                                                        ";
		gotoxy(30,12); cout<<"                                                        ";
		goto user;
		
	}
	
}
gotoxy(40,12); cout<<"                                                                              ";

gotoxy(40,10);	cout<<"Cargando Juego...";


  
    Beep(doo, negra); // Reproducir la nota DO por el tiempo de una negra
    Beep(mi, negra); // Reproducir la nota MI por el tiempo de una negra
    Beep(sol, negra); // Reproducir la nota SOL por el tiempo de una negra
    Beep(si, negra); // Reproducir la nota SI por el tiempo de una negra
    Beep(sol, blanca); // Reproducir la nota SOL por el tiempo de una blanca
    Beep(mi, blanca); // Reproducir la nota MI por el tiempo de una blanca
    Beep(doo, blanca); // Reproducir la nota DO por el tiempo de una blanca
  

	
		vuelve:
	int digito[4]= {0};
	double aux;
	int aux2;
	srand(time(NULL));
	
	int x = 1000+rand()%8999+ 1; //diferecia entre 1000 y 9999
	aux2 = x;
	for(int i = 0; i <= 3;){
		aux = aux2%10;
		digito[i] = aux;
		aux2 =  aux2/10;
		i++;
}
//comprobacion si los numeros son diferentes
bool repetido = false; //falso porque no hay numeros repetidos
for(int i = 3; i >= 0; i--){
	digito[i];
	
	if(digito[3] == digito[2] or digito[3] == digito[1] or digito[3] == digito[0] or
	   digito[2] == digito[1] or digito[2] == digito[0] or
	   	digito[1] == digito[0]){
	   		
	   		repetido = true;
	   	
	   		break;
		   }else{}
}
if(digito[3] == digito[2] or digito[3] == digito[1] or digito[3] == digito[0] or
	   digito[2] == digito[1] or digito[2] == digito[0] or
	   	digito[1] == digito[0]){
	   		
	   		goto vuelve;
		   }
		   cout<<endl<<endl;
		   for(int i = 0; i <= 3 ; i++){
		   gotoxy(33+i,24);cout<<"*";
		   gotoxy(10,24);cout<<"|";
		   gotoxy(63,24);cout<<"|";
		   gotoxy(88,24);cout<<"|";
		   }
gotoxy(40,10); cout<<"                      ";


while(vidas >= 0){

//Imprimiendo el juego

gotoxy(10,15);	cout<<"_______________________________________________________________________________"<<endl;   
gotoxy(10,16);	cout<<"|                                                    |                        |"<<endl;
gotoxy(10,17);	cout<<"|                 MUERTES Y HERIDOS                  |       Jugador          |"<<endl;
gotoxy(10,18);  cout<<"|____________________________________________________|________________________|"<<endl;
gotoxy(10,19);  cout<<"|                                                    |                        |"<<endl;
gotoxy(10,20); cout<<"|"<<"                                                    |"<<"                        |";
gotoxy(70,20);cout<<User;
gotoxy(10,21);	cout<<"|                                                    |________________________|"<<endl;
gotoxy(10,22);	cout<<"|                 Numero Generado                    |                        |"<<endl;
gotoxy(10,23);	 cout<<"|                                                    |   Numero Insertado     |";
gotoxy(10,25);  cout<<"|                                                    |                        |"<<endl;
		
gotoxy(10,26);	cout<<"|"<<endl;
gotoxy(63,26);	cout<<"|"<<endl;
gotoxy(88,26);	cout<<"|"<<endl;

gotoxy(10,27);	cout<<"|                                                    |________________________|"<<endl;	
gotoxy(10,28);	cout<<"|                                                    |                        |"<<endl;	
gotoxy(10,29);	cout<<"|                 Numero a Buscar                    |                        |"<<endl;
gotoxy(10,30); cout<<"|";
gotoxy(63,30); cout<<"|";
gotoxy(88,30); cout<<"|";
		   
gotoxy(10,31);	cout<<"|                 [ ] [ ] [ ] [ ]                    |  Muertes      Heridos  |"<<endl;
gotoxy(10,32);  cout<<"|                                                    |                        |"<<endl;

gotoxy(69,33); cout<<Muertes;
gotoxy(82,33);cout<<Heridos;
gotoxy(10,33); cout<<"|";
gotoxy(63,33); cout<<"|";
gotoxy(88,33); cout<<"|";	

gotoxy(10,34);	cout<<"|                                                    |                        |"<<endl;
gotoxy(10,35);	cout<<"|                                                    |________________________|"<<endl;
gotoxy(10,36);	cout<<"|                                                    |                        |"<<endl;
gotoxy(10,37);	cout<<"|                                                    |         Vidas          |"<<endl;

gotoxy(10,38);	cout<<"|                                                    |                        |"<<endl;
for(int i = 0; i < vidas; i++){
gotoxy(72+i,38); printf("%c",3);
}	
gotoxy(10,39);	cout<<"_______________________________________________________________________________"<<endl;


gotoxy(17,41);cout<<"  ___________________________________________________";
gotoxy(17,42);cout<<"  |                                                 |";
gotoxy(17,43);cout<<"  |                 Numeros Digitados               |";
gotoxy(17,44);cout<<"  |_________________________________________________|" ;   
gotoxy(17,45);cout<<"  |                                                 |";
gotoxy(17,46);cout<<"  |";
gotoxy(67,46);cout<<"  |";
gotoxy(17,47);cout<<"  |";
gotoxy(67,47);cout<<"  |";
gotoxy(17,48);cout<<"  |";
gotoxy(67,48);cout<<"  |";
gotoxy(17,49);cout<<"  |";
gotoxy(67,49);cout<<"  |";
gotoxy(17,50);cout<<"  |";
gotoxy(67,50);cout<<"  |";
gotoxy(17,51);cout<<"  |";
gotoxy(67,51);cout<<"  |";
gotoxy(17,52);cout<<"  |";
gotoxy(67,52);cout<<"  |";
gotoxy(17,53);cout<<"  ____________________________________________________";
 







numero:
// la digitacion de los numeros
gotoxy(29,31); for(int i = 0 ;i < 3; ){
	cin>>num[i];
	i++;
	gotoxy(33,31);cin>>num[i];
	i++;
	gotoxy(37,31);cin>>num[i];
	i++;
	gotoxy(41,31);cin>>num[i];
	i++;

	}
	
	
	
	// si mete un valor mayor que 10 o menor que 0, automaticamente es game over
	if(num[3] > 9 or num[3] < 0 or num[2] > 9 or num[2] < 0 or num[1] > 9 or num[1] < 0 or num[0] > 9 or num[0] < 0)
	 	{
   			game_over();
   			break;
      }

	
	// si activa el codigo secreto
	if(num[3] == 0 and num[2] == 0 and num[1] == 0 and num[0] == 0){
		string aler2 = "Activando codigo secreto...";
		 for(int i = 0; i <= aler2.length(); i++){
		 gotoxy(11+i,34);Beep(300,60);cout<<aler2[i];
		 
	
		 }
			Sleep(1200);
		 gotoxy(11,34);cout<<"                              ";
	   	  for(int i = 0; i <= 3 ; i++){
	   	  
		   gotoxy(33+i,24);Beep(900,500);cout<<digito[i];
		   
		   }
	   	 
	   }
	   //para ocultar el codigo secreto
	   if(num[3] == 1 and num[2] == 1 and num[1] == 1 and num[0] == 1){
		string aler2 = "Activando codigo secreto...";
		 for(int i = 0; i <= aler2.length(); i++){
		 gotoxy(11+i,34);Beep(300,60);cout<<aler2[i];
		 
	
		 }
			Sleep(1200);
		 gotoxy(11,34);cout<<"                              ";
	   	  for(int i = 0; i <= 3 ; i++){
	   	  
		   gotoxy(33+i,24);Beep(900,500);cout<<"*";
		   
		   }
	   	 
	   } 
	   	//borra los numeros puestos y se devuelve a la al sitio para la digitacion de numeros		
	 if(num[3] == 0 and num[2] == 0 and num[1] == 0 and num[0] == 0 or 
	    num[3] == 1 and num[2] == 1 and num[1] == 1 and num[0] == 1  ){
		
	   	gotoxy(29,31);cout<<" ";
		gotoxy(33,31);cout<<" ";
		gotoxy(37,31);cout<<" ";
		gotoxy(41,31);cout<<" ";
	   
	   goto numero;
	   
      }else if(num[3]== num[2] or num[3]== num[2] or num[3]== num[0] or //condicion si pone numeros iguales
	   num[2]== num[1] or num[2]== num[0] or
	   num[1]== num[0]){
		string aler = "No puedes poner numeros iguales.";
		for(int i= 0; i<= aler.length(); i++){
		gotoxy(11+i,34);Beep(300,60);cout<<aler[i];
		gotoxy(29,31);cout<<" ";
		gotoxy(33,31);cout<<" ";
		gotoxy(37,31);cout<<" ";
		gotoxy(41,31);cout<<" ";
		}
		Sleep(1900);
		gotoxy(11,34);cout<<"                                 ";
		goto numero;
		
}
	

	//imprime los numeros en una esquina de cuadro principal
gotoxy(70,26);for(int i = 0; i < 4 ; ){
	
	gotoxy(71,26);cout<<num[i];
	i++;
	gotoxy(73,26);cout<<num[i];
	i++;
	gotoxy(75,26);cout<<num[i];
	i++;
	gotoxy(77,26);cout<<num[i];
	i++;
   // aqui la imprime los intentos puestos
  if(vidas == 7)
  {
   	
   for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,46);cout<<num[i];
   	
   }
  }
   
   if(vidas  == 6)
   {
   	for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,47);cout<<num[i];
   	
    }
  }	
   
    if(vidas  == 5)
   {
   	for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,48);cout<<num[i];
   	
    }
  }
	 if(vidas  == 4)
   {
   	for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,49);cout<<num[i];
   	
    }
  }
	
	 if(vidas  == 3)
   {
   	for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,50);cout<<num[i];
   	
    }
  }
  
   if(vidas  == 2)
   {
   	for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,51);cout<<num[i];
   	
    }
  }
  
   if(vidas  == 1)
   {
   	for(int i = 0; i < 4 ; i++){
   	gotoxy(43+i,52);cout<<num[i];
   	
    }
  }
	
}
// para que suene musiquita
while(vidas > 1){

Beep(400,200);
Beep(300,200);
break;
}



	
	
	Muertes = 0;
	Heridos = 0;
// comprobacion de muertes y heridos
	 if(num[3]== digito[3] or num[2]== digito[2] or num[1]== digito[1] or
	 	num[0]== digito[0]){
								 
	 
	 
	if(num[3]== digito[3]){
		Muertes++;
		
	} 
	if(num[2]== digito[2]){
		Muertes++;
		
	} 
	if(num[1]== digito[1]){
		Muertes++;
		
	}
	 if(num[0]== digito[0]){
		Muertes++;
		}
		
	}else{
		Muertes = 0;
	
}
	
	if(num[3] == digito[2] or num[3] == digito[1] or num[3] == digito[0] or
	   num[2] == digito[1] or num[2] == digito[0] or 
	   num[1] == digito[0]){
	   
	
	
	if(num[3]== digito[2]){
		Heridos++;	
	} 
	if(num[3]== digito[1]){
		Heridos++;
	}    
	if(num[3]== digito[0]){
		Heridos++;	
	} 
	if(num[2]== digito[3]){
		Heridos++;	
	} 
	if(num[2]== digito[1]){
		Heridos++;	
	} 
	if(num[2]== digito[0]){
		Heridos++;	
	}
	if(num[1]== digito[3]){
		Heridos++;	
	}
	if(num[1]== digito[2]){
		Heridos++;	
	}
	if(num[1]== digito[0]){
		Heridos++;	
	}
	if(num[0]== digito[1]){
		Heridos++;	
	}
	if(num[0]== digito[2]){
		Heridos++;	
	}
	if(num[0]== digito[3]){
		Heridos++;	
	}
	  	  	  
}else{
	Heridos=0;
}
	 // una alerta si le queda una vida  
if(vidas == 2){
		string aler3 = "Cuidado te queda una sola vida...";
		for(int i= 0; i<= aler3.length(); i++){
		gotoxy(11+i,34);Beep(1000,20);cout<<aler3[i];
	
       }
}
	Sleep(900);
	// condicion si gana
	   if(Muertes == 4){
	   	victory();
	   	break;
	   }
	   
	   	vidas--;
	   	// condicion si pierde
	   if(vidas == 0){
	   	game_over();
	   	break;
	   }
	 
	
	

	//final del ciclo while 
}





				

	
	
	//final del void

	}
	
	



int main(){
	main:
int intentos = 4; // esto si el usuario mete un digito no valido

char op;
do{

system("cls");
// el menu
gotoxy(35,5);  cout<<"-----------------------------------------"<<endl;
gotoxy(35,6);  cout<<"----------Muerte y Heridos---------------"<<endl;
gotoxy(35,7);  cout<<"-----------------------------------------"<<endl;
gotoxy(35,8);  cout<<"1) Start Game                           -"<<endl;
gotoxy(35,9);  cout<< "2) Instructions                         -"<<endl;
gotoxy(35,10); cout<<"3) Author                               -"<<endl;
gotoxy(35,11); cout<<"4) Leave the Game                       -"<<endl<<endl;	
hola:
gotoxy(35,13);cout<<"Option: "; op = getche(); // esta funcion permite meter cualquier variable sin aplicarle enter
if(op == '1'){ //esto es para que me borre si es usuario mete un digito invalido
cout<<endl<<endl;	
cout<<"                            "<<endl;	
cout<<"                           ";
gotoxy(35,13);cout<<"                               ";
cout<<endl<<endl;
}
		
	
	// lo case para los digitos
		switch(op){
			case '1':{
				play();
				break;
			}
			case '2': {
				intruction();
				break;
			}
			case '3': {
				autor();
				break;
			}
			case '4': {
				return 0;
				
			}
			
			default:{
				if(intentos == 1){
					Beep(1000, 500);
					return 0;
				}
				//default si no mete los digitos que corresponde
				cout<<endl<<endl;
				cout<<"!Digito Invalido!"<<endl;
				intentos--;
				
				cout<<"Numero de intentos: "<<intentos;
				cout<<endl<<endl;
				
				
				goto hola;
				
			}
			
		}
	
}while(1);
	
//Elaborado por: Roger Montero, C.I: 30.679.063
//Universidad Santa Maria
//Profesor: Carlos Ferrer
//Programacion I.
}
