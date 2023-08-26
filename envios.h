#ifndef DELIVERIES_H_INCLUDED
#define DELIVERIES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <malloc.h>


#define CODE 8
#define NAME 80
#define DATE 11


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
char* getCodigo(Deliveries d){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(d.code));
    strcpy(aux, d.code);
    return aux;
}


long getDni(Deliveries d){
    return d.doc;
}


long getDniRem(Deliveries d){
    return d.docSender;
}


char* getNomAp(Deliveries d){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(d.name));
    strcpy(aux, d.name);
    return aux;
}


char* getNomApRem(Deliveries d){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(d.nameSender));
    strcpy(aux, d.nameSender);
    return aux;
}


char* getDomicilio(Deliveries d){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(d.address));
    strcpy(aux, d.address);
    return aux;
}


char* getFechaEnv(Deliveries d){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(d.dateSender));
    strcpy(aux, d.dateSender);
    return aux;
}


char* getFechaRec(Deliveries d){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(d.dateReceived));
    strcpy(aux, d.dateReceived);
    return aux;
}

#endif