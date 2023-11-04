#include "minishell.h"
void ft_exit()
{
    printf("syntax error!");
    exit (0);
}

int check_redirection(char  *str, int *a)
{
    int i;

    i = 0;
    if ((str[0] == '<' && str[1] != '>') || (str[0] == '>' &&  str[1] != '<'))
        i += 1;
    if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
        i += 1;
    *a += i;
    if (i)
        return (1);
    else
        return (0);
}

int check_Q(char    *str, int   *a)
{
    int i;

    i = 0;
    if (str[i] == 34)
    {
        i++;
        while (str[i] != 34 && str[i])
            i++;
        if (str[i] != 34)
            return (0);
        i++;
    }
    else if (str[i] == 39)
    {
        i++;
        while (str[i] != 39 && str[i])
            i++;
        if (str[i] != 39)
            return (0);
        i++;
    }
    *a += i;
    return (1);
}

int check_operator(char check)
{
    if(check && check != ' ' && check != '|' && check != '<' && check != '>' && check != 34 && check != 39)
        return (1);
    return (0);
}
int word_count(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i] == '|')
        {
            count++;
            i++;
            if (str[i] == '\0')
                ft_exit();
        }
        else if(str[i] == '<' || str[i] == '>')
        {
            if (!check_redirection(&str[i], &i))
                ft_exit();
            if (str[i] == '\0')
                ft_exit();
            count++;
        }
        else if (str[i] == 34 || str[i] == 39)
        {
            if (!check_Q(&str[i], &i))
                ft_exit();
            count++;
        }
        else if (check_operator(str[i]))
        {
            while(check_operator(str[i]))
                i++;
            count++;
        }
    }
    return (count);
}

int char_count(char *str, int *a)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i] == ' ')
        i++;
    *a += i;
    if (str[i] == '|')
    {
        *a += 1;
        return (1);
    }
    else if (str[i] == '<' || str[i] == '>')
    {
        count++;
        i++;
        if (str[i] == '<' || str[i] == '>')
            count++;
        *a += count; 
        return (count);
    }
    else if (str[i] == 34)
    {
        i++;
        count++;
        while (str[i++] != 34)
            count++;
        *a += count;
        return (count);
    }
    else if (str[i] == 39)
    {
        i++;
        count++;
        while (str[i++] != 39)
            count++;
        *a += count;
        return (count);
    }
    else if (check_operator(str[i]))
    {
        while(check_operator(str[i++]))
            count++;
        *a += count;
        return (count);
    }
    return (0);
}

/* char **special_split(char *str)
{
    t_commen data;

    data.i = -1;
    data.j = 0;
    data.k = 0;
    data.l = 0;
  
    data.res = malloc(sizeof(char *) * word_count(str));
    if (!data.res)
        return (0);
    while(str[data.j])
    {
        data.t = 0;
        data.k = char_count(&str[data.j], &data.j);
        data.res[++data.i] = malloc(sizeof(char) * (data.k + 1));
        if (!data.res[data.i])
            return (0);
        while (str[data.l] == ' ')
            data.l++;
        while (data.l < data.j)
            data.res[data.i][data.t++] = str[data.l++];
        data.res[data.i][data.t] != '\0';
    }
    data.res[++data.i] = NULL;
    //printf("%stest\n", *data.res);
    return (data.res);
} */

void    special_split(t_lexer **lexer, char *str)
{
    char    *content;
    int     temp;
    int     i;

    temp = 0;
    i = 0;
    while (str[i])
    {
        i = char_count(&str[i], &i);
        content = ft_substr(str, temp, i);
        lexer_lstadd_back(lexer, lexer_listnew(content));
    }
}

void    init_tables(t_core *g_core)
{
    g_core->lexer = malloc(sizeof(t_lexer));
    g_core->lexer = NULL;
}

int main(int argc, char **argv, char **env)
{
    char *input;
    t_core  *g_core;
    t_lexer *temp;
    
    g_core = malloc(sizeof(t_core));
    if (!g_core)
        return (0);
    init_tables(g_core);    
    (void)argc;
    (void)argv;
    (void)env;
    temp = &g_core->lexer;
    while(1)
    {
        input = readline(">monkeys: ");
        special_split(&g_core->lexer, input);
         while(temp)
        {
            printf("%s\n", temp->content);
            temp = temp->next;
        }
        if (!strcmp(input, "exit"));
            exit(0);
    }

}