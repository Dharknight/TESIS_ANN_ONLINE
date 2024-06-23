import sys
import numpy as np
from tensorflow.keras.models import load_model

def replace_variables(file_content, new_values):
    lines = file_content.split('\n')
    var_lines = [i for i, line in enumerate(lines) if line.startswith('x') and 'in' in line]

    for i, new_value in zip(var_lines, new_values):
        parts = lines[i].split(' ')
        lines[i] = f"{parts[0]} {parts[1]} {parts[2]} [{new_value[0]},{new_value[1]}];"

    return '\n'.join(lines)

def main():
    # Leer datos de stdin
    input_data = sys.stdin.read()
    features = [float(x) for x in input_data.split(',')]

    # Leer y modificar el archivo .bch
    with open('ship.bch', 'r') as file:
        file_content = file.read()

    # Reemplazar variables en el archivo
    new_values = [(features[i], features[i+1]) for i in range(0, len(features), 2)]
    modified_content = replace_variables(file_content, new_values)

    with open('modified_ship.bch', 'w') as file:
        file.write(modified_content)

    # Cargar el modelo de la red neuronal
    model = load_model('MFV3.h5')

    # Crear un DataFrame para la predicción
    data = np.array(features).reshape(1, -1)
    y_predtest = model.predict(data)

    # Formatear el output
    cont = 0
    for i in y_predtest:
        if i[0] > i[1] and i[0] > i[2]:
            y_predtest[cont] = [1, 0, 0]
        if i[1] > i[0] and i[1] > i[2]:
            y_predtest[cont] = [0, 1, 0]
        if i[2] > i[1] and i[2] > i[0]:
            y_predtest[cont] = [0, 0, 1]
        cont += 1

    # Ejecutar el solucionador apropiado basado en la predicción
    if y_predtest[0][0] == 1:
        solver = "bis:LSmear"
    elif y_predtest[0][1] == 1:
        solver = "bis:RoundRobin"
    else:
        solver = "bis:LargestFirst"

    print("Solución seleccionada:", solver)

if __name__ == "__main__":
    main()
