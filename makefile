a.out : main.o display.o create.o save.o search.o update.o validation.o 
	gcc -o a.out main.o display.o create.o save.o search.o update.o validation.o 
main.o: main.c
	gcc -c main.c
display.o : display.c
	gcc -c display.c
create.o : create.c
	gcc -c create.c
save.o : save.c
	gcc -c save.c
search.o : search.c
	gcc -c search.c
update.o : update.c
	gcc -c update.c
validation.o : validation.c
	gcc -c validation.c
clean : 
	rm -f *.o a.out