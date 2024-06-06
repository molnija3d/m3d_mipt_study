all: prg	
	.\bin\tmp_stat.exe -f .\bin\temperature_small.csv -m 2
prg: tmp_stat.o temp_sys.o temp_api.o
	gcc -o .\bin\tmp_stat tmp_stat.o temp_sys.o temp_api.o

tmp_stat.o: .\src\tmp_stat.c
	gcc -c -o tmp_stat.o .\src\tmp_stat.c -I .\include\

temp_sys.o: .\src\temp_sys.c
	gcc -c -o temp_sys.o .\src\temp_sys.c -I .\include\

temp_api.o: .\src\temp_api.c
	gcc -c -o temp_api.o .\src\temp_api.c -I .\include\

clean: 
	del .\bin\*.exe 
	del *.o   