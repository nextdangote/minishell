

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


// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// #define MAX_TOKEN_LENGTH 100

// // Token types
// typedef enum {
//     TOKEN_WORD,
//     TOKEN_FLAG,
//     TOKEN_PIPE,
//     TOKEN_DOUBLE_QUOTE,
//     TOKEN_SINGLE_QUOTE,
//     TOKEN_INPUT_REDIRECTION,
//     TOKEN_OUTPUT_REDIRECTION,
//     TOKEN_APPEND_OUTPUT_REDIRECTION,
//     TOKEN_EOF
// } TokenType;

// // Token structure
// typedef struct Token {
//     TokenType type;
//     char value[MAX_TOKEN_LENGTH];
//     struct Token* next;
// } Token;

// // Custom function to tokenize the input and store tokens in the linked list
// Token* tokenizeInput(const char* input) 
// {
//     Token* head = NULL;
//     Token* current = NULL;
//     char buffer[MAX_TOKEN_LENGTH];
//     int bufferIndex = 0;
//     int inQuote = 0;

//     for (int i = 0; input[i] != '\0'; i++) {
//         char c = input[i];

//         // Handle double quotes
//         if (c == '"') {
//             inQuote = !inQuote;
//             buffer[bufferIndex++] = c;
//         } else if (!inQuote && (c == ' ' || c == '\t' || c == '\n')) {
//             // Handle whitespace outside quotes as token separator
//             if (bufferIndex > 0) {
//                 buffer[bufferIndex] = '\0';
//                 Token* newToken = (Token*)malloc(sizeof(Token));
//                 newToken->next = NULL;
//                 strcpy(newToken->value, buffer);

//                 // Categorize the token based on content
//                 if (strcmp(buffer, "|") == 0) {
//                     newToken->type = TOKEN_PIPE;
//                 } else if (strcmp(buffer, "<") == 0) {
//                     newToken->type = TOKEN_INPUT_REDIRECTION;
//                 } else if (strcmp(buffer, ">") == 0) {
//                     newToken->type = TOKEN_OUTPUT_REDIRECTION;
//                 } else if (strcmp(buffer, ">>") == 0) {
//                     newToken->type = TOKEN_APPEND_OUTPUT_REDIRECTION;
//                 } else if (strcmp(buffer, "<<") == 0) {
//                     // Handle double redirection
//                     newToken->type = TOKEN_INPUT_REDIRECTION;
//                 } else if (buffer[0] == '"') {
//                     newToken->type = TOKEN_DOUBLE_QUOTE;
//                 } else if (buffer[0] == '\'') {
//                     newToken->type = TOKEN_SINGLE_QUOTE;
//                 } else if (buffer[0] == '-' && isalpha(buffer[1])) {
//                     newToken->type = TOKEN_FLAG;
//                 } else {
//                     newToken->type = TOKEN_WORD;
//                 }

//                 // Append the new token to the linked list
//                 if (head == NULL) {
//                     head = newToken;
//                     current = newToken;
//                 } else {
//                     current->next = newToken;
//                     current = newToken;
//                 }

//                 bufferIndex = 0; // Reset the buffer
//             }
//         } else {
//             // Add characters to the buffer
//             buffer[bufferIndex++] = c;
//         }
//     }

//     if (bufferIndex > 0) {
//         buffer[bufferIndex] = '\0';
//         Token* newToken = (Token*)malloc(sizeof(Token));
//         newToken->next = NULL;
//         strcpy(newToken->value, buffer);

//         // Categorize the token based on content
//         if (strcmp(buffer, "|") == 0) {
//             newToken->type = TOKEN_PIPE;
//         } else if (strcmp(buffer, "<") == 0) {
//             newToken->type = TOKEN_INPUT_REDIRECTION;
//         } else if (strcmp(buffer, ">") == 0) {
//             newToken->type = TOKEN_OUTPUT_REDIRECTION;
//         } else if (strcmp(buffer, ">>") == 0) {
//             newToken->type = TOKEN_APPEND_OUTPUT_REDIRECTION;
//         } else if (strcmp(buffer, "<<") == 0) {
//             // Handle double redirection
//             newToken->type = TOKEN_INPUT_REDIRECTION;
//         } else if (buffer[0] == '"') {
//             newToken->type = TOKEN_DOUBLE_QUOTE;
//         } else if (buffer[0] == '\'') {
//             newToken->type = TOKEN_SINGLE_QUOTE;
//         } else if (buffer[0] == '-' && isalpha(buffer[1])) {
//             newToken->type = TOKEN_FLAG;
//         } else {
//             newToken->type = TOKEN_WORD;
//         }

//         // Append the new token to the linked list
//         if (head == NULL) {
//             head = newToken;
//             current = newToken;
//         } else {
//             current->next = newToken;
//             current = newToken;
//         }
//     }

//     return head; // Return the head of the linked list
// }

// // Function to free the linked list of tokens
// void freeTokenList(Token* head) {
//     while (head != NULL) {
//         Token* current = head;
//         head = head->next;
//         free(current);
//     }
// }

// int main(int argc, char **argv, char **env)
// {
//     Token* tokenList = NULL; // Head of the token linked list

//     if (argc != 1)
//     {
//         printf("execute the program like so : ./minishell\n");
//         return(0);
//     }
//     //using_history();
//     while (1) 
//     {
//         char *input = readline("> Lumumbash : "); // Use readline to read user input
//         if (input == NULL)
//             break;

//         add_history(input);

//         // Tokenize the input and store tokens in the linked list
//         tokenList = tokenizeInput(input);

//         // Process tokens or perform other operations with the linked list
//         Token* current = tokenList;
//         while (current != NULL) {
//             printf("Token type: %d, Value: %s\n", current->type, current->value);
//             current = current->next;
//         }
//         // ft_parser(tokenList); // 🇨🇲🇨🇲🇨🇲🇨🇲 If you have a small draft of parser you can try to work with it
//         free(input); // Free the input buffer returned by readline
//         freeTokenList(tokenList); // Free the linked list of tokens
//     }

//     clear_history();

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// #define MAX_TOKEN_LENGTH 100

// // Token types
// typedef enum 
// {
//     TOKEN_WORD,
//     TOKEN_FLAG,
//     TOKEN_PIPE,
//     TOKEN_DOUBLE_QUOTE,
//     TOKEN_SINGLE_QUOTE,
//     TOKEN_INPUT_REDIRECTION,
//     TOKEN_OUTPUT_REDIRECTION,
//     TOKEN_APPEND_OUTPUT_REDIRECTION,
//     TOKEN_EOF
// } TokenType;

// // Token structure
// typedef struct Token 
// {
//     TokenType type;
//     char value[MAX_TOKEN_LENGTH];
//     struct Token* next;
// } Token;

// // Function to categorize a token based on its content
// TokenType categorizeToken(const char* tokenValue) 
// {
//     if (strcmp(tokenValue, "|") == 0)
//         return TOKEN_PIPE;
//     else if (strcmp(tokenValue, "<") == 0)
//         return TOKEN_INPUT_REDIRECTION;
//     else if (strcmp(tokenValue, ">") == 0)
//         return TOKEN_OUTPUT_REDIRECTION;
//     else if (strcmp(tokenValue, ">>") == 0)
//         return TOKEN_APPEND_OUTPUT_REDIRECTION;
//     else if (strcmp(tokenValue, "<<") == 0)
//         return TOKEN_INPUT_REDIRECTION;
//     else if (tokenValue[0] == '"')
//         return TOKEN_DOUBLE_QUOTE;
//     else if (tokenValue[0] == '\'')
//         return TOKEN_SINGLE_QUOTE;
//     else if (tokenValue[0] == '-' && isalpha(tokenValue[1]))
//         return TOKEN_FLAG;
//     else
//         return TOKEN_WORD;
// }

// // Function to create a new token and append it to the linked list
// Token* createAndAppendToken(Token** head, Token** current, const char* tokenValue) 
// {
//     Token* newToken = (Token*)malloc(sizeof(Token));
//     newToken->next = NULL;
//     strcpy(newToken->value, tokenValue);
//     newToken->type = categorizeToken(tokenValue);

//     if (*head == NULL) 
//     {
//         *head = newToken;
//         *current = newToken;
//     } 
//     else 
//     {
//         (*current)->next = newToken;
//         *current = newToken;
//     }

//     return newToken;
// }

// // Function to tokenize the input using a while loop
// Token* tokenizeInput(const char* input) 
// {
//     Token* head = NULL;
//     Token* current = NULL;
//     char buffer[MAX_TOKEN_LENGTH];
//     int bufferIndex = 0;
//     int inQuote = 0;

//     int i = 0;
//     while (input[i] != '\0') 
//     {
//         char c = input[i];

//         if (c == '"') 
//         {
//             inQuote = !inQuote;
//             buffer[bufferIndex++] = c;
//         } 
//         else if (!inQuote && (c == ' ' || c == '\t' || c == '\n')) 
//         {
//             if (bufferIndex > 0) 
//             {
//                 buffer[bufferIndex] = '\0';
//                 createAndAppendToken(&head, &current, buffer);
//                 bufferIndex = 0;
//             }
//         } 
//         else 
//             buffer[bufferIndex++] = c;
//         i++;
//     }

//     if (bufferIndex > 0) 
//     {
//         buffer[bufferIndex] = '\0';
//         createAndAppendToken(&head, &current, buffer);
//     }

//     return head;
// }

// // Function to free the linked list of tokens
// void freeTokenList(Token* head) 
// {
//     while (head != NULL) 
//     {
//         Token* current = head;
//         head = head->next;
//         free(current);
//     }
// }

// int main(int argc, char **argv, char **env) 
// {
//     Token* tokenList = NULL; // Head of the token linked list

//     if (argc != 1) 
//     {
//         printf("execute the program like so : ./minishell\n");
//         return 0;
//     }

//     // Initialize history
//     using_history();

//     while (1) 
//     {
//         char *input = readline("> Lumumbash : "); // Use readline to read user input

//         if (input == NULL)
//             break;

//         // Add input to history
//         add_history(input);

//         // Tokenize the input and store tokens in the linked list
//         tokenList = tokenizeInput(input);

//         // Process tokens or perform other operations with the linked list
//         Token* current = tokenList;
//         while (current != NULL) 
//         {
//             printf("Token type: %d, Value: %s\n", current->type, current->value);
//             current = current->next;
//         }

//         free(input); // Free the input buffer returned by readline
//         freeTokenList(tokenList); // Free the linked list of tokens
//     }
//     // Clean up history
//     clear_history();

//     return 0;
// }


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOKEN_LENGTH 100

// Token types
typedef enum 
{
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
typedef struct Token 
{
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
    struct Token* next;
} Token;

// Function to categorize a token based on its content
TokenType categorizeToken(const char* tokenValue) 
{
    if (strcmp(tokenValue, "|") == 0)
        return TOKEN_PIPE;
    else if (strcmp(tokenValue, "<") == 0)
        return TOKEN_INPUT_REDIRECTION;
    else if (strcmp(tokenValue, ">") == 0)
        return TOKEN_OUTPUT_REDIRECTION;
    else if (strcmp(tokenValue, ">>") == 0)
        return TOKEN_APPEND_OUTPUT_REDIRECTION;
    else if (strcmp(tokenValue, "<<") == 0)
        return TOKEN_INPUT_REDIRECTION;
    else if (tokenValue[0] == '"')
        return TOKEN_DOUBLE_QUOTE;
    else if (tokenValue[0] == '\'')
        return TOKEN_SINGLE_QUOTE;
    else if (tokenValue[0] == '-' && isalpha(tokenValue[1]))
        return TOKEN_FLAG;
    else
        return TOKEN_WORD;
}

// Function to create a new token and append it to the linked list
Token* createAndAppendToken(Token** head, Token** current, const char* tokenValue) 
{
    Token* newToken = (Token*)malloc(sizeof(Token));
    newToken->next = NULL;
    strcpy(newToken->value, tokenValue);
    newToken->type = categorizeToken(tokenValue);

    if (*head == NULL) 
    {
        *head = newToken;
        *current = newToken;
    } 
    else 
    {
        (*current)->next = newToken;
        *current = newToken;
    }

    return newToken;
}

// Function to free the linked list of tokens
void freeTokenList(Token* head) 
{
    while (head != NULL) 
    {
        Token* current = head;
        head = head->next;
        free(current);
    }
}

// Function to tokenize the input using a while loop
Token* tokenizeInput(const char* input) 
{
    Token* head = NULL;
    Token* current = NULL;
    char buffer[MAX_TOKEN_LENGTH];
    int bufferIndex = 0;
    int inDoubleQuote = 0;
    int inSingleQuote = 0;

    int i = 0;
    while (input[i] != '\0') {
        char c = input[i];

        if (c == '"') {
            if (!inSingleQuote) 
            {
                inDoubleQuote = !inDoubleQuote;
                buffer[bufferIndex++] = c;
            } 
            else 
            {
                // Unmatched quote within single quote, handle as a regular character
                buffer[bufferIndex++] = c;
            }
        }
        else if (c == '\'') 
        {
            if (!inDoubleQuote) 
            {
                inSingleQuote = !inSingleQuote;
                buffer[bufferIndex++] = c;
            } 
            else 
            {
                // Unmatched quote within double quote, handle as a regular character
                buffer[bufferIndex++] = c;
            }
        } 
        else if (!inDoubleQuote && !inSingleQuote && (c == ' ' || c == '\t' || c == '\n')) 
        {
            if (bufferIndex > 0) 
            {
                buffer[bufferIndex] = '\0';
                createAndAppendToken(&head, &current, buffer);
                bufferIndex = 0;
            }
        } 
        else 
            buffer[bufferIndex++] = c;
        i++;
    }

    if (bufferIndex > 0) 
    {
        // Check for unmatched quotes at the end of the input
        if (inDoubleQuote || inSingleQuote) 
        {
            printf("Error: Unmatched quotes in the input\n");
            freeTokenList(head); // Clean up and release the token list
            return NULL;
        }

        buffer[bufferIndex] = '\0';
        createAndAppendToken(&head, &current, buffer);
    }

    // Check for unmatched quotes at the end of the input
    if (inDoubleQuote || inSingleQuote) 
    {
        printf("Error: Unmatched quotes in the input\n");
        freeTokenList(head); // Clean up and release the token list
        return NULL;
    }

    return head;
}

int main(int argc, char **argv, char **env) 
{
    Token* tokenList = NULL; // Head of the token linked list

    if (argc != 1) 
    {
        printf("execute the program like so : ./minishell\n");
        return 0;
    }

    // Initialize history
    using_history();

    while (1) 
    {
        char *input = readline("> Lumumbash : "); // Use readline to read user input

        if (input == NULL)
            break;

        // Add input to history
        add_history(input);

        // Tokenize the input and store tokens in the linked list
        tokenList = tokenizeInput(input);

        // Process tokens or perform other operations with the linked list
        Token* current = tokenList;
        while (current != NULL) 
        {
            printf("Token type: %d, Value: %s\n", current->type, current->value);
            current = current->next;
        }

        free(input); // Free the input buffer returned by readline
        freeTokenList(tokenList); // Free the linked list of tokens
    }
    // Clean up history
    clear_history();

    return 0;
}

