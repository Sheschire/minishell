/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:48:07 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/29 13:20:32 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	reformat(t_node *l, t_global *g, int i)
{
	if (!ft_strcmp(l->cmd[i], "$?"))
	{
		free(l->cmd[i]);
		l->cmd[i] = ft_itoa(g_sig.exit_status);
	}
	if (ft_strchr(l->cmd[i], '$'))
		expand_variables(l, g, i);
	if (ft_strchr(l->cmd[i], '\'') || ft_strchr(l->cmd[i], '\"'))
		dequote(l, g, i);
}

void	quote_expand_parser(t_node **l, t_global *g, int i)
{
	t_node	*tmp;

	tmp = (*l);
	while (*l)
	{
		if ((*l)->token_type == CMD)
		{
			i = -1;
			while ((*l)->cmd[++i])
				reformat(*l, g, i);
			recreate_cmd(*l, 0);
		}
		(*l) = (*l)->n;
	}
	(*l) = tmp;
}
