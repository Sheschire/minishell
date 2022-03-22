/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:21 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/22 15:46:44 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_parser(char *line, t_node **list)
{
	int		curr_token_type;
	int		i;

	curr_token_type = 0;
	while (*line)
	{
		i = 0;
		if (find_token_type(*line))
		{
			curr_token_type = find_token_type(*line);
			while (find_token_type(line[i]) == curr_token_type)
			{
				if (line[i] == '\'' || line[i] == '\"')
					i = find_quote_pair(line, line[i], i + 1);
				if (find_token_type(line[i]) == curr_token_type)
					i++;
			}
			if (*line && find_token_type(*line))
				newnode_add_back(ft_substr(line, 0, i), curr_token_type, list);
			line += i;
		}
		if (*line && find_token_type(*line) == 0)
			line++;
	}
	return (curr_token_type);
}

void	tmp_loop(t_node *tmp, int *cmd_up)
{
	if (tmp->token_type == TOKEN_FLUX)
		find_flux_direction(tmp);
	if (tmp->token_type == TOKEN_PIPE)
	{
		if (tmp->n)
			tmp->n->token_type = TOKEN_COMMAND;
		*cmd_up = 0;
	}
}

void	syntax_parser(t_node **list, t_global *g)
{
	t_node	*tmp;
	int		command_up;

	tmp = *list;
	command_up = 0;
	check_syntax_error(list, g);
	if (!g->syntax_err)
	{
		if (!tmp->n || (tmp->token_type != TOKEN_PIPE && \
		tmp->token_type != TOKEN_FLUX))
		{
			tmp->token_type = TOKEN_COMMAND;
			command_up = 1;
		}
		while (tmp)
		{
			tmp_loop(tmp, &command_up);
			tmp = tmp->n;
		}
	}
}

int	input_parser(char *line, t_global *g)
{
	if (!lexer_parser(line, &g->list))
		return (0);
	syntax_parser(&g->list, g);
	if (found_token_flux(&g->list))
		reorganize_commandline(&g->list);
	group_nodes_into_commands(&g->list);
	quote_expand_parser(&g->list, g);
//	print_list(&g->list);
	return (1);
}
