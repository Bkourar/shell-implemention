NAME = minishell
DIR1 = prs
DIR2 = exec
DIR3 = expand
SRCS1 = $(wildcard $(DIR1)/*.c)
SRCS2 = $(wildcard $(DIR2)/*.c)
SRCS3 = $(wildcard $(DIR3)/*.c)

SRCS = $(SRCS1) $(SRCS2) $(SRCS3) main.c
OBJS = $(SRCS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Default target
all: $(NAME)

# Linking the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

# Compiling .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
