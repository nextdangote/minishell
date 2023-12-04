#include "lumumbash.h"



// int	main(int argc, char **argv, char **env)
// {
// 	((void)argc, (void)argv);
//     t_minishell minishell;
// 	ft_init_minishell(&minishell, env);
// 	while (1)
// 	{
// 		minishell.line = readline(PROMPT);
// 		if (!minishell.line)
// 			(clean_shell(&minishell),
// 				ft_putstr_fd("exit\n", 1), exit(minishell.exit_s));
// 		if (minishell.line[0])
// 			add_history(minishell.line);
// 		minishell.tokens = tokenize(minishell.line, &minishell.exit_s);
// 		if (!minishell.tokens)
// 			continue ;
// 		// minishell.ast = ft_parse(&minishell);
// 		// if (minishell.parse_error.type)
// 		// {
// 		// 	handle_parse_error(&minishell);
// 		// 	continue ;
// 		// }
// 		// start_execution(&minishell);
// 	}
// 	to_trash(NULL, true);
// 	return (clean_shell(&minishell), minishell.exit_s);
// }

// typedef struct s_node {
//     t_node_type type;
//     struct s_node *left;
//     struct s_node *right;
//     char *value;  // You may need to adjust this based on your actual structure
// } t_node;



// const char *token_type_to_str[] = {
//     "TOKEN_WORD",
//     "TOKEN_PIPE",
//     "TOKEN_INPUT_REDIRECTION",
//     "TOKEN_OUTPUT_REDIRECTION",
//     "TOKEN_APPEND_OUTPUT_REDIRECTION",
//     "TOKEN_HEREDOC",
//     "TOKEN_NL"
// };

// const char *node_type_to_str[] = {
//     "NODE_CMD",
//     "NODE_PIPE",
//     "NODE_UNKNOWN"
// };

// const char *redir_type_to_str[] = {
//     "REDIR_IN",
//     "REDIR_OUT",
//     "REDIR_APPEND",
//     "REDIR_HEREDOC"
// };


// const char *get_token_type_str(t_token_type type) {
//     if (type >= 0 && type < sizeof(token_type_to_str) / sizeof(token_type_to_str[0])) {
//         return token_type_to_str[type];
//     }
//     return "UNKNOWN_TOKEN_TYPE";
// }


// const char *get_node_type_str(t_node_type type) {
//     if (type >= 0 && type < sizeof(node_type_to_str) / sizeof(node_type_to_str[0])) {
//         return node_type_to_str[type];
//     }
//     return "UNKNOWN_NODE_TYPE";
// }


// const char *get_redir_type_str(t_redir_type type) {
//     if (type >= 0 && type < sizeof(redir_type_to_str) / sizeof(redir_type_to_str[0])) {
//         return redir_type_to_str[type];
//     }
//     return "UNKNOWN_REDIR_TYPE";
// }


// void print_tokens(t_token *token_list) {
//     while (token_list != NULL) {
//         printf("Type: %s, Value: %s\n", get_token_type_str(token_list->type), token_list->value);
//         token_list = token_list->next;
//     }
// }

// void print_redir_list(t_redir_node *redir_list) {
//     while (redir_list != NULL) {
//         printf("Redir Type: %s, Value: %s\n", get_redir_type_str(redir_list->type), redir_list->value);
//         redir_list = redir_list->next;
//     }
// }

// //Function to print AST or result
// void print_ast_or_result(t_node *node) {
//     if (node == NULL) {
//         printf("Error: Unable to print AST or result. AST is NULL.\n");
//         return;
//     }

//     printf("Node Type: %s\n", get_node_type_str(node->type));

//     switch (node->type) {
//         case NODE_CMD:
//             printf("Args:\n");
//             for (int i = 0; node->args[i] != NULL; ++i) {
//                 printf("  %s\n", node->args[i]);
//             }
//             printf("Redirections:\n");
//             print_redir_list(node->redir_list);
//             break;
//         case NODE_PIPE:
//             printf("Type: NODE_PIPE\n");

//             printf("Left:\n");
//             print_ast_or_result(node->left);
//             printf("Right:\n");
//             print_ast_or_result(node->right);
//             break;
//         // Add more cases for other node types if needed
//         default:
//             printf("Unknown node type\n");
//     }
// }



// int main() {
//     t_minishell minishell;
//     // Test input line
//     char input_line[] = "ls -l | grep test > output.txt";

//     // Tokenize the input line
//     t_token *token_list = tokenize(input_line);

//     // Print the tokens
//     printf("=== Token List ===\n");
//     print_tokens(token_list);


//     minishell.tokens = token_list;
//     minishell.current_token = token_list;

 
//     // Parse the tokens
//     t_node *ast = ft_parse(&minishell);


//     // Print AST/result
//     printf("\n=== AST/Result ===\n");
//     print_ast_or_result(ast);

//     // Clean up the token list
//     clear_token_list(&token_list);

//     // Clean up the AST
//     ft_clear_ast(&ast, &minishell);

//     return 0;
// }
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
		// start_execution(&minishell);
	}
	collector(NULL, true);
	return (clean_shell(&minishell), minishell.exit_s);
}
