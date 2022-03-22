/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:48:07 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/22 17:29:56 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pair(char *s, int i, char c)
{
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

int	dup_size(char *s)
{
	int		i;
	char	actual_quote;
	int		pair_to_remove;

	i = -1;
	actual_quote = 0;
	pair_to_remove = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			actual_quote = s[i];
			if (find_pair(s, i, actual_quote))
				pair_to_remove++;
			i++;
			while (s[i] && s[i] != actual_quote)
				i++;
			if (!s[i])
				return (i);
		}
	}
	return (i - (pair_to_remove * 2));
}

void	dup_without_quotes(char *dup, char *s)
{
	int		i;
	int		j;
	char	actual_quote;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && find_pair(s, i, s[i]))
		{
			actual_quote = s[i];
			while (s[++i] != actual_quote)
			{
				dup[j] = s[i];
				j++;
			}
		}
		else
		{
			dup[j] = s[i];
			j++;
		}
	}
	dup[j] = '\0';
}

void	dequote(t_node *list, t_global *g, int i)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (dup_size(list->cmd[i]) + 1));
	if (!dup)
		ft_exit_signal(g);
	dup_without_quotes(dup, list->cmd[i]);
	free(list->cmd[i]);
	list->cmd[i] = dup;
}

void	recreate_cmd(t_node *list)
{
	int	i;
	int	nb_empty;
	char	**cmd_cpy;
	int	j;

	i = 0;
	j = 0;
	nb_empty = 0;
	i = 0;
	while (list->cmd[i])
	{
		if (!ft_strcmp(list->cmd[i], ""))
			nb_empty++;
		i++;
	}
	if (nb_empty)
	{
		cmd_cpy = (char **)calloc(i - nb_empty + 1, sizeof(char *));
		i = -1;
		while (list->cmd[++i])
		{
			if (ft_strcmp(list->cmd[i], ""))
				cmd_cpy[j++] = ft_strdup(list->cmd[i]);
		}
		free_array(list->cmd);
		list->cmd = cmd_cpy;
	}
}

void	quote_expand_parser(t_node **list, t_global *g)
{
	int		i;
	t_node	*tmp;

	tmp = (*list);
	while (*list)
	{
		if ((*list)->token_type == CMD)
		{
			i = 0;
			while ((*list)->cmd[i])
			{
				if (!ft_strcmp((*list)->cmd[i], "$?"))
				{
					free((*list)->cmd[i]);
					(*list)->cmd[i] = ft_itoa(g_sig.exit_status);
				}
				if (ft_strchr((*list)->cmd[i], '$'))
					expand_variables(*list, g, i);
				if (ft_strchr((*list)->cmd[i], '\'') || ft_strchr((*list)->cmd[i], '\"'))
					dequote(*list, g, i);
				i++;
			}
			recreate_cmd(*list);
		}
		(*list) = (*list)->n;
	}
	(*list) = tmp;
}
