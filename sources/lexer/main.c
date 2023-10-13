#include "../../include/minishell.h"
// int main(int argc, char **argv)
// {
//     char* input = readline("Enter a command: ");char* input = readline("Enter a command: ");

//     if (argv != 1)
//     {
//         printf("execute the program like so : ./minishell");
//         free(input);
//         return(0);
//     }

//     add_history(input);
//     free(input);

// }

int main() 
{
    char* input;
    
    while (1) {
        input = readline("Enter a command: ");
        
        if (input == NULL) {
            // Handle input error or EOF
            break;
        }
        
        if (input[0] != '\0') {
            // Add non-empty input to history
            add_history(input);
        }
        
        printf("You entered: %s\n", input);
        
        free(input); // Free memory allocated by readline
    }
    
    return 0;
}
