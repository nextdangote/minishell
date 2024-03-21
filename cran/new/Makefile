NAME		:= lumumbash

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra

BUILTINS	:=	builtins/echo.c \
				builtins/exit.c \
				builtins/pwd.c \
				builtins/env.c \
				builtins/export.c \
				builtins/unset.c \

CLEANERS	:=	cleaners/clean.c \
				cleaners/free.c \

EXEC		:=	exec/checks.c \
				exec/errors.c \
				exec/exec_redir.c \
				exec/exec_simple.c \
				exec/exec_utils.c \
				exec/exec.c \
				exec/pipes_exec.c \
				exec/tree.c \

HELP		:=  help/ft_helpers.c \
				help/ft_exphelp.c \

PARSER		:=	parser/nodes.c \
				parser/parser_errors.c \
				parser/parser_helpers.c \
				parser/parser_utils.c \
				parser/parser.c \

TOKENIZER	:=	tokenizer/tokenizer.c \
				tokenizer/handlers.c \
				tokenizer/tokens_list.c \
				tokenizer/tokens_utils.c \

SRCS		:=	$(BUILTINS)\
				$(HELP)\
				$(CLEANERS)\
				$(EXEC)\
				$(PARSER)\
				$(TOKENIZER)\
				main.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	/goinfre/homebrew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iincludes -I$(READLINE_PATH)/include

all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(READLINE_PATH)/lib -lreadline

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
