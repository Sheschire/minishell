/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:53:48 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/05 12:24:35 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recreate_cmd_varsplit(t_global *g)
{
	char	*str;
	int		size;
	int		i;

	size = 0;
	i = -1;
	if (g->double_quotes == 0)
	{
		while (g->list->cmd[size])
			size++;
		while (++i < size)
			if (!ft_strcmp(g->list->cmd[i], ""))
				return ;
		str = ft_strjoin_charset(size, g->list->cmd, " ");
		free_array(g->list->cmd);
		g->list->cmd = ft_split(str, ' ');
		free(str);
	}
}

char	*split_var(char *var, t_global *g)
{
	char	**var_split;
	int		size;
	char	*dup;

	if (g->double_quotes == 0)
	{
		size = 0;
		var_split = ft_split(var, ' ');
		while (var_split[size])
			size++;
		free(var);
		var = ft_strjoin_charset(size, var_split, " ");
		free_array(var_split);
	}
	else
	{
		dup = ft_strdup(var);
		free(var);
		var = dup;
	}
	return (var);
}
