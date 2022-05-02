##
## SYSNAV PROJECT, 2022
## sysnavTask05
## File description:
## Makefile
##

SRC	=	$(shell echo src/*.c src/error_handling/*.c src/help/*.c src/solver/*.c src/utils/*.c)

INC	=	-I include

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	$(INC) -g

NAME	=	task05

all:		$(OBJ)
	@gcc -g -o $(NAME) $(OBJ) $(CFLAGS)
	@make -s clean

clean:
	@rm -f $(OBJ)

fclean:		clean
	@rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re