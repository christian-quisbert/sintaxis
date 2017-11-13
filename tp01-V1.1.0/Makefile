SRC = $(wildcard *.c)
HEADER = $(wildcard *.h)
COMPRESSED = TP01.tar.gz
OBJ = $(SRC:.c=.o)
EJECUTABLE = programa
LIBRERIAS = -lm

Link:$(OBJ)
	gcc $(OBJ) -o $(EJECUTABLE)
%.o:%.c
	gcc -c $< -o $@

clean:
	rm ./*.o programa

comprimir:
	tar zcvf $(COMPRESSED) $(SRC) $(HEADER)
