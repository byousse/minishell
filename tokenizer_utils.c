/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:44:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/19 20:15:46 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *is_redirections(t_token_list **tokens, char *line)
{
    if (*line == '>')
    {	
        if (*(line + 1) == '>')
        {
            addback(tokens, ">>", APPEND);
            return (line + 2);
        }
        addback(tokens, ">", RIGHTRED);
    }
    else if (*line == '<')
    {
        if (*(line + 1) == '<')
        {
            addback(tokens, "<<", HEREDOC);
            return (line + 2);
        }
        addback(tokens, "<", LEFTRED);
    }
	return (line + 1);
}

char    *is_wspace(t_token_list **tokens, char *line)
{
    int i;
    i = 0;
    while (ft_strchr(" \t\v\f\r", line[i]) && line[i])
        i++;
    addback(tokens, " ", SPACE);
    return (line + i);
}

char    *is_dollar_pipe(t_token_list **tokens, char *line)
{
    if(*line == '$')
    {
        addback(tokens,"$", DOLLAR);
            return (line + 1);
    }
    else if(*line == '|')
    {
        addback(tokens,"|", PIPE);
            return (line + 1);
    }
	return(0);
}

char    *is_word(t_token_list **tokens, char *line)
{
    int		i;
    char    *word;

    i = 0;
    while (!ft_strchr(" \t\v\f\r><$|\'", line[i]))
        i++;
	word = malloc(i + 1);
	i = 0;
	while (!ft_strchr(" \t\v\f\r><$|\'", line[i]))
	{
		
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	addback(tokens, word, WORD);
	return (line + i);
}

int is_open_quote(char *line)
{
    int i;
    int x;

    i = 0 ;
    x = 0;
    while(line[i])
    {
        if(line[i] == '\'')
            x++;
        i++;
    }
    return (x % 2);
}

int to_alloc(char *line)
{
    int i;
    int j;
    int count;
    int flag;

    i = 0;
    j = 0;
    count = is_open_quote(line);
    flag = 0;
    while (line[i] && count == 0)
    {
		if(line[i] == 39 && flag == 0)
        {
            flag = 1;
            i++;
        }
        if(line[i] != 39 && flag  == 1)
        {
            i++;
            j++;
        }
        if(line[i] == 39 && flag == 1)
		{
			i++;
            break;
		}
    }
	return (j);
}

char    *is_squote(t_token_list **tokens, char *line, int *open)
{
    int i;
    int j;
    int count;
    int flag;
    char    *word;

    i = 0;
    j = 0;
    count = is_open_quote(line);
    flag = 0;
	word = malloc(to_alloc(line) + 1);
	if (count == 0)
	{
		while (line[i])
		{
			if(line[i] == 39 && flag == 0)
			{
				flag = 1;
				i++;
			}
			if(line[i] != 39 && flag  == 1)
			{
				word[j] = line[i];
				i++;
				j++;
			}
			if(line[i] == 39 && flag == 1)
			{
				i++;	
				break;
			}
			
		}
		word[j]= '\0';
		addback(tokens, word, WORD);
	}
	else
	{
		write(1, "Open quote\n", ft_strlen("Open quote\n"));
		*open = 1;
	}
	return (line + i);
}