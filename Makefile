CC=gcc
SQL3DIR=deps/sqlite3/

main: main.o sqlite.o
	$(CC) main.o sqlite.o -o main.elf

main.o: main.c
	$(CC) -c main.c -I$(SQL3DIR) main.o

sqlite.o: $(SQL3DIR)sqlite3.c 
	$(CC) -c $(SQL3DIR)sqlite3.c -o sqlite.o

clean:
	rm -f main.elf main.o sqlite.o
