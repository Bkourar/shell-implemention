NAME = minishell

SRC_FILES = main.c pars_word.c list_tools.c ft_split.c pars_command.c free_likend.c syntax_errors.c parsing.c checker.c process_argement.c file_descriptor.c allocation.c here_doc.c get_next_line.c get_next_utlis.c checker_tools.c general_tools.c process.c m.sh_tools.c

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -fsanitize=address -g -Wall -Werror -Wextra

%.o : %.c minishell.h minishell1.h
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