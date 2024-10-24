import time
import os
import random
import threading
import ctypes
import ctypes.wintypes
import sys


# Constan
MAR = " "
N = 10  # rows
M = 10  # Columns
TIEMPO_LIMITE = 10  

# Symbol
AGUA = "X"
TOCADO = "*"
BARCO = "B"

# Aviables botas and their size
barcos_disponibles = {
    "Portaaviones": 4,
    "Submarino": 3,
    "Acorazado": 3,
    "Destructor": 2,
    "Fragata": 1,
}



LETRAS_BARCOS = {
    "Portaaviones": "P",
    "Submarino": "S",
    "Acorazado": "A",
    "Destructor": "D",
    "Fragata": "F"
}




def crear_matriz():
    """Create a matrix NxM with empty spaces"""
    return [[MAR] * M for _ in range(N)]

def imprimir_matriz(matriz):
    """print the complete matrix (including the boats)."""
    print("\nEstado completo de tu tablero:")
    imprimir_tablero(matriz)

def imprimir_matriz_oculta(matriz):
    """print the oponet matriz with hidden boats."""
    print("\nTablero del oponente (barcos ocultos):")
    matriz_oculta = [
        [celda if celda in [AGUA, TOCADO] else MAR for celda in fila]
        for fila in matriz
    ]
    imprimir_tablero(matriz_oculta)

def imprimir_tablero(matriz):
    borde = "+----" * M + "+"
    encabezado = "    " + "    ".join(f"{i + 1}" for i in range(M))
    print(encabezado)
    print("  " + borde)

    for idx, fila in enumerate(matriz):
        letra = chr(65 + idx)
        fila_texto = f"{letra} | " + "  | ".join(celda.center(1) for celda in fila) + "  |"
        print(fila_texto)
        print("  " + borde)
        time.sleep(0.1)

def posicion_valida(matriz, fila, col, tamaño, orientacion):
    """to check if the boat can put into the matrix without pass the size of the matrix or with a empty cell around."""
    #  checking if the boat can get in the matrix
    if orientacion == "H" and col + tamaño > M:
        return False
    if orientacion == "V" and fila + tamaño > N:
        return False

    # Verify that the cells where the boat will be placed and the adjacent ones are empty.  
    for i in range(-1, tamaño + 1):  # Extends range to include adjacent cells
        for j in [-1, 0, 1]:  # cheking cells to left/right/up/down
            if orientacion == "H":
                fila_check = fila + j
                col_check = col + i
            else:
                fila_check = fila + i
                col_check = col + j

            # Check if the cell is inside the board 
            if 0 <= fila_check < N and 0 <= col_check < M:
                if matriz[fila_check][col_check] != MAR:
                    return False  # If any adjacent cell is not empty, return False

    return True


def colocar_barco(matriz, fila, col, tamaño, orientacion, letra):
    """Coloca el barco en la matriz usando su letra única."""
    for i in range(tamaño):
        if orientacion == "H":
            matriz[fila][col + i] = letra
        else:
            matriz[fila + i][col] = letra


def ingresar_coordenadas():
    """Allows the player to enter the coordinates of the shot without the program closing"""
    while True:
        try:
            fila = input("Ingresa la fila (A-J): ").strip().upper()
            if not fila:  #verifity if the entrace is not empty
                print("Entrada vacía. Intenta nuevamente.")
                continue

            col = input("Ingresa la columna (1-10): ").strip()
            if not col:  
                print("Entrada vacía. Intenta nuevamente.")
                continue

            fila = ord(fila) - 65  # converts the letter to number (A -> 0, B -> 1, ...) 
            col = int(col) - 1      # converts the column to an index (1 -> 0, 2 -> 1, ...)

            if 0 <= fila < N and 0 <= col < M:
                return fila, col
            else:
                print("Coordenadas fuera de rango. Inténtalo nuevamente.")
        except ValueError:
            print("Entrada inválida. Asegúrate de ingresar una letra para la fila y un número para la columna.")



def seleccionar_barcos_automatica():
    barcos_seleccionados = {"Portaaviones": 1, "Fragata": 1}  

    #Randomly distribute 3 between Submarine and Battleship
    submarinos = random.randint(0, 3)
    acorazados = 3 - submarinos
    barcos_seleccionados["Submarino"] = submarinos
    barcos_seleccionados["Acorazado"] = acorazados

    #Destroyers are also distributed automatically
    destructores = 3  # Always there are 3 destroyes in total
    barcos_seleccionados["Destructor"] = destructores

    print("\nBarcos seleccionados automáticamente:")
    for barco, cantidad in barcos_seleccionados.items():
        print(f"{barco}: {cantidad}")

    return barcos_seleccionados

def colocar_barcos_jugador(matriz, barcos, jugador):
    """Permite al jugador colocar todos sus barcos en la matriz."""
    print(f"\n--- Colocación de barcos para {jugador} ---")
    for barco, cantidad in barcos.items():
        letra = LETRAS_BARCOS[barco]  # Expesifict letter for each ship
        tamaño = barcos_disponibles[barco]

        for _ in range(cantidad):
            while True:
                print(f"\nColocando {barco} (tamaño {tamaño}):")
                imprimir_matriz(matriz)
                fila, col = ingresar_coordenadas()
                orientacion = input("Orientación (H para horizontal, V para vertical): ").upper()

                if orientacion in ["H", "V"]:
                    if posicion_valida(matriz, fila, col, tamaño, orientacion):
                        # put the ship with the correspondent letter
                        colocar_barco(matriz, fila, col, tamaño, orientacion, letra)
                        break
                    else:
                        print("No se puede colocar el barco en esa posición. Inténtalo nuevamente.")
                        input("Presiona cualquier tecla para continuar...")
                        os.system("cls")
                else:
                    print("Orientación inválida. Debe ser 'H' o 'V'.")
                    input("Presiona cualquier tecla para continuar...")
                    os.system("cls")

def disparar(matriz_enemiga, fila, col):
    if matriz_enemiga[fila][col] in [TOCADO, AGUA]:
        print("Ya disparaste a esta posición, cambio de turno.")
        time.sleep(1.5)
        os.system("cls")
        return False  

    letra_barco = matriz_enemiga[fila][col]
    if letra_barco in LETRAS_BARCOS.values():
        matriz_enemiga[fila][col] = TOCADO
        print("¡Le diste a un barco! Sigue tu turno.")
        
        if verificar_hundimiento(matriz_enemiga, letra_barco):
            print(f"¡El {letra_barco} ha sido hundido!")
        
        input("Presiona Enter para continuar...")
        os.system("cls")
        return True 
    else:
        matriz_enemiga[fila][col] = AGUA
        print("Agua... Turno del siguiente jugador.")
        input("Presiona Enter para continuar...")
        os.system("cls")
        return False  


def verificar_hundimiento(matriz, letra_barco):
    for fila in matriz:
        if letra_barco in fila:  
            return False
    print(f"El barco '{letra_barco}' ha sido hundido!")
    return True


    
def verificar_ganador(matriz):
    for fila in matriz:
        for celda in fila:
            if celda in LETRAS_BARCOS.values():  
                return False
    return True 



def ingresar_coordenadas_con_tiempo(bandera_tiempo):
    """Allows you to enter coordinates until they are valid or time runs out."""
    while not bandera_tiempo.is_set():  # Keep trying until the time runs out
        try:
            fila = input("Ingresa la fila (A-J): ").strip().upper()
            if not fila:
                print("No ingresaste una fila. Inténtalo de nuevo.")
                continue  # Requested entry

            col = input("Ingresa la columna (1-10): ").strip()
            if not col:
                print("No ingresaste una columna. Inténtalo de nuevo.")
                continue  

            # Convert row and column to numeric indexes
            fila_num = ord(fila) - 65
            col_num = int(col) - 1

            if 0 <= fila_num < N and 0 <= col_num < M:
                bandera_tiempo.set() 
                return fila_num, col_num
            else:
                print("Coordenadas fuera de rango. Inténtalo nuevamente.")
        except ValueError:
            print("Entrada inválida. Asegúrate de ingresar una letra y un número correctos.")

    print("Se acabó el tiempo.")
    return None  #  times out or  invalid entry



def temporizador(segundos, bandera_tiempo, tiempo_agotado):
    """Muestra el temporizador en una ubicación fija y marca si se agota el tiempo."""
    for i in range(segundos, 0, -1):
        if bandera_tiempo.is_set():  # If coordinates were entered, stop the timer. 
            return
        
        #print(f"Tiempo restante: {i} segundos", end="\r")  
        #sys.stdout.flush()  
        time.sleep(1)


    print(" " * 30, end="\r")  #delete the timer line
    print("\n\n")
    tiempo_agotado.set()  # Mark that time has run out
    print("Tiempo agotado, aun puedes meter tus coordenadas")

   

def instrucciones():
    os.system("cls")
    print("""
¡Bienvenido a Battleship!

Battleship es un emocionante juego de estrategia naval donde dos jugadores se enfrentan en un tablero para hundir los barcos del oponente. 
Cada jugador coloca sus barcos en una cuadrícula y luego, por turnos, intenta adivinar las posiciones de los barcos enemigos disparando a 
coordenadas específicas.

Reglas del juego:

 1) Colocación de barcos: Cada jugador coloca sus barcos en su tablero de manera oculta.
 2) Turnos alternos: Los jugadores se turnan para disparar a las coordenadas del tablero enemigo.
 3) Impactos y fallos: Si un disparo acierta un barco, se marca como “Tocado”. Si falla, se marca como “Agua”.
          
Ganar el juego: El primer jugador en hundir todos los barcos del oponente gana.


""")
    os.system("pause")
    os.system("cls")



def game():
    os.system("cls")
    # create maxtrix to both players
    matriz_jugador1 = crear_matriz()
    matriz_jugador2 = crear_matriz()

    # choose ship
    print("Seleccionando barcos para el Jugador 1...")
    barcos_seleccionados1 = seleccionar_barcos_automatica()
    colocar_barcos_jugador(matriz_jugador1, barcos_seleccionados1, "Jugador 1")

    print("Finalizo de colocar el barco del jugador 1")
    print("Turno del siguiente jugador")
    os.system("pause")
    os.system("cls")

    print("Jugador 2, selecciona tus barcos:")
    barcos_seleccionados2 = seleccionar_barcos_automatica()
    colocar_barcos_jugador(matriz_jugador2, barcos_seleccionados2, "Jugador 2")

    print("Todo listo, a batallar!")

    os.system("pause")
    os.system("cls")

    print("empezara el jugador...")
    time.sleep(2)

    turno = random.choice([1, 2])

    print(f"jugador {turno}")

    os.system("pause")
    os.system("cls")


    print(f"El Jugador {turno} comienza.")


    while True:
        if turno == 1:
            print("\n--- Turno del Jugador 1 ---")
            imprimir_matriz_oculta(matriz_jugador2)
            accion = input("¿Quieres ver tu tablero? (S/N): ").upper()
            if accion == "S":
                imprimir_matriz(matriz_jugador1)
                input("Presiona cualquier tecla para continuar...")
                os.system("cls")
                imprimir_matriz_oculta(matriz_jugador2)

            bandera_tiempo = threading.Event()
            tiempo_agotado = threading.Event() # band for detect the time out

            # Iniciar el temporizador en un hilo separado
            hilo_temporizador = threading.Thread(
                target=temporizador, args=(TIEMPO_LIMITE, bandera_tiempo, tiempo_agotado)
            )
            
            print(f"tu turno durara {TIEMPO_LIMITE} segundos")
            hilo_temporizador.start()
            
            coordenadas = ingresar_coordenadas_con_tiempo(bandera_tiempo)
            hilo_temporizador.join()  # wait that the timer finishe

            if tiempo_agotado.is_set() or coordenadas is None:
                print("Turno perdido. Presiona cualquier tecla para pasar al siguiente jugador...")
                os.system("pause")  
                os.system("cls")  
                turno = 2 if turno == 1 else 1  # changes player

               
                print(" " * 30, end="\r")

            else:
                fila, col = coordenadas
                if not disparar(matriz_jugador2 if turno == 1 else matriz_jugador1, fila, col):
                    turno = 2 if turno == 1 else 1 

            if verificar_ganador(matriz_jugador2):
                print("¡Jugador 1 ha ganado!")
                os.system("pause")
                os.system("cls")
                break

        else:
            print("\n--- Turno del Jugador 2 ---")
            imprimir_matriz_oculta(matriz_jugador1)
            accion = input("¿Quieres ver tu tablero? (S/N): ").upper()
            if accion == "S":
                imprimir_matriz(matriz_jugador2)
                input("Presiona cualquier tecla para continuar...")
                os.system("cls")
                imprimir_matriz_oculta(matriz_jugador1)

            bandera_tiempo = threading.Event()
            tiempo_agotado = threading.Event()  

            
            hilo_temporizador = threading.Thread(
                target=temporizador, args=(TIEMPO_LIMITE, bandera_tiempo, tiempo_agotado)
            )
            
            print(f"tu turno durara {TIEMPO_LIMITE} segundos")
            hilo_temporizador.start()

            coordenadas = ingresar_coordenadas_con_tiempo(bandera_tiempo)
            hilo_temporizador.join()  

            if tiempo_agotado.is_set() or coordenadas is None:
                print("Turno perdido. Presiona cualquier tecla para pasar al siguiente jugador...")
                os.system("pause")  
                os.system("cls")
                turno = 2 if turno == 1 else 1  
            else:
                fila, col = coordenadas
                if not disparar(matriz_jugador2 if turno == 1 else matriz_jugador1, fila, col):
                    turno = 2 if turno == 1 else 1 

            if verificar_ganador(matriz_jugador1):
                print("¡Jugador 2 ha ganado!")
                os.system("pause")
                os.system("cls")
                break



while True:
    print("""
    |-----------------------------------------|
    |--------------BATTLESHIP-----------------|
    |-----------------------------------------|
    |1) Jugar                                 |
    |2) instrucciones                         |
    |3) Salir                                 |
    |-----------------------------------------|
    """.center(90," "))
    op = int(input("opcion: "))
    try: 
        if op == 1:
            game()
        elif op == 2:
            instrucciones()
        else: 
            break
    except(ValueError):
        print("valor invalido, intente de nuevo.")
        continue
