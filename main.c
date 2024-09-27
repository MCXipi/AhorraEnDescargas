#include "des.h"

#define MAXLEN 100

int main() {
    char dirpath[MAXLEN];
    char temp[MAXLEN];
    long double s;

    do 
        GetUserInput(dirpath, MAXLEN, "Ingresa direccion de directorio a revisar:");
    while (!OpenDir(dirpath));

    GetUserInput(temp, MAXLEN, "Ingresa tamaño esperado en gigabytes, usando '.' como decimal:");
    s = gb_to_mb(atof(temp)); // Tamaño en bytes

    while (TRUE) {
        // Mientras HAYAN cambios cada 5 minutos no hacer nada. Si verifydirsize NO cambia en 5 minutos, verificar el tamaño y si supera al esperado, apagar. Si no, continuar el bucle.
        if (!VerifyDirSizeChanges(dirpath) && ActualDirSize(dirpath) >= s)
            printf("DESCARGA LISTA!\n");
    }
    return 0;
}

void GetUserInput(char *buf, int max, char *message) {
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