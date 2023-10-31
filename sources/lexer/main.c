#include "../../include/minishell.h"

int main(int argc, char **argv, char **env)
{
    char* input;
    int i;

    i = 0;

    if (argc != 1)
    {
        printf("execute the program like so : ./minishell");
        free(input);
        return(0);
    }

    while(1)
    {
        input = readline("minishell : ");
        add_history(input);
        ft_lexer(input);
        free(input);
    }

}

// {

// }

 
