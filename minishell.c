/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:40 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/04 14:05:54 by byoussef         ###   ########.fr       */
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
		c = NULL;
		finals_m(tokens, &finals);
		while (finals)
		{
			printf("*%s*  %d\n", finals->value, finals->type);
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
		free(line);
    }
}
