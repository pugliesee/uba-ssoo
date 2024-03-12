Hola metegolito
:D

# Ejercicio 4
Reemplazar el while() del ejercicio 3 por un wait(). El handler de interrupciones, asociado al número 7, se encarga de dar el signal() y dejarnos continuar con la ejecución.

# Ejercicio 7
Supongamos ya hecha la estructura de operaciones. Vamos a escribir la función write().

### a)
```
int driver_write(int sector, void* data) {

    sema.wait();

    if (IN(DOR_STATUS) == 0) {
        OUT(DOR_IO, 1);
        sleep(50);  // Dormimos 50ms luego de encenderlo.
    }

    // A esta altura, el motor ya está encendido.
    int pista = cantidad_sectores_por_pista();
    pista /= sector;    // Conseguimos la pista en la que queremos escribir.

    OUT(ARM, pista);    // Seleccionamos la pista
    while (IN(ARM_STATUS) == 0);    // busy waiting

    // Ya estamos en la pista que queremos
    OUT(SEEK_SECTOR, sector);
    escribir_datos(data);   // Escribimos en el sector pedido

    while (OUT(DATA_READY) == 0);   // Otro busy waiting
    OUT(DOR_IO, 0);    // Apagamos
    sleep(200);

    sema.signal();

    return sizeof(data);
}
```

### b)
Ahora tenemos que hacer la misma función de antes pero con interrupciones.

Hacemos primero los handlers.

```
void handler6(void) {
    armData.signal();
}

void handler7(void) {
    dormir.signal();
}

int driver_write(int sector, void* data) {

    sema.wait();

    if (IN(DOR_STATUS) == 0) {
        OUT(DOR_IO, 1);
        dormir.wait();
    }

    // A esta altura, el motor ya está encendido.
    int pista = cantidad_sectores_por_pista();
    pista /= sector;    // Conseguimos la pista en la que queremos escribir.

    OUT(ARM, pista);    // Seleccionamos la pista
    armData.wait();     // Cuando ARM_DATA es 1 (estamos en la pista que queremos), envía una interrupción al 6.

    // Ya estamos en la pista que queremos
    OUT(SEEK_SECTOR, sector);
    escribir_datos(data);   // Escribimos en el sector pedido

    armData.wait();     // DATA_READY envía una interrupción al 6 cuando terminó de escribir en el sector.

    OUT(DOR_IO, 0);    // Apagamos
    
    int repes = 4;
    while(repes--) dormir.wait();   // Cada 50ms se activa la interrupción 7

    sema.signal();

    return sizeof(data);
}
```

# Ejercicio 8

Tenemos que escribir el init(), remove() y write() del driver de la impresora. A su vez, hay que implementar las interrupciones HP_LOW_INK_INT y HP_FINISHED_INT, donde una nos indica si nos queda poca tinta, mientras que la otra nos dice que finalizó la impresión.

### REGISTROS:
- LOC_TEXT_POINTER: Ecritura
- LOC_TEXT_SIZE: Escritura
- LOC_CTRL: Lectura/Escritura
- LOC_STATUS: Lectura

Vamos a codear primero el init() y el remove().

```
int driver_init(void) {
    sem_t mutexImprimiendo = sem_init(1);   // Las impresiones son BLOQUEANTES

    // También declaramos un mutex para cada interrupción.
    sem_t mutexLowInk = sem_init(0);
    sem_t mutexFinished = sem_init(0);

    irq_register(HP_LOW_INK_INT, handlerInk);
    irq_register(HP_FINISHED_INT, handlerFinished);

    return 0;
}

void driver_remove(void) {      // O(1)
    free_irq(HP_LOW_INK_INT);
    free_irq(HP_FINISHED_INT);
}

void driver_write(void* data, int size) {
    mutexImprimiendo.wait(); // Bloqueamos la impresora

    int repes = 5;
    while (IN(LOC_CTRL) != LOW_INK && repes) {
        repes--;
    }

    if (repes > 0) {
        mutexImprimiendo.signal();
        return;  // Termina el proceso porque no tenemos tinta
    } 
    // Si llegamos hasta acá, entonces podemos imprimir
    OUT(LOC_CTRL, PRINTING);
    OUT(LOC_STATUS, BUSY);

    mutexFinished.wait();   // Esperamos a que termine la impresión.

    OUT(LOC_CTRL, FINISHED);
    OUT(LOC_STATUS, READY);

    mutexImprimiendo.signal();

}
```

<br>

# Ejercicio 10

## resolvemos el ej 10 de la g5 de drivers 

### driver del sensor 

```

void handler(){
    movimiento.signal();
}


driver_init(){
    movimiento = semaforo_create(0);
    irq_register(MOVIMIENTO_INT,handler);   
}


driver_read(char* buffer){
    movimiento.wait(); 
    bool mov = 1; 
    copy_to_user(buffer,&mov,sizeof(mov));
    return sizeof(mov);
}

driver_remove(){
    free_irq(MOVIMIENTO_INT);
}

```

<hr>

### usuario 

```


int ON =  1; 

int main(){
    int sensor = open("/dev/sensor"); //device id 
    int camara = open("/dev/camara"); 
    while(1){
        bool tmp; 
        read(sensor,&tmp,sizeof(tmp)); //bloqueante
        if(tmp){
            write(camara, &ON, sizeof(tmp));
        }
    }
}
```


<hr>






### driver de la camara 

registro T de escritura, le escribimos a la camara T 

```



driver_init(){
    
}

struct camara(){
    int tiempo; 
}

driver_write(char* buffer){
    camara c;
    OUT(T,c.tiempo);
    return(sizeof(c.tiempo));
    
}


```