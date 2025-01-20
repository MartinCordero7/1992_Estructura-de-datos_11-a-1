

#/*************************
# * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
# * ALUMNO:  Steven Egas,Pablo Dominguez, Esteban Santos
# * FECHA CREACION: Domingo,  10 de noviembre de 2024
# *  FECHA MODIFICACION: Domingo,  12 de noviembre de 2024
# * Nivel: TERCERO     NRC: 1992
# *************************/


from Singly_Linked_List import  SinglyLinkedList
from validation import Validation
import os



def menu():
    opciones = [
        "1. Insertar Persona",
        "2. Buscar Persona",
        "3. Eliminar Persona",
        "4. Mostrar Lista",
        "5. Ordenar Lista",
        "6. Hacer Backup",
        "7. Restaurar Backup",
        "8. Salir",
    ]

    print("\n--- Menú Principal ---")
    for opcion in opciones:
        print(opcion)
    return Validation.enter_a_number(
        "int", "Seleccione una opción: ", 1, len(opciones)
    )


def ordenar_menu():
    opciones = [
        "1. Ordenar por Primer Nombre",
        "2. Ordenar por Apellido",
        "3. Ordenar por Cédula",
        "3. Ordenar por Fecha",

    ]

    print("\n--- Opciones de Ordenamiento ---")
    for opcion in opciones:
        print(opcion)
    return Validation.enter_a_number(
        "int", "Seleccione un criterio: ", 1, len(opciones)
    )



def seleccionar_backup(archivos):
    print("\n--- Seleccionar Backup ---")
    for i, archivo in enumerate(archivos, start=1):
        print(f"{i}. {archivo}")
    return Validation.enter_a_number(
        "int", "Seleccione un archivo: ", 1, len(archivos)
    ) - 1  # Ajuste para índice base-0

def main():
    lista = SinglyLinkedList()
    carpeta_principal = os.path.dirname(__file__)
    carpeta_backup = os.path.join(carpeta_principal, "backup")

    while True:
        opcion = menu()

        try:
            if opcion == 1:
                lista.insertar_persona()
            elif opcion == 2:
                lista.buscar_persona()
            elif opcion == 3:
                lista.eliminar_persona()
            elif opcion == 4:
                lista.mostrar_lista()
            elif opcion == 5:
                criterio = ordenar_menu()
                lista.ordenar(criterio)
            elif opcion == 6:
                lista.hacer_backup()
            elif opcion == 7:
                archivos = lista.listar_backups()
                if archivos:
                    indice_seleccionado = seleccionar_backup(archivos)
                    lista.restaurar_backup(archivos[indice_seleccionado])
                else:
                    print("No hay backups disponibles.")
            elif opcion == 8:
                print("Saliendo del programa.")
                break
        except Exception as e:
            print(f"Error: {e}")

        input("Presione Enter para continuar...")


if __name__ == "__main__":
    main()