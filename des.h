#ifndef INCLUDE
    #define INCLUDE
    #include <Windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
#endif

#define gb_to_mb(g) \
    g * 1000000000

int VerifyDirSizeChanges(char *);
int OpenDir(char *);
LONGLONG ActualDirSize(char *);