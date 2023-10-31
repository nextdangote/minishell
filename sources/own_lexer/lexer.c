

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

// Custom function to tokenize the input and store tokens in the linked list
Token* tokenizeInput(const char* input) {
    Token* head = NULL;
    Token* current = NULL;
    char buffer[MAX_TOKEN_LENGTH];
    int bufferIndex = 0;
    int inQuote = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        // Handle double quotes
        if (c == '"') {
            inQuote = !inQuote;
            buffer[bufferIndex++] = c;
        } else if (!inQuote && (c == ' ' || c == '\t' || c == '\n')) {
            // Handle whitespace outside quotes as token separator
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                Token* newToken = (Token*)malloc(sizeof(Token));
                newToken->next = NULL;
                strcpy(newToken->value, buffer);

                // Categorize the token based on content
                if (strcmp(buffer, "|") == 0) {
                    newToken->type = TOKEN_PIPE;
                } else if (strcmp(buffer, "<") == 0) {
                    newToken->type = TOKEN_INPUT_REDIRECTION;
                } else if (strcmp(buffer, ">") == 0) {
                    newToken->type = TOKEN_OUTPUT_REDIRECTION;
                } else if (strcmp(buffer, ">>") == 0) {
                    newToken->type = TOKEN_APPEND_OUTPUT_REDIRECTION;
                } else if (strcmp(buffer, "<<") == 0) {
                    // Handle double redirection
                    newToken->type = TOKEN_INPUT_REDIRECTION;
                } else if (buffer[0] == '"') {
                    newToken->type = TOKEN_DOUBLE_QUOTE;
                } else if (buffer[0] == '\'') {
                    newToken->type = TOKEN_SINGLE_QUOTE;
                } else if (buffer[0] == '-' && isalpha(buffer[1])) {
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

                bufferIndex = 0; // Reset the buffer
            }
        } else {
            // Add characters to the buffer
            buffer[bufferIndex++] = c;
        }
    }

    if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';
        Token* newToken = (Token*)malloc(sizeof(Token));
        newToken->next = NULL;
        strcpy(newToken->value, buffer);

        // Categorize the token based on content
        if (strcmp(buffer, "|") == 0) {
            newToken->type = TOKEN_PIPE;
        } else if (strcmp(buffer, "<") == 0) {
            newToken->type = TOKEN_INPUT_REDIRECTION;
        } else if (strcmp(buffer, ">") == 0) {
            newToken->type = TOKEN_OUTPUT_REDIRECTION;
        } else if (strcmp(buffer, ">>") == 0) {
            newToken->type = TOKEN_APPEND_OUTPUT_REDIRECTION;
        } else if (strcmp(buffer, "<<") == 0) {
            // Handle double redirection
            newToken->type = TOKEN_INPUT_REDIRECTION;
        } else if (buffer[0] == '"') {
            newToken->type = TOKEN_DOUBLE_QUOTE;
        } else if (buffer[0] == '\'') {
            newToken->type = TOKEN_SINGLE_QUOTE;
        } else if (buffer[0] == '-' && isalpha(buffer[1])) {
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
        //ft_parser(tokenList); // 🇨🇲🇨🇲🇨🇲🇨🇲 If you have a small draft of parser you can try to work with it
        free(input); // Free the input buffer returned by readline
        freeTokenList(tokenList); // Free the linked list of tokens
    }

    return 0;
}