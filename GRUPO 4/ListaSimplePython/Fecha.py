import datetime

class Fecha:
    @staticmethod
    def validar_fecha(fecha_str):
        try:
            fecha = datetime.datetime.strptime(fecha_str, "%Y-%m-%d").date()
            return True
        except ValueError:
            return False

    @staticmethod
    def ingresar_fecha(mensaje):
        while True:
            fecha_str = input(mensaje)
            if Fecha.validar_fecha(fecha_str):
                return fecha_str
            else:
                print("Fecha inválida. Asegúrese de que el formato sea AAAA-MM-DD y considere años bisiestos. Intente de nuevo.")