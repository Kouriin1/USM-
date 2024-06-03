#include<conio.h> 
#include<iostream>
#include<windows.h> 
using namespace std;

void gotoxy(int x, int y){
	COORD coordenadas;
	coordenadas.X = x;
	coordenadas.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenadas);
	
	
}





main()
{
int mm=5,ss=0, tab=0; //Se inicializa las variables del reloj 5:00; y una variable que nos servirá para saber cuantos caracteres se han introducido
string clave="**"; //se carga clave con 2 caracteres cualquiera para establecer su longitud

// Una serie de mensajes para iniciar el juego...
string mensaje = "OH NO! Alguien a activado una bomba...";
	for(int i = 0; i <= mensaje.length(); i++ ){
	Beep(300, 30);
	gotoxy(1+i,5);cout<<mensaje[i];
}
Sleep(1500);

string mensaje2 = "Por favor Carlos Ferrer ayudanos a desactivar la bomba!";
	for(int i = 0; i <= mensaje2.length(); i++ ){
	Beep(300, 30);
	gotoxy(1+i,7);cout<<mensaje2[i];
}
Sleep(1500);

cout<<endl<<endl<<endl;
system("pause");

system("cls");


while (mm>=0) //nos interesa que los minutos lleguen hasta cero, y una vez sea menor a este, salga del while para la explosión

         {

    Sleep(600); 
	system("cls"); 
	
	
	gotoxy(40,4);cout<<"RAPIDO! desactiva la bomba!"; 
	gotoxy(50,6);cout <<mm<<":"<<ss<<endl; //se imprime el valor inicial de la bomba 5:00
	 
         if(kbhit()!=0)

             {

              if(clave[0]=='*') //verificamos si no se ha introducido algun caracter 

                   {

                    clave[0]=getch(); //cargamos lo capturado en la posicion 0

                    cout<<"Clave: *"; //imprimimos un * simulando la contraseña introducida por el usuario
					tab=tab+1; //como se introdujo el primer caracter, incrementamos en 1 esta variable
                   }

                   else //en caso de que en la posicion 0 ya halla un valor, entonces lo cargamos en la posicion 1

                   {

                    clave[1]=getch(); 


                    tab=tab+1; //incrementamos tab a 2, lo cual signific que dos veces se presiono alguna tecla, lo que significa que se introdujeron 2 caracteres

                    cout<<"Clave: **"; //simulamos los dos caracteres introducidos 

                    }
                    
               if (tab==2)    { //en caso de ya haberse introducido dos caracteres verificamos si cumple con la contraseña
			    

             if (clave=="af" or clave=="AF") //en caso de ser igual se desactiva la bomba

                       {
                       	system("cls");
                       	//animacion de victoria
                       	 Beep(750,500);
                       	 Beep(350,500);
                       	
						string victoria = "Bomba desactivada";
                      	 	for(int i = 0; i <= victoria.length(); i++ ){
							Beep(800, 100);
							gotoxy(45+i,3);cout<<victoria[i];
							}


                       cout<<endl<<endl;

                        return 0; 

                        }

                        else //de no serlo, se le resta 1 min a la cuenta y se vuelve a colocar tab en 0

                        {

                                      system("cls");
		                       		gotoxy(50,3);cout <<mm<<":"<<ss<<" **"<<endl;
                                      Beep(600, 500);Beep(860,450);Beep(880,300);
                                      cout <<endl<<"Clave incorrecta"<<endl;
                                      cout <<"1 minuto menos"<<endl<<endl;
                                      Sleep(900);	
                                      mm=mm-1;
                                      clave="**";
                                      tab=0;
                                      Sleep(900);
                       }     
             }

           }
           ss=ss-1;
          Beep(300,350); //restamos los segundos y que suene un beep por cada seg que pase
          if(ss<0) // en caso de ser menor a cero se coloca seg en 59 y se disminuye mmm
	 	{
	 	mm=mm-1;
	 	ss=59;
		}    
         }
   system("cls");
   
        //si ya salio del while, es decir, mm es menor a cero, se acabo el tiempo, por lo que la bomba explota
        
Beep(300,1000);
 string derrota = "Has explotado"; //animacion de derrota
 	for(int i = 0; i <= derrota.length(); i++ ){
	Beep(800, 100);
	gotoxy(45+i,3);cout<<derrota[i];
}

cout<<endl<<endl<<endl;





}
