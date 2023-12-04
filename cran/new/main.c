#include "lumumbash.h"


static void	ft_init_minishell(t_minishell *minishell, char **env)
{    
    memset(minishell, 0, sizeof(t_minishell));
	minishell->environ = env;
	tcgetattr(STDIN_FILENO, &(minishell->original_term));

}


int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
    t_minishell minishell;
	ft_init_minishell(&minishell, env);
	while (1)
	{
		minishell.line = readline(PROMPT);
		if (!minishell.line)
			(clean_shell(&minishell),
				ft_putstr_fd("exit\n", 1), exit(minishell.exit_s));
		if (minishell.line[0])
			add_history(minishell.line);
		minishell.tokens = tokenize(minishell.
		line);
		if (!minishell.tokens)
			continue ;
		minishell.ast = ft_parse(&minishell);
		if (minishell.parse_error.type)
		{
			handle_parse_error(&minishell);
			continue ;
		}
	}
	collector(NULL, true);
	return (clean_shell(&minishell), minishell.exit_s);
}
