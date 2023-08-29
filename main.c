//Grupo 7  Sarubbi Franco - Orozco Mateo

#include "lso.h"
#include <ctype.h>

//Funciones del menu
void loadList(list *, Deliveries *, int *);  //Cargar elementos
void preload(list *, int *);    //Realizar precarga de datos por archivo
void delete(list *, int *);    //Eliminar elementos
void changeList(list *);    //Modificar elementos
void information(list );     //Mostrar informacion de un elemento


//Funciones internas
void loadDeliveries(Deliveries *);   //Funcion auxiliar de carga de datos
void changeDeliveries(Deliveries *);   //Funcion auxiliar de modificacion de datos


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
        printf("\n|  1.Ingresar nuevos envios            |");
        printf("\n|  2.Eliminar envios existentes        |");
        printf("\n|  3.Modificar datos de un envio       |");
        printf("\n|  4.Consultar informacion de un envio |");
        printf("\n|  5.Memorizacion previa               |");
        printf("\n|  6.Mostrar todos los envios          |");
        printf("\n|  7.Salir del sistema                 |");
        printf("\n|======================================|\n\n");
        scanf("%d", &opcion);
    }

    switch(opcion){
        case 1: if(cant == SIZE){
                    printf("\n|------------------------------------------------|");
                    printf("\n| No se pueden cargar datos. La lista esta llena |");
                    printf("\n|------------------------------------------------|\n");
                }
                else{
                    loadList(&lso, &dev, &cant);
                }
                break;

        case 2: delete(&lso, &cant);
                break;

        case 3: if(cant == 0){
                    printf("\n|---------------------------------------------------|");
                    printf("\n| No se pueden modificar datos. La lista esta vacia |");
                    printf("\n|---------------------------------------------------|\n");
                }
                else{
                    changeList(&lso);
                }
                break;

        case 4: if(cant == 0){
                    printf("\n|-------------------------------------------------|");
                    printf("\n| No se pueden mostrar datos. La lista esta vacia |");
                    printf("\n|-------------------------------------------------|\n");
                }
                else{
                    information(lso);
                }
                break;

        case 5: preload(&lso, &cant);
                break;

        case 6: if(cant == 0){
                    printf("\n|-------------------------------------------------|");
                    printf("\n| No se pueden mostrar datos. La lista esta vacia |");
                    printf("\n|-------------------------------------------------|\n");
                }
                else{
                    printf("\n\n      Mostrando %d elementos\n", cant);
                    show(lso);
                }
                break;
    }
 }while(opcion != 7);

 printf("\n|===========================================|");
 printf("\n|       GRACIAS POR USAR EL SISTEMA         |");
 printf("\n|             ENVIOS EL REVOLEO             |");
 printf("\n|===========================================|\n\n");

 return 0;
}



//Funciones del menu
void loadList(list *lso, Deliveries *dev, int *cant){

    int n, i = 0, highValue, enter;
    do{
        printf("|----------------------------------------------|\n");
        printf("| ¿Cuantas reservas quiere cargar? Maximo 300  |\n");
        printf("|----------------------------------------------|\n");
        printf("         Lleva cargados %d elementos            \n", *cant);
        printf("|----------------------------------------------|\n\n");
        scanf("%d", &n);
    }while(n < 1 || n > (SIZE - (*cant)));

    do{
        printf("\n|--------------------------------|");
        printf("\n|-------- Cargando Datos --------|");
        printf("\n|--------------------------------|\n\n");
        loadDeliveries(dev);
        highValue = high(lso, *dev);
        switch(highValue){
            case 0: printf("|----------------------------------------------|\n");
                    printf("| Error al cargar elemento. No hay mas espacio |\n");
                    printf("|----------------------------------------------|\n\n");
                    break;
            
            case 1: printf("|-------------------------------------------------|\n");
                    printf("| Error al cargar elemento. El elemento ya existe |\n");
                    printf("|-------------------------------------------------|\n\n");
                    break;

            case 2: printf("|----------------------------------------------|\n");
                    printf("|           Carga exitosa de datos             |\n");
                    printf("|----------------------------------------------|\n\n");
                    i++;
                    *cant = *cant + 1;
                    break;
        }
    }while(highValue != 0 && (i < n));

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
   }while(enter != 1);
}


void preload(list *lso, int *cant){
    
    Deliveries dev;
    char code[CODE], name[NAME], nameSender[NAME], addres[NAME], dateS[DATE], dateR[DATE];
    long dni, dniS;
    int highValue, enter, belongsValue;

    FILE *preload;
    preload = fopen("Envios.txt", "r");

    if(preload == NULL){
        printf("|----------------------------------------------|\n");
        printf("|       No se pudo acceder al archivo          |\n");
        printf("|----------------------------------------------|\n\n");
        exit(1);
    }
    else{
        while(!feof(preload)){
            fscanf(preload, " %[^\n]\n", code);
            setCodigo(&dev, code);
            fscanf(preload, "%ld\n", &dni);
            setDni(&dev, dni);
            fscanf(preload, " %[^\n]\n", nameSender);
            setNomApRem(&dev, nameSender);
            fscanf(preload, " %[^\n]\n", addres);
            setDomicilio(&dev, addres);
            fscanf(preload, "%ld\n", &dniS);
            setDniRem(&dev, dniS);
            fscanf(preload, " %[^\n]\n", name);
            setNomAp(&dev, name);
            fscanf(preload, " %[^\n]\n", dateS);
            setFechaEnv(&dev, dateS);
            fscanf(preload, " %[^\n]\n", dateR);
            setFechaRec(&dev, dateR);

            highValue = high(lso, dev);

            switch(highValue){
                case 0: printf("|----------------------------------------------|\n");
                        printf("| Error al cargar elemento. No hay mas espacio |\n");
                        printf("|----------------------------------------------|\n\n");
                        exit(1);
                        break;
            
                case 1: printf("|-------------------------------------------------|\n");
                        printf("| Error al cargar elemento. El elemento ya existe |\n");
                        printf("|-------------------------------------------------|\n\n");
                        break;

                case 2: printf("|----------------------------------------------|\n");
                        printf("|            Carga exitosa de datos            |\n");
                        printf("|----------------------------------------------|\n\n");
                        *cant = *cant + 1;
                        break;
            }
        }
        printf("           Elementos cargados: %d\n", *cant);
    }
    fclose(preload);
    
    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
   }while(enter != 1);
}


void delete(list *lso, int *cant){

    Deliveries dev;
    char code[CODE];
    int n, i = 0, j = 0, lowValue, evocationValue, enter;

    if(*cant < 1){
        printf("\n|------------------------------------------|");
        printf("\n| No se pueden eliminar datos. Lista vacia |");
        printf("\n|------------------------------------------|\n");
    }
    else{
        do{
            printf("|---------------------------------------------------|\n");
            printf("    ¿Cuantos envios quiere eliminar? Maximo %d\n", *cant);
            printf("|---------------------------------------------------|\n");
            scanf("%d", &n);
        }while(n < 1 || n > *cant);

        do{
            printf("\n|----------------------------------------------|");
            printf("\n|-------------- Eliminando Datos --------------|");
            printf("\n|----------------------------------------------|");
            printf("\n|   Ingrese el codigo del envio a eliminar:    |\n");
            scanf("%s", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            setCodigo(&dev, code);
            evocationValue = evocation(*lso, &dev);

            if(evocationValue == 1){
                lowValue = low(lso, dev);
                switch(lowValue){
                    case 1: printf("|-----------------------------------------------------|\n");
                            printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                            printf("|-----------------------------------------------------|\n\n");
                            break;

                    case 2: printf("|----------------------------------------------|\n");
                            printf("|            Baja exitosa de datos             |\n");
                            printf("|----------------------------------------------|\n\n");
                            j++;
                            *cant = *cant - 1;
                            break;
                }
            }
            else{
                printf("|---------------------------------------------------|\n");
                printf("|  Error al borrar elemento. No existe en la lista  |\n");
                printf("|---------------------------------------------------|\n\n");
            }
        }while(lowValue != 0 && (j < n));
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
   }while(enter != 1);
}


void changeList(list *lso){
    
    Deliveries d;
    char code[CODE];
    int i, changeValue, evocationValue, enter;

    printf("|----------------------------------------------------|\n");
    printf("|  Ingrese el codigo del envio que desea modificar:  |\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    setCodigo(&d, code);
    
    evocationValue = evocation(*lso, &d);
    if(evocationValue == 0){
        printf("|----------------------------------------------------------------------------|\n");
        printf("   No se pueden modificar datos, no hay coincidencias para el codigo %s      \n", code);
        printf("|----------------------------------------------------------------------------|\n");
    }
    else{
        changeDeliveries(&d);
        changeValue = change(lso, d);
        if(changeValue == 1){
            printf("|-------------------------------------------------------|\n");
            printf("|   Se han realizado las modificaciones correctamente   |\n");
            printf("|-------------------------------------------------------|\n");
        }
        else{
            printf("|----------------------------------------------|\n");
            printf("|         Error al modificar los datos         |\n");
            printf("|----------------------------------------------|\n");
        }
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void information(list lso){

    Deliveries d;
    int i, evocationValue, enter;
    char code[CODE];

    printf("\n|----------------------------------------------------------------|");
    printf("\n|   Ingrese el codigo del envio que desea obtener informacion:   |");
    printf("\n|----------------------------------------------------------------|\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    setCodigo(&d, code);

    evocationValue = evocation(lso, &d);
    if(evocationValue == 1){
        printf("\n|---------------------------------|");
        printf("\n    INFORMACION DEL ENVIO %s", code);
        printf("\n|---------------------------------|\n\n");
        printf("\n| Codigo: %s", getCodigo(d));
        printf("\n| Dni receptor: %ld", getDni(d));
        printf("\n| Dni remitente: %ld", getDniRem(d));
        printf("\n| Nombre y apellido del receptor: %s", getNomAp(d));
        printf("\n| Nombre y apellido del remitente: %s", getNomApRem(d));
        printf("\n| Domicilio del envio: %s", getDomicilio(d));
        printf("\n| Fecha de envio: %s", getFechaEnv(d));
        printf("\n| Fecha de recepcion: %s", getFechaRec(d));
    }
    else{
        printf("|--------------------------------------------------------------|\n");
        printf("    No se han encontrado coincidencias para el codigo %s\n", code);
        printf("|--------------------------------------------------------------|\n\n");
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


//Funciones internas
void loadDeliveries(Deliveries *dev){

    int i;
    long d;
    char c[CODE], n[NAME], date[DATE];

    printf("|---------------------------------------------|\n");
    printf("| Ingrese el codigo correspondiente al envio: |\n");
    scanf("%s", c);
    for(i = 0; c[i] != '\0'; i++){
        c[i] = toupper(c[i]);
    }
    setCodigo(dev, c);

    do{
        printf("|------------------------------------|\n");
        printf("| Ingrese el documento del receptor: |\n");
        scanf("%ld", &d);
    }while(d < 4000000 || d > 50000000);  //rango de documento entre 4.000.000 hasta 50.000.000
    setDni(dev, d);

    do{
        printf("|----------------------------------|\n");
        printf("| Ingrese el documento del emisor: |\n");
        scanf("%ld", &d);
    }while(d < 4000000 || d > 50000000);  //rango de documento entre 4.000.000 hasta 50.000.000
    setDniRem(dev, d);

    printf("|---------------------------------|\n");
    printf("| Ingrese el nombre del receptor: |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    setNomAp(dev, n);

    printf("|-------------------------------|\n");
    printf("| Ingrese el nombre del emisor: |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    setNomApRem(dev, n);

    printf("|-----------------------------------|\n");
    printf("|  Ingrese la direccion del envio:  |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    setDomicilio(dev, n);

    printf("|------------------------------|\n");
    printf("|  Ingrese la fecha de envio:  |\n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    setFechaEnv(dev, date);

    printf("|----------------------------------|\n");
    printf("|  Ingrese la fecha de recepcion:  |\n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    setFechaRec(dev, date);
}


void changeDeliveries(Deliveries *dev){

    int i, j, cantChange, cant = 0, option;
    int control[7];
    long d, ds;
    char n[NAME], date[DATE];

    for(j = 0; j < 7; j++){
        control[j] = 0;
    }

    do{
        printf("\n|--------------------------------------------|");
        printf("\n|              MODIFICANDO DATOS             |");
        printf("\n|--------------------------------------------|");
        printf("\n|       ¿Cuantos datos desea modificar?      |");
        printf("\n| Recuerde que puede modificar hasta 7 datos |");
        printf("\n|--------------------------------------------|");
        printf("\n| Documento del receptor                     |");
        printf("\n| Documento del emisor                       |");
        printf("\n| Nombre del receptor                        |");
        printf("\n| Nombre del emisor                          |");
        printf("\n| Domicilio                                  |");
        printf("\n| Fecha de envio                             |");
        printf("\n| Fecha de recepcion                         |");
        printf("\n|--------------------------------------------|\n");
        scanf("%d", &cantChange);
    }while(cantChange < 1 || cantChange > 7);

    while(cant < cantChange){
        
        do{
            printf("\n|--------------------------------------------|");
            printf("\n|         ¿Que dato desea modificar?         |");
            printf("\n|--------------------------------------------|");
            printf("\n| 1.Documento del receptor                   |");
            printf("\n| 2.Documento del emisor                     |");
            printf("\n| 3.Nombre del receptor                      |");
            printf("\n| 4.Nombre del emisor                        |");
            printf("\n| 5.Domicilio                                |");
            printf("\n| 6.Fecha de envio                           |");
            printf("\n| 7.Fecha de recepcion                       |");
            printf("\n|--------------------------------------------|\n");
            scanf("%d", &option);
        }while(option < 1 || option > 7);

        if(control[option - 1] == 1){
            do{
                printf("\n|------------------------------------------------------------------|");
                printf("\n| Ha modificado el dato previamente. No puede volver a modificarlo |");
                printf("\n| Elija el dato a modificar a continuacion:                        |");
                printf("\n|------------------------------------------------------------------|");
                printf("\n| 1.Documento del receptor                                         |");
                printf("\n| 2.Documento del emisor                                           |");
                printf("\n| 3.Nombre del receptor                                            |");
                printf("\n| 4.Nombre del emisor                                              |");
                printf("\n| 5.Domicilio                                                      |");
                printf("\n| 6.Fecha de envio                                                 |");
                printf("\n| 7.Fecha de recepcion                                             |");
                printf("\n|------------------------------------------------------------------|\n");
                scanf("%d", &option);
            }while(control[option - 1] == 1);
        }
        
        switch(option){
            case 1: printf("|--------------------------------------|\n");
                    printf("|  Ingrese el documento del receptor:  |\n");
                    scanf("%ld", &d);
                    setDni(dev, d);
                    control[0] = 1;
                    break;

            case 2: printf("|-------------------------------------|\n");
                    printf("|  Ingrese el documento del emisor:   |\n");
                    scanf("%ld", &ds);
                    setDniRem(dev, ds);
                    control[1] = 1;
                    break;

            case 3: printf("|------------------------------------|\n");
                    printf("|  Ingrese el nombre del receptor:   |\n");
                    scanf(" %[^\n]", n);
                    for(i = 0; n[i] != '\0'; i++){
                        n[i] = toupper(n[i]);
                    }
                    setNomAp(dev, n);
                    control[2] = 1;
                    break;

            case 4: printf("|---------------------------------|\n");
                    printf("|  Ingrese el nombre del emisor:  |\n");
                    scanf(" %[^\n]", n);
                    for(i = 0; n[i] != '\0'; i++){
                        n[i] = toupper(n[i]);
                    }
                    setNomApRem(dev, n);
                    control[3] = 1;
                    break;

            case 5: printf("|-----------------------------------|\n");
                    printf("|  Ingrese la direccion del envio:  |\n");
                    scanf(" %[^\n]", n);
                    for(i = 0; n[i] != '\0'; i++){
                        n[i] = toupper(n[i]);
                    }
                    setDomicilio(dev, n);
                    control[4] = 1;
                    break;

            case 6: printf("|------------------------------|\n");
                    printf("|  Ingrese la fecha de envio:  |\n");
                    scanf(" %[^\n]", date);
                    for(i = 0; date[i] != '\0'; i++){
                        date[i] = toupper(date[i]);
                    }
                    setFechaEnv(dev, date);
                    control[5] = 1;
                    break;

            case 7: printf("|----------------------------------|\n");
                    printf("|  Ingrese la fecha de recepcion:  |\n");
                    scanf(" %[^\n]", date);
                    for(i = 0; date[i] != '\0'; i++){
                        date[i] = toupper(date[i]);
                    }
                    setFechaRec(dev, date);
                    control[6] = 1;
                    break;
        }
        cant = cant + 1;
    }
}

