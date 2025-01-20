
#/*************************
# * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
# * ALUMNO:  Steven Egas,Pablo Dominguez, Esteban Santos
# * FECHA CREACION: Domingo,  10 de noviembre de 2024
# *  FECHA MODIFICACION: Domingo,  12 de noviembre de 2024
# * Nivel: TERCERO     NRC: 1992
# *************************/

import os
import json
from datetime import datetime
from node import Node
from validation import Validation
from Fecha import Fecha


import os
import json
from datetime import datetime

class Node:
    def __init__(self, nombre1, nombre2, apellido, correo, cedula, fecha):
        self.nombre1 = nombre1
        self.nombre2 = nombre2
        self.apellido = apellido
        self.correo = correo
        self.cedula = cedula
        self.fecha = fecha
        self.siguiente = None
        self.anterior = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.last_backup_data = []

    def validar_cedula(self, cedula):
        if not cedula.isdigit() or len(cedula) != 10:
            return False

        # Verificar que no todos los dígitos sean iguales
        if cedula == cedula[0] * 10:
            return False

        coeficientes = [2, 1, 2, 1, 2, 1, 2, 1, 2]
        suma = 0
        for i in range(9):
            valor = int(cedula[i]) * coeficientes[i]
            if valor >= 10:
                valor -= 9
            suma += valor

        digito_verificador = int(cedula[9])
        suma = (10 - (suma % 10)) % 10

        return suma == digito_verificador

    def cedula_existente(self, cedula):
        current = self.head
        while current:
            if current.cedula == cedula:
                return True
            current = current.siguiente
        return False

    def insertar(self, nombre1, nombre2, apellido, correo, cedula, fecha):
        new_node = Node(nombre1, nombre2, apellido, correo, cedula, fecha)
        if not self.head:
            self.head = self.tail = new_node
        else:
            self.tail.siguiente = new_node
            new_node.anterior = self.tail
            self.tail = new_node

    def mostrar(self):
        current = self.head
        while current:
            print(f"{current.nombre1} {current.nombre2} {current.apellido}, Correo: {current.correo}, Cédula: {current.cedula}, Fecha de Nacimiento: {current.fecha}")
            current = current.siguiente

    def mostrar_lista(self):
        if not self.head:
            print("La lista está vacía.")
        else:
            self.mostrar()

    def hacer_backup(self):
        if not self.head:
            print("No hay elementos en la lista. No se puede realizar un backup.")
            return

        carpeta_principal = os.path.dirname(__file__)
        carpeta = os.path.join(carpeta_principal, "backup")
        if not os.path.exists(carpeta):
            os.makedirs(carpeta)

        data = []
        current = self.head
        while current:
            data.append({
                "nombre1": current.nombre1,
                "nombre2": current.nombre2,
                "apellido": current.apellido,
                "correo": current.correo,
                "cedula": current.cedula,
                "fecha": current.fecha
            })
            current = current.siguiente

        if data == self.last_backup_data:
            print("El contenido no ha cambiado desde el último backup. No se realizará un nuevo backup.")
            return

        fecha_actual = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        archivo = os.path.join(carpeta, f"{fecha_actual}.json")

        with open(archivo, 'w', encoding='utf-8') as file:
            json.dump(data, file, ensure_ascii=False, indent=4)
        print(f"Backup realizado exitosamente en '{archivo}'.")
        self.last_backup_data = data


    def insertar_persona(self):
        while True:
            print("Por favor, ingrese los detalles de la persona.")
            cedula = Validation.enter_a_string_as_num(10, "Ingrese cédula (10 dígitos): ")
            if self.validar_cedula(cedula) and not self.cedula_existente(cedula):
                break
            print("Cédula inválida o ya existente. Intente de nuevo.")
        
        nombre1 = Validation.enter_a_char_or_string_with_may(20, "Ingrese primer nombre: ", allow_special_chars=False)
        nombre2 = Validation.enter_a_char_or_string_with_may(20, "Ingrese segundo nombre: ", allow_special_chars=False, allow_empty=True)
        apellido = Validation.enter_a_char_or_string_with_may(20, "Ingrese apellido: ", allow_special_chars=False)
        correo = Validation.generate_email(nombre1, nombre2, apellido)
        print(f"Correo generado automáticamente: {correo}")
        fecha = Fecha.ingresar_fecha("Ingrese la fecha de nacimiento (AAAA-MM-DD): ")
        
        self.insertar(nombre1, nombre2, apellido, correo, cedula, fecha)
        print("Persona insertada correctamente.")

    def buscar(self, cedula):
        current = self.head
        while current:
            if current.cedula == cedula:
                print(f"Persona encontrada: {current.nombre1} {current.nombre2} {current.apellido}, Correo: {current.correo}, Cédula: {current.cedula}")
                return
            current = current.siguiente
        print("Persona no encontrada.")

    def buscar_persona(self):
        cedula = Validation.enter_a_string_as_num(10, "Ingrese cédula de la persona a buscar: ")
        self.buscar(cedula)

    def eliminar(self, cedula):
        current = self.head
        while current:
            if current.cedula == cedula:
                if current == self.head:
                    self.head = current.siguiente
                    if self.head:
                        self.head.anterior = None
                elif current == self.tail:
                    self.tail = current.anterior
                    if self.tail:
                        self.tail.siguiente = None
                else:
                    current.anterior.siguiente = current.siguiente
                    current.siguiente.anterior = current.anterior
                print(f"Persona con Cédula {cedula} eliminada.")
                return
            current = current.siguiente
        print("Persona no encontrada.")

    def eliminar_persona(self):
        cedula = Validation.enter_a_string_as_num(10, "Ingrese cédula de la persona a eliminar: ")
        if Validation.confirm_action("¿Está seguro de eliminar esta persona? (s/n): "):
            self.eliminar(cedula)



    def restaurar_backup(self, archivo_seleccionado):
        carpeta_principal = os.path.dirname(__file__)
        carpeta = os.path.join(carpeta_principal, "backup")
        ruta_archivo = os.path.join(carpeta, archivo_seleccionado)

        try:
            with open(ruta_archivo, 'r', encoding='utf-8') as file:
                data = json.load(file)

            self.head = self.tail = None
            for item in data:
                self.insertar(
                    item["nombre1"],
                    item["nombre2"],
                    item["apellido"],
                    item["correo"],
                    item["cedula"],
                    item["fecha"]
                )
            print(f"Lista restaurada exitosamente desde '{ruta_archivo}'.")
        except FileNotFoundError:
            print(f"El archivo '{ruta_archivo}' no existe.")
        except json.JSONDecodeError:
            print("El archivo no tiene un formato válido.")

    def listar_backups(self):
        carpeta_principal = os.path.dirname(__file__)
        carpeta = os.path.join(carpeta_principal, "backup")
        if not os.path.exists(carpeta):
            print(f"La carpeta '{carpeta}' no existe.")
            return []

        archivos = [f for f in os.listdir(carpeta) if f.endswith('.json')]
        if not archivos:
            print("No hay archivos de backup disponibles.")
        return archivos
    

    def ordenar(self, criterio):
        if not self.head or not self.head.siguiente:
            print("No hay suficientes elementos para ordenar.")
            return

        def key_func(node):
            if criterio == 1:  # Ordenar por nombre1
                return node.nombre1
            elif criterio == 2:  # Ordenar por apellido
                return node.apellido
            elif criterio == 3:  # Ordenar por cedula
                return node.cedula
            elif criterio == 4:  # Ordenar por fecha
                try:
                    return datetime.strptime(node.fecha, '%Y-%m-%d')
                except ValueError:
                    return datetime.min  # Si la fecha no es válida, se coloca al principio
            return ""

        # Convertir lista enlazada en una lista de nodos
        nodes = []
        current = self.head
        while current:
            nodes.append(current)
            current = current.siguiente

        # Ordenar la lista de nodos
        nodes.sort(key=lambda n: key_func(n))

        # Reconstruir la lista enlazada
        self.head = nodes[0]
        self.tail = nodes[-1]
        for i in range(len(nodes)):
            nodes[i].siguiente = nodes[i + 1] if i + 1 < len(nodes) else None
            nodes[i].anterior = nodes[i - 1] if i > 0 else None

        print("Lista ordenada correctamente.")
        self.mostrar_lista()