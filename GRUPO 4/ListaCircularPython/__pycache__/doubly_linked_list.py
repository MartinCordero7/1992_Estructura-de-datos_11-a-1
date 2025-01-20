#/*************************
# * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
# * ALUMNO:  Steven Egas
# * FECHA CREACION: Domingo,  10 de noviembre de 2024
# *  FECHA MODIFICACION: Domingo,  12 de noviembre de 2024
# * Nivel: TERCERO     NRC: 1992
# *************************/
import json
from node import Node

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def validar_cedula(self, cedula):
        return cedula.isdigit() and len(cedula) == 10

    def cedula_existente(self, cedula):
        current = self.head
        while current:
            if current.cedula == cedula:
                return True
            current = current.siguiente
        return False

    def insertar(self, nombre1, nombre2, apellido, correo, cedula):
        new_node = Node(nombre1, nombre2, apellido, correo, cedula)
        if not self.head:
            self.head = self.tail = new_node
        else:
            self.tail.siguiente = new_node
            new_node.anterior = self.tail
            self.tail = new_node

    def buscar(self, cedula):
        current = self.head
        while current:
            if current.cedula == cedula:
                print(f"Persona encontrada: {current.nombre1} {current.nombre2} {current.apellido}, Correo: {current.correo}, Cédula: {current.cedula}")
                return
            current = current.siguiente
        print("Persona no encontrada.")

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

    def mostrar(self):
        current = self.head
        while current:
            print(f"{current.nombre1} {current.nombre2} {current.apellido}, Correo: {current.correo}, Cédula: {current.cedula}")
            current = current.siguiente



    
    def ordenar(self, criterio):
        if not self.head or not self.head.siguiente:
            print("No hay suficientes elementos para ordenar.")
            return

        def key_func(node):
            if criterio == 1:
                return node.nombre1
            elif criterio == 2:
                return node.apellido
            elif criterio == 3:
                return node.cedula
            return ""

        nodes = []
        current = self.head
        while current:
            nodes.append(current)
            current = current.siguiente

        nodes.sort(key=lambda n: key_func(n))

        self.head = nodes[0]
        self.tail = nodes[-1]
        for i in range(len(nodes)):
            nodes[i].siguiente = nodes[i + 1] if i + 1 < len(nodes) else None
            nodes[i].anterior = nodes[i - 1] if i > 0 else None
        print("Lista ordenada correctamente.")

    def hacer_backup(self, archivo):
        """
        Guarda la lista en un archivo JSON.
        """
        data = []
        current = self.head
        while current:
            data.append({
                "nombre1": current.nombre1,
                "nombre2": current.nombre2,
                "apellido": current.apellido,
                "correo": current.correo,
                "cedula": current.cedula
            })
            current = current.siguiente

        with open(archivo, 'w', encoding='utf-8') as file:
            json.dump(data, file, ensure_ascii=False, indent=4)
        print(f"Backup realizado exitosamente en '{archivo}'.")

    def restaurar_backup(self, archivo):
        """
        Restaura la lista desde un archivo JSON.
        """
        try:
            with open(archivo, 'r', encoding='utf-8') as file:
                data = json.load(file)

            self.head = self.tail = None  # Vaciar lista actual
            for item in data:
                self.insertar(
                    item["nombre1"],
                    item["nombre2"],
                    item["apellido"],
                    item["correo"],
                    item["cedula"]
                )
            print(f"Lista restaurada exitosamente desde '{archivo}'.")
        except FileNotFoundError:
            print(f"El archivo '{archivo}' no existe.")
        except json.JSONDecodeError:
            print("El archivo no tiene un formato válido.")

        