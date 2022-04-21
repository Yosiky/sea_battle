CC		=	gcc

DIR_SRC	=	src
DIR_OBJ	=	obj

SRC		=	main

OBJ		=	$(addprefix $(DIR_OBJ)/,$(SRC:=.o))

NAME	=	sea_battle

.PHONY:	all clean fclean re

all:	$(DIR_OBJ)
	$(MAKE) -j $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	$(CC) $< -c -o $@

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $@

$(DIR_OBJ):
	mkdir -p $@

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:		fclean \
		all
