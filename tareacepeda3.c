#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<locale.h> 
#include<ctype.h> // Necesario para toupper


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


struct login{
	char user[90];
	int password;
	
	
};



void estudiantes();
void logo_usm();
void Maria_victoria();
void Robert_mora();
void Michelle_Montanes();
void calendario1();
void calendario2();
void calendario3();


int main(){
	
setlocale ( LC_ALL,"spanish" ); 


char us[] = "Usuario: ";
char con[] = "Contraseña: ";
int i;

struct login log;
	
Beep(100,90);gotoxy(8,2);printf("  _______ _______ _______      _______ _______ _______ _______ _______ _______ ______ _______ _______ ");   
Beep(100,90);gotoxy(8,3);printf(" |   |   |     __|   |   |    |     __|   _   |    |  |_     _|_     _|   _   |   __ \\_      _|       |  ");   
Beep(100,90);gotoxy(8,4);printf(" |   |   |__     |       |    |__     |       |       |_|   |_  |   | |       |       <_|   |_|   -   |");   
Beep(100,90);gotoxy(8,5);printf(" |_______|_______|__|_|__|    |_______|___|___|__|____|_______| |___| |___|___|___ |__|_______|_______|");  
  
  
for (i = 0; i < strlen(us); i++){
		Sleep(40);
		gotoxy(20+i,13);printf("%c",us[i]);
	}
	
for (i = 0; i < strlen(con); i++){
		Sleep(40);
		gotoxy(70+i,13);printf("%c",con[i]);
	}
    
                                                        


//gotoxy(70,13);printf("Contraseña:"); 

gotoxy(28,13);fgets(log.user, sizeof(log.user), stdin);



gotoxy(82,13);scanf("%d",&log.password);
	

/*
if(log.user != sizeof(char)){
	printf("tipo de dato no valido!");
	return 0;
}else if(log.password != sizeof(int)){
	printf("tipo de dato no valido!");
	return 0;
}
*/







do{
system("cls");


printf("Usuario: "); 
printf("%s",log.user);
int op = 0;
gotoxy(35,5);printf("|-----------------------------------------|\n");
gotoxy(35,6);printf("|---------------Sanitario USM-------------|\n");
gotoxy(35,7);printf("|-----------------------------------------|\n");
gotoxy(35,8);printf("|1) Estudiantes                           |\n");
gotoxy(35,9);printf("|2) USM                                   |\n");
gotoxy(35,10);printf("|3) Salir                                 |\n");
gotoxy(35,11);printf("|opcion:                                  |\n");
gotoxy(35,12);printf("|-----------------------------------------|");
gotoxy(43,11); scanf("%d",&op);



switch (op)
{
case 1:
	estudiantes();
    break;

case 2:

    logo_usm();
    break;


case 3: 

	return 0;

case sizeof(op) == sizeof(char):
		
		printf("\n\n");
		printf("digito invalido!");
		
			return 0;		



}

}while(1);

}





void logo_usm(){
system("cls");
int i;
char palabra[13] = "contactenos!";

Beep(0,1000); printf("La santa maria ofrece practicas gratis de odontologia para nuestros estudiantes \n");
Beep(0,900);printf("si quieres ser partes de esta practica,\n");
Beep(100,800);printf("Correo: usm@usm.edu.ve");



Beep(500,40);gotoxy(35,5); printf("xMMMMMMMMMMWWWWWWWMMMWWWWWWMMMMWWWWWWWWWWWWWWWMMMMMMMMMMMM");
Beep(500,40);gotoxy(35,6); printf("xMMMMMMMMNOocccccxXXxccccco0NN0occcccccccccccoONMMMMMMMMMM");
Beep(500,40);gotoxy(35,7); printf("xMMMMMMMNx,. .  'okl..   .ck0x,.             .'dXWMMMMMMMM");
Beep(500,40);gotoxy(35,8); printf("xMMMMMMXd,.....,oxc......lko:,.................,dXWMMMMMMM");
Beep(500,40);gotoxy(35,9); printf("xMMMMWKd;'''..;dxc,''..'lko,.....'ldxddddddddddxkKNMMMMMMM");
Beep(500,40);gotoxy(35,10); printf("xMMMW0l,''''';oo:,'''.;oko,.....,dOd;,,,,,,,,,,,',ckNMMMMM");
Beep(500,40);gotoxy(35,11); printf("xMMW0:........'......;dko;,'''.;dOo.. ... .........'xNMMMM");
Beep(500,40);gotoxy(35,12); printf("xMMMXo'.............:xxl;,,'.':xOl'.,;'...;:,......;kNMMMM");
Beep(500,40);gotoxy(35,13); printf("xMMMMN0xoooooooooooxkx:'....':kkl''lxo;.,oko;,''.'cONMMMMM");
Beep(500,40);gotoxy(35,14); printf("xMMMMMMNklcccccccccc:'.....cdkx:',oxl,.;dxl,'''.'l0NMMMMMM");
Beep(500,40);gotoxy(35,15); printf("xMMMMMMW0:................lxko,.,od:..;dd;.....,dKWMMMMMMM");
Beep(500,40);gotoxy(35,16); printf("cMMMMMMMMWKl'............,oOdc,.:xkc''ckx:.....;xXWMMMMMMMM");
Beep(500,40);gotoxy(35,17); printf("xMMMMMMMMMNKOOOOOOOOOOOO0XNXK00KNNKO0XNX0OOOOOKNMMMMMMMMMM");
Beep(500,40);gotoxy(35,18); printf("xMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");



Sleep(1700);

for(i = 0; i <= strlen(palabra);i++){

Beep(50,50);
gotoxy(39+i,1);  printf("%c",palabra[i]);

}


gotoxy(0,22);


system("pause");
 
 
}






void estudiantes(){
	system("cls");
	int i;
	int op;
	char opc[] = "opcion: ";
	printf("      ------------------------------------------Estudiantes--------------------------------------  \n\n\n");
	
	printf("1) Maria victoria\n");
	printf("2) Robert Mora\n");
	printf("3) Michelle Montañez\n");
	printf("4) volver\n");
	Sleep(700);
	
	for (i = 0; i < strlen(opc); i++){
		Beep(400,30);
		gotoxy(0+i,10);printf("%c",opc[i]);
	}
	scanf("%d",&op);
	
	
	switch (op){
		
		case 1:
			Maria_victoria();
			break;
		
		case 2: 
		Robert_mora();
		break;
		
		case 3: 
		Michelle_Montanes();
		break;
		
		
	}

}


void Maria_victoria(){
	system("cls");
		printf("      ------------------------------------------Maria Victoria--------------------------------------  \n\n\n");
	int op;
	printf("Estudiande de octavo semestre especializandose en Odontopediatría\n");
	printf("Busca la mejoria y la aprendizaje en la odontologia en base a al cuidado\n");
	printf("y crecimiento de los niños.\n\n\n\n");
	
	
	
	
	printf("desea pedir una cita con el estudiante?\n");
	printf("1 = si, 2 =  no\n");
	printf("Opcion:");scanf("%d",&op);
	
		switch (op){	
		case 1:
		calendario1();
		 break;
		 
		case 2:	
		estudiantes();
		break;
		
		default:
			main();
}

	

}






void Robert_mora(){
	system("cls");
		printf("      ------------------------------------------Robert Mora--------------------------------------  \n\n\n");
	int op;
	printf("Estudiante de sexto semestre especializandose en\n");
	printf("odontologia preventina. Interesado en la prevención de enfermedades bucodentales y\n");
	printf("la promoción de la salud oral a largo plazo.\n\n\n\n");
	
	
	
	
	printf("desea pedir una cita con el estudiante?\n");
	printf("1 = si, 2 =  no\n");
	printf("Opcion:");scanf("%d",&op);
	
		switch (op){	
		case 1:
		calendario2();
		 break;
		 
		case 2:	
		estudiantes();
		break;
		
		default:
			main();
}


}



void Michelle_Montanes(){
	system("cls");
		printf("      ------------------------------------------Michelle Montañez--------------------------------------  \n\n\n");
	int op;
	printf("Estudiante de cuarto semestre\n");
	printf("actualmente sin ninguna especializacion\n");
	printf("en proceso de aprendizaje y la aventura de nuevos retos que puedan surgir en el camino\n\n\n\n");
	
	
	
	
	printf("desea pedir una cita con el estudiante?\n");
	printf("1 = si, 2 =  no\n");
	printf("Opcion:");scanf("%d",&op);
	
		switch (op){	
		case 1:
		calendario3();
		 break;
		 
		case 2:	
		estudiantes();
		break;
		
		default:
			main();
}

}



void calendario3(){
		system("cls");
	int i;
	char op[10];
		printf("      ------------------------------------------Horarios--------------------------------------  \n\n\n");
	
	
	printf("Hora      |   Mar 	 |   Jue   | 		\n");
	printf("2:30PM    |	         |	   |   	     	 \n");
	printf("4:30PM    |aula:812      |aula:812 |	 \n ");
	printf("4:30PM   |aula:812	 |aula:812 |	 \n");
	printf("5:30PM    |aula:812	 |aula:812 |	 \n\n\n");

	select:
	printf("Seleccione un dia (martes, jueves)\n");
	scanf("%s",&op);
	
	  for ( i = 0; op[i]; i++) {
        op[i] = tolower(op[i]);
    }


    if (strcmp(op, "martes") != 0 && strcmp(op, "jueves") != 0) {
        printf("\n\n\n");
        printf("Día ingresado no válido, inténtelo de nuevo.\n");
	goto select;
}else {
	
	system("cls");
	gotoxy(45,1);printf("Tu cita fue creada!\n\n\n");
	
		  FILE *archivo = fopen("cita1.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Dia: %s\n", op);
    fputs("Hora de inicio: 4:30PM\n", archivo);
    fputs("Salon: 812\n", archivo);
    fputs("Estudiante: Michelle Montañez\n", archivo);
    fputs("Por favor, antes de subir, confirmar en recepción.\n", archivo);

    fclose(archivo);
    printf("Se creó un archivo de texto con referencia a tu cita.\n");
	
	
	
	
	
	
	Sleep(1000);
	gotoxy(0,10);system("pause");
	
	
}
	
	
	
	
	
}

void calendario2(){
	system("cls");
	int i;
	char op[10];
	printf("      ------------------------------------------Horarios--------------------------------------  \n\n\n");
	
	
	printf("Hora       |  Mar 	 |   Mie   | 		\n");
	printf("10:00AM    |	         |	   |   	     	 \n");
	printf("10:45AM    |aula:722     |aula:722 |	 \n ");
	printf("10:45AM   |aula:722	 |aula:722 |	 \n");
	printf("11:30AM    |aula:722	 |aula:722 |	 \n\n\n");

	select:
	printf("Seleccione un dia (martes, miercoles)\n");
	scanf("%s",&op);
	
	  for ( i = 0; op[i]; i++) {
        op[i] = tolower(op[i]);
    }


    if (strcmp(op, "martes") != 0 && strcmp(op, "miercoles") != 0) {
        printf("\n\n\n");
        printf("Día ingresado no válido, inténtelo de nuevo.\n");
	goto select;
}else {
	
	system("cls");
	gotoxy(45,1);printf("Tu cita fue creada!\n\n\n");
	
	
		  FILE *archivo = fopen("cita1.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Dia: %s\n", op);
    fputs("Hora de inicio: 10:45AM\n", archivo);
    fputs("Salon: 722\n", archivo);
    fputs("Estudiante: Robert Mora\n", archivo);
    fputs("Por favor, antes de subir, confirmar en recepción.\n", archivo);

    fclose(archivo);
    printf("Se creó un archivo de texto con referencia a tu cita.\n");
	
	
	
	
	
	
	Sleep(1000);
	gotoxy(0,10);system("pause");
	
	
}

	
	
	
}



void calendario1(){
	system("cls");
	int i;
	char op[10];
		printf("      ------------------------------------------Horarios--------------------------------------  \n\n\n");
	
	
	printf("Hora      |  Lun 	 |   Mie   | Vie		\n");
	printf("7:00AM    |	         |	   |   	     	 \n");
	printf("7:45AM    |aula:910      |aula:922 |aula:910	 \n ");
	printf("7:45AM   |aula:910	 |aula:922 |aula:910	 \n");
	printf("8:30AM    |aula:910	 |aula:922 |aula:910	 \n\n\n");

	select:
	printf("Seleccione un dia (lunes, miercoles, viernes)\n");
	scanf("%s",&op);
	
	  for ( i = 0; op[i]; i++) {
        op[i] = tolower(op[i]);
    }


    if (strcmp(op, "lunes") != 0 && strcmp(op, "miercoles") != 0 && strcmp(op, "viernes") != 0) {
        printf("\n\n\n");
        printf("Día ingresado no válido, inténtelo de nuevo.\n");
	goto select;
}else {
	
	system("cls");
	gotoxy(45,1);printf("Tu cita fue creada!\n\n\n");
	
	
	  FILE *archivo = fopen("cita1.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Dia: %s\n", op);
    fputs("Hora de inicio: 7:45AM\n", archivo);
    fputs("Salon: 910\n", archivo);
    fputs("Estudiante: Maria Victoria\n", archivo);
    fputs("Por favor, antes de subir, confirmar en recepción.\n", archivo);

    fclose(archivo);
    printf("Se creó un archivo de texto con referencia a tu cita.\n");
	
	
	
	
	
	Sleep(1000);
	gotoxy(0,10);system("pause");
	


   
}



	
}





















