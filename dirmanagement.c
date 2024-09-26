#include "des.h"

int VerifyDirSize(char *dirpath) {
    // Funcion que revisa con las funciones de win32 si el directorio en dirpath cambió de tamaño.
    // Espera 5 minutos a que cambie.
    // Si cambia retorna 1, si no, 0 (Incluyendo cualquier error en espera).

    HANDLE hFileChangeNotify;
    DWORD rWait;

    if ((hFileChangeNotify = FindFirstChangeNotification((LPCWSTR) dirpath, TRUE, FILE_NOTIFY_CHANGE_SIZE)) == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Directorio invalido o error al seguir cambios.\n");
        exit(1);
    }

    rWait = WaitForSingleObject(hFileChangeNotify, 300000);
    FindCloseChangeNotification(hFileChangeNotify);
    return (rWait == WAIT_OBJECT_0 ? 1 : 0);
}

unsigned long long ActualDirSize(char *dirpath) {
    // Funcion que retorna el tamaño actual del directorio en dirpath

    // CreateFile abre directorios para luego usar GeteFileSize
}