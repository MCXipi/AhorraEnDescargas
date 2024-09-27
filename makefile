
CP = cl /c /nologo

DownloadEnergySaver.exe : main.obj dirmanagement.obj
	LINK /nologo /OUT:DownloadEnergySaver.exe main.obj dirmanagement.obj
	del *.obj

main.obj : dirmanagement.obj main.c
	$(CP) main.c dirmanagement.obj

dirmanagement.obj : dirmanagement.c 
	$(CP) dirmanagement.c