/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:21 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/04 16:03:01 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_parser(char *line, t_node **list)
{
	int		current_token_type;
	int		i;

	
	while (*line) 
	{
		i = 0;
		if (find_token_type(*line))
		{
			current_token_type = find_token_type(*line);
			while (find_token_type(line[i]) == current_token_type)
			{
				if (line[i] == '\'' || line[i] == '\"')
					i = find_quote_pair(line, line[i], i + 1);
				if (find_token_type(line[i]) == current_token_type)
					i++;
			}
			if (*line && find_token_type(*line))
				newnode_add_back(ft_substr(line, 0, i), current_token_type, list);
			line += i;
		}
		if (*line && find_token_type(*line) == 0)
			line++;
	}
}

void	syntax_parser(t_node **list)
{
	t_node *tmp;
	int	command_up;

	tmp = *list;
	command_up = 0;
	check_syntax_error(list);
	if (!tmp->n || (tmp->token_type != TOKEN_PIPE && tmp->token_type != TOKEN_FLUX))
	{
		tmp->token_type = TOKEN_COMMAND;
		command_up = 1;
	}
	while (tmp)
	{
		if (tmp->token_type == TOKEN_FLUX)
			find_flux_direction(tmp);
		if (tmp->token_type == TOKEN_PIPE)
		{
			if (tmp->n)
				tmp->n->token_type = TOKEN_COMMAND;
			command_up = 0;
		}
		tmp = tmp->n;
	}
}

void	input_parser(char *line, t_global *g)
{
	t_node	*list;

	list = 0;
	lexer_parser(line, &list);
	syntax_parser(&list);
	if (found_token_flux(&list))
		reorganize_commandline(&list);
	quote_expand_parser(&list, g);
	group_nodes_into_commands(&list);
	g->list = &list;
	//print_list(g->list);
}
