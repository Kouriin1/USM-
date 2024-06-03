/* 
	Nombre: Sistema de Control Bombeo Plastilago Etileno
	Autores: Sebastian Baloa, Osler Solano, Roger Montero
	Fecha: 12-12-2023 17:32
	Descripcion: Elaborar un programa que permita determinar el flujo de etileno a traves de un sistema de bombeo con tres bombas y seis válvulas.
	
Historial de Revisiones:
Rev 0 : 03-12-23 
Rev 1 : 05-12-23 = Todos los esquemas de bombeo listos y funcionando correctamente
Rev 2: 06-12-23 = Interfaz actualizada sin parpadeo
Rev 2.1: 08-12-23 = Cambios menores y bug fix
Rev 2.2.: 09-12-2023 = Creacion automatica de archivo de texto, agregado opcion para salir del programa
Rev 2.3: 10-12-2023 = Creacion de interfaz para menu de inicio, creacion de directorio de archivos para el sistema
Rev 2.4: 10-12-2023 = Cambios a la logica del sistema, Se agrega un contador de Tiempo de ejecucion del sistema en todo momento, Bug fixes en el refresco de pantalla
Rev 2.5: 11-12-2023 = Correciones de errores menores, Implementacion de reporte automatico de errores en el sistema de rotacion
Rev 3.0: 12-12-2023 = Correciones Errores, Bugs fixes
*/


#include <iostream> // Mostrar datos en pantalla
#include <fstream> // Leer y escribir en un archivo de texto
#include <windows.h> // Control de ejecución (tiempo de refrescamiento de pantalla)
#include <locale.h> // Configurar el idioma de la consola en español
#include <conio.h> // Uso de kbhit y getch()
#include <iomanip> // libreria para mostrar el tiempo en el formato de minutos y segundos (mm:ss) y configurar la cantidad de decimales a mostrar

using namespace std;


// Funciones: 

// Función para convertir una palabra a mayúsculas
string convertirPalabraAMayusculas( string palabra ) {
    // Copiamos la palabra original para no modificar la entrada
    string palabraMayusculas = palabra;
    char c;
    // Iteramos a través de cada carácter en la palabraMayusculas
    for ( int x = 0; x < palabraMayusculas.length(); x++ ) { 
        c = palabraMayusculas[x];
        // Verificamos si el carácter es una letra minúscula (en ASCII)
        if ( c >= 'a' && c <= 'z' ) {
            // Convertimos la letra minúscula a mayúscula restando 32 al valor ASCII
            c = c - 32;
            palabraMayusculas[x] = c; // Cambiamos cada elemento del string 
        }
    }
    // Devolvemos la palabra convertida a mayúsculas
    return palabraMayusculas;
}

// Función que genera variables string de forma aleatoria
string random(int len)
{	
	//Se obtiene el valor del tiempo del sistema haciendo un llamado a la funcion 'GetSystemTime()' guardado en la variable "st" con estructura 'SYSTEMTIME'
	SYSTEMTIME st;
    GetSystemTime(&st);
    //Se genera una semilla para la funcion rand() basada en los valores del tiempo local de la maquina
    srand(st.wSecond + st.wMilliseconds);
	//Declaramos variable string "a" donde se almacenan 61 caracteres en formato de texto para añadirlo en la variable r
    string a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string r;//Se declara variable a modificar
    for(int i = 0; i < len; i++) r.push_back(a.at(size_t(rand() % 62))); // bucle "for" que le asigna un valor a "r" a traves de los valores eligidos aleatoriamente de "a"
    return r;
}

// Funcion para mover el cursor de la consola a una posicion especifica en la pantalla
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para limpiar los campos necesarios
void limpiarCampos() {
    // Lista de posiciones a limpiar:
    int posicionesX[] = {14, 14, 14, 44, 44, 44, 22, 20, 16, 25, 32, 23, 8, 8, 8, 33, 33, 33, 9, 9, 9, 70, 70, 70 , 28, 33, 21, 50}; // Arreglo con las posiciones en x
    int posicionesY[] = {5, 6, 7, 5, 6, 7, 9, 11, 12, 12, 13, 13, 17, 18, 19, 17, 18, 19, 23, 24, 25, 4, 7, 10, 29, 31, 27, 27}; // Arreglo con las posiciones en y

    // Iteramos sobre cada posición a limpiar
    for (int i = 0; i < sizeof(posicionesX) / sizeof(posicionesX[0]); ++i) {
        // Mover el cursor a la posición especificada
        gotoxy(posicionesX[i], posicionesY[i]);
        // Limpiar 9 espacios en cada posición menos en la (21,27), donde se limpiaran 8 espacios y la (50,27) que se limpiaran 3 espacios
        if ( posicionesX[i] == 21 ){
        	cout << "        ";
		}	else if ( posicionesX[i] == 50 ){
			cout << "   ";
		}
		else{
			cout << "         ";
		}
    }
}

// Función para mostrar el tiempo en el formato de minutos y segundos (mm:ss)
void mostrarTiempo(int tiempo) {
    // Calculamos la cantidad de minutos dividiendo el tiempo total por 60
    int minutos = tiempo / 60;
    // Calculamos la cantidad de segundos restantes después de obtener los minutos completos
    int segundos = tiempo % 60; // Nos quedamos con el residuo de la división
    // Imprime el tiempo en formato mm:ss en la consola
    // Asegura que tanto los minutos como los segundos se impriman con dos dígitos,
    // rellenando con ceros a la izquierda si es necesario
    cout << setfill('0') << setw(2) << minutos << ":" << setw(2) << segundos << "\n";
}

// Función para contar el tiempo de funcionamiento de cada bomba 
void contadorBomba(const string estadobomba, int& tiempo) {
    if (estadobomba == "ENCENDIDA") {
        // Verifica si el estado de la bomba es "ENCENDIDA"
        tiempo++; // Incrementa el tiempo si la bomba está encendida
    } else if (estadobomba == "APAGADA") {
        // Si el estado de la bomba es "APAGADA"
        tiempo = 0; // Reinicia el contador de tiempo a 0
    }
}

// Función para evaluar el estado de una bomba
void evaluarEstadoBomba(string switchEstado, int presion, bool& bombaOperativa) {
    // Si el switch está en normal, la presión está a menos de 51 psi y la bomba no está operativa
    if ((switchEstado == "ON" && presion <= 50) && !bombaOperativa) {
        bombaOperativa = true; // La bomba se vuelve operativa
    } 
    // Si el switch está en normal, la presión está a más de 50 psi, y la bomba está operativa
    else if ((switchEstado == "ON" && presion > 50) && bombaOperativa) {
        bombaOperativa = false; // La bomba se vuelve inoperativa
    } 
    // Si el switch está en alarma, la presión está a menos de 51 psi y la bomba está operativa
    else if ((switchEstado == "OFF" && presion <= 50) && bombaOperativa) {
        bombaOperativa = false; // La bomba se vuelve inoperativa
    } 
    // Si el switch está en alarma, la presión está a más de 50 psi, y la bomba está operativa
    else if ((switchEstado == "OFF" && presion > 50) && bombaOperativa) {
        bombaOperativa = false; // La bomba se vuelve inoperativa
    }
}

// --------------------------------------------------------------------------


// *** Declaración de variables

// Flujo total por segundo 
double flujo_por_segundo;

// Total de galones descargados por el sistema
double total_galones = 0.0; // Inicialización en cero

// Flujo total por minuto
int flujo_por_minuto; 

// ---------------------------------------------------------


int main()
{
    
    setlocale ( LC_ALL,"spanish" ); // Configuramos el idioma en español
    
    // *** Pantalla de incio del programa
	Beep(4400,350);
	menu: //Etiqueta para reiniciar el menu desde el comando goto en la linea 228
	cout <<"                  *#######+       .:-:    \n"; 	// pos(20,0) 
	cout <<"                  *#######=   -*#####=  \n"; // pos(20,1)
	cout <<"                 .*######*. +########= \n";	// pos(20,3)
	cout <<"                 :#######-:##########=\n"; // pos(20,4)
	cout <<"                 +#####*:=###########=  +######+    +#####=   =#+      .#*  +#+   .#* =######## -#######= :#######+\n"; // pos(20,5)
	cout <<"                -#####* +######*++=--:  +#=   +#+ :##:   :##. =#+      .#*  +##*  .#*    .#*    -#+       :#*    =#+\n"; // pos(19,6)
	cout <<"               -####*. =###+            +#=  .*#= +#-     +#+ =#+      .#*  +#=##..#*    .#*    -######*: :##:::=##-\n"; // pos(18,7)                    
	cout <<"             .*###:   -##=              +#####+   +#-     +#+ =#+      .#*  +#..*#-#*    .#*    -#+       :##:=##:\n"; // pos(16,8)
	cout <<"          :*#*:      .**.               +#=       :##-   :##. =#+      .#*  +#.  *##*    .#*    -#+       :#*   +#* \n"; // pos(12,9)
	cout <<" ::=++=-:.           -#:                +#=         =#####=   =#######:.#*  +#.   +#*    :#*    =#######* :#*    -#*. \n"; // pos(2,10)
	cout <<"                     *= \n"; // pos(26,10)
	cout <<"                     .*.                Poliolefinas Internacionales C.A.\n"; // pos(26,11)
	cout <<"                     -+                 [Plásticos del lago, C.A. (Plastilago), Polímeros del Lago C.A. (Polilago), Resinas Lineales S.A. (Resilin)] \n"; // pos(26,12)
	cout <<"                     =-\n"; // pos(26,13)                                        
    cout <<"----------------------------------------------------------------------------------------------------------------------------------------------------------";	
		//Variable para elegir opcion en el menu de incio
		char sc;
		
    gotoxy(40,17);
    cout <<"*** Sistema de Control Bombeo de Etileno a Plastilago [version 3.0] ***" <<endl;
    gotoxy(68,19);
    cout <<"MODOS DE OPERACIÓN" <<endl; 
    gotoxy(40,21);
	cout <<"MODO LOCAL = presione la tecla [L] " << "	MODO REMOTO = presione tecla [R]";
	gotoxy(40,23);
	cout <<"Eliga una opción:  ";
	sc=getche();
	
//*** Condiciones del menu de inicio

    while (sc=='L' or sc=='l') //Condicion para opcion de control en modo local
    {
     system("cls");
     cout << " **** MODO LOCAL - EL PROGRAMA NO CONTROLA LA BOMBA ***\n"; 
     if(kbhit()!=0)
     return 0;
	}
	
	if(sc=='R' or sc=='r') //Condicion para opcion de control en modo remoto
	{	
		system("cls");
		// Se declara una variable con la ruta en la que se creara el archivo con el tipo “Long Pointer to Const String" para guardar un puntero 'char' en la Windows API
		LPCSTR ruta = "C:\\Users\\Public\\Downloads\\Bombeo_Etileno_Plastilago";
		
		// Se imprime interfaz
		cout << "---------------------------------------------------------------------------\n";
		cout <<"| PARA OPERAR EL SISTEMA EN MODO REMOTO, SE REQUIERE DE UN ARCHIVO DE TEXTO |" <<endl;
		cout << "---------------------------------------------------------------------------\n";
		cout << "--> El sistema procederá a crear el archivo con el nombre = Controlador.txt" <<endl <<endl;
		
			//Se hace un llamado a la funcion 'CreateDirectory()' que permite crear un directorio de archivos en sistemas operativos Windows NT
			
			if(not CreateDirectory(ruta, NULL)) // Se verifica que la funcion esta operativa, de haber algun error el sistema lo detectaria y no crearia el directorio, avisaria al usuario del error
			{	
				 //Declaramos variable entero 'dir_error' que contiene la funcion 'GetLastError' del header file 'windows.h' que permite obtener el codigo de error en 'winerror.h'
				int dir_error = GetLastError();
				
				// Verificamos si el tipo de error que se guardo en 'dir_error' es error de 'YA EXISTE' flageado por 'windows.h' con el valor numerico entero = 183
        		if (dir_error == ERROR_ALREADY_EXISTS) 
				{
            	cout << "|!| = [El directorio ya existe] " <<endl <<endl;
        		} 
				else 
				{
					cout<<"--> [Error] al crear directorio, cerrando el programa.. \n";
					cout << "|!| Código de error: " <<dir_error;
					return 0;
				}
	}
	
			//Procedemos a crear un archivo de texto que contenga todo lo necesario para que el programa pueda ser utilizado   
  			ofstream controlador("C:\\Users\\Public\\Downloads\\Bombeo_Etileno_Plastilago\\Controlador.txt"); 
  
  			//Creacion del archivo de texto.
  			controlador<<"      ABIERTA      ABIERTA       ABIERTA       ABIERTA       ABIERTA       ABIERTA                30          "<<endl;
  			controlador<<"|                                          |                                        |                        |"<<endl;
  			controlador<<"|      V101          V102         V103     |    V201          V202          V203    |   Tiempo de rotación   |"<<endl;
  			controlador<<"|                  (Succión)               |               (Descarga)               |                        |"<<endl;
  			controlador<<"|                                          |                                        |                        |"<<endl;
  			controlador<<"|               (ABIERTA/CERRADA)          |           (ABIERTA/CERRADA)            |           (seg)        |"<<endl;
  			controlador<<"|                                          |                                        |                        |"<<endl;
  			controlador<<"|---------------------------------------> Válvulas <--------------------------------|---------> Bombas <-----|"<<endl<<endl;
  			controlador << "El valor del tiempo de rotación debe ser mayor a 1 segundo                                                           " << endl << endl;
  			controlador << "Nota: Este archivo de texto controla únicamente el estado de las válvulas y el tiempo de rotación de las bombas.     ";
  
  			controlador.close(); //Cerramos el archivo.
  			
			  // ! Nota: Se puede evaluar cualquier escenario como primer escenario antes de comenzar la ejecución, cambiando el archivo de texto mientras se muestra la pantalla de inicio
  
	Sleep(800);		
	cout <<"--> El archivo de texto se ha creado correctamente en el siguiente directorio =  " << ruta <<endl <<endl;
	system("pause");
	system("cls");
	}
	else
	{		
		cout <<endl << "[Error]  [" <<sc <<"]  no es una opción valida\n\n";
		system("pause");
		system("cls");
		goto menu;
	}


// *** Declaramos el resto de variables controladas por el sistema:

    // Transmisores de presión:
    int PT201 = 0; // Presión inicial de la línea 1 (cero)
	int PT202 = 0; // Presión inicial de la línea 2 (cero) 
	int PT203 = 0; // Presión inicial de la línea 3 (cero)

    // Estado de las bombas (ENCENDIDA/APAGADA)
    string P101 = "APAGADA"; // Estado de la bomba P101 (inicialmente APAGADA)
    string P102 = "APAGADA"; // Estado de la bomba P102 (inicialmente APAGADA)
    string P103 = "APAGADA"; // Estado de la bomba P103 (inicialmente APAGADA)
    string bombaAveriadaEstadoAnterior; // Variable para guardar el nombre de la bomba que se averíe
    // Estado de operatividad de las bombas (true = operativa; false = inoperativa):
    bool P101_Operativa = false; // Estado de la bomba P101 (inicialmente false)
    bool P102_Operativa = false; // Estado de la bomba P102 (inicialmente false)
    bool P103_Operativa = false; // Estado de la bomba P103 (inicialmente false)
    int bombas_Operativas; // Variable para contabilizar cuantas bombas se encuentran funcionando
    // Variables para contabilizar el tiempo de funcionamiento de cada bomba en segundos:
    int tiempo_funcionamiento_P101 = 0; // Tiempo de funcionamiento de la bomba P101 (Inicialización en cero)
    int tiempo_funcionamiento_P102 = 0; // Tiempo de funcionamiento de la bomba P102 (Inicialización en cero)
    int tiempo_funcionamiento_P103 = 0; // Tiempo de funcionamiento de la bomba P103 (Inicialización en cero)
    int bombasEncendidas = 0; // Variable para contabilizar cuantas bombas se encuentran encendidas 
        	
	// Sistema de rotación:
	bool activarRotacion; // Variable booleana para el sistema de rotación
    bool modoRotacionTresBombas; // Variable booleana para el sistema de rotación de tres bombas
    bool modoRotacionDosBombas; // Variable booleana para el sistema de rotación de dos bombas
	string modoRotacion; // Indicador de funcionamiento del sistema de rotacion
    string bomba_a_relevar; // Variable que almacena la bomba que tiene mas tiempo funcionando
    string bomba_a_activar; // Variable que almacena la bomba que se encuentra inactiva
	bool primeraVuelta = true; // Variable para chequear si es la primera vuelta
	bool Error_register =false; // Variable que verifica si existe algun error en el sistema de rotacion
    string Razon; // Variable que almacena la razon por la cual existe un error en el sistema de rotacion
		
	// Contador de funcionamiento del sistema:		
	int tiempo_ejecucion = 0; // Variable que almacena el tiempo que tiene el sistema ejecutandose

    // Estado de los switch de flujo (ON: Normal/OFF: Alarma)
    string FS201 = "ON"; // Estado del switch FS201 (inicialmente ON)
    string FS202 = "ON"; // Estado del switch FS202 (inicialmente ON)
    string FS203 = "ON"; // Estado del switch FS203 (inicialmente ON)

// *** Declaramos las variables controladas por el archivo de texto:

    // Válvulas de succión:
    string V101;    string V102;    string V103; 
    // Válvulas de descarga:
    string V201;    string V202;    string V203; 

    // Tiempo de rotación de las bombas:
    int duracion_ciclo_bombas; // Variable para almacenar el tiempo de rotación entre bombas en segundos
    // Este valor representa el tiempo de espera antes del apagado de una bomba y el encendido de la siguiente
    int tiempo_ciclo = 0; // Contador de tiempo de rotación 

// *** Declaramos variables para la interfaz de la consola

    // Modo del simulador (REMOTO/LOCAL):  
    string modo_simulador = "REMOTO"; // En modo REMOTO el sistema funciona sin problemas. El modo local indica un error de entrada en el archivo de texto 
    int aux; // Variable para imprimir la pantalla en el modo que corresponda

    string texto; // Variable para imprimir textos
    
    char op; //Creamos una variable char para la seleccion de opcion si el usuario quiere salir del programa

// --------------------------------------------------------------------------
	
	system("cls");
    
    // *** Imprimimos la plantilla de la interfaz del usuario
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "|                Sistema de Bombeo                   | Niveles de presión del sistema |" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "| Bombas:                | Contadores:               | Transmisor PT201:              |" << endl; 
    cout << "-----------------------------------------------------| Presión (psi):                 |" << endl;	
    cout << "| Bomba P101:            | Tiempo encendida:         |--------------------------------|" << endl; 	
    cout << "| Bomba P102:            | Tiempo encendida:         | Transmisor PT202:              |" << endl;	
    cout << "| Bomba P103:            | Tiempo encendida:         | Presión (psi):                 |" << endl;	
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "| Tiempo de rotación:                                | Transmisor PT203:              |" << endl;	
    cout << "-----------------------------------------------------| Presión (psi):                 |" << endl;	
    cout << "| Próxima rotación:                                  |--------------------------------|" << endl;
    cout << "| - Relevando:                                       | Tiempo de ejecución:            " << endl;	
    cout << "| - Será relevada por:                               |" << endl;	
    cout << "------------------------------------------------------" << endl;
    cout << "| Válvulas de succión:   | Válvulas de descarga:     |" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "| V101:                  | V201:                     |" << endl;		
    cout << "| V102:                  | V201:                     |" << endl;	
    cout << "| V103:                  | V201:                     |" << endl;	
    cout << "------------------------------------------------------" << endl;		
    cout << "| Switch's de flujo:                                 |" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "| FS201:                                             |" << endl;		
    cout << "| FS202:                                             |" << endl;		
    cout << "| FS203:                                             |" << endl;		
    cout << "------------------------------------------------------" << endl;
    cout << "| Conteo de gal/seg:         | Conteo de gal/min:    |" << endl;		
    cout << "------------------------------------------------------" << endl;		
    cout << "| Total Galones ingresados:                          |" << endl;		
    cout << "------------------------------------------------------" << endl;
	cout << "| Sistema de rotación / Status: [         ]          |" << endl;	
	cout << "------------------------------------------------------" << endl;
	cout<<"¿Desea Salir del Programa?" << endl;
	cout<<"Presione |S| ó |s|" << endl;
	
// --------------------------------------------------------------------------

	// *** Iniciamos el ciclo donde se va a ejecutar el sistema de bombeo
	
	char detener_sistema; // Variable para detener el ciclo del sistema 
	
    do
    {
    	// *** Lectura del archivo de texto
    	
        // Leemos los datos del archivo de texto 'Controlador' a través de la función 'pulse'
       	ifstream pulse ( "C:\\Users\\Public\\Downloads\\Bombeo_Etileno_Plastilago\\Controlador.txt");         			
		
        if ( pulse.fail() ) // Verificamos que el archivo se abra correctamente
        {

            // Mensaje a mostrar si no se puede abrir el archivo
            texto = "El archivo no pudo abrirse       ";
            int longitud = texto.length(); // Longitud del mensaje

            // Bucle para simular un texto en movimiento si el archivo no se abre
            for ( int z = 0; z < ( longitud + 8 ); z++ ) // El bucle simula el movimiento 8 veces más allá de la longitud original del texto
            {
                system("cls"); 
                cout << texto << endl; 

                // Simular movimiento eliminando el primer carácter y agregándolo al final
                texto = texto.substr( 1, longitud - 1 ) + texto[0]; // Agregamos el último carácter al principio del mensaje para simular movimiento

                Sleep(150); // Retraso de 100 milisegundos entre iteraciones para crear el efecto de desplazamiento
            }

            return 1; // retornamos un código de error

        }

        // Una vez que el archivo haya abierto correctamente procedemos a leer las variables 
        pulse >> V101 >> V102 >> V103 >> V201 >> V202 >> V203 >> duracion_ciclo_bombas;
		
        // Normalizamos los estados de las válvulas en un mismo formato (MAYUSCULAS):
        V101 = convertirPalabraAMayusculas( V101 ); V102 = convertirPalabraAMayusculas( V102 ); V103 = convertirPalabraAMayusculas( V103 );
        V201 = convertirPalabraAMayusculas( V201 ); V202 = convertirPalabraAMayusculas( V202 ); V203 = convertirPalabraAMayusculas( V203 );

        // Verficamos que los datos de las válvulas estén escritos correctamente:
        if ( V101 != "ABIERTA" && V101 != "CERRADA" ){
            modo_simulador = "LOCAL";
        }
        if ( V102 != "ABIERTA" && V102 != "CERRADA" ){
            modo_simulador = "LOCAL";
        }
        if ( V103 != "ABIERTA" && V103 != "CERRADA" ){
            modo_simulador = "LOCAL";
        }
        if ( V201 != "ABIERTA" && V201 != "CERRADA" ){
            modo_simulador = "LOCAL";
        }
        if ( V202 != "ABIERTA" && V202 != "CERRADA" ){
            modo_simulador = "LOCAL";
        }
        if ( V203 != "ABIERTA" && V203 != "CERRADA" ){
            modo_simulador = "LOCAL";
        }

        // Validamos el tiempo de rotación:  
        // Verificamos si la entrada es un numero mayor que cero
        
        if ( duracion_ciclo_bombas == 0 )
       	{
		   modo_simulador = "LOCAL";	
		}	

        // Verificamos el modo de operación del sistema
        if ( modo_simulador == "REMOTO" )
        {
            aux = 0;
        }
        else
        {
            aux = 1;
        }

        // HACEMOS TODOS LOS CÁLCULOS PARA EL MODO REMOTO AUTOMÁTICO
  
 		if ( aux == 0 )
 		{
  
 			// imprimimos los valores en pantalla para el modo Remoto

			// Limpiamos los campos a actualizar:
			limpiarCampos(); // Llamamos a la función creada anteriormente para limpiar unicamente los campos a actualizar evitando el parpadeo de la pantalla
			// *** Imprimimos la data de las bombas:
			// - Estados:
			gotoxy(14,5);
			// Bomba P101:
			cout << P101; 
			gotoxy(14,6);
			// Bomba P102:
			cout << P102; 
			gotoxy(14,7);
			// Bomba P103:
			cout << P103; 
    		// - Tiempo de funcionamiento:
			// Bomba P101:
			gotoxy(45,5);
			mostrarTiempo(tiempo_funcionamiento_P101);
			// Bomba P102:
			gotoxy(45,6);
			mostrarTiempo(tiempo_funcionamiento_P102);
			// Bomba P103:
			gotoxy(45,7);
			mostrarTiempo(tiempo_funcionamiento_P103);		
			// *** Imprimimos el esquema de rotación:
			gotoxy(22,9);
			cout << duracion_ciclo_bombas; // Tiempo de rotación asignado actualmente
			// Primero validamos si el esquema de rotacion esta activo
			if ( activarRotacion )
			{
				gotoxy(20,11);
				// Imprimimos la cuenta para la siguiente rotacion
				mostrarTiempo(tiempo_ciclo);  
				gotoxy(16,12);
				// Imprimimos la bomba que sera relevada
			    cout << "Bomba: " << bomba_a_relevar; 
			    gotoxy(23,13);	
			    // Imprimimos la bomba relevo
			    cout << "Bomba: " << bomba_a_activar; 
			    modoRotacion = "Encendido";
			} else{
				modoRotacion = " Apagado";
			}
			// *** Imprimimos el estado de las válvulas:
			// - Válvulas de succión:
			gotoxy(8,17);
			// Válvula V101:
			cout << V101; 
			gotoxy(8,18);
			// Válvula V102:
			cout << V102; 
			gotoxy(8,19);
			// Válvula V103:
			cout << V103; 
			// - Válvulas de descarga:
			gotoxy(33,17);
			// Válvula V201:
			cout << V201; 
			gotoxy(33,18); 
			// Válvula V202:
			cout << V202; 
			gotoxy(33,19);
			// Válvula V203:
			cout << V203; 
			// *** Imprimimos el estado de los switch's de flujo:
			gotoxy(9,23);
			// Switch FS201:
			cout << FS201; 
			gotoxy(9,24);
			// Switch FS202:
			cout << FS202; 
			gotoxy(9,25);
			// Switch FS203:
			cout << FS203; 
			// *** Imprimimos los niveles de presión del sistema
			gotoxy(70,4);
			// Presion de la linea 1:
			cout << PT201; 
			gotoxy(70,7);
			// Presion de la linea 2:
			cout << PT202; 
			gotoxy(70,10);
			// Presion de la linea 3:
			cout << PT203;
			// *** Imprimimos el contador de gal/seg y gal/min:
			gotoxy(21,27);
			// Flujo por segundo:
			cout << setprecision(5) << flujo_por_segundo; // Imprimimos 5 decimales
			gotoxy(50,27);
			// Flujo por minuto:
			cout << flujo_por_minuto <<" ";
			// *** Imprimimos el contador de galones totales ingresados: 
			gotoxy(28,29);
			cout << total_galones;
			// *** Imprimimos el indicador del sistema de rotacion:
			gotoxy(33,31);
			cout << modoRotacion;
			// *** Imprimimos el tiempo que lleva el programa ejecutandose
			gotoxy(76,12);
			mostrarTiempo(tiempo_ejecucion);	
			tiempo_ejecucion++;
			gotoxy(10,34);	
				
            Sleep(1000);
            
			// --------------------------------------------------------------
			
			
			
			// *** Esquema de los switches de flujo:
			
			// Simulamos el switch de flujo FS201:
			if ( V101 == "ABIERTA" && FS201 == "OFF" )
			{
				FS201 = "ON";
			}
			
			if ( V101 == "CERRADA" && FS201 == "ON" )
			{
				FS201 = "OFF";
			} 
			
			
			// Simulamos el switch de flujo FS202:
			if ( V102 == "ABIERTA" && FS202 == "OFF" )
			{
				FS202 = "ON";
			}
			
			if ( V102 == "CERRADA" && FS202 == "ON" )
			{
				FS202 = "OFF";
			}
			
			
			// Simulamos el switch de flujo FS203:
			if ( V103 == "ABIERTA" && FS203 == "OFF" )
			{
				FS203 = "ON";
			}
			
			if ( V103 == "CERRADA" && FS203 == "ON" )
			{
				FS203 = "OFF";
			} 
			
			
			
			// *** Esquema de las bombas:
			 
			// Simulamos el encendido y apagado de la bomba P101:
			if ( ( PT201 < 20 && FS201 == "ON" && P101 == "APAGADA" ) && !activarRotacion ) // Nos aseguramos de que activarRotacion sea falso (! significa negación)
			{
    			// la verificación del modo de rotación en este contexto es crucial para determinar si el encendido de la bomba (P101) está controlado por el sistema de rotación
    			// o por el esquema individual de las bombas.
				P101 = "ENCENDIDA";
			}
			if ( PT201 < 20 && FS201 == "OFF" && P101 == "ENCENDIDA" )
			{
				P101 = "APAGADA";
				Razon = " |!| Switch de Flujo FS201 en Alarma = [Revisar estado de Valvula V101 en linea de Bombeo #1]";
				Error_register =true; 
			}
			
			if ( PT201 >= 20 && PT201 <= 50 )
			{
				if( FS201 == "OFF" && P101 == "ENCENDIDA" )
				{
					P101 = "APAGADA";
					Razon = "|!| Switch de Flujo FS201 en Alarma = [Revisar estado de Valvula V101 en linea de Bombeo #1]";
					Error_register =true;
				}
			}
			
			if ( PT201 > 50 && FS201 == "ON" && P101 == "ENCENDIDA" )
			{
				P101 = "APAGADA";
				Razon = " |!| Presión mayor a 50 (psi) = [Revisar estado de Valvula V201 en linea de Bombeo #1]";
				Error_register =true;
			}
			
			if ( PT201 > 50 && FS201 == "OFF" && P101 == "ENCENDIDA" )
			{
				P101 = "APAGADA";
				Razon = " |!| FS201 en Alarma :: Presión > 50 (psi) = [Revisar estado de Valvulas V101 y V201 en linea de Bombeo #1]";
				Error_register =true;
			} 
			
			
			
			// Simulamos el encendido y apagado de la bomba P102:
			if ( ( PT202 < 20 && FS202 == "ON" && P102 == "APAGADA" ) && !activarRotacion ) // Nos aseguramos de que activarRotacion sea falso (! significa negación)
			{
				// la verificación del modo de rotación en este contexto es crucial para determinar si el encendido de la bomba (P102) está controlado por el sistema de rotación 
				// o por el esquema individual de las bombas.
				P102 = "ENCENDIDA";
			}
			if ( PT202 < 20 && FS202 == "OFF" && P102 == "ENCENDIDA" )
			{
				P102 = "APAGADA";
				Razon = " |!| Switch de Flujo FS202 en Alarma = [Revisar estado de Valvula V102 en linea de Bombeo #2]";
				Error_register =true; 
			}
			
			if ( PT202 >= 20 && PT202 <= 50 )
			{
				if( FS202 == "OFF" && P102 == "ENCENDIDA" )
				{
					P102 = "APAGADA";
					Razon = " |!| Switch de Flujo FS202 en Alarma = [Revisar estado de Valvula V102 en linea de Bombeo #2]"; 
					Error_register =true;
				}
			}
			
			if ( PT202 > 50 && FS202 == "ON" && P102 == "ENCENDIDA" )
			{
				P102 = "APAGADA";
				Razon = " |!| Presión mayor a 50 (psi) = [Revisar estado de Valvula V202 en linea de Bombeo #2]";
				Error_register =true;
			}
			
			if ( PT202 > 50 && FS202 == "OFF" && P102 == "ENCENDIDA" )
			{
				P102 = "APAGADA";
				Razon = " |!| FS202 en Alarma :: Presión > 50 (psi) = [Revisar estado de Valvulas V102 y V202 en linea de Bombeo #2]";
				Error_register =true;
			}
			
			
			
			// Simulamos el encendido y apagado de la bomba P103:
			if ( ( PT203 < 20 && FS203 == "ON" && P103 == "APAGADA" ) && !activarRotacion ) // Nos aseguramos de que activarRotacion sea falso (! significa negación)
			{
				// la verificación del modo de rotación en este contexto es crucial para determinar si el encendido de la bomba (P103) está controlado por el sistema de rotación 
				// o por el esquema individual de las bombas.
				P103 = "ENCENDIDA";
			}
			if ( PT203 < 20 && FS203 == "OFF" && P103 == "ENCENDIDA" )
			{
				P103 = "APAGADA";
				Razon = " |!| Switch de Flujo FS203 en Alarma = [Revisar estado de Valvula V103 en linea de Bombeo #3]";;
				Error_register =true;
				
			}
			
			if ( PT203 >= 20 && PT203 <= 50 )
			{
				if( FS203 == "OFF" && P103 == "ENCENDIDA" )
				{
					P103 = "APAGADA";
					Razon = " |!| Switch de Flujo FS203 en Alarma = [Revisar estado de Valvula V103 en linea de Bombeo #3]";
					Error_register =true;
				}
			}
				
			if ( PT203 > 50 && FS203 == "ON" && P103 == "ENCENDIDA" )
			{
				P103 = "APAGADA";
				Razon = " |!| Presión mayor a 50 (psi) = [Revisar estado de Valvula V203 en linea de Bombeo #3]";
				Error_register =true;
				
			}
			
			if ( PT203 > 50 && FS203 == "OFF" && P103 == "ENCENDIDA" )
			{
				P103 = "APAGADA";
				Razon = " |!| FS203 en Alarma :: Presión > 50 (psi) = [Revisar estado de Valvulas V103 y V203 en linea de Bombeo #2]";
				Error_register =true;
			}
		
		
		
			// *** Lógica para la rotación de las bombas
			
			// Guardamos el estado anterior de la bomba averiada que se acaba de arreglar:
			if ( !P101_Operativa && P102_Operativa && P103_Operativa )
			{
				bombaAveriadaEstadoAnterior = "P101";
			}
			else if ( P101_Operativa && !P102_Operativa && P103_Operativa )
			{
				bombaAveriadaEstadoAnterior = "P102";
			}
			else if ( P101_Operativa && P102_Operativa && !P103_Operativa )
			{
				bombaAveriadaEstadoAnterior = "P103";
			}
			
			// Evaluamos el estado de cada bomba (Operativa/Inoperativa) llamando a la función evaluarEstadoBomba
			evaluarEstadoBomba( FS201, PT201, P101_Operativa );
			evaluarEstadoBomba( FS202, PT202, P102_Operativa );
			evaluarEstadoBomba( FS203, PT203, P103_Operativa );
			
			// Iniciamos en cero nestra variable contador de bombas operativas bombas_Operativas
			bombas_Operativas = 0;
			
			// Verificamos el estado de cada bomba y contamos las que están operativas
			if ( P101_Operativa ) 
			{
			    bombas_Operativas++;
			}
			
			if ( P102_Operativa ) 
			{
			    bombas_Operativas++;
			}
			
			if ( P103_Operativa ) 
			{
			    bombas_Operativas++;
			}
			// Ahora la variable bombas_Operativas contiene el número de bombas operativas
			
			// Evaluamos cuantas bombas estan operativas
			if ( bombas_Operativas == 3 ) // Si tenemos tres bombas operativas
			{
				
				if ( primeraVuelta ) // Chequeamos la primera vuelta
				{
					// Verifico si se encendieron las tres bombas
					if ( P101 == "ENCENDIDA" && P102 == "ENCENDIDA" && P103 == "ENCENDIDA" ) 
					{
						P103 = "APAGADA"; // Apago la bomba P103
					}
					
				}
				
				activarRotacion = true; // Activamos el sistema de rotación
				modoRotacionTresBombas = true; // Fijamos el modo de rotación
				
				// Esperamos a que el modo de rotación de dos bombas se desactive si está activo
				if ( !modoRotacionDosBombas )				 
				{
					// Verificamos cual es la bomba que tiene más tiempo funcionando
					if ( tiempo_funcionamiento_P101 >= tiempo_funcionamiento_P102 && tiempo_funcionamiento_P101 >= tiempo_funcionamiento_P103 )
					{
						// Asignamos la bomba a relevar
						bomba_a_relevar = "P101";
						// Verificamos cual es la bomba que esta apagada
						if ( P102 == "APAGADA" )
						{
							bomba_a_activar = "P102"; // Asignamos la bomba a activar
						}
						else
						{
							bomba_a_activar = "P103"; // Asignamos la bomba a activar
						}
						
					}
					else if ( tiempo_funcionamiento_P102 >= tiempo_funcionamiento_P101 && tiempo_funcionamiento_P102 >= tiempo_funcionamiento_P103 )
					{
						// Asignamos la bomba a relevar
						bomba_a_relevar = "P102";
						// Verificamos cual es la bomba que esta apagada
						if ( P101 == "APAGADA" )
						{
							bomba_a_activar = "P101"; // Asignamos la bomba a activar
						}
						else
						{
							bomba_a_activar = "P103"; // Asignamos la bomba a activar
						}
						
					}
					else 
					{
						// Asignamos la bomba a relevar
						bomba_a_relevar = "P103";
						// Verificamos cual es la bomba que esta apagada
						if ( P101 == "APAGADA" )
						{
							bomba_a_activar = "P101"; // Asignamos la bomba a activar
						}
						else
						{
							bomba_a_activar = "P102"; // Asignamos la bomba a activar
						}
						
					}
					
				}
				
				// Verificamos si estamos finalizando el último ciclo del otro sistema de rotación, si lo hay
				if (modoRotacionDosBombas && tiempo_ciclo == 1) 
				{
				    // Verifica si hubo una avería y si se ha solucionado
				    if (bombaAveriadaEstadoAnterior == "P101") 
					{
				        P101 = "ENCENDIDA"; // Si la bomba P101 estaba averiada, se enciende
				    } 
					else if (bombaAveriadaEstadoAnterior == "P102") 
					{
				        P102 = "ENCENDIDA"; // Si la bomba P102 estaba averiada, se enciende
				    } 
					else 
					{
				        P103 = "ENCENDIDA"; // Si no fue ninguna de las bombas anteriores, se enciende la P103
				    }
				    
				}
					
			} 
			else if ( bombas_Operativas == 2 )
			{
				
				if ( primeraVuelta ) // Chequeamos la primeta vuelta
				{
					// Verifico si se encendieron las dos bombas	
					if ( P101 == "ENCENDIDA" && P102 == "ENCENDIDA" )
					{
						P102 = "APAGADA";
					}
					else if ( P101 == "ENCENDIDA" && P103 == "ENCENDIDA" )
					{
						P103 = "APAGADA";
					}
					else
					{
						P103 = "APAGADA";
					}
					
				}
				
				activarRotacion = true; // Activamos el sistema de rotación
				modoRotacionDosBombas = true; 
				
				// Esperamos a que el modo de rotación de tres bombas se desactive si esta activo
				if ( !modoRotacionTresBombas ) 
				{
					
					// Verifica el estado operativo de las bombas P101, P102 y P103 y toma decisiones en función de ello
					if (P101_Operativa && P102_Operativa) 
					{ 
						// Si P101 y P102 están operativas
					    if (P101 == "ENCENDIDA") 
						{ 	// Si P101 está encendida
					        bomba_a_activar = "P102"; // Activar P102
					        bomba_a_relevar = "P101"; // Desactivar P101
					    } else 
						{
					        bomba_a_activar = "P101"; // Activar P101
					        bomba_a_relevar = "P102"; // Desactivar P102
					    }
					} 
					else if (P101_Operativa && P103_Operativa) 
					{ 	
						// Si P101 y P103 están operativas
					    if (P101 == "ENCENDIDA") 
						{ 
							// Si P101 está encendida
					        bomba_a_activar = "P103"; // Activar P103
					        bomba_a_relevar = "P101"; // Desactivar P101
					    } else 
						{
					        bomba_a_activar = "P101"; // Activar P101
					        bomba_a_relevar = "P103"; // Desactivar P103
					    }
					} 
					else 
					{ 	// Si no se cumple ninguna de las condiciones anteriores (P102 y P103 están operativas)
					    if (P102 == "ENCENDIDA") 
						{ 	// Si P102 está encendida
					        bomba_a_activar = "P103"; // Activar P103
					        bomba_a_relevar = "P102"; // Desactivar P102
					    } else 
						{
					        bomba_a_activar = "P102"; // Activar P102
					        bomba_a_relevar = "P103"; // Desactivar P103
					    }
					}
				}
									
			}
			else
			{
				activarRotacion = false; // Si hay menos de dos bombas operativas desactivamos la rotación
			}
			
			
			if (activarRotacion) 
			{ 	
				// Verificamos si la rotación esta activa
			    if (tiempo_ciclo == 0 && primeraVuelta) 
				{ 	// Si es el inicio del ciclo y la primera vuelta
			        tiempo_ciclo = duracion_ciclo_bombas - 1; // Ajustamos el tiempo del ciclo para sincronizar con el funcionamiento de las bombas en la primera vuelta
			    } 
				else if (tiempo_ciclo == 0) 
				{ 	// Si es el inicio de un ciclo regular
			        tiempo_ciclo = duracion_ciclo_bombas; // Establecemos el tiempo del ciclo a la duración especificada
			    } 
				else 
				{ 	// Si no es el inicio del ciclo, se reduce el tiempo del ciclo en uno
			        tiempo_ciclo--;
			    }
			    
			    if (tiempo_ciclo == 0) 
				{ 	// Cuando el tiempo del ciclo llega a cero
			        // Encendemos la bomba que está inactiva (bomba_a_activar)
			        if (bomba_a_activar == "P101") 
					{
			            P101 = "ENCENDIDA";
			        } 
					else if (bomba_a_activar == "P102") 
					{
			            P102 = "ENCENDIDA";
			        } 
					else 
					{
			            P103 = "ENCENDIDA";
			        }
			        
			        // Apagamos la bomba que ha estado funcionando más tiempo (bomba_a_relevar)
			        if (bomba_a_relevar == "P101") 
					{
			            P101 = "APAGADA";
			        } 
					else if (bomba_a_relevar == "P102") 
					{
			            P102 = "APAGADA";
			        } 
					else 
					{
			            P103 = "APAGADA";
			        }
			        
			        // Reinicia el tiempo del ciclo y desactiva los modos de rotación
			        tiempo_ciclo = duracion_ciclo_bombas;
			        modoRotacionTresBombas = false;
			        modoRotacionDosBombas = false;
			        
			    }
			    
			}

			// Contadores de funcionamiento:
			contadorBomba( P101, tiempo_funcionamiento_P101 );
			contadorBomba( P102, tiempo_funcionamiento_P102 );
			contadorBomba( P103, tiempo_funcionamiento_P103 );
			
			primeraVuelta = false; // Marcamos la primera vuelta
			
			
			
			// *** Esquema de la presión:
   			
   			// Simulamos la presión de la linea Nro 1:
   			if ( V101 == "ABIERTA" && V201 == "ABIERTA" && P101 == "ENCENDIDA" && PT201 < 33 )
   			{
   				PT201 = PT201 + 1;
			}
			else if ( V101 == "ABIERTA" && V201 == "ABIERTA" && P101 == "ENCENDIDA" && PT201 > 33 )
   			{
   				PT201 = PT201 - 1;
			}
			
			if ( V101 == "ABIERTA" && V201 == "ABIERTA" && P101 == "APAGADA" )
   			{
   				PT201 = PT201 - 1;
			}
			
			if ( V101 == "ABIERTA" && V201 == "CERRADA" && P101 == "ENCENDIDA" )
   			{
   				PT201 = PT201 + 1;
			}
			
			if ( V101 == "CERRADA" && V201 == "ABIERTA" && P101 == "APAGADA" )
   			{
   				PT201 = PT201 - 1;
			}			
			
			
			// Simulamos la presión de la linea Nro 2:
   			if ( V102 == "ABIERTA" && V202 == "ABIERTA" && P102 == "ENCENDIDA" && PT202 < 33 )
   			{
   				PT202 = PT202 + 1;
			}
			else if ( V102 == "ABIERTA" && V202 == "ABIERTA" && P102 == "ENCENDIDA" && PT202 > 33 )
   			{
   				PT202 = PT202 - 1;
			}
			
			if ( V102 == "ABIERTA" && V202 == "ABIERTA" && P102 == "APAGADA" )
   			{
   				PT202 = PT202 - 1;
			}
			
			if ( V102 == "ABIERTA" && V202 == "CERRADA" && P102 == "ENCENDIDA" )
   			{
   				PT202 = PT202 + 1;
			}
			
			if ( V102 == "CERRADA" && V202 == "ABIERTA" && P102 == "APAGADA" )
   			{
   				PT202 = PT202 - 1;
			}			
			
			
			// Simulamos la presión de la linea Nro 3:
   			if ( V103 == "ABIERTA" && V203 == "ABIERTA" && P103 == "ENCENDIDA" && PT203 < 33 )
   			{
   				PT203 = PT203 + 1;
			}
			else if ( V103 == "ABIERTA" && V203 == "ABIERTA" && P103 == "ENCENDIDA" && PT203 > 33 )
   			{
   				PT203 = PT203 - 1;
			}
			
			if ( V103 == "ABIERTA" && V203 == "ABIERTA" && P103 == "APAGADA" )
   			{
   				PT203 = PT203 - 1;
			}
			
			if ( V103 == "ABIERTA" && V203 == "CERRADA" && P103 == "ENCENDIDA" )
   			{
   				PT203 = PT203 + 1;
			}
			
			if ( V103 == "CERRADA" && V203 == "ABIERTA" && P103 == "APAGADA" )
   			{
   				PT203 = PT203 - 1;
			}			
			
			
			// Evitamos que la presion sea negativa:
			if ( PT201 < 0 )
			{
				PT201 = 0;
			}
			
			if ( PT202 < 0 )
			{
				PT202 = 0;
			}
			
			if ( PT203 < 0 )
			{
				PT203 = 0;
			}
			
			
			
			// *** Cálculo del flujo de etileno y total de galones bombeados:
						
			// Verificamos cuántas bombas estan encendidas:
			// Iniciamos en cero nuestra variable contador de bombas encendidas bombasEncendidas
			bombasEncendidas = 0;
			
			// Verificamos el estado de cada bomba y contamos las que están encendidas
			if ( P101 == "ENCENDIDA" ) 
			{
			    bombasEncendidas++;
			}
			
			if ( P102 == "ENCENDIDA" ) 
			{
			    bombasEncendidas++;
			}
			
			if ( P103 == "ENCENDIDA" ) 
			{
			    bombasEncendidas++;
			}
			
			// Ahora la variable bombasEncendidas contiene el número de bombas encendidas
			
			flujo_por_segundo = ( 40.0 / 60.0 ) * bombasEncendidas;	
			// Calcula el flujo por segundo dividiendo el flujo por minuto (40) entre los 60 segundos
			// por minuto. Multiplica este valor por la cantidad de bombas encendidas para obtener
			// el flujo total de etileno por segundo.
			
			flujo_por_minuto = 40 * bombasEncendidas;
			// Calcula el flujo por minuto multiplicando el flujo por minuto (40) por la cantidad
			// de bombas encendidas. Esto proporciona el flujo total de etileno por minuto.
			
			total_galones = total_galones + flujo_por_segundo;
			// Actualiza el total de galones sumando el flujo por segundo al total de galones.
			// Esto representa la cantidad total de galones que se han bombeado hasta el momento.
			// Se incrementa con el flujo por segundo en cada iteración o intervalo de tiempo.
			
//------------------------------------------------------------------------	
	
	// *** Reporte de errores para el sistema de rotacion de bombas
			
		string detc_error = "|!| Se detectó un error en el sistema de rotación  "; //Se crea esta variable para una simple animacion de borre
			
		if(Error_register == true) //Condicion en la que existe un error en el sistema de rotacion de bombas
		{
				// Se obtiene el tiempo local de la maquina con la funcion 'GetLocalTime(&lct)' del header file 'windows.h' se guarda en la varianle "lct" de tipo estructura 'SYSTEMTIME'
				SYSTEMTIME lct;	GetLocalTime(&lct); 
				
				// Se crea un array tipo entero en el que se guardan los datos de la fecha y hora del dispositivo en Windows NT
				int lc_tiempo[]= {lct.wDay, lct.wMonth ,lct.wYear , lct.wHour, lct.wMinute, lct.wSecond}; 
				
				string n =random(5); // Variable que guarda 5 (cinco) valores aleatorios obtenidos de la funcion random()
				string ext =".txt"; // Declaramos tipo de extension del archivo a crear
				string file ="Reporte de Error #" +n +ext ; // Variable que guarda el nombre del archivo a crear
				
				// Se define la ruta de acceso al directorio indicado en la variable 'dir_report'
				LPCSTR dir_report ="C:\\Users\\Public\\Downloads\\Bombeo_Etileno_Plastilago\\Reportes de Error (sistema de rotacion)\\";  
				
				if (not CreateDirectory(dir_report, NULL)); // Se verifica que la funcion esta operativa, de haber algun error el sistema lo detectaria y no crearia el directorio
				
				string chstring = dir_report + file; //Se declara variable 'chstring' que contiene el valor de la ruta de acceso y el nombre del archivo a crear en una sola variable tipo std::string
				
				// Se hace una conversion de la variable tipo string a un puntero de tipo 'const char' para asegurar compatibilidad con dialectos desde c++ 1998 y superior 
				const char* csfile = chstring.c_str(); 

				ofstream reporte(csfile); // Se crea el archivo de texto con la ruta indicada por 'csfile'
				
				// Se escribe la informacion que va a contener el archivo de texto 
				reporte << "----- Reporte de Error del Sistema de Rotación -----\n\n\n";
				reporte << "Fecha y Hora: " <<lc_tiempo[0] <<"-" <<lc_tiempo[1] <<"-" << lc_tiempo[2] <<" a las " <<lc_tiempo[3] <<":" <<lc_tiempo[4] <<endl <<endl <<endl;
				reporte << "(Descripción del Error)" <<endl <<endl <<endl;
				reporte << 	 Razon <<endl <<endl <<endl;
				reporte << "----- Este reporte es generado automaticamente por el sistema, por favor contactarse con el supervisor de planta -----" <<endl;
				reporte.close(); // Cerramos el archivo de texto
				
				//Se imprime en pantalla la deteccion del error
				gotoxy(65,30);
				cout << "|!| Se detectó un error en el sistema de rotación ";
				gotoxy(55,33);
				cout << "           [Reporte de error generado en]           ";
				gotoxy(50,34);
				cout << "                   |                   |                 ";
				gotoxy(50,35);
				cout << "                   v                   v                 ";
				gotoxy(32,36);
				cout <<"C:\\Users\\Public\\Downloads\\Bombeo_Etileno_Plastilago\\Reportes de Error (sistema de rotacion)";
				Beep(500,250);
				Sleep(2000);
				
				
				// Animación para borrar solamente la primera linea
				for(int i = 49; i <= detc_error.length() ; i--){
					gotoxy(65+i,30);
					Beep(100,20);cout<<" ";
					
				}
				//Borro pantalla de error
				gotoxy(55,33);
				cout << "                                              ";
				gotoxy(50,34);
				cout << "                                                          			";
				gotoxy(50,35);
				cout << "                                                          			";
				gotoxy(32,36);
				cout<<"                                                                                           ";
				gotoxy(10,34);
				
				Error_register = false; //Se reinicia la condicion de error en el sistema de rotacion	
			
		}
			
			
			// *** Salir del sistema: 
			gotoxy(13,34);
			if ( kbhit() != 0 ) // Aplicamos tecnica kbhit para que el usuario presione una tecla y salga del programa.
			{
						
				op = getche();
					
				if ( op == 's' or op =='S' ) // Si cumple la condicion, rompe el ciclo y cierra el programa.
				{
					break;
				}
				
			}
			
   			// --------------------------------------------------------------

    	}

        // PRESENTAMOS LOS DATOS DEL MODO LOCAL
        if ( aux == 1 ) 
        {
        
        	// imprimimos los valores en pantalla para el modo Local

        	system("cls");
       		cout << " **** MODO LOCAL **** "; 
        	cout << "LOS DATOS ESCRITOS EN EL ARCHIVO .TXT ESTAN INCORRECTOS *****";
        
        }   

    } while ( detener_sistema != 's' ); // Ciclo para que el programa funcione el tiempo que sea requerido por el usuario
// rev 2.5
}
