post : main.o menu.o tape.o comand.o run.o
	gcc -o post main.o menu.o tape.o comand.o run.o

main.o : main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

menu.o : menu.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o menu.o menu.c

tape.o : tape.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o tape.o tape.c

comand.o : comand.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o comand.o comand.c

run.o : run.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o run.o run.c


