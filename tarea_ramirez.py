import os

def eliminar_y_ordenar(entrance):

    ordenar = sorted(entrance)
    eliminar_caracter_adicional = ''.join(ordenar)
    resultado = [eliminar_caracter_adicional[0]]

    for comparar in eliminar_caracter_adicional[1:]:
        if comparar != resultado[-1]:
            resultado.append(comparar)
    return ''.join(resultado)

while True:

    try:
        entrada = input("Ingrese una cadena de texto solo con letras (o escriba 'salir' para terminar): ").upper()
    except (EOFError, KeyboardInterrupt): # Maneja Ctrl+D o Ctrl+C por si el profe quiere aplicar maldad
        print("\nNo combinaciones de tecla porfavor.")
        continue

    if entrada == "SALIR":
        print("Programa finalizado.")
        break

    if not entrada.isalpha(): # Verifica si la cadena contiene solo letras
        print("Error: La cadena debe contener solo letras (sin espacios, números ni signos).")
        continue

    if len(entrada) < 2 or len(entrada) > 20000:
        print("Error: La cadena debe tener al menos 2 caracteres.")
        continue
    
    os.system("cls" if os.name == "nt" else "clear")

    print()
    valor_entrada = len(eliminar_y_ordenar(entrada))
    valor_ordenado = len(entrada)
    print()
    print("Solucion del error de gabriel")
    print()
    print(f"Cadena de entrada :{entrada} = {len(entrada)}")
    print("Cadena Ordenada: ", eliminar_y_ordenar(entrada), " = ", len(eliminar_y_ordenar(entrada)))
    print(f"Valor de la cadena original: {valor_ordenado} - {valor_entrada} = ", valor_ordenado - valor_entrada)
    os.system("pause")
    
# Enzo ortiz, Roger Montero