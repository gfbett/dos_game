#include "log.h"
#include <stdio.h>

FILE *logfile;

/*
    Inicialización archivo de log
*/
void initLog() {
    logfile = fopen("log.txt", "at");
}

/*
    Agrega un string a un mensaje de log, agregando un newline
*/
void log(char* message){

    fprintf(logfile, "%s\n", message);
    fflush(logfile);
}

/*
    Cierra el archivo de logs
*/
void closeLog(){
    fclose(logfile);
}