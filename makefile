
CP = cl /c /nologo 

DownloadEnergySaver.exe : main.obj dirmanagement.obj
	LINK /nologo /OUT:DownloadEnergySaver.exe main.obj dirmanagement.obj
	del *.obj

main.obj : dirmanagement.obj src/main.c
	$(CP) src/main.c

dirmanagement.obj : src/dirmanagement.c 
	$(CP) src/dirmanagement.c