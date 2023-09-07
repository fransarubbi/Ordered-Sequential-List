#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#define SIZE 300
#include "envios.h"


typedef struct{
    Deliveries deliveriesList[SIZE];
    int last;
}list;


void init(list *lso){  //Inicializar la lista es poner last en -1 (vacia)
    lso->last = -1;
}


/*
Codificacion de Localizacion:
return 0 - Fracaso, no esta el elemento
return 1 - Exito
*/
int localizarLSO(list lso, char c[], int *position){   //Localizar 
    int i = 0;

    while((i <= lso.last) && strcmp(lso.deliveriesList[i].code, c) < 0){   //Porque esta ordenada de menor a mayor
        i++;
    }

    *position = i;  
    if(strcmp(lso.deliveriesList[i].code, c) == 0){  
        return 1;
    }
    else{
        return 0;
    } 
}


/*
Codificacion del Alta:
return 0 - Fracaso por lista llena
return 1 - Fracaso por elemento existente
return 2 - Exito
*/
int altaLSO(list *lso, Deliveries dev){    //Alta
    int position, last;

    last = lso->last;  //Variable last para no modificar el valor de lso.last

    if(last < (SIZE - 1)){
        if(localizarLSO(*lso, dev.code, &position) == 1){  //Elemento localizado en la lista
            return 1; 
        }
        else{
            //El elemento no existe en la lista
            while(position <= last){   //Realizar shifteo a derecha
                lso->deliveriesList[last + 1] = lso->deliveriesList[last];
                last = last - 1;
            }
            lso->deliveriesList[position] = dev;   //Ingresar el nuevo elemento en el sitio adecuado
            lso->last = lso->last + 1;   //Actualizar el valor de lso.last
            return 2; 
        }
    }
    else{
        return 0;  //No hay espacio en la lista
    }
}


/*
Codificacion de Baja:
return 0 - Fracaso por elemento inexistente en lista
return 1 - Fracaso por no confirmar la baja
return 2 - Exito
*/
int bajaLSO(list *lso, Deliveries dev){      //Baja
    int position, ok;
    
    if(localizarLSO(*lso, dev.code, &position) == 0){
        return 0;   //No podemos dar de baja porque no existe el elemento
    }
    else{
        do{
            printf("\n===========================================================");
            printf("\n            Esta por eliminar datos. Estos son:         ");
            printf("\n===========================================================\n");
            printf("\n| Codigo: %s", lso->deliveriesList[position].code);
            printf("\n| Dni receptor: %ld", lso->deliveriesList[position].doc);
            printf("\n| Dni remitente: %ld", lso->deliveriesList[position].docSender);
            printf("\n| Nombre y apellido del receptor: %s", lso->deliveriesList[position].name);
            printf("\n| Nombre y apellido del remitente: %s", lso->deliveriesList[position].nameSender);
            printf("\n| Domicilio del envio: %s", lso->deliveriesList[position].address);
            printf("\n| Fecha de envio: %s", lso->deliveriesList[position].dateSender);
            printf("\n| Fecha de recepcion: %s", lso->deliveriesList[position].dateReceived);
            printf("\n===========================================================");
            printf("\n                    ¿Esta de acuerdo?                    ");
            printf("\n             0.No                        1.Si            ");
            printf("\n===========================================================\n");
            scanf("%d", &ok);
        }while(ok < 0 || ok > 1);

        if(ok == 1){
            if(position == lso->last){
                lso->last = lso->last - 1;
            }
            else{
                while(position < lso->last){
                    lso->deliveriesList[position] = lso->deliveriesList[position + 1];
                    position = position + 1;
                }
                lso->last = lso->last - 1;
            }
            return 2;  //Baja exitosa
        }
        else{
            return 1;
        }
    }
}


/*
Codificacion de la Evocacion:
return 0 - Fracaso por no existir coincidencias
return 1 - Exito
*/
int evocacionLSO(list lso, Deliveries *dev){    //Evocacion
    int position;

    if((localizarLSO(lso, (*dev).code, &position)) == 0){
        return 0;
    }
    else{
        strcpy((*dev).code, lso.deliveriesList[position].code);
        (*dev).doc = lso.deliveriesList[position].doc;
        (*dev).docSender = lso.deliveriesList[position].docSender;
        strcpy((*dev).name, lso.deliveriesList[position].name);
        strcpy((*dev).nameSender, lso.deliveriesList[position].nameSender);
        strcpy((*dev).address, lso.deliveriesList[position].address);
        strcpy((*dev).dateSender, lso.deliveriesList[position].dateSender);
        strcpy((*dev).dateReceived, lso.deliveriesList[position].dateReceived);
        return 1;
    }
}


/*
Codificacion de Pertenece:
return 0 - Fracaso por no existir elemento
return 1 - Fracaso por existir elemento, pero no coincide con los atributos
return 2 - Exito
*/
int perteneceLSO(Deliveries dev, list lso){   //Pertenece
    int position;
    
    if((localizarLSO(lso, dev.code, &position)) == 1){
        int a = strcmp((dev).code, lso.deliveriesList[position].code);
        int b = strcmp((dev).name, lso.deliveriesList[position].name);
        int c = strcmp((dev).nameSender, lso.deliveriesList[position].nameSender);
        int d = strcmp((dev).address, lso.deliveriesList[position].address);
        int e = strcmp((dev).dateSender, lso.deliveriesList[position].dateSender);
        int f = strcmp((dev).dateReceived, lso.deliveriesList[position].dateReceived);

        if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && (dev.doc == lso.deliveriesList[position].doc) && (dev.docSender == lso.deliveriesList[position].docSender)){
            return 2;
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
    }
}


/*
Codificacion del modificar:
return 0 - Fracaso por elemento inexistente en lista
return 1 - Exito en la modificacion
*/
int modificarLSO(list *lso, Deliveries *dev){  //Modificar
    int position, i, j = 0, option;
    char n[NAME], date[DATE];

    if((localizarLSO(*lso, (*dev).code, &position)) == 1){
       
        (*dev) = lso->deliveriesList[position];

        printf("\n==================================================================");
        printf("\n               Esta por modificar datos. Estos son:         ");
        printf("\n==================================================================\n");
        printf("\n| Codigo: %s", lso->deliveriesList[position].code);
        printf("\n| Dni receptor: %ld", lso->deliveriesList[position].doc);
        printf("\n| Dni remitente: %ld", lso->deliveriesList[position].docSender);
        printf("\n| Nombre y apellido del receptor: %s", lso->deliveriesList[position].name);
        printf("\n| Nombre y apellido del remitente: %s", lso->deliveriesList[position].nameSender);
        printf("\n| Domicilio del envio: %s", lso->deliveriesList[position].address);
        printf("\n| Fecha de envio: %s", lso->deliveriesList[position].dateSender);
        printf("\n| Fecha de recepcion: %s", lso->deliveriesList[position].dateReceived);
        printf("\n===================================================================\n");

        do{
            do{
                printf("\n");
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

            switch(option){
                case 1: printf("|--------------------------------------|\n");
                        printf("|  Ingrese el documento del receptor:  |\n");
                        scanf("%ld", &(*dev).doc);
                        break;

                case 2: printf("|-------------------------------------|\n");
                        printf("|  Ingrese el documento del emisor:   |\n");
                        scanf("%ld", &(*dev).docSender);
                        break;

                case 3: printf("|------------------------------------|\n");
                        printf("|  Ingrese el nombre del receptor:   |\n");
                        scanf(" %[^\n]", n);
                        for(i = 0; n[i] != '\0'; i++){
                            n[i] = toupper(n[i]);
                        }
                        strcpy((*dev).name, n);
                        break;

                case 4: printf("|---------------------------------|\n");
                        printf("|  Ingrese el nombre del emisor:  |\n");
                        scanf(" %[^\n]", n);
                        for(i = 0; n[i] != '\0'; i++){
                            n[i] = toupper(n[i]);
                        }
                        strcpy((*dev).nameSender, n);
                        break;

                case 5: printf("|-----------------------------------|\n");
                        printf("|  Ingrese la direccion del envio:  |\n");
                        scanf(" %[^\n]", n);
                        for(i = 0; n[i] != '\0'; i++){
                            n[i] = toupper(n[i]);
                        }
                        strcpy((*dev).address, n);
                        break;

                case 6: printf("|------------------------------|\n");
                        printf("|  Ingrese la fecha de envio:  |\n");
                        scanf(" %[^\n]", date);
                        for(i = 0; date[i] != '\0'; i++){
                            date[i] = toupper(date[i]);
                        }
                        strcpy((*dev).dateSender, date);
                        break;

                case 7: printf("|----------------------------------|\n");
                        printf("|  Ingrese la fecha de recepcion:  |\n");
                        scanf(" %[^\n]", date);
                        for(i = 0; date[i] != '\0'; i++){
                            date[i] = toupper(date[i]);
                        }
                        strcpy((*dev).dateReceived, date);
                        break;
            }

            do{
                printf("\n");
                printf("|---------------------------------------------|\n");
                printf("| Ingrese 1 si desea seguir modificando datos |\n");
                printf("|---------------------------------------------|\n");
                printf("|          Ingrese 0 si desea salir           |\n");
                printf("|---------------------------------------------|\n");
                scanf("%d", &j);
            }while(j > 1 || j < 0);

        }while(j == 1);
        
        lso->deliveriesList[position] = (*dev);
        return 1;    //Modificacion exitosa
    }
    else{
        return 0;   //No podemos modificar porque no existe el elemento
    }
}


void mostrarLSO(list lso){      //Mostrar
    int i, enter, cont = 0;

    for(i = 0; i <= lso.last; i++){
        printf("\n|========================================|");
        printf("\n| Codigo: %s", lso.deliveriesList[i].code);
        printf("\n| Dni receptor: %ld", lso.deliveriesList[i].doc);
        printf("\n| Dni remitente: %ld", lso.deliveriesList[i].docSender);
        printf("\n| Nombre y apellido del receptor: %s", lso.deliveriesList[i].name);
        printf("\n| Nombre y apellido del remitente: %s", lso.deliveriesList[i].nameSender);
        printf("\n| Domicilio del envio: %s", lso.deliveriesList[i].address);
        printf("\n| Fecha de envio: %s", lso.deliveriesList[i].dateSender);
        printf("\n| Fecha de recepcion: %s", lso.deliveriesList[i].dateReceived);
        printf("\n|========================================|\n\n");
        cont++;

        if(cont == 3){
            cont = 0;
            do{
                printf("\n|---------------------------------|");
                printf("\n|     Ingrese 1 para continuar    |");
                printf("\n|---------------------------------|\n");
                scanf("%d", &enter);
            }while(enter != 1);
        }
    }
}


#endif