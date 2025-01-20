

#/*************************
# * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
# * ALUMNO:  Steven Egas,Pablo Dominguez, Esteban Santos
# * FECHA CREACION: Domingo,  10 de noviembre de 2024
# *  FECHA MODIFICACION: Domingo,  12 de noviembre de 2024
# * Nivel: TERCERO     NRC: 1992
# *************************/

import curses
from Singly_Linked_List import  SinglyLinkedList
from validation import Validation
import os

def menu():
    opciones = [
        "Insertar Persona",
        "Buscar Persona",
        "Eliminar Persona",
        "Mostrar Lista",
        "Ordenar Lista",
        "Hacer Backup",
        "Restaurar Backup",
        "Salir",
    ]
    return mostrar_menu_con_flechas("Menú Principal", opciones)

def ordenar_menu():
    opciones = [
        "Ordenar por Primer Nombre",
        "Ordenar por Apellido",
        "Ordenar por Cédula",
        "Ordenar por Fecha",
    ]
    return mostrar_menu_con_flechas("Opciones de Ordenamiento", opciones)

def mostrar_menu_con_flechas(titulo, opciones):
    def render_menu(stdscr):
        curses.curs_set(0)  # Ocultar el cursor
        curses.start_color()
        curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_WHITE)
        current_row = 0

        while True:
            stdscr.clear()
            stdscr.addstr(0, 0, f"--- {titulo} ---\n", curses.A_BOLD)

            for idx, row in enumerate(opciones):
                if idx == current_row:
                    stdscr.addstr(idx + 2, 2, row, curses.color_pair(1))
                else:
                    stdscr.addstr(idx + 2, 2, row)

            stdscr.refresh()

            key = stdscr.getch()

            if key == curses.KEY_UP and current_row > 0:
                current_row -= 1
            elif key == curses.KEY_DOWN and current_row < len(opciones) - 1:
                current_row += 1
            elif key in [curses.KEY_ENTER, 10, 13]:
                return current_row + 1

    return curses.wrapper(render_menu)

def seleccionar_backup(archivos):
    opciones = [f"Backup {i + 1}: {archivo}" for i, archivo in enumerate(archivos)]
    return mostrar_menu_con_flechas("Seleccionar Backup", opciones) - 1  # Ajuste para índice base-0

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
