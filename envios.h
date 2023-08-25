#ifndef DELIVERIES_H_INCLUDED
#define DELIVERIES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define CODE 7
#define NAME 80
#define DATE 10

typedef struct{
    char code[CODE];
    long doc, docSender;
    char name[NAME];
    char nameSender[NAME];
    char address[NAME];
    char dateSender[DATE];
    char dateReceived[DATE];
}Deliveries;


//Setters 
void setCodigo(Deliveries *d, char c[]){
    strcpy((*d).code, c);
}

void setDni(Deliveries *d, long dni){
    (*d).doc = dni;
}

void setDniRem(Deliveries *d, long dni){
    (*d).docSender = dni;
}

void setNomAp(Deliveries *d, char n[]){
    strcpy((*d).name, n);
}

void setNomApRem(Deliveries *d, char n[]){
    strcpy((*d).nameSender, n);
}

void setDomicilio(Deliveries *d, char a[]){
    strcpy((*d).address, a);
}

void setFechaEnv(Deliveries *d, char f[]){
    strcpy((*d).dateSender, f);
}

void setFechaRec(Deliveries *d, char f[]){
    strcpy((*d).dateReceived, f);
}


//Getters
void showDeliveries(Deliveries d){

    printf("Codigo: %s\n",d.code);
    printf("DNI: %ld\n",d.doc);
    printf("DNI Remitente: %ld\n",d.docSender);
    printf("Nombre y apellido del receptor: %s\n",d.name);
    printf("Nombre y apellido del remitente: %s\n",d.nameSender);
    printf("Domicilio de envio: %s\n",d.address);
    printf("Fecha de envio: %s\n",d.dateSender);
    printf("Fecha de recepcion: %s\n\n",d.dateReceived);
}

#endif