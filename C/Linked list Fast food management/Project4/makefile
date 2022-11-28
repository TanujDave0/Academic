Project4: main.o channel.o linked_list.o
	gcc -o Project4 main.o channel.o linked_list.o
	clear

main.o: main.c linked_list.h
	gcc -c main.c

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

channel.o: channel.c linked_list.h
	gcc -c channel.c

