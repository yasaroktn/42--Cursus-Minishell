#ifndef     STRUCTS_H
#define     STRUCTS_H

typedef struct s_commen
{
    char **res;
    int i;
    int j;
    int k;
    int l;;
    int t;
}   t_commen;

typedef struct s_lexer
{
    char            *content;
    int             type;
    struct s_lexer  *next;
}       t_lexer;

typedef struct s_core
{
    t_lexer *lexer;
}       t_core;

#endif