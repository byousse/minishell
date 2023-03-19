/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/19 20:44:18 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_token_list *tokenizer(char *line)
{
	t_token_list	*tokens;
	int	i = 0;

	tokens = NULL;
    while (*line)
    {
        if (ft_strchr(" \t\v\f\r", *line))
            line = is_wspace(&tokens, line);
        else if (ft_strchr("><", *line))
            line = is_redirections(&tokens, line);
        else if (ft_strchr("$|", *line))
            line = is_dollar_pipe(&tokens, line);
        else if (ft_strchr("\'", *line))
		{
            line = is_squote(&tokens, line, &i);
			if (i == 1)
			{
				break;
			}
				
		}
        else
            line = is_word(&tokens, line);
    }
	return(tokens);
}

char    *prompt(void)
{
    char	*line;

	line = readline("\x1B[36m""minishell$ ""\001\e[0m\002");
	add_history(line);
	line = remove_additional_spaces(line);
    return (line);
}

int main()
{
    char	*line;
	t_token_list	*token;

    while (1)
    {
		line = prompt();
		token = tokenizer(line);
		while (token)
		{
			printf("%s|\n", token->value);
			token = token->next;
		}
    }
}