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
                    mostrarLSO(lso);
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

    int highValue, enter;

    printf("\n|--------------------------------|");
    printf("\n|-------- Cargando Datos --------|");
    printf("\n|--------------------------------|\n\n");
    loadDeliveries(dev);
    highValue = altaLSO(lso, *dev);
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
                *cant = *cant + 1;
                break;
    }

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
    int highValue, enter, i;

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
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);
            
            fscanf(preload, "%ld\n", &dni);
            dev.doc = dni;
            
            fscanf(preload, " %[^\n]\n", nameSender);
            for(i = 0; nameSender[i] != '\0'; i++){
                nameSender[i] = toupper(nameSender[i]);
            }
            strcpy(&dev.nameSender, nameSender);
            
            fscanf(preload, " %[^\n]\n", addres);
            for(i = 0; addres[i] != '\0'; i++){
                addres[i] = toupper(addres[i]);
            }
            strcpy(&dev.address, addres);
            
            fscanf(preload, "%ld\n", &dniS);
            dev.docSender = dniS;

            fscanf(preload, " %[^\n]\n", name);
            for(i = 0; name[i] != '\0'; i++){
                name[i] = toupper(name[i]);
            }
            strcpy(&dev.name, name);
            
            fscanf(preload, " %[^\n]\n", dateS);
            for(i = 0; dateS[i] != '\0'; i++){
                dateS[i] = toupper(dateS[i]);
            }
            strcpy(&dev.dateSender, dateS);

            fscanf(preload, " %[^\n]\n", dateR);
            for(i = 0; dateR[i] != '\0'; i++){
                dateR[i] = toupper(dateR[i]);
            }
            strcpy(&dev.dateReceived, dateR);

            highValue = altaLSO(lso, dev);

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
            strcpy(&dev.code, code);
            evocationValue = evocacionLSO(*lso, &dev);

            if(evocationValue == 1){
                lowValue = bajaLSO(lso, dev);
                switch(lowValue){
                    case 1: printf("|-----------------------------------------------------|\n");
                            printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                            printf("|-----------------------------------------------------|\n\n");
                            j++;
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
                j++;
            }
        }while(j < n);
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
    strcpy(&d.code, code);

    changeValue = modificarLSO(lso, &d);
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
    strcpy(&d.code, code);

    evocationValue = evocacionLSO(lso, &d);
    if(evocationValue == 1){
        printf("\n|---------------------------------|");
        printf("\n    INFORMACION DEL ENVIO %s", code);
        printf("\n|---------------------------------|\n\n");
        printf("\n| Codigo: %s", d.code);
        printf("\n| Dni receptor: %ld", d.doc);
        printf("\n| Dni remitente: %ld", d.docSender);
        printf("\n| Nombre y apellido del receptor: %s", d.name);
        printf("\n| Nombre y apellido del remitente: %s", d.nameSender);
        printf("\n| Domicilio del envio: %s", d.address);
        printf("\n| Fecha de envio: %s", d.dateSender);
        printf("\n| Fecha de recepcion: %s", d.dateReceived);
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
    strcpy(dev->code, c);

    do{
        printf("|------------------------------------|\n");
        printf("| Ingrese el documento del receptor: |\n");
        scanf("%ld", &d);
    }while(d < 0 || d > 99999999);  //rango de documento entre 4.000.000 hasta 50.000.000
    dev->doc = d;

    do{
        printf("|----------------------------------|\n");
        printf("| Ingrese el documento del emisor: |\n");
        scanf("%ld", &d);
    }while(d < 0 || d > 99999999);  //rango de documento entre 4.000.000 hasta 50.000.000
    dev->docSender = d;

    printf("|---------------------------------|\n");
    printf("| Ingrese el nombre del receptor: |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    strcpy(dev->name, n);

    printf("|-------------------------------|\n");
    printf("| Ingrese el nombre del emisor: |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    strcpy(dev->nameSender, n);

    printf("|-----------------------------------|\n");
    printf("|  Ingrese la direccion del envio:  |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    strcpy(dev->address, n);

    printf("|------------------------------|\n");
    printf("|  Ingrese la fecha de envio:  |\n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    strcpy(dev->dateSender, date);

    printf("|----------------------------------|\n");
    printf("|  Ingrese la fecha de recepcion:  |\n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    strcpy(dev->dateReceived, date);
}