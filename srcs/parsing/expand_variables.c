/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/04 16:49:39 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_env(char *var, char **env)
{
	char	*var_value;

	var_value = getenv(var);
	if (var_value != NULL)
		var = var_value;
}

void	rebuild_string(t_node *tmp, char **env, int i)
{
	char	*buf;
	char	*var;
	char	*new_string;

	buf = NULL;
	if (i > 0)
	{
		buf = ft_substr(tmp->s, 0, i);
		tmp->s += i + 1;
		i = 0;
	}
	else
		tmp->s++;
	while (tmp->s[i] && tmp->s[i] != '$')
		i++;
	var = ft_substr(tmp->s, 0, i);
	parse_env(var, env);
	printf("var = %s\n", var);
}

void	expand_variables(t_node **list, t_global *g)
{
	t_node	*tmp;
	int		i;
	
	tmp = *list;
	while (tmp)
	{
		i = -1;
		while (tmp->s[++i])
		{
			if (tmp->s[i] == '$')
				rebuild_string(tmp, g->env, i);
		}
		tmp = tmp->n;
	}
}