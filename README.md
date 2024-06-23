Este proyecto esta estructurado como si quisiera tener dos entornos virtuales.
Si no hara uso de entornos virtuales, entonces asegurese que tenga instalado en su sistema python2.7 y python3 para usar Ibex-lib y dependencias de script python.
env_py2: Entorno virtual con python2.7, este es necesario para la instalacion y uso de la libreria Ibex-lib https://github.com/ibex-team/ibex-lib
env_py3: Entorno virtual con python3 instalado para poder hacer uso de la libreria tensorflow.

Despues de creado el entorno virtual env_py2 siga las instrucciones de la documentacion de ibex para su instalacion y uso.
Los archivos llamados Ibex_Optimizer.cpp y Ibex_Optimizer.h estan modificados para este proyecto. Debe reemplazarlos por los originales de la libreria Ibex-lib para probarlos.

En entorno env_py3 esta el script de python, este llamado main.py es llamado desde Ibex_Optimizer.cpp para su uso.
Script manda su respuesta a Ibex_Optimizer.cpp y este sigue con su funcionamiento.

Comando para ejecutar problema:
Se ubica en ibex-lib: ./__build__/src/ibexopt benchs/optim/medium/ex8_5_2_1.bch --random-seed=3
Ajuste o cambie el archivo .bch a usar y el numero de semilla.
