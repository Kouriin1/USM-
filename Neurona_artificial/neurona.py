from PIL import Image          # Librería para abrir y procesar imágenes BMP o PGM
import numpy as np             # Para convertir la imagen en un arreglo numérico
import random                  # Para generar pesos aleatorios
import math                    # Para aplicar funciones matemáticas como la sigmoide
import tkinter as tk           # Para abrir el selector de archivos
from tkinter import filedialog # Para el cuadro de diálogo de selección de archivos

# Estructura de la neurona
class Neurona:
    def __init__(self, entradas):
        self.entradas = entradas              # Lista de valores normalizados (píxeles entre 0.0 y 1.0)
        self.cantidad = len(entradas)         # Número total de entradas (cantidad de píxeles)
        self.pesos = self.inicializar_pesos() # Inicializa pesos aleatorios para cada entrada
        self.salida = None                    # Variable para guardar la salida final de la neurona

    def inicializar_pesos(self):
        # Genera un peso aleatorio entre -1 y 1 para cada entrada
        return [random.uniform(-1, 1) for _ in range(self.cantidad)]

    def calcular_salida(self, tipo='sigmoide'):
        # Calcula la suma ponderada de entradas multiplicadas por sus respectivos pesos
        suma_ponderada = sum(e * p for e, p in zip(self.entradas, self.pesos))
        # Aplica la función de activación seleccionada a la suma
        self.salida = self.funcion_activacion(suma_ponderada, tipo)
        return self.salida

    def funcion_activacion(self, x, tipo):
        if tipo == 'sigmoide':
            # Función sigmoide: salida entre 0 y 1
            return 1 / (1 + math.exp(-x))
        elif tipo == 'relu':
            # ReLU: devuelve 0 si x < 0, o x si x >= 0
            return max(0, x)
        elif tipo == 'escalon':
            # Escalón: devuelve 1 si x >= 0, o 0 si x < 0
            return 1 if x >= 0 else 0
        else:
            # Si el tipo no es válido, lanza un error
            raise ValueError("Tipo de activación no válido")

    def guardar_resultado(self, archivo):
        # Guarda los resultados en un archivo de texto
        with open(archivo, 'w') as f:
            f.write("Cantidad de entradas: {}\n".format(self.cantidad))
            f.write("Primeros 10 valores de entrada:\n")
            f.write(', '.join(f"{x:.3f}" for x in self.entradas[:10]) + "\n")
            f.write("Primeros 10 pesos:\n")
            f.write(', '.join(f"{w:.3f}" for w in self.pesos[:10]) + "\n")
            f.write("Salida final: {:.4f}\n".format(self.salida))

# Función para cargar imagen y extraer entradas
def cargar_imagen(ruta):
    imagen = Image.open(ruta).convert('L')           # Abre la imagen y la convierte a escala de grises
    imagen = imagen.resize((28, 28))                 # Redimensiona la imagen a 28x28 píxeles para estandarizar el tamaño
    datos = np.asarray(imagen, dtype=np.float32)     # Convierte la imagen a un arreglo numérico
    normalizados = datos.flatten() / 255.0           # Aplana el arreglo y normaliza los valores de 0–255 a 0.0–1.0
    return normalizados.tolist()                     # Devuelve la lista de entradas normalizadas

# Función principal con ventana de selección de imagen
def main():
    # Crear ventana oculta de Tkinter
    root = tk.Tk()
    root.withdraw()

    # Abrir diálogo para seleccionar imagen
    ruta_imagen = filedialog.askopenfilename(
        title="Selecciona una imagen para procesar",
        filetypes=[("Archivos de imagen", "*.bmp;*.pgm;*.png;*.jpg;*.jpeg")]
    )

    # Si no se selecciona imagen, salir
    if not ruta_imagen:
        print("No se seleccionó ninguna imagen. Saliendo del programa.")
        return

    ruta_salida = "resultado.txt"  # Archivo donde se guardará el resultado

    entradas = cargar_imagen(ruta_imagen)         # Carga y procesa la imagen seleccionada
    neurona = Neurona(entradas)                   # Crea una neurona con esas entradas
    salida = neurona.calcular_salida(tipo='sigmoide')  # Calcula la salida usando la función sigmoide
    neurona.guardar_resultado(ruta_salida)        # Guarda los resultados en un archivo de texto

    print(f"Imagen procesada: {ruta_imagen}")
    print(f"Salida calculada: {salida:.4f}")
    print(f"Resultado guardado en: {ruta_salida}")

# Punto de entrada del programa
if __name__ == "__main__":
    main()
