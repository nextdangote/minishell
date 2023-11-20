NAME		:= lumumbash

CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra 
LDFLAGS 	:= -lreadline -lncurses

SRCS		:=	main.c\
				exec.c\
				tokenizer.c\
				parser.c\
				builtins.c\

OBJS		:=	$(SRCS:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $@ $^ $(LDFLAGS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME)


.PHONY: all clean fclean re valgrind
