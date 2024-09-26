#include "des.h"

#define MAXLEN 100

int main() {
    char dirpath[MAXLEN];
    char temp[MAXLEN];
    long double s;
    int downloaded = FALSE;

    GetUserInput(dirpath, MAXLEN, "Ingresa direccion de directorio a revisar:");
    GetUserInput(temp, MAXLEN, "Ingresa tamaño esperado en gigabytes, usando '.' como decimal:");
    s = atof(temp) * 1000000000; // Tamaño en bytes

    while (!downloaded) {
        if (VerifyDirSize(dirpath) && ActualDirSize(dirpath) >= s) {
            downloaded = TRUE;
            printf("LISTO\n");
        }    
    }
    //system("shutdown /s");
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