#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include "tokenizer.h"
# include "parser.h"
# include "header.h"


# define PROMPT "lumumbash$ "

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_token			*current_token;
	t_node			*ast;
	int				exit_s;
	// bool			signint_child;
	t_parse_error		parse_error;
	int				stdin;
	int				stdout;
	char			**environ;
	// t_env			*envlst;
	bool			heredoc_sigint;
	struct termios	original_term;
}					t_minishell;

#endif