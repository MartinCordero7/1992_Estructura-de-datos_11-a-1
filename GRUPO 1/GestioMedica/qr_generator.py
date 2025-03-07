import qrcode
from datetime import datetime
import os

class CitaQRGenerator:
    def __init__(self):
        self.output_dir = os.path.join(os.path.dirname(__file__), 'qr_codes')
        if not os.path.exists(self.output_dir):
            os.makedirs(self.output_dir)

    def generar_qr_cita(self, datos_cita):
        # Crear el contenido del QR
        contenido_qr = f"""
        CITA MÉDICA ACEPTADA
        Paciente: {datos_cita['nombre_paciente']}
        Cédula: {datos_cita['cedula']}
        Doctor: {datos_cita['doctor']}
        Especialidad: {datos_cita['especialidad']}
        Fecha: {datos_cita['fecha']}
        Hora: {datos_cita['hora']}
        """
        
        # Crear QR
        qr = qrcode.QRCode(
            version=1,
            error_correction=qrcode.constants.ERROR_CORRECT_L,
            box_size=10,
            border=4,
        )
        qr.add_data(contenido_qr)
        qr.make(fit=True)

        # Crear imagen
        qr_image = qr.make_image(fill_color="black", back_color="white")
        
        # Generar nombre único para el archivo
        nombre_archivo = f"cita_{datos_cita['cedula']}_{datos_cita['fecha']}_{datos_cita['hora'].replace(':', '')}.png"
        ruta_archivo = os.path.join(self.output_dir, nombre_archivo)
        
        # Guardar imagen
        qr_image.save(ruta_archivo)
        return ruta_archivo

    def leer_cita_aceptada(self):
        citas = []
        with open('output/citas_aceptadas.txt', 'r', encoding='utf-8') as file:
            cita_actual = {}
            for line in file:
                line = line.strip()
                if line.startswith('Nombre Paciente:'):
                    cita_actual['nombre_paciente'] = line.split(': ')[1]
                elif line.startswith('Cedula:'):
                    cita_actual['cedula'] = line.split(': ')[1]
                elif line.startswith('Doctor Asignado:'):
                    cita_actual['doctor'] = line.split(': ')[1]
                elif line.startswith('Especialidad Doctor:'):
                    cita_actual['especialidad'] = line.split(': ')[1].strip()
                elif line.startswith('Fecha de Cita:'):
                    cita_actual['fecha'] = line.split(': ')[1]
                elif line.startswith('Hora de Cita:'):
                    cita_actual['hora'] = line.split(': ')[1]
                elif line == '-------------------------':
                    if cita_actual:
                        citas.append(cita_actual.copy())
                        cita_actual = {}
            # Agregar la última cita si existe
            if cita_actual:
                citas.append(cita_actual.copy())
        return citas

# Ejemplo de uso:
if __name__ == "__main__":
    qr_gen = CitaQRGenerator()
    citas = qr_gen.leer_cita_aceptada()
    for cita in citas:
        ruta_qr = qr_gen.generar_qr_cita(cita)
        print(f"QR generado: {ruta_qr}")
