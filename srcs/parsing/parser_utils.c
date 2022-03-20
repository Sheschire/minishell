/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:06:26 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/20 12:40:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_syntax_error(char *token_err, t_global *g, t_node **list)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	ft_putstr_fd(token_err, 2);
	ft_putstr_fd("'\n", 2);
	g->syntax_err = 1;
	free_list(list);
}

void	check_syntax_error(t_node **list, t_global *g)
{
	t_node	*tmp;
	char	*token_err;

	tmp = *list;
	token_err = ft_strdup("");
	while (tmp)
	{
		if ((is_redir(tmp) && (!tmp->n || is_redir(tmp->n) || \
		tmp->n->token_type == TOKEN_PIPE)) || \
		(!tmp->n && tmp->token_type == TOKEN_PIPE))
		{
			free(token_err);
			token_err = ft_strdup(tmp->s);
		}
		tmp = tmp->n;
	}
	if (ft_strcmp(token_err, ""))
		print_syntax_error(token_err, g, list);
	free(token_err);
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
