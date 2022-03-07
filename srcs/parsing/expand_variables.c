/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/07 14:26:15 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	replace_expand(char *dup, char *to_replace, int j)
{
	int	i;

	i = -1;
	while (to_replace[++i])
	{
		dup[j] = to_replace[i];
		j++;
	}
	return (j);
}

void	recreate_string(char *to_find, char *to_replace, t_node *node)
{
	char	*dup;
	int		i;
	int		j;
	int		replaced_one;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(node->s) + \
	ft_strlen(to_replace) - (ft_strlen(to_find) + 1) + 1));
	i = -1;
	j = 0;
	replaced_one = 0;
	while (node->s[++i])
	{
		if (node->s[i] == '$' && !replaced_one)
		{
			j = replace_expand(dup, to_replace, j);
			i += ft_strlen(to_find) + 1;
			replaced_one = 1;
		}
		dup[j] = node->s[i];
		j++;
	}
	dup[j] = '\0';
	free(node->s);
	node->s = dup;
}

void	expand_variables_2(t_node *node, t_global *g, int i, int j)
{
	char	*tmp;
	char	*var;

	tmp = ft_substr(node->s, j, i - j);
	var = ft_strdup(parse_env(tmp, g->env));
	if (var)
		recreate_string(tmp, var, node);
	free(tmp);
	free(var);
}

void	expand_variables(t_node *node, t_global *g)
{
	int		i;
	int		j;

	i = -1;
	while (node->s[++i])
	{
		if (node->s[i] == '\'' && find_pair(node->s, i, node->s[i]))
			while (node->s[++i] && node->s[i] != '\'')
				i++;
		if (node->s[i] == '$')
		{
			if (!node->s[i + 1] || is_in_set(node->s[i + 1], "\'\""))
				return ;
			i++;
			j = i;
			while (node->s[i] && !is_in_set(node->s[i], " \'\"$"))
				i++;
			expand_variables_2(node, g, i, j);
			i = -1;
		}
	}
}
