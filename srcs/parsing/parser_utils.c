/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:06:26 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/03 14:30:27 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_syntax_error(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (is_redir(tmp) && (!tmp->n || is_redir(tmp->n) || tmp->n->token_type == TOKEN_PIPE))
			printf("SYNTAX ERROR\n");
		if (!tmp->n && tmp->token_type == TOKEN_PIPE)
			printf("SYNTAX ERROR\n");
		tmp = tmp->n;
	}
}

int	is_redir(t_node *tmp)
{
	int	type;

	type = tmp->token_type;
	if ((tmp->token_type >= R_FLUX_CREATE && tmp->token_type <= L_FLUX_APPEND) || tmp->token_type == TOKEN_FLUX)
		return (1);
	return (0);
}

int	found_token_flux(t_node **list)
{
	t_node	*tmp;
	int		nb_flux;

	tmp = *list;
	nb_flux = 0;
	while (tmp)
	{
		if (is_redir(tmp))
			nb_flux += 2;
		tmp = tmp->n;
	}
	return (nb_flux);
}

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

void    find_flux_direction(t_node *tmp)
{
	if (!ft_strcmp(tmp->s, ">"))
		tmp->token_type = R_FLUX_CREATE;
	if (!ft_strcmp(tmp->s, ">>"))
		tmp->token_type = R_FLUX_APPEND;
	if (!ft_strcmp(tmp->s, "<"))
		tmp->token_type = L_FLUX_CREATE;
	if (tmp->n && is_redir(tmp) && tmp->n->token_type != TOKEN_PIPE)
		tmp->n->token_type = TOKEN_FILE;
	if (!ft_strcmp(tmp->s, "<<"))
	{
		tmp->token_type = L_FLUX_APPEND;
		if (tmp->n && tmp->n->token_type != TOKEN_PIPE)
			tmp->n->token_type = HERE_DOC;
	}
}

char    *create_double_quote_node(char *line, t_node **list)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] == '"' && is_in_set(line[i + 1], " |><"))
	{
		newnode_add_back(ft_substr(line, 0, i + 1), DOUBLE_QUOTE_NODE, list);
		return (line + i + 1);
	}
	else if (line[i] == '"')
	{
		while (line[i] && !is_in_set(line[i], " |><"))
			i++;
		newnode_add_back(ft_substr(line, 0, i), DOUBLE_QUOTE_NODE, list);
		return (line + i);
	}
	return (line);
}

char    *create_quote_node(char *line, t_node **list)
{
	int i;

	i = 1;
	if (*line == '\'')
	{
		while (line[i] && line[i] != '\'')
			i++;
		if (line[i] == '\'' && is_in_set(line[i + 1], " |><"))
		{
			newnode_add_back(ft_substr(line, 0, i + 1), SINGLE_QUOTE_NODE, list);
			return (line + i + 1);
		}
		else if (line[i] == '\'')
		{
			while (line[i] && !is_in_set(line[i], " |><"))
				i++;
			newnode_add_back(ft_substr(line, 0, i), SINGLE_QUOTE_NODE, list);
			return (line + i);
		}
	}
	else if (*line == '"')
		line = create_double_quote_node(line, list);
	return (line);
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

char	*create_option_node(char *line, t_node **list)
{
	int		i;
	t_node	*tmp;

	i = 1;
	if (!find_token_type(line[i]))
	{
		newnode_add_back("-", TOKEN_LITERAL, list);
		return (line + 1);
	}
	else
	{
		while (find_token_type(line[i]))
		{
			if (line[i] == '\'' || line[i] == '\"')
				i += find_quote_pair(line, line[i], i + 1);
			i++;
		}
		newnode_add_back(ft_substr(line, 0, i), TOKEN_OPTION, list);
		return (line + i);
	}
	return (line);
}

int		find_token_type(char c)
{
	// if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	// 	return (TOKEN_LITERAL);
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '>' || c == '<')
		return (TOKEN_FLUX);
	if (c == ' ')
		return (0);
	if (c >= 32 && c <= 127)
		return (TOKEN_LITERAL);
	// if (c == '\'' || c == '"' || c == '/' || c == '=' || c == '$' || c == '-')
	// 	return (TOKEN_LITERAL);
	// if (c == '-')
	// 	return (TOKEN_OPTION);
	return (0);
}
