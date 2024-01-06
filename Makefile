CC		=	cc
CFLAGS 	= 	-lmlx -framework OpenGL -framework AppKit

# Path: srcs
SRC		=	main.c initAndDestroyWin.c
OBJ		=	$(SRC:.c=.o)

# Path: includes
INC		=	-I./includes

# Executable name
NAME	=	RayCaster

# Execute
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) -g3 -fsanitize=address

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "demo"
	git push

.PHONY: clean fclean re