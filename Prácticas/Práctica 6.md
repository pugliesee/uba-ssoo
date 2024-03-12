# Práctica 6 - Sistemas Operativos

## 1) 
Se necesitan N-1 accesos a disco. Estamos asumiendo que queremos llegar al último bloque y no leerlos / traerlo a memoria.

<br>

## 2)
### a)
1. *Cálculo de la Cantidad de Bloques:*
   - Capacidad del disco: 128 GB
   - Tamaño del bloque: 8 KB
   - Cantidad de bloques = (Capacidad del disco) / (Tamaño del bloque)
   - Cantidad de bloques ≈ 128 GB / 8 KB ≈ 16 millones

2. *Cálculo de la Cantidad de Entradas en la Tabla:*
   - Tamaño de una entrada de tabla: 24 B
   - Tamaño de la tabla = Cantidad de bloques * Tamaño de una entrada de tabla
   - Tamaño de la tabla ≈ 16 millones * 24 B ≈ 384 MB
   - Cantidad de entradas en la tabla ≈ 16 millones

Por lo tanto, el tamaño de la tabla sería aproximadamente 384 MB.

### b)

Tenemos que ver cuánto espacio disponible nos queda en el disco. Para ello:
- Capacidad restante del disco: 128GB * 1024 - 384MB =  130.688MB

Luego, para saber cuántos archivos de 10MB podemos guardar en ese espacio, alcanza con dividir ese número por 10:
- 130.688MB / 10MB = 13.068 archivos

### c)
Siguiendo la lógica de la FAT, vemos que el archivo ocupa 7 bloques de 8K cada uno. Entonces:
- Peso del archivo: 7 * 8KB = 56KB 

<br>

## 3) 
### a)
En un bloque, entran 4KB / 8B direccionamientos distintos. En particular:
- Direccionamientos por bloque = 512 

Veamos la cantidad de bloques que tenemos en total:
- 5 bloques directos
- 2 bloques indirectos, con 512 entradas cada uno --> 2 * 512 = 1024 bloques más.
- Un bloque doblemente indirecto --> 512 direccionamientos a bloques de indirección simple --> 512^2 bloques más.


- TOTAL = 263.173 bloques

En definitiva, cada bloque soporta hasta 4KB, entonces, el archivo más grande que podemos tener es de 263.173 * 4KB
- Tamaño del archivo más grande ≈ 1028 MB

### b)
Recordemos que cada bloque tiene un espacio de 4KB
- 50% del disco: Archivos de 2KB, entonces ocupan medio bloque cada uno. Desperdician la mitad de un bloque.
- 25% del disco: Archivos de 4KB. No desperdician bloques.
- 25% restante: Archivos de 8KB. Ocupan 2 bloques cada uno.

En resumen, solo los archivos de 2KB desperdician espacio. Como cada uno desperdicia la mitad de un bloque y ocupan un 50% del disco, desperdician un 25% del almacenamiento total.

## c)
Un archivo de 5MB ocupa 5120KB. En total, este archivo ocupa 1280 bloques.
- 5 accesos directos.
- 2 accesos indirectos + 512 accesos directos dentro de cada bloque.
- 1 acceso doblemente indirecto + 1 acceso indirecto + 251 accesos directos.

1280 + 4 accesos = 1284

<br>

## 4) 
### a)
Cada bloque tiene 4KB, y en Ext2 tenemos 12 bloques directos.
Como nuestro archivo pesa 40KB, podemos leerlos accediendo únicamente a los primeros 10 bloques directos.

### b)
- 12 lecturas de los primeros 12 bloques directos
- Lectura del primer bloque indirecto 
- Lectura de los primeros 8 bloques del bloque indirecto

21 lecturas en total

<br>

## 5)
## Lo hacemos con un sistema Ext2
### I) 
- Los bloques 1, 2, 3, 5, 7, 11 pueden leerse directamente con un único acceso a disco.
- Los bloques 13, 17, 23 van a estar dentro del primer bloque indirecto. Luego, dentro de este bloque, podemos leer a cada uno con una única lectura.

- TOTAL: 10 lecturas

### II)
- Del 1 al 6, 6 lecturas en total

Para leer el 10001, estamos asumiendo que cada bloque tiene 256 entradas. Veamos cuántos y cuáles bloques deberíamos leer.

Tenemos 12 entradas directas y 3 entradas indirectas, las cuales nos redirigen a un bloque indirecto con 256 entradas. Esto implica un total de 780 bloques. El nuestro está en el 10001, entonces debemos ir a la entrada doble indirecta.

- Tenemos 1 lectura en el bloque de indirección doble. Otra lectura más en alguno de los 2 bloques en el que se encuentre el bloque 10001. Y una última lectura que es para leer el bloque 10001.

- TOTAL: 9 lecturas

### III) 
- El bloque 13 se encuentra en el primer bloque de indirección simple: 2 lecturas

- El bloque 10.000 se encuentra en el bloque de indirección doble: 3 lecturas

- El bloque 1.000.000 se encuentra en el bloque de indirección triple: 4 lecturas

- TOTAL: 9 lecturas

### IV)
Todos están en el primer bloque de indirección simple. Tenemos que leer una única vez ese bloque.
- TOTAL: 38 lecturas

<br>

## 7)

### 1) 
Inodos. Visto en la teórica.
### 2)
Inodos. Permiten mayor flexibilidad respecto al espacio que sus estructuras auxiliares ocupan.
### 3)
FAT.
### 4)
Inodos. Pasa que FAT te carga si o si toda la tabla en memoria.

<br>

## 10)
### a) 
- Nombre del archivo
- Dirección inicial desde *root*
- Tipo de archivo - Con esto podremos saber si es un directorio o no.


### b)
Vamos a escribir un pseudo-código de la cunfión "cargar_archivo". Recordemos que estamos trabajando sobre un sistema FAT.

```
void cargar_archivo(directorio[]) {
   raw_data = root_table();

   // Cada directorio ocupa un solo bloque

   for (int i = 0; i < directorios.size() - 1; i++) {
      listaDirs = parse_directory_entries(raw_data); // Vemos los directorios que hay en raw_data

      for (int j = 0; j < listaDirs.size(); j++) {
         if (listaDirs[j].type == directorio && directorio[i] == listaDirs[j].name) {
            
            // Sabemos dónde empieza el primer bloque por cómo definimos la estructura en el ítem a).

            raw_data = read_blocks(listaDirs[j].first_block);
            break;

         }
      }

   }

   // Ya estamos adentro del directorio en el que se encuentra el archivo que queremos.

   n = directorios.size();
   listaDirs = parse_directory_entries(raw_data);

   for (int i = 0; i < listaDirs.size(); i++) {
      if (listaDirs[i].type == archivo && directorio[n-1] == listaDirs[i].name) {
         raw_data = listaDirs[i].first_block;
         break;
      }
   } 

   empty = [];
   while (!raw_data.EOF) {
      empty.push_back(raw_data.block_address);
      raw_data = FAT_entry(raw_data).next_block;   // Estamos dandole un atributo que nos devuelve el bloque que le sigue al archivo que queremos ver.
   }

   raw_data = read_blocks(empty);
   
   return raw_data;

}
```

<br>

## 11)
