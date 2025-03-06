from flask import Flask, request, jsonify
from flask_cors import CORS
import os

app = Flask(__name__)
CORS(app)

DATA_FILE = "clientes.txt"
TEMP_ZONE_FILE = "selected_zone.txt"
LOCAL_COORDS_FILE = "local_coords.txt"

@app.route('/save_local', methods=['POST'])
def save_local():
    data = request.get_json()
    if not data or 'lat' not in data or 'lon' not in data:
        return "Datos invalidos", 400
    
    with open(LOCAL_COORDS_FILE, 'w', encoding='utf-8') as f:
        f.write(f"{data['lat']},{data['lon']}")
    return "Coordenadas guardadas correctamente"

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
        f.write(f"Cedula: {data['cedula']}, Nombre: {data['nombre']}, Zona de entrega: {data['zona']}\n")
    
    return "Cliente registrado correctamente."

@app.route('/save_zone', methods=['POST'])
def save_zone():
    data = request.get_json()
    if not data or 'zona' not in data or not data['zona'].strip():
        return "Datos de zona invalidos", 400
    
    # Guardar la zona limpiando espacios extra
    zona = data['zona'].strip()
    with open(TEMP_ZONE_FILE, 'w', encoding='utf-8') as f:
        f.write(zona)
    return "Zona guardada correctamente"

@app.route('/get_clients', methods=['GET'])
def get_clients():
    if not os.path.exists(DATA_FILE):
        return "No hay clientes registrados.", 200
    with open(DATA_FILE, "r", encoding="utf-8") as f:
        content = f.read()
    return content, 200

if __name__ == '__main__':
    app.run(debug=True)