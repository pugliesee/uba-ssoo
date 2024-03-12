# Práctica 8 - SEGURIDAD - SO

### Cabe aclarar que en este archivo solo fueron solucionados los ejercicios con ⋆

## 3)
### a)
En este código tenemos un caso de *buffer overflow*. Es como el que vimos en la práctica. Puede suceder que el usuario escriba más de los 80 caracteres que permite el string "nombre".

### b)
Puede controlar los 80 bytes del nombre y cualquier valor anterior del stack.

### c)
Desconozco.

### d)
No. El problema viene dado por la función *gets()*, ya que no chequea que la cantidad de bytes leídos por el estandar input se corresponda con los 80 bytes del string "nombre".

<br>

## 4)
### a)
El error surge con la función **fgets()**, la cual nos permite escribir hasta *sizeof(user)* bytes al user.name y al user.pass. Esto significa que podemos escribir 64 bytes sobre estructuras de 32.

Por el lado del stack, tenemos primero 32 bytes de user.name, luego 32 bytes de user.pass y por último 32 bytes de *realpass*. Si escribimos 64 bytes sobre user.pass, podemos sobreescribir la *realpass* y acceder al sistema.

### b)
- User.name: *admin*
- User.pass: (64 letras 'a' seguidas) aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

Con esto tenemos 32 bytes de user.pass (32 'a' de contraseña), y luego sobreescribimos la *realpass* con otras 32 'a'. 

<br>

## 6)
### a)
Podemos pasar como número f un valor especial "no numérico". Si el programa recibe el **NaN** (*Not a Number*), ninguna comparación vale, por lo que desembocaremos en el *assert()*.

### b)
No sería seguro. En todo caso, hay un "return 0" al final del código, por lo que podemos esperar también recibir ese valor en caso de un error inesperado.

<br>

## 8)
### a)
Como queremos leer el archivo *passwd*, tenemos que usar el comando **cat**. El problema surge con que ya estamos ejecutando previamente el comando 'ls', por lo que debemos colocar un **;** para poder ejecutar 2 comandos en una misma línea (ls y cat).

```
; cat /etc/passwd
```
Con esto bastaría para ejecutar:
```
ls ; cat /etc/passwd
```
que se traduce como:
```
ls
cat /etc/passwd
```

### b)
La *backslash* en Linux nos hace interpretar los caracteres especiales de forma literal. Por ejemplo, si ponemos 
```
ls \; cat /etc/passwd
```
este comando interpreta de forma literal al ; en vez de ejecutar en una misma línea 2 comandos distintos, como hicimos antes.

Para evitar esta solución parcial, podemos colocar un espacio en el comando, para que la backslash interprete primero al espacio como algo literal, y luego el ; siga funcionando como nosotros queremos.
```
 ; cat /etc/passwd
```
// No se ve ahí arriba, pero literalmente hay un espacio entre el principio de la línea y el punto y coma.

### c)
Podemos optar por usar un && entre comandos. De esta forma, el segundo comando se ejecuta si el primero no falla, es decir, si retorna 0 luego de su ejecución.
```
 && cat /etc/passwd
```

En el caso de que esto no funcione (si falla el **ls**, que me parecería super extraño), podemos usar pipes. El comando **cat** no usa ningún estándar input, por lo que podemos usar el pipe sin ningún drama.
```
| cat /etc/passwd
```

### d)
Haría uso de la función **strtok()** y eliminaría todos los caracteres especiales posibles del parámetro de entrada, es decir, le haría una "limpieza".

```
char* dir_sanitized = strtok(dir, " -\&()|;" ");
```

<br>

## 15)
### a)
- Línea 7: El programa corre con permisos de *root*. Esto lo hace para ejecutar el comando "*echo*" y luego imprimir por pantalla lo que el usuario quiere.

### b)
El problema de seguridad surge dentro del segundo *if( )*. 

- Environment Variables

La idea del "*echo %s*" que se encuentra dentro del **snprintf()** es, básicamente, concatenar el comando *echo* a nuestro texto, así es impreso por pantalla. 

El problema que surge aquí es que se puede cambiar el PATH. Podemos crear una carpeta en /tmp/ que lleve el mismo nombre (echo), pero que dentro de ella se encuentre un código malicioso.

- Shell con privilegios de root

Por cómo está escrito el código, en ningún momento se nos prohíbe escribir caracteres especiales en el texto que queremos imprimir. 

Vimos que en la línea 7 se corre con privilegios de root al ejecutar la "instrucción" *system*. Con esto en mente, podemos abrir una shell con privilegios de root tan solo colocando un ; al comienzo de nuestro texto a "imprimir".
```
; sh -p
```
Lo cual resulta en:
```
echo "" ; sh -p
```

### c)
Recién lo expliqué en el ítem anterior.

### d)
Los tres requisitos de la seguridad de la información son:
- Confidencialidad
- Integridad
- Disponibilidad

En este caso, al correr en **root**, se violan los 3 requisitos ya que estamos en el máximo privilegio posible.

### e)
Una solución para Environment Vairables es ir a buscar el comando echo a donde corresponde. Más precisamente, se modificaría el snprintf() de la siguiente manera:
```
snprintf(cmd, tam_imprimir+4, "/usr/bin/echo %s", imprimir)
```
De esta manera, se pueden crear carpetas o archivos con el mismo nombre, pero nuestro programa SIEMPRE busca el comando en la ruta correspondiente.

Para el segundo problema, alcanza con eliminar todos los caracteres especiales del input que recibimos. Es como en el ejercicio que hicimos antes, sanitizamos el input a través de la función **strtok()**.

<br>

## 16)
No se entiende un carajo ese código.

<br>

## 17)
El código lee e imprime una serie de caracteres en pantalla. En particular, no podemos escribir más de 128 caracteres.

La función **algo_asi_si()** se encarga de "filtrar" la cantidad de caracteres que escribimos en consola, para luego usar la palabra "filtrada" como parámetro de la función **algo_asi_no()**. Esta última arroja un error en el caso de que el *string* recibido sea de mayor longitud al esperado. Caso contrario, imprime por pantalla usando el comando **echo**.

La vulnerabilidad del programa surge con la función *algo_asi_no()*, pues en la tercera línea corre la instrucción "system()", la cual funciona con privilegios de *root*. Además, en ningún momento se realiza una sanitización del string recibido, el programa solo se asegura de que tenga la longitud ideal.

Teniendo esto en cuenta, podemos abrir una shell con privilegios de root pasando el siguiente string como parámetro:
```
; sh -p
```
En mi opinión, esta es la vulnerabilidad más grande que se tiene, pues sabemos que root tiene acceso irrestricto al sistema (en la mayoría de los casos).

Por otro lado, también tenemos un problema de Environment Variables. El problema vuelve a surgir con *echo*, pues en ningún momento se le sugiere al programa mismo a dónde debe ir a buscar ese comando. 

Para tomar provecho de esto, se pueden ejecutar los siguientes comandos:
```
$ echo -e "#!/bin/sh\n/bin/sh -p" > /tmp/echo
$ chmod +x /tmp/echo
$ export PATH="/tmp:$PATH"
```

<br>

## 18)
Ya sabemos que el juego corre con máximo privilegio, entonces en todo momentodel programa nos encontramos con privilegios de *root*. Vemos que en la línea 9 se corre la función **system()**, la cual nos permite ejecutar comandos en la consola. 

Como vemos que se ejecuta el comando *echo* en consola, podemos hacer uso entonces de links simbólicos para abrir una consola en modo root. Funciona de la misma forma que en el **ejercicio 17**, aunque hay una ligera diferencia: En el segundo *snprintf()*, la frase es leída con ' ', entonces se interpreta como texto. Es por esto que el comando para abrir la shell en modo root tiene que estar incluído en el parámetro de *nombre_ganador*.

Por otro lado, la vulnerabilidad vuelve a ser el directorio de búsqueda del comando *echo*. Podemos modificar el PATH y crear un archivo en /tmp con su mismo nombre, para luego abrir con él una consola en modo root.

<br>

## 19)
En la primera línea de la función **ejecutar_si_quedan_creditos()** notamos que el saldo es de tipo *unsigned int*. Sin embargo, *creditos* y *costo* son enteros. Esto significa que la resta del crédito de un usuario y el precio de cierta función puede ser negativo. 

Notamos entonces que, al momento de corroborar si al usuario le alcanza o no para pagar la función, no se tiene en cuenta la posibilidad de que el saldo sea negativo (pues saldo es de tipo *unsigned int*), aunque SÍ puede suceder. 

Viendo esto, podemos concluír entonces que la vulnerabilidad del programa se encuentra allí, provocando que cualquier usuario pueda "pagar" cualquier función aunque no le alcance.

## 20)
