NAME1=control
NAME2=client
all: $(NAME1).o $(NAME2).o
	gcc -o $(NAME1) $(NAME1).o
	gcc -o $(NAME2) $(NAME2).o

$(NAME).o: $(NAME1).c $(NAME2).c work15.h
	gcc -c $(NAME1).c
	gcc -c $(NAME2).c

clean:
	rm -f ./$(NAME1)
	rm -f ./$(NAME1).o
	rm -f ./$(NAME2)
	rm -f ./$(NAME2).o
	rm -f story.txt
	rm *~
