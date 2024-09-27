#include "des.h"

HANDLE hDir;

int VerifyDirSizeChanges(char *dirpath) {
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

LONGLONG ActualDirSize(char *dirpath) {
    // Funcion que retorna el tamaño actual del directorio en dirpath
    LONGLONG DirSize;
    LARGE_INTEGER uSize;

    if (!GetFileSizeEx(hDir, (PLARGE_INTEGER) &uSize))
        return 0;
    
    DirSize = uSize.QuadPart;
    return DirSize;
}

int OpenDir(char *dirpath) {
    // Funcion que abre directorio ubicado en dirpath, y lo asigna a un HANDLE para uso en las demás funciones
    // Retorna 0 si hay un error. Retorna 1 si se abrió sin problemas.

    if ((hDir = CreateFileA((LPCSTR) dirpath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL)) == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error abriendo directorio. ¿Ingresaste una ruta correcta?\n");
        return 0;
    }
    return 1;
}