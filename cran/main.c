#include "tokenizer.h"
#include "minishell.h"
#include "parser.h"
#include "header.h"


// start of simple main for tokenizer & parser

// void print_tokens(t_token *tokens) {
//     while (tokens) {
//         printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
//         tokens = tokens->next;
//     }
// }

// void print_ast_helper(t_node *node, int indent) {
//     if (!node)
//         return;

//     for (int i = 0; i < indent; ++i)
//         printf("  ");

//     printf("Type: %d\n", node->type);

//     print_ast_helper(node->left, indent + 1);
//     print_ast_helper(node->right, indent + 1);
// }

// void print_ast(t_node *ast, int indent) {
//     printf("Abstract Syntax Tree:\n");
//     print_ast_helper(ast, indent);
// }



// int main() {


//     t_minishell minishell;
    

//     int exit_status = 0;
//     // Example command to test
//     char input[] = "echo Hello, world! | grep world";

//     t_token *tokens = tokenize(input, &exit_status);

//     // Print the tokens for verification
//     printf("Tokens:\n");
//     print_tokens(tokens);

//     minishell.tokens = tokens;

//     t_node *ast = ft_parse(&minishell);

//     // Print the abstract syntax tree (AST) for verification
//     print_ast(ast, 0);

//     clear_token_list(&tokens);
//     clear_ast(&ast, &tokens);

//     return exit_status;
// }





static void	ft_init_minishell(t_minishell *minishell, char **env)
{    
    memset(minishell, 0, sizeof(t_minishell));
	minishell->environ = env;
	tcgetattr(STDIN_FILENO, &(minishell->original_term));

}

static void	start_execution(t_minishell *minishell)
{
	ft_init_tree(minishell->ast, minishell);
	if (minishell ->heredoc_sigint)
	{
		clear_ast(&(minishell->ast), NULL);
		minishell->heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->original_term));
	minishell->exit_s = exec_node(minishell->ast, false, minishell);
	clear_ast(&(minishell->ast), NULL);
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
		minishell.tokens = tokenize(minishell.line, &minishell.exit_s);
		if (!minishell.tokens)
			continue ;
		minishell.ast = ft_parse(&minishell);
		if (minishell.parse_error.type)
		{
			handle_parse_error(&minishell);
			continue ;
		}
		start_execution(&minishell);
	}
	to_trash(NULL, true);
	return (clean_shell(&minishell), minishell.exit_s);
}
