**Calculadora de Sistemas de Ecuaciones Lineales** \
Proyecto desarrollado para la materia Programaci�n 2 de la carrera de Ingenier�a en Inform�tica. El objetivo de este trabajo es aplicar los conceptos fundamentales de la programaci�n en C++, como la modularidad, la recursividad y el manejo de archivos, para crear una herramienta robusta capaz de resolver sistemas de ecuaciones lineales de distintos tama�os.

Integrantes del Grupo \
Abril Teo \
Lavezzari Fabricio \
Martos Felipe

**Caracter�sticas Principales** \
El programa cuenta con las siguientes funcionalidades:

Resoluci�n de Sistemas Cuadrados y Rectangulares: Capaz de manejar sistemas donde el n�mero de ecuaciones y de inc�gnitas es igual o diferente.

Selecci�n Autom�tica de M�todo: El programa analiza las dimensiones de la matriz ingresada y elige el m�todo m�s eficiente para el c�lculo del determinante:

F�rmula est�ndar para matrices de 2x2.

Regla de Sarrus para matrices de 3x3.

Expansi�n de Laplace (Recursiva) para matrices de orden superior.

Reducci�n por Gauss-Jordan: Es el m�todo principal utilizado para encontrar la soluci�n del sistema, robusto incluso para casos no cuadrados.

Detecci�n de Sistemas sin Soluci�n: El programa es capaz de identificar sistemas inconsistentes (sin soluci�n) o con infinitas soluciones (determinante cero).

Persistencia de Resultados: Cada soluci�n calculada se guarda en un archivo de historial llamado resultado.txt, conservando las ejecuciones anteriores.

C�digo Modular: El proyecto est� organizado en m�dulos (.h y .cpp) para separar responsabilidades (entrada/salida, operaciones de matrices, resoluci�n, etc.), siguiendo las buenas pr�cticas de la programaci�n.


**Casos de Prueba** \
A continuaci�n, se muestran tres ejecuciones del programa que demuestran su correcto funcionamiento en distintos escenarios.

Caso 1: Sistema 2x2 con Soluci�n �nica
Esta prueba verifica la correcta resoluci�n de un sistema cuadrado simple y el c�lculo de su determinante. \
![Imagen del Caso 1](./sist2x2.png)
Caso 2: Sistema 3x2 Rectangular
Esta prueba demuestra la capacidad del algoritmo de Gauss-Jordan para manejar sistemas no cuadrados y encontrar la soluci�n correcta.
![Imagen del Caso 2](./sist3x2.png)
Caso 3: Sistema Inconsistente (Sin Soluci�n)
Esta prueba confirma que el programa es capaz de identificar sistemas que no tienen soluci�n, en este caso, a trav�s del c�lculo de un determinante igual a cero.
![Imagen del Caso 3](./sist-incosistente.png)