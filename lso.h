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

    if(localizarLSO(*lso, dev.code, &position) == 1){  //Elemento localizado en la lista
        return 1; 
    }
    else{
        last = lso->last;  //Variable last para no modificar el valor de lso.last
        if(last < (SIZE - 1)){    //Hay espacio en la lista
            while(position <= last){   //Realizar shifteo a derecha
               lso->deliveriesList[last + 1] = lso->deliveriesList[last];
               last = last - 1;
            }
            lso->deliveriesList[position] = dev;   //Ingresar el nuevo elemento en el sitio adecuado
            lso->last = lso->last + 1;   //Actualizar el valor de lso.last
            return 2;  
        }
        else{      
            return 0;
        }
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
            printf("\n| Codigo: %s", getCodigo((*lso).deliveriesList[position]));
            printf("\n| Dni receptor: %ld", getDni((*lso).deliveriesList[position]));
            printf("\n| Dni remitente: %ld", getDniRem((*lso).deliveriesList[position]));
            printf("\n| Nombre y apellido del receptor: %s", getNomAp((*lso).deliveriesList[position]));
            printf("\n| Nombre y apellido del remitente: %s", getNomApRem((*lso).deliveriesList[position]));
            printf("\n| Domicilio del envio: %s", getDomicilio((*lso).deliveriesList[position]));
            printf("\n| Fecha de envio: %s", getFechaEnv((*lso).deliveriesList[position]));
            printf("\n| Fecha de recepcion: %s", getFechaRec((*lso).deliveriesList[position]));
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
int modificarLSO(list *lso, Deliveries dev){  //Modificar
    int position;

    if((localizarLSO(*lso, dev.code, &position)) == 1){
        lso->deliveriesList[position] = dev;
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
        printf("\n| Codigo: %s", getCodigo(lso.deliveriesList[i]));
        printf("\n| Dni receptor: %ld", getDni(lso.deliveriesList[i]));
        printf("\n| Dni remitente: %ld", getDniRem(lso.deliveriesList[i]));
        printf("\n| Nombre y apellido del receptor: %s", getNomAp(lso.deliveriesList[i]));
        printf("\n| Nombre y apellido del remitente: %s", getNomApRem(lso.deliveriesList[i]));
        printf("\n| Domicilio del envio: %s", getDomicilio(lso.deliveriesList[i]));
        printf("\n| Fecha de envio: %s", getFechaEnv(lso.deliveriesList[i]));
        printf("\n| Fecha de recepcion: %s", getFechaRec(lso.deliveriesList[i]));
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