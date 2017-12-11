NAME=control
all: $(NAME).o client.o
	gcc -o $(NAME) $(NAME).o
	gcc -o client client.o

$(NAME).o: $(NAME).c
	gcc -c $(NAME).c

client.o: client.c
	gcc -c client.c

run: all
	./$(NAME) -c 4
	./$(NAME) -v
	./$(NAME) -c 3
	./$(NAME) -v
	./$(NAME) -r

clean:
	rm -f ./$(NAME)
	rm -f ./$(NAME).o
	rm -f story.txt
	rm *~
