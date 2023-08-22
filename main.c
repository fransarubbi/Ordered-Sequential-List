#include "lso.h"
#include <ctype.h>

//Funciones del menu
void loadList(list *, Deliveries *, int *);
void showList(list );
void preload(list *, int *);
void delete(list *, int *);
void changeList(list *);
void information(list , Deliveries *);


//Funciones internas
void loadDeliveries(Deliveries *);


/*
consultar la informacion completa asociada al envio
*/

int main(){

 list lso;
 Deliveries dev;
 int opcion, cant = 0;
 
 init(&lso);
 do{
    printf("\n|===========================================|");
    printf("\n|                BIENVENIDOS!               |");
    printf("\n|              ENVIOS EL REVOLEO            |");
    printf("\n|===========================================|");
    printf("\n|              MENU DE OPCIONES             |");
    printf("\n|===========================================|");
    printf("\n|     1.Ingresar nuevos envios              |");
    printf("\n|     2.Eliminar envios existentes          |");
    printf("\n|     3.Modificar datos de un envio         |");
    printf("\n|     4.Consultar informacion de un envio   |");
    printf("\n|     5.Memorizacion previa                 |");
    printf("\n|     6.Mostrar todos los envios            |");
    printf("\n|     7.Salir del sistema                   |");
    printf("\n|===========================================|\n\n");
    scanf("%d", &opcion);

    while(opcion < 1 || opcion > 7){
        printf("\n|--------------------------------------|");
        printf("\n| Por favor, ingrese un valor correcto |");
        printf("\n|--------------------------------------|");
        printf("\n  1.Ingresar nuevos envios");
        printf("\n  2.Eliminar envios existentes");
        printf("\n  3.Modificar datos de un envio");
        printf("\n  4.Consultar informacion de un envio");
        printf("\n  5.Memorizacion previa");
        printf("\n  6.Mostrar todos los envios");
        printf("\n  7.Salir del sistema");
        printf("\n=========================================\n\n");
        scanf("%d", &opcion);
    }

    switch(opcion){
        case 1: loadList(&lso, &dev, &cant);
                break;

        case 2: delete(&lso, &cant);
                break;

        case 3: changeList(&lso);
                break;

        case 4: information(lso, &dev);
                break;

        case 5: preload(&lso, &cant);
                break;

        case 6: show(lso);
                break;
    }
 }while(opcion != 7);

 return 0;
}



//Funciones del menu
void loadList(list *lso, Deliveries *dev, int *cant){

    int n, i = 0, highValue, enter;
    do{
        printf("¿Cuantas reservas quiere cargar? Maximo 300\n");
        printf("Lleva cargados %d elementos.\n", *cant);
        scanf("%d", &n);
    }while(n < 1 || n > (SIZE - (*cant)));

    do{
        printf("------- Cargando Datos -------\n");
        loadDeliveries(dev);
        highValue = high(lso, *dev);
        switch(highValue){
            case 0: printf("Error al cargar elemento. No hay mas espacio.\n");
                    break;
            
            case 1: printf("Error al cargar elemento. El elemento ya existe.\n");
                    break;

            case 2: printf("Carga exitosa de datos.\n");
                    i++;
                    *cant = *cant + 1;
                    break;
        }
    }while(highValue != 0 && (i < n));

    do{
      printf("\nCarga completa. Ingrese 1 para continuar...\n\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void preload(list *lso, int *cant){
    
    Deliveries dev;
    char code[CODE], name[NAME], nameSender[NAME], addres[NAME], dateS[DATE], dateR[NAME];
    long dni, dniS;
    int highValue, enter;

    FILE *preload;
    preload = fopen("Envios.txt", "r");

    if(preload == NULL){
        printf("No se pudo acceder al archivo.\n");
        exit(1);
    }
    else{
        while(!feof(preload)){
            fscanf(preload, " %[^\n]\n", code);
            setCodigo(&dev, code);
            fscanf(preload, "%ld\n", &dni);
            setDni(&dev, dni);
            fscanf(preload, " %[^\n]\n", name);
            setNomAp(&dev, name);
            fscanf(preload, " %[^\n]\n", addres);
            setDomicilio(&dev, addres);
            fscanf(preload, "%ld\n", &dniS);
            setDniRem(&dev, dniS);
            fscanf(preload, " %[^\n]\n", nameSender);
            setDniRem(&dev, nameSender);
            fscanf(preload, " %[^\n]\n", dateS);
            setFechaEnv(&dev, dateS);
            fscanf(preload, " %[^\n]\n", dateR);
            setFechaRec(&dev, dateR);
            highValue = high(lso, dev);

            switch(highValue){
            case 0: printf("Error al cargar elemento. No hay mas espacio.\n");
                    exit(1);
                    break;
            
            case 1: printf("Error al cargar elemento. El elemento ya existe.\n");
                    break;

            case 2: printf("Carga exitosa de datos.\n");
                    *cant = *cant + 1;
                    break;
            }
        }
        printf("Se ha realizado correctamente la carga de datos.\n");
    }
    fclose(preload);
    printf("CANT VALE: %d\n", *cant);
    do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void delete(list *lso, int *cant){

    Deliveries dev;
    char code[CODE];
    int n, i = 0, j = 0, lowValue, evocationValue, enter;
    do{
        printf("¿Cuantos envios quiere eliminar? Maximo %d\n", *cant);
        scanf("%d", &n);
    }while(n < 1 || n > *cant);

    do{
        printf("------- Eliminando Datos -------\n");
        printf("Ingrese el codigo del envio a eliminar: \n");
        scanf("%s", code);
        for(i = 0; code[i] != '\0'; i++){
            code[i] = toupper(code[i]);
        }
        setCodigo(&dev, code);
        evocationValue = evocation(*lso, &dev);

        if(evocationValue == 1){
            lowValue = low(lso, dev);
            switch(lowValue){
                case 1: printf("Error al borrar elemento. Ha cancelado el proceso.\n");
                        break;

                case 2: printf("Baja exitosa de datos.\n");
                        j++;
                        *cant = *cant - 1;
                        break;
            }
        }
        else{
            printf("Error al borrar elemento. No existe en la lista.\n");
        }
    }while(lowValue != 0 && (j < n));

    do{
      printf("\nBaja completa. Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void changeList(list *lso){
    
    Deliveries dev;
    char code[CODE];
    int i, changeValue, evocationValue;

    printf("Ingrese el codigo del envio que desea modificar: \n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    setCodigo(&dev, code);
    
    evocationValue = evocation(*lso, &dev);
    if(evocationValue == 0){
        printf("No se pueden modificar datos, no hay coincidencias para el codigo %s\n", code);
    }
    else{
        printf("Se encontraron coincidencias para el codigo %s\n", code);
        loadDeliveries(&dev);
        changeValue = change(lso, dev);
        if(changeValue == 1){
            printf("Se han realizado las modificaciones correctamente.\n");
        }
        else{
            printf("Error al modificar los datos.\n");
        }
    }
}


void information(list lso, Deliveries *dev){

    int i, evocationValue;
    char code[CODE];

    printf("Ingrese el codigo del envio que desea obtener informacion: \n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    setCodigo(&dev, code);

    evocationValue = evocation(lso, &dev);
    if(evocationValue == 1){
        printf("-------------------------------\n");
        printf("   INFORMACION DEL ENVIO %s\n", code);
        printf("-------------------------------\n");
        printf("Codigo: %s\n",(*dev).code);
        printf("DNI: %ld\n",(*dev).doc);
        printf("DNI Remitente: %ld\n",(*dev).docSender);
        printf("Nombre y apellido del receptor: %s\n",(*dev).name);
        printf("Nombre y apellido del remitente: %s\n",(*dev).nameSender);
        printf("Domicilio de envio: %s\n",(*dev).address);
        printf("Fecha de envio: %s\n",(*dev).dateSender);
        printf("Fecha de recepcion: %s\n\n",(*dev).dateReceived);
        //showDeliveries(*dev);
    }
    else{
        printf("No se han encontrado coincidencias para el codigo %s\n", code);
    }
}


//Funciones internas
void loadDeliveries(Deliveries *dev){

    int i;
    long d, ds;
    char c[CODE], n[NAME], date[DATE];

    printf("Ingrese el codigo correspondiente al envio: \n");
    scanf("%s", c);
    for(i = 0; c[i] != '\0'; i++){
        c[i] = toupper(c[i]);
    }
    setCodigo(dev, c);

    printf("Ingrese el documento del receptor: \n");
    scanf("%ld", &d);
    setDni(dev, d);

    printf("Ingrese el documento del emisor: \n");
    scanf("%ld", &ds);
    setDniRem(dev, ds);

    printf("Ingrese el nombre del receptor: \n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    setNomAp(dev, n);

    printf("Ingrese el nombre del emisor: \n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    setNomApRem(dev, n);

    printf("Ingrese la direccion del envio: \n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    setDomicilio(dev, n);

    printf("Ingrese la fecha de envio: \n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    setFechaEnv(dev, date);

    printf("Ingrese la fecha de recepcion: \n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    setFechaRec(dev, date);
}

