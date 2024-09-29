NAME = minishell
DIR1 = tokenisation
DIR2 = parsing
DIR3 = expand
DIR4 = exec
DIR5 = signal
SRCS1 = $(wildcard $(DIR1)/*.c)
SRCS2 = $(wildcard $(DIR2)/*.c)
SRCS3 = $(wildcard $(DIR3)/*.c)
SRCS4 = $(wildcard $(DIR4)/*.c)
SRCS5 = $(wildcard $(DIR5)/*.c)

SRCS = $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) main.c
OBJS = $(SRCS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Default target
all: $(NAME)

# Linking the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -fsanitize=address

# Compiling .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

# Cleaning object files
clean:
	rm -f $(OBJS)

# Cleaning everything
fclean: clean
	rm -f $(NAME)

# Rebuilding everything
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re