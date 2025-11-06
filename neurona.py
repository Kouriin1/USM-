import os
import random
import math
import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image
import numpy as np

# ---------- CLASES DE NEURONA Y RED ----------
class Neurona:
    def __init__(self, cantidad_entradas):
        self.pesos = [random.uniform(-0.1, 0.1) for _ in range(cantidad_entradas)]
        self.salida = 0.0

    def activar(self, entradas):
        suma = sum(e * p for e, p in zip(entradas, self.pesos))  # Suma ponderada
        suma = max(min(suma, 100), -100)  # Evitar overflow
        self.salida = 1 / (1 + math.exp(-suma))  # Función de activación sigmoide
        return self.salida

    def entrenar(self, entradas, error, tasa_aprendizaje):
        for i in range(len(self.pesos)):
            self.pesos[i] += tasa_aprendizaje * error * entradas[i]


class RedNeuronal:
    def __init__(self, entradas, ocultas):
        self.ocultas = [Neurona(entradas) for _ in range(ocultas)]
        self.salida = Neurona(ocultas)

    def forward(self, entradas):
        salidas_ocultas = [n.activar(entradas) for n in self.ocultas]
        salida_final = self.salida.activar(salidas_ocultas)
        return salida_final, salidas_ocultas

    def entrenar(self, entradas, etiqueta, tasa=0.001):
        salida_final, salidas_ocultas = self.forward(entradas)
        error_salida = etiqueta - salida_final
        self.salida.entrenar(salidas_ocultas, error_salida, tasa)
        for i, neurona_oculta in enumerate(self.ocultas):
            error_oculta = error_salida * self.salida.pesos[i]
            neurona_oculta.entrenar(entradas, error_oculta, tasa)
        return abs(error_salida)


# ---------- FUNCIONES AUXILIARES ----------
def cargar_imagen(ruta, tamaño=(28, 28)):
    try:
        imagen = Image.open(ruta).convert('L').resize(tamaño)
        datos = np.asarray(imagen, dtype=np.float32).flatten() / 255.0
        return datos.tolist()
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo procesar la imagen:\n{e}")
        return None


def cargar_dataset(ruta_base):
    datos = []
    for etiqueta, carpeta in [(1, "normal"), (0, "neumonia")]:
        carpeta_completa = os.path.join(ruta_base, carpeta)
        if not os.path.exists(carpeta_completa):
            continue
        print(f"📂 Cargando carpeta: {carpeta_completa}")
        for archivo in os.listdir(carpeta_completa):
            if archivo.lower().endswith((".png", ".jpg", ".jpeg")):
                ruta = os.path.join(carpeta_completa, archivo)
                entradas = cargar_imagen(ruta)
                if entradas:
                    datos.append((entradas, etiqueta))
    print(f"✅ Dataset cargado: {len(datos)} imágenes totales")
    return datos


def guardar_modelo(red, ruta):
    with open(ruta, 'w', encoding="utf-8") as f:
        for neurona in red.ocultas:
            f.write(','.join(f"{p:.6f}" for p in neurona.pesos) + '\n')
        f.write(','.join(f"{p:.6f}" for p in red.salida.pesos) + '\n')


def cargar_modelo(red, ruta):
    with open(ruta, 'r', encoding="utf-8") as f:
        lineas = f.readlines()
        for i, neurona in enumerate(red.ocultas):
            neurona.pesos = [float(x) for x in lineas[i].strip().split(',')]
        red.salida.pesos = [float(x) for x in lineas[-1].strip().split(',')]


def guardar_resultado(ruta_resultado, salida, diagnostico, entradas, pesos):
    """Guarda el resultado del diagnóstico en un archivo UTF-8."""
    try:
        with open(ruta_resultado, "w", encoding="utf-8") as f:
            f.write(f"Diagnóstico: {diagnostico}\n")
            f.write(f"Salida: {salida}\n")
            f.write(f"Entradas: {entradas}\n")
            f.write(f"Pesos: {pesos}\n")
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo guardar el resultado:\n{e}")


def es_fuera_de_distribucion(entrada_nueva, datos, umbral=5.0):
    """Evita diagnosticar imágenes sin correlación usando distancia euclidiana."""
    def distancia(v1, v2):
        return math.sqrt(sum((a - b) ** 2 for a, b in zip(v1, v2)))
    distancias = [distancia(entrada_nueva, entrada) for entrada, _ in datos]
    return min(distancias) > umbral


# ---------- INTERFAZ ----------
class InterfazNeurona:
    def __init__(self, master):
        self.master = master
        master.title("🧠 Neurona Diagnóstica")
        master.geometry("500x300")
        master.config(bg="#202630")

        self.red = RedNeuronal(784, 16)
        self.dataset = []
        self.ruta_modelo = ""
        self.ruta_imagen = ""

        tk.Label(master, text="Menú Principal", font=("Arial", 16, "bold"), bg="#202630", fg="white").pack(pady=10)
        tk.Button(master, text="📂 Cargar Dataset", command=self.cargar_dataset, width=25, bg="#444", fg="white").pack(pady=5)
        tk.Button(master, text="🧠 Entrenar Neurona", command=self.entrenar_neurona, width=25, bg="#556", fg="white").pack(pady=5)
        tk.Button(master, text="💾 Cargar Modelo", command=self.cargar_modelo, width=25, bg="#556", fg="white").pack(pady=5)
        tk.Button(master, text="🖼️ Seleccionar Imagen", command=self.seleccionar_imagen, width=25, bg="#445", fg="white").pack(pady=5)
        tk.Button(master, text="🔍 Diagnosticar Imagen", command=self.diagnosticar, width=25, bg="#565", fg="white").pack(pady=5)

        self.label_estado = tk.Label(master, text="Esperando acción...", bg="#202630", fg="lightgray")
        self.label_estado.pack(pady=10)

    def cargar_dataset(self):
        ruta = filedialog.askdirectory(title="Seleccionar carpeta base del dataset (normal/neumonia)")
        if not ruta:
            return
        self.dataset = cargar_dataset(ruta)
        if self.dataset:
            self.label_estado.config(text=f"✅ Dataset cargado ({len(self.dataset)} imágenes)")
        else:
            messagebox.showwarning("Advertencia", "No se encontraron imágenes válidas.")

    def entrenar_neurona(self):
        if not self.dataset:
            messagebox.showerror("Error", "Primero carga el dataset.")
            return

        epocas = 40
        print("🧠 Iniciando entrenamiento...\n")
        for epoca in range(epocas):
            random.shuffle(self.dataset)
            error_total = 0
            for entradas, etiqueta in self.dataset:
                error_total += self.red.entrenar(entradas, etiqueta)
            print(f"Época {epoca + 1}/{epocas} - Error total: {error_total:.4f}")

        self.ruta_modelo = filedialog.asksaveasfilename(defaultextension=".txt", title="Guardar modelo entrenado")
        if self.ruta_modelo:
            guardar_modelo(self.red, self.ruta_modelo)
            self.label_estado.config(text=f"✅ Modelo guardado: {os.path.basename(self.ruta_modelo)}")
            print(f"\nModelo guardado en: {self.ruta_modelo}")

    def cargar_modelo(self):
        ruta = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
        if ruta:
            cargar_modelo(self.red, ruta)
            self.ruta_modelo = ruta
            self.label_estado.config(text=f"✅ Modelo cargado: {os.path.basename(ruta)}")

    def seleccionar_imagen(self):
        ruta = filedialog.askopenfilename(filetypes=[("Imágenes", "*.jpg *.jpeg *.png")])
        if ruta:
            self.ruta_imagen = ruta
            self.label_estado.config(text=f"🖼️ Imagen: {os.path.basename(ruta)}")

    def diagnosticar(self):
        if not self.ruta_imagen:
            messagebox.showerror("Error", "Primero selecciona una imagen.")
            return
        if not self.ruta_modelo:
            messagebox.showerror("Error", "Primero carga o entrena un modelo.")
            return

        entradas = cargar_imagen(self.ruta_imagen)
        if entradas:
            # Verificación básica de validez de imagen
            if np.std(entradas) < 0.05:
                messagebox.showwarning("Imagen inválida", "La imagen no contiene información útil para diagnosticar.")
                return

            # Comprobación fuera de distribución
            if self.dataset and es_fuera_de_distribucion(entradas, self.dataset):
                messagebox.showwarning("Advertencia", "Imagen fuera de distribución.")
                return

            salida, _ = self.red.forward(entradas)
            ambigua = 0.45 < salida < 0.55
            diagnostico = "Imagen ambigua ⚠️" if ambigua else ("Sano 🟢" if salida >= 0.5 else "Neumonía 🔴")

            messagebox.showinfo("Resultado", f"Diagnóstico: {diagnostico}\nSalida: {salida:.4f}")
            self.label_estado.config(text=f"Diagnóstico: {diagnostico}")
            print(f"🩻 Diagnóstico: {diagnostico} (Salida: {salida:.4f})")

            # ✅ Preguntar si desea guardar el resultado
            ruta_resultado = os.path.join(os.getcwd(), "resultado_diagnostico.txt")
            guardar = messagebox.askyesno("Guardar diagnóstico", "¿Deseas guardar el resultado del diagnóstico?")
            if guardar:
                guardar_resultado(ruta_resultado, salida, diagnostico, entradas, self.red.salida.pesos)
                messagebox.showinfo("Guardado", f"El diagnóstico ha sido guardado en:\n{ruta_resultado}")
            else:
                messagebox.showinfo("No guardado", "El diagnóstico no fue guardado.")


if __name__ == "__main__":
    root = tk.Tk()
    app = InterfazNeurona(root)
    root.mainloop()
