#include "../../include/minishell.h"

t_lexer   *init_lexer(char *src)
{
    t_lexer *lexer = calloc(1, sizeof(struct s_lexer));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return lexer;
}

void    lexer_advance(t_lexer *lexer)
{
    if (lexer->i < lexer->src_size && lexer->c != '\0')
    {
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}

char lexer_peek(t_lexer *lexer, int offset)
{
    return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

t_token *lexer_advance_with(t_lexer *lexer, t_token *token)
{
    lexer_advance(lexer);
    return (token);
}

void lexer_skip_whitespace(t_lexer *lexer)
{
    while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
        lexer_advance(lexer);
}

t_token *lexer_parse_id(t_lexer *lexer)
{
    char *value = calloc(1, sizeof(char));
    while (isalnum(lexer->c))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
    }

    return init_token(value, TOKEN_ID);
}


t_token *lexer_next_token(t_lexer *lexer)
{
    while (lexer->c != '\0')
    {
        if (isalnum(lexer->c))// what is isalnum ?
            return lexer_advance_with(lexer, lexer_parse_id(lexer));
        switch (lexer->c)
        {
            case '=':
            {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token(" =>, TOKEN_RIGHT_ARROW"));
                return lexer_advance_with(lexer, init_token(" =>, TOKEN_EQUALS"));
            } break;
        }
    }

    return (init_token(0, TOKEN_EOF));
}

void    tac_compile(char *src)
{
    t_lexer *lexer = init_lexer(src);
}