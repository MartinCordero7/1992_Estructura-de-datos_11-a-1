
from Fecha import Fecha
class Node:
    def __init__(self, nombre1, nombre2, apellido, correo, cedula,fecha):
        self.nombre1 = nombre1
        self.nombre2 = nombre2
        self.apellido = apellido
        self.correo = correo
        self.cedula = cedula
        self.Fecha= fecha
        self.siguiente = None
        self.anterior = None