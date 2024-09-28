#ifndef INCLUDE
    #define INCLUDE
    #include <Windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>
#endif

#define gb_to_b(g) \
    g * 1000000000

int VerifyDirSizeChanges(char *, int);
int OpenDir(char *);
LONGLONG ActualDirSize(char *);