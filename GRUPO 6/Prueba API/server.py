from flask import Flask, request
from flask_cors import CORS
import os

app = Flask(__name__)
CORS(app)  # Habilita CORS para todas las rutas

DATA_FILE = "clientes.txt"

@app.route('/save_client', methods=['POST'])
def save_client():
    data = request.get_json()
    if not data:
        return "No se recibieron datos.", 400

    required_fields = ["cedula", "nombre", "zona"]
    for field in required_fields:
        if field not in data or data[field] == "":
            return f"Falta el campo {field}.", 400

    # Guardar los datos del cliente en modo append
    with open(DATA_FILE, "a", encoding="utf-8") as f:
        f.write(f"Cédula: {data['cedula']}, Nombre: {data['nombre']}, Zona de entrega: {data['zona']}\n")
    
    return "Cliente registrado correctamente."

@app.route('/get_clients', methods=['GET'])
def get_clients():
    if not os.path.exists(DATA_FILE):
        return "No hay clientes registrados.", 200
    with open(DATA_FILE, "r", encoding="utf-8") as f:
        content = f.read()
    return content, 200

if __name__ == '__main__':
    app.run(debug=True)
