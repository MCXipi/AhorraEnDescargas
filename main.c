#include "des.h"

#define MAXLEN 100
#define TIMELEN 250

int main() {
    char dirpath[MAXLEN], temp[MAXLEN], sTime[MAXLEN], *GetTime(char *, int);
    long double s;
    void GetUserInput(char *, int, char *), TrimStr(char *);

    do 
        GetUserInput(dirpath, MAXLEN, "Ingresa direccion de directorio a revisar:");
    while (!OpenDir(dirpath));

    GetUserInput(temp, MAXLEN, "Ingresa tamaño esperado en gigabytes, usando '.' como decimal:");
    s = gb_to_mb(atof(temp)); // Tamaño en bytes

    while (TRUE) {
        // Mientras HAYAN cambios cada 5 minutos no hacer nada. Si verifydirsize NO cambia en 5 minutos, verificar el tamaño y si supera al esperado, apagar. Si no, continuar el bucle.
        if (!VerifyDirSizeChanges(dirpath) && ActualDirSize(dirpath) >= s)
            printf("DESCARGA LISTA!\n");
        fprintf(stdout, "%s El archivo aun esta en descarga.\n", GetTime(sTime, MAXLEN));
    }
    return 0;
}

void GetUserInput(char *buf, int max, char *message) {
    // Funcion para obtener input desde el usuario entregando el mensaje message-
    // Almacena el input en buf considerando el limite max.

    fprintf(stdout, "%s", message);
    fgets(buf, max, stdin);
    TrimStr(buf);
}

void TrimStr(char *pStr) {
    // Funcion para limpiar el '\n' al final de un string.

    char *piStr = pStr;

    for (piStr; *piStr != '\n'; ++piStr)
        ;
    if (*piStr == '\n')
        *piStr = '\0';
}

char *GetTime(char *strTime, int max) {
    // Funcion que escribe la fecha en formato dia/mes/año hora:minuto en la cadena en temp.
    // Intenta obtener la fecha en un bucle infinito.
    // Comprueba que el largo de la fecha sea suficiente para el maximo de tamaño establecido por max.
    // Retorna NULL si no hay suficiente espacio, o strTime si fue satisfactorio.

    struct tm *TimeInfo;
    time_t tActualTime;
    char temp[TIMELEN];

    while (time(&tActualTime) == -1)
        fprintf(stderr, "Error obteniendo fecha. Intentando denuevo. (CTRL + C para salir).\n");

    TimeInfo = localtime(&tActualTime);
    
    sprintf(temp, "%d/%d/%d %d:%d", TimeInfo->tm_mday, TimeInfo->tm_mon + 1, TimeInfo->tm_year - 100, TimeInfo->tm_hour, TimeInfo->tm_min);
    if (sizeof(temp) >= max)
        return NULL;

    sprintf(strTime, "%s", temp);
    return strTime;
}