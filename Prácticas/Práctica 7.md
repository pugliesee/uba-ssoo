# Práctica 7 - SISTEMAS DISTRIBUIDOS - SO

## 1)

### a)
- No
- No

Para estos primeros 2 casos, el nodo A no sabe diferenciar si B está caído o si el enlace entre A y B lo está.
- Si

### b)
No. Puede suceder que D envía el mensaje y, durante la transacción del mismo a lo largo del camino, D se cae.

### c)
No. En los sistemas distribuídos, el orden en el que se envían los mensajes puede no corresponderse con el orden de llegada.


<br>

## 2) 
Lo considero un sistema *paralelo* pues el sistema funciona como una única computadora. No presenta las mismas dificultades que los sistemas distribuídos (los tiempos de comunicación, por ejemplo).

<br>

## 3)
Esta "solución" no resuelve el problema. Por más de que los nodos confirmen que se terminó de escribir en cierto archivo, puede suceder que el nodo que pidió escribir se caiga. Si este nodo se rompe post-escritura, jamás envía la notificación de confirmación.

<br>

## 4)
### a)
Como están conectados bajo un orden topológico, asumo que las aristas del anillo NO SON bidireccionales. Luego, la idea del algoritmo es idéntica a la de FloodMax:
- El nodo inicial le manda su ID al próximo.
- El nodo que sigue compara su ID con el que recibió. 
- Le envía al siguiente nodo el ID más pequeño.

Finalmente, cuando todos los nodos tengan el número de ID más chico de todo el anillo, ya reconocen al líder. (En 2 vueltas al anillo podemos encontrarlo).

### b)
No sé.

## 6)
- Cada nodo le envía su ID a todos sus vecinos. 
- Cuando un nodo recibe un ID, lo compara con el mínimo/máximo que encontró hasta el momento.
- Luego, procede a enviar el mínimo/máximo ID que resultó de la comparación.

<br>

## 7)
### 1) 
Es un poco debatible ese "Paso 1"... Si un nodo es el ID máximo en funcionamiento, no va a tener ningún otro nodo al que mandarle ELECCIÓN. En todo caso, se lo envía al líder, que está descompuesto y no recibe ninguna respuesta. De esta forma, se convierte en el líder (lo cual está bien, pero suena un poco "líder autoproclamado").

Aún así, cuando este nodo de mayor ID que detectó que el líder dejó de funcionar, envía un mensaje de <COORDINADOR, ID> al resto de los nodos. Por como funciona este algoritmo, el nodo que envía la señal de COORDINADOR está esperando una respuesta del nuevo líder (ACEPTAR). En este caso, el nodo jamás recibe respuesta pues la tiene que dar él mismo.

Suena a un caso borde, pero eventualmente el algoritmo encuentra al nuevo nodo líder, ya que repite la secuencia la cantidad de veces que sea necesaria hasta encontrar un nuevo líder.

### 2)
Es muy parecido al algoritmo de *Bully*. Los nodos también tienen 3 fases: "ELECTION" - "OK" - "I WON".

<br>

## 8)
### 1)
Es un quilombo que cada nodo se comunique con el resto. Hay un aumento cuadrático de mensajes. Encima cada nodo tiene que evaluar si puede seguir o no con el *commit*.

### 2)
Si sé que el coordinador del protocolo no se va a caer, usaría 2PC. Caso contrario, usaría 3PC o la variante que presentan en este ejercicio.

<br>

## 9)
### a)
Se puede usar 2PC. El sistema que recibe los pedidos consulta antes de comprar/vender si hay stock de cierta divisa. En el caso de que no haya, recibe la señal ABORT y no se realiza la transacción. 

### b) 
No estoy de acuerdo. Puede perderse la coherencia del sistema en cierto punto, es importante mantenerla.

<br>

## 10)
### a) Univalente vs Bivalente explicar
Llamamos configuración a la colección de los estados de todos los nodos. Es un estado global.
- Univalente: Una configuración C es *univalente* cuando su valor final puede ser 0 y 1. (0-valente / 1-valente)
- Bivalente: El valorr final de la configuración puede ser 0 o 1. Es un estado de incertidumbre.

### b) 
No. El estado inicial del sistema es bivalente.

### c) Qué causa que un sistema entre en un estado univalente
Cuando uno de los nodos recibe un mensaje.

### d) Cómo afecta el teorema de la imposibilidad al diseño de sistemas reales
No sé como afecta al diseño de sistemas reales, pero el teorema de la imposibilidad nos demuestra que CUALQUIER algoritmo tolerante a fallos que resuelvan el consenso tienen ejecuciones que nunca terminan.

### e) Ejemplo donde Paxos no termina


### f) Condiciones de seguridad de Paxos
Como todos los nodos reciben diversas propuestas, cuando ya la mayoría haya "acordado" elegir la misma versión v (v es un número), luego todas las propuestas (v', n') que se aceptan deben tener a v' = v. 

En criollo, no podemos cambiar el valor v cuando la mayoría de los aceptadores ya aceptaron (valga la redundancia) a v.

### g) Ventajas / Desventajas de tener un único aceptador
*VENTAJAS*
- Podemos aceptar más rápido las propuestas que recibimos. (?)

*DESVENTAJAS*
- El único aceptador siempre va a terminar aceptando la primera propuesta que le llegue.
- Si se cae el nodo aceptador, cagamos la fruta.

### h)
Cuando el *proponedor* recibe un SÍ como respuesta del *quórum*, se encarga de propagar la señal (aceptar, n, v) por todos los nodos, donde v es el valor de propuesta más alto que recibió entre todas las respuestas.

