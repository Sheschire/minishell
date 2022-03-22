/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/22 12:32:26 by tlemesle         ###   ########.fr       */
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

int	replace_expand(char *dup, char *to_replace, int j)
{
	int	i;

	i = 0;
	while (to_replace[i])
		dup[j++] = to_replace[i++];
	return (j);
}

void	recreate_string_with_empty(t_node *node, char *tmp, int j)
{
	char	*sub1;
	char	*sub2;
	char	*join;

	sub1 = ft_substr(node->s, 0, j - 1);
	if ((j + ft_strlen(tmp)) == ft_strlen(node->s))
		sub2 = ft_strdup("");
	else
		sub2 = ft_substr(node->s, j + ft_strlen(tmp), ft_strlen(node->s) - ft_strlen(tmp));
	join = ft_strjoin(sub1, sub2);
	free(node->s);
	node->s = ft_strdup(join);
	if (!ft_strcmp(node->s, ""))
		printf("\n");
	free(join);
	free(sub2);
}

char	*recreate_string(char *to_find, char *to_replace, t_node *node, int start)
{
	char	*dup;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(node->s) + ft_strlen(to_replace) - ft_strlen(to_find);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (node->s[i])
	{
		while (i < start)
			dup[j++] = node->s[i++];
		j = replace_expand(dup, to_replace, j);
		i += ft_strlen(to_find) + 1;
		if (node->s[i])
			while (node->s[i])
				dup[j++] = node->s[i++];
	}
	dup[j] = '\0';
	return (dup);
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
		if (node->s[i] && node->s[i] == '\'' && find_pair(node->s, i, node->s[i]))
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
