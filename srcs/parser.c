/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:21 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/02 15:12:54 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			if (current_token_type == TOKEN_OPTION)
				line = create_option_node(line, list);
			if (*line == '\'' || *line == '"')
				line = create_quote_node(line, list);
			while (find_token_type(line[i]) == current_token_type)
				i++;
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
	if (!tmp->n || tmp->token_type == TOKEN_LITERAL)
	{
		tmp->token_type = TOKEN_COMMAND;
		command_up = 1;
	}
	while (tmp->n)
	{
		if (tmp->token_type == TOKEN_LITERAL)
			analyse_literal_token(tmp, command_up);
		if (tmp->token_type == TOKEN_FLUX)
			find_flux_direction(tmp);
		if (tmp->token_type == TOKEN_PIPE)
		{
			tmp->n->token_type = TOKEN_COMMAND;
			command_up = 0;
		}
		tmp = tmp->n;
	}
}

void	reorganize_commandline(t_node **list)
{
	t_node	*tmp;
	t_node	*scout;
	
	tmp = *list;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		if (tmp->n->token_type >= R_FLUX_CREATE && tmp->n->token_type <= L_FLUX_APPEND)
		{
			scout = tmp;
			while (scout && scout->token_type != TOKEN_PIPE)
			{
				if (scout->token_type != TOKEN_FILE && (scout->token_type < R_FLUX_CREATE && scout->token_type > L_FLUX_APPEND))
					swap_nodes(tmp, scout);
				scout = scout->n;
			}
		}
		tmp = tmp->n;
	}
}

void	input_parser(char *line)
{
	t_node	*list;

	lexer_parser(line, &list);
	syntax_parser(&list);
	if (found_token_flux(&list))
		reorganize_commandline(&list);
	print_list(&list);
}
