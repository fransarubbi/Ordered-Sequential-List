#ifndef DELIVERIES_H_INCLUDED
#define DELIVERIES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <malloc.h>


#define CODE 8
#define NAME 81
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

#endif