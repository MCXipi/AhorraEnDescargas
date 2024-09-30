#include "des.h"

int VerifyDirSizeChanges(char *dirpath, int ending) {
    // Funcion que revisa con las funciones de win32 si el directorio en dirpath cambió de tamaño.
    // Crea al llamar por primera vez a la funcion para crear en HANDLE de notificacion, y luego sigue los cambios con FindNextChangeNotification
    // Espera infinitamente hasta que cambie, pero si ending es TRUE, entonces se espera a que el resultado sea WAIT_TIMEOUT,
    // cuando despues de 10 minutos no han habido más cambios, y posiblemente haya terminado la descarga.

    static HANDLE hFileChangeNotify;

    if (hFileChangeNotify == NULL) { // Problema del else colgante al haber if-else anidados en if o else.
        if ((hFileChangeNotify = FindFirstChangeNotificationA((LPCSTR) dirpath, TRUE, FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_FILE_NAME)) == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Directorio invalido o error al seguir cambios.\n");
            exit(1);
        }
    }
    else
        if (!FindNextChangeNotification(hFileChangeNotify)) {
            fprintf(stderr, "Error siguiendo cambios.\n");
            exit(1);
        }

    while(WaitForSingleObject(hFileChangeNotify, 600000) != (ending ? WAIT_TIMEOUT : WAIT_OBJECT_0))
        ;
    return 0;
}

LONGLONG ActualDirSize(char *dirpath) {
    // Funcion que retorna el tamaño actual del directorio en dirpath
    // Los directorios por si mismos NO tienen tamaño, por lo que se calcula el tamaño total sumando el de cada archivo individual
    // Se llama recursivamente en el caso de que el archivo sea un directorio

    HANDLE hFileSearch;
    WIN32_FIND_DATAA sFileData;
    LONGLONG sFileSize = 0;
    LARGE_INTEGER sSizeStruct;
    char sPathCopy[MAX_PATH];
    char sRecursivePath[MAX_PATH];

    sprintf(sPathCopy, "%s\\*", dirpath);
    
    if ((hFileSearch = FindFirstFileA((LPCSTR) sPathCopy, (LPWIN32_FIND_DATAA) &sFileData)) == INVALID_HANDLE_VALUE)
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            return sFileSize;
        else {
            fprintf(stderr, "Error en busqueda de archivo 1 en directorio %s.\n", sPathCopy);
            exit(1);
        }
    
    do {
        if (!(sFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            sSizeStruct.HighPart = sFileData.nFileSizeHigh;
            sSizeStruct.LowPart = sFileData.nFileSizeLow;
            sFileSize += sSizeStruct.QuadPart;
        }
        else if (strcmp(sFileData.cFileName, ".") != 0 && strcmp(sFileData.cFileName, "..") != 0){ // Ignorar si el archivo encontrado es el directorio actual o padre
            sprintf(sRecursivePath, "%s\\%s", dirpath, sFileData.cFileName);
            sFileSize += ActualDirSize(sRecursivePath);
        }
    }
    while (FindNextFileA(hFileSearch, (LPWIN32_FIND_DATAA) &sFileData));

    if (GetLastError() == ERROR_NO_MORE_FILES)
        return sFileSize;
    else {
        fprintf(stderr, "Error en busqueda de archivo 2.\n");
        exit(1);
    }
}

int OpenDir(char *dirpath) {
    // Funcion que abre directorio ubicado en dirpath.
    // Utilizado para comprobar que la carpeta realmente exista.
    // Otorga permisos de FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE para permitir la descarga.
    // Retorna 0 si hay un error. Retorna 1 si se abrió sin problemas.
    
    if (CreateFileA((LPCSTR) dirpath, FILE_GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL) == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error abriendo directorio. Ingresaste una ruta correcta?\n");
        return 0;
    }
    return 1;
}