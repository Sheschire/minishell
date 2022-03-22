/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/22 13:16:00 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_env(char *var, char **env)
{
	char	*var_value;
	int		i;

	i = -1;
	var_value = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
		{
			if (env[i][ft_strlen(var)] == '=')
			{
				var_value = env[i];
				while (*var_value != '=')
					var_value++;
				var_value++;
				return (var_value);
			}
		}
	}
	return ("");
}

void	expand_variables_3(t_node *node, t_global *g, int i, int j)
{
	char	*tmp;
	char	*var;
	char	*dup;

	tmp = ft_substr(node->s, j, i - j);
	var = ft_strdup(parse_env(tmp, g->env));
	if (ft_strcmp(var, ""))
	{
		dup = recreate_string(tmp, var, node, j - 1);
		free(node->s);
		node->s = dup;
	}
	else
		recreate_string_with_empty(node, tmp, j);
	free(tmp);
	free(var);
}

int	expand_variables_2(t_node *node, t_global *g, int i)
{
	int	j;

	if (!node->s[i] || is_in_set(node->s[i], "\'\""))
		return (0);
	j = i;
	while (node->s[i] && !is_in_set(node->s[i], " \'\"$"))
		i++;
	expand_variables_3(node, g, i, j);
	return (1);
}

void	expand_variables(t_node *node, t_global *g)
{
	int		i;

	i = 0;
	while (node->s[i])
	{
		if (node->s[i] && node->s[i] == '\'' && \
		find_pair(node->s, i, node->s[i]))
			while (node->s[++i])
				if (node->s[i] == '\'')
					break ;
		if (node->s[i] == '$')
		{
			if (expand_variables_2(node, g, i + 1))
				i = 0;
		}
		else
			i++;
	}
}
