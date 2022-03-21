/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:48:07 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/21 10:46:40 by tlemesle         ###   ########.fr       */
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

void	dequote(t_node *tmp, t_global *g)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (dup_size(tmp->s) + 1));
	if (!dup)
		ft_exit_signal(g);
	dup_without_quotes(dup, tmp->s);
	free(tmp->s);
	tmp->s = dup;
}

void	quote_expand_parser(t_node **list, t_global *g)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->s, "$?"))
		{
			free(tmp->s);
			tmp->s = ft_itoa(g_sig.exit_status);
		}
		if (ft_strchr(tmp->s, '$'))
			expand_variables(tmp, g);
		if (ft_strchr(tmp->s, '\'') || ft_strchr(tmp->s, '\"'))
			dequote(tmp, g);
		tmp = tmp->n;
	}
}
