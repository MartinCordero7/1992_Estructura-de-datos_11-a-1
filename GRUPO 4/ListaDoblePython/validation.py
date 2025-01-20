#/*************************
# * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
# * ALUMNO:  Steven Egas
# * FECHA CREACION: Domingo,  10 de noviembre de 2024
# *  FECHA MODIFICACION: Domingo,  12 de noviembre de 2024
# * Nivel: TERCERO     NRC: 1992
# *************************/

class Validation:
    @staticmethod
    def enter_a_number(data_type="int", message="Ingrese un número: ", min_value=None, max_value=None):
        while True:
            try:
                num = int(input(message)) if data_type == "int" else float(input(message))
                if (min_value is None or num >= min_value) and (max_value is None or num <= max_value):
                    return num
                print(f"El número debe estar entre {min_value} y {max_value}.")
            except ValueError:
                print("Entrada inválida. Intente de nuevo.")

    @staticmethod
    def enter_a_string_as_num(length, message="Ingrese un número: "):
        while True:
            string = input(message)
            if string.isdigit() and len(string) == length:
                return string
            print(f"El número debe tener exactamente {length} dígitos. Intente de nuevo.")

    @staticmethod
    def enter_a_char_or_string_with_may(max_length, message="Ingrese un texto: ", allow_special_chars=True, allow_empty=False):
        while True:
            string = input(message).strip()
            if len(string) == 0 and not allow_empty:
                print("El texto no puede estar vacío.")
                continue
            if len(string) > max_length:
                print(f"El texto no puede superar {max_length} caracteres.")
                continue
            if not allow_special_chars and not string.isalpha():
                print("Solo se permiten letras.")
                continue
            return string

    @staticmethod
    def generate_email(first_name, second_name, last_name):
        first_letter = first_name[0].lower()
        second_letter = second_name[0].lower() if second_name else ""
        last_name_clean = last_name.replace(" ", "").lower()
        return f"{first_letter}{second_letter}{last_name_clean}@espe.edu.ec"

    @staticmethod
    def confirm_action(message):
        while True:
            confirm = input(message).strip().lower()
            if confirm in ['s', 'n']:
                return confirm == 's'
            print("Entrada inválida. Responda 's' para sí o 'n' para no.")
