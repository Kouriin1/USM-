import os
import winsound

def limpiar_pantalla():
    # Para sistemas Windows
    if os.name == 'nt':
        os.system('cls')
    # Para sistemas Unix (Linux, Mac, etc.)
    else:
        os.system('clear')


def minusculas(texto):
    return texto.lower()


def USM():
    limpiar_pantalla()
    print("""

    La santa maria ofrece practicas gratis de odontologia para nuestros estudiantes
    si quieres ser partes de esta practica, Contactenos!
    Correo: usm@usm.edu.ve          

          xMMMMMMMMMMWWWWWWWMMMWWWWWWMMMMWWWWWWWWWWWWWWWMMMMMMMMMM
        xMMMMMMMMNOocccccxXXxccccco0NN0occcccccccccccoONMMMMMMMMMM
        xMMMMMMMNx,. .  'okl..   .ck0x,.             .'dXWMMMMMMMM
        xMMMMMMXd,.....,oxc......lko:,.................,dXWMMMMMMM
        xMMMMWKd;'''..;dxc,''..'lko,.....'ldxddddddddddxkKNMMMMMMMM
        xMMMW0l,''''';oo:,'''.;oko,.....,dOd;,,,,,,,,,,,',ckNMMMMM
        xMMW0:........'......;dko;,'''.;dOo.. ... .........'xNMMMM
        xMMMXo'.............:xxl;,,'.':xOl'.,;'...;:,......;kNMMMM
        xMMMMN0xoooooooooooxkx:'....':kkl''lxo;.,oko;,''.'cONMMMMM
        xMMMMMMNklcccccccccc:'.....cdkx:',oxl,.;dxl,'''.'l0NMMMMMM
        xMMMMMMW0:................lxko,.,od:..;dd;.....,dKWMMMMMMM
        cMMMMMMMMWKl'............,oOdc,.:xkc''ckx:.....;xXWMMMMMMM
        xMMMMMMMMMNKOOOOOOOOOOOO0XNXK00KNNKO0XNX0OOOOOKNMMMMMMMMMM
        xMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

    """)
    input("Presiona cualquier tecla para continuar...")
    
    
    
def estudiantes():
    limpiar_pantalla()
    print("Estudiantes".center(90,'-'))
    print("""
    
    1) Maria victoria
	2) Robert Mora
	3) Michelle Montañez
	4) volver    
    

    """)
  
    op = int(input("Opcion: "))

    if op == 1:
        Maria_victoria()
    elif op == 2:
        Robert_mora()
    elif op == 3:
        Michelle_motanes()
    else: 
        pass        
    

def Michelle_motanes():
        limpiar_pantalla()
        print("Michelle Montañez".center(90,'-'))
        print("""
     	# Michelle Montañez
        ## Estudiante de Cuarto Semestre

        **Apasionada por el conocimiento y abierta a la exploración de nuevas áreas de estudio.**

        *En búsqueda constante de superar desafíos y expandir horizontes académicos.*



        desea pedir una cita con el estudiante?
        1 = si, 2 = no
        """)

        op = int(input("Opcion: "))

        if op == 1:
            calendario3()
        else: 
            pass




def Robert_mora():
        limpiar_pantalla()
        print("Robert Mora".center(90,'-'))
        print("""
        # Robert Mora
        ## Estudiante de Odontología Preventiva

        **Interesado en la prevención de enfermedades bucodentales y la promoción de la salud oral a largo plazo.**

        *Especializándose en odontología preventiva con un enfoque en el cuidado y la educación sostenible de la salud bucal.*

	
	
              
        desea pedir una cita con el estudiante?
        1 = si, 2 = no
        """)

        op = int(input("Opcion: "))

        if op == 1:
            calendario2()
        else: 
            pass




def Maria_victoria():
        limpiar_pantalla()
        print("Maria Victoria".center(90,'-'))
        print("""
        # María Victoria
        ## Especialista en Odontología Pediátrica

        **Enfocada en mejorar el aprendizaje en la odontología a través del cuidado infantil.**

        *Comprometida con la excelencia y la innovación en la atención dental pediátrica.*

              
        desea pedir una cita con el estudiante?
        1 = si, 2 = no
        """)

        op = int(input("Opcion"))

        if op == 1:
            calendario1()
        else: 
            pass


def calendario1():
    limpiar_pantalla()
    print("Horarios".center(90,'-'))
    print("""
        
           
        Hora      |   Lun 	 |   Mie   |   Vie		
	7:00AM    |	         |	   |   	     	 
	7:45AM    |aula:910      |aula:922 |aula:910	 
	7:45AM    |aula:910	 |aula:922 |aula:910	 
	8:30AM    |aula:910	 |aula:922 |aula:910	 

	
    """)
    op = input("Seleccione un dia (lunes, miercoles, viernes) ")
  
    if op == "lunes":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...")    
        
    elif op == "miercoles":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...") 
        
    elif op == "viernes":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...")
        
    else:
        exit



def calendario2():
    limpiar_pantalla()
    print("Horarios".center(90,'-'))
    print("""
        
   	
	    Hora       |  Mar 	 |   Mie   | 		
	    10:00AM    |         |	   |   	     	 
	    10:45AM    |aula:912 |aula:722 |	 
	    10:45AM    |aula:912 |aula:722 |	 
	    11:30AM    |aula:912 |aula:722 |	

	
        """)
    op = input("Seleccione un dia (martes, viernes) ")
    if op == "martes":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...")    
        
    elif op == "miercoles":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...") 
        
    else:
        exit

def calendario3():
    limpiar_pantalla()
    print("Horarios".center(90,'-'))
    print("""
        
   	
	  Hora    |   Mar 	 |   Jue   | 
         2:30PM   |	         |	   |   	     
	4:30PM    |aula:812      |aula:722 |	
	4:30PM    |aula:812	 |aula:722 |
	5:30PM    |aula:812	 |aula:722 |	 


	
        """)
    op = input("Seleccione un dia (martes, jueves) ")
    if op == "martes":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...")    
        
    elif op == "jueves":
        limpiar_pantalla()
        print("Tu cita fue creada!".center(90," "))
        input("Presiona cualquier tecla para continuar...") 
        
    else:
        exit



while True:
    limpiar_pantalla()
    print("""
    |-----------------------------------------|
    |-------------Sanitario USM---------------|
    |-----------------------------------------|
    |1) Estudiantes                           |
    |2) USM                                   |
    |3) Salir                                 |
    |-----------------------------------------|
    """.center(90," "))
    op = int(input("opcion: "))
    if op == 1:
       estudiantes()
    elif op == 2:
        USM()
    else: 
        break
        
        


