NAME=control
all: $(NAME).o
	gcc -o $(NAME) $(NAME).o

$(NAME).o: $(NAME).c
	gcc -c $(NAME).c


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
