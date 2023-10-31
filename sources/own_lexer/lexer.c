

// int	main(int argc, char **argv, char **env)
// {
// 	char		initialDirectory[PATH_MAX];
// 	TokenList	*tokenList;
// 	int			i;
// 	size_t		input_len;

// 	char input[MAX_TOKEN_LENGTH]; // Read input into a fixed-size buffer
// 	tokenList = initTokenList();
// 	i = 0;
// 	if (argc != 1)
// 	{
// 		printf("execute the program like so: ./minishell");
// 		freeTokenList(tokenList); // Free the token list before exiting
// 		return (0);
// 	}
// 	getcwd(initialDirectory, sizeof(initialDirectory));
// while (1) {
//     printf("> "); // Print the prompt
//     fflush(stdout); // Flush the output to ensure it's displayed

//     if (fgets(input, MAX_TOKEN_LENGTH, stdin) == NULL) {
//         break;
//     }

//     // Remove the trailing newline character, if it exists
//     size_t input_len = strlen(input);
//     if (input_len > 0 && input[input_len - 1] == '\n') {
//         input[input_len - 1] = '\0';
//     }

//     // Tokenize the input and store tokens in the linked list
//     tokenizeInput(input, tokenList);

//     // Now, you can pass the tokenList to your parser for further processing
// }
// 	// Free the token list before exiting
// 	freeTokenList(tokenList);
// 	return (0);
// }


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOKEN_LENGTH 100

// Token types
typedef enum {
    TOKEN_WORD,
    TOKEN_FLAG,
    TOKEN_PIPE,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_SINGLE_QUOTE,
    TOKEN_INPUT_REDIRECTION,
    TOKEN_OUTPUT_REDIRECTION,
    TOKEN_APPEND_OUTPUT_REDIRECTION,
    TOKEN_EOF
} TokenType;

// Token structure
typedef struct Token {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
    struct Token* next;
} Token;

// Function to tokenize the input and store tokens in the linked list
Token* tokenizeInput(const char* input) {
    Token* head = NULL;
    Token* current = NULL;

    const char delimiters[] = " \t\n";
    char* token = strtok((char*)input, delimiters);

    while (token != NULL) {
        Token* newToken = (Token*)malloc(sizeof(Token));
        newToken->next = NULL;
        strcpy(newToken->value, token);

        // Categorize the token based on content
        if (strcmp(token, "|") == 0) {
            newToken->type = TOKEN_PIPE;
        } else if (strcmp(token, "<") == 0) {
            newToken->type = TOKEN_INPUT_REDIRECTION;
        } else if (strcmp(token, ">") == 0) {
            newToken->type = TOKEN_OUTPUT_REDIRECTION;
        } else if (strcmp(token, ">>") == 0) {
            newToken->type = TOKEN_APPEND_OUTPUT_REDIRECTION;
        } else if (strcmp(token, "<<") == 0) {
            // Handle double redirection
            newToken->type = TOKEN_INPUT_REDIRECTION;
        } else if (token[0] == '"' && token[strlen(token) - 1] == '"') {
            newToken->type = TOKEN_DOUBLE_QUOTE;
        } else if (token[0] == '\'' && token[strlen(token) - 1] == '\'') {
            newToken->type = TOKEN_SINGLE_QUOTE;
        } else if (token[0] == '-' && isalpha(token[1])) {
            newToken->type = TOKEN_FLAG;
        } else {
            newToken->type = TOKEN_WORD;
        }

        // Append the new token to the linked list
        if (head == NULL) {
            head = newToken;
            current = newToken;
        } else {
            current->next = newToken;
            current = newToken;
        }

        token = strtok(NULL, delimiters);
    }

    return head; // Return the head of the linked list
}

// Function to free the linked list of tokens
void freeTokenList(Token* head) {
    while (head != NULL) {
        Token* current = head;
        head = head->next;
        free(current);
    }
}

int main(int argc, char **argv, char **env)
{
    Token* tokenList = NULL; // Head of the token linked list

    if (argc != 1)
    {
        printf("execute the program like so : ./minishell\n");
        return(0);
    }
    while (1) 
    {
        char *input = readline("> Lumumbash : "); // Use readline to read user input
        if (input == NULL)
            break;

        // Tokenize the input and store tokens in the linked list
        tokenList = tokenizeInput(input);

        // Process tokens or perform other operations with the linked list
        Token* current = tokenList;
        while (current != NULL) {
            printf("Token type: %d, Value: %s\n", current->type, current->value);
            current = current->next;
        }

        free(input); // Free the input buffer returned by readline
        freeTokenList(tokenList); // Free the linked list of tokens
    }

    return 0;
}









