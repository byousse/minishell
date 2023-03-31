/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/31 15:54:39 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	body(char *line)
{
	t_token_list	*tokens;
	t_token_list	*finals;

	tokens = tokenizer(line);
	
	syntax_red(&tokens);
	syntax_pipe(&tokens);
	char *c;
	finals = NULL;
	// finals_maker(tokens, &finals);
	c = NULL;
	if(tokens)
	{
		while (tokens->next)
		{
				if( tokens->type != SPACE )
					c = ft_strjoin(c, tokens->value);
				if( tokens->next->type == SPACE)
				{
					addback(&finals, c, WORD);
					c = NULL;
					tokens = tokens->next;	
				}
				else if(tokens->next->value[0] == '|')
				{
					if(c)
						addback(&finals, c, WORD);
					addback(&finals, tokens->next->value, PIPE);
					c = NULL;
					if(tokens->next->next)
						tokens = tokens->next;
				}
				else if(tokens->next->value[0] == '<')
				{
					if(c)
						addback(&finals, c, WORD);
					addback(&finals, tokens->next->value, LEFTRED);
					c = NULL;
					if(tokens->next->next)
						tokens = tokens->next;	
				}
				else if(tokens->next->value[0] == '>')
				{
					if(c)
						addback(&finals, c, WORD);
					addback(&finals, tokens->next->value, RIGHTRED);
					c = NULL;
					if(tokens->next->next)
						tokens = tokens->next;	
				}
				else if(tokens->next->value[0] == '>' && tokens->next->value[1] == '>')
				{
					if(c)
						addback(&finals, c, WORD);
					addback(&finals, tokens->next->value, APPEND);
					c = NULL;
					if(tokens->next->next)
						tokens = tokens->next;	
				}
				else if(tokens->next->value[0] == '<' && tokens->next->value[1] == '<')
				{
					if(c)
						addback(&finals, c, WORD);
					addback(&finals, tokens->next->value, HEREDOC);
					c = NULL;
					if(tokens->next->next)
						tokens = tokens->next;	
				}
				tokens = tokens->next;
		}
			if(tokens->value[0] != '|')
			{
				c = ft_strjoin(c, tokens->value);
				addback(&finals, c, WORD);
			}
		free(c);	
	}
	while (finals)
	{
		printf("*%s*\n", finals->value);
		finals = finals->next;
	}
}

char    *prompt(void)
{
    char	*line;

	line = readline("\033[33m""minishell$ ""\001\e[0m\002");
	add_history(line);
	
	line = remove_additional_spaces(line);
    return (line);
}

int main()
{
    char	*line;

    while (1)
    {
		line = prompt();
		if (!ft_strcmp(line, "exit"))
			exit(0);
		body(line);
    }
}