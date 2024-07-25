NAME = minishell

SRC_FILES = main.c pars_word.c list_tools.c ft_split.c pars_command.c free_likend.c syntax_errors.c parsing.c
 
OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -fsanitize=address -g -Wall -Werror -Wextra 

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) -lreadline

clean :
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean 