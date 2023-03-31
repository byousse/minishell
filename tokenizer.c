/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:20 by byoussef          #+#    #+#             */
/*   Updated: 2023/03/31 16:06:21 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

// void free_node(t_token_list **tokens)
// {
// 	t_token_list *head;
// 	head = *tokens;
// 	if(!head->next)
// 		free_node(&head->next);
// 	free(head);
// }

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
			if(is_open_quote(line, '\''))
			{
				printf("open quote!!\n");
				break;
			}
			else
				line = quotes_maker(&tokens, line);	
		}
		else if (ft_strchr("\"", *line))
		{
			line = is_dquote(&tokens, line, &i);
			if (*line == '$')
				line = afdollar(&tokens, line);
			if (i == 1)
				break;
		}
        else
		{
            line = word_maker(&tokens, line);
		}
    }
	return(tokens);
}
