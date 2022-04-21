CC		=	gcc

DIR_SRC	=	src
DIR_OBJ	=	obj

SRC		=	main

OBJ		=	$(addprefix $(DIR_OBJ)/,$(SRC:=.o))

NAME	=	sea_battle

.PHONY:	$(NAME) $(DIR_OBJ) all clean fclean re

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	$(CC) $< -c -o $@

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $@

$(DIR_OBJ):
	mkdir -p $@

all:	$(DIR_OBJ)
	$(MAKE) -j $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:		fclean \
		all
