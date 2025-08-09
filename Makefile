CC = gcc
CFLAGS = -Wall -Werror -Wextra

programa1:p1.o Pilha.o
	$(CC) $(CFLAGS) -o $@ $^
programa2:p2.o Pilha.o
	$(CC) $(CFLAGS) -o $@ $^
programa3: p3.o Pilha.o
	$(CC) $(CFLAGS) -o $@ $^

p1.o:programa1.c Pilha.h
	$(CC) $(CFLAGS) -c $< -o $@

p2.o: programa2.c Pilha.h
	$(CC) $(CFLAGS) -c $< -o $@

p3.o: programa3.c Pilha.h
	$(CC) $(CFLAGS) -c $< -o $@
	
Pilha.o: Pilha.c Pilha.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
