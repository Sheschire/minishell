/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:06:26 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/10 17:21:38 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	analyse_literal_token(t_node *tmp, int command_up)
{
	if (!command_up)
	{
		if (tmp->n && (tmp->n->token_type == TOKEN_OPTION))
			if (tmp->token_type != TOKEN_OPTION)
				tmp->token_type = TOKEN_COMMAND;
	}
	else
		tmp->token_type = TOKEN_ARG;
}

int	find_quote_pair(char *line, char c, int i)
{
	int	save;

	save = i;
	while (line[i] && line[i] != c)
		i++;
	if (line[i] == c)
		return (i + 1);
	else
		return (save);
}

void	check_syntax_error(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (is_redir(tmp) && (!tmp->n || is_redir(tmp->n) || \
		tmp->n->token_type == TOKEN_PIPE))
			printf("SYNTAX ERROR\n");
		if (!tmp->n && tmp->token_type == TOKEN_PIPE)
			printf("SYNTAX ERROR\n");
		tmp = tmp->n;
	}
}

int	find_token_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '>' || c == '<')
		return (TOKEN_FLUX);
	if (c == ' ')
		return (0);
	if (c >= 32 && c <= 127)
		return (TOKEN_LITERAL);
	return (0);
}
