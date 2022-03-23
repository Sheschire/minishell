/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/23 11:30:44 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recreate_cmd(t_node *list, int j)
{
	int		i;
	int		nb_empty;
	char	**cmd_cpy;

	i = 0;
	nb_empty = 0;
	while (list->cmd[i])
	{
		if (!ft_strcmp(list->cmd[i], ""))
			nb_empty++;
		i++;
	}
	if (nb_empty)
	{
		cmd_cpy = (char **)ft_calloc(i - nb_empty + 1, sizeof(char *));
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

void	expand_variables_3(t_global *g, int i, int j, int cmdi)
{
	char	*tmp;
	char	*var;
	char	*dup;

	tmp = ft_substr(g->list->cmd[cmdi], j, i - j);
	var = ft_strdup(parse_env(tmp, g->env));
	if (ft_strcmp(var, ""))
	{
		dup = recreate_string(tmp, var, g->list->cmd[cmdi], j - 1);
		free(g->list->cmd[cmdi]);
		g->list->cmd[cmdi] = dup;
	}
	else
		recreate_string_with_empty(g, tmp, j, cmdi);
	free(tmp);
	free(var);
}

int	expand_variables_2(t_node *list, t_global *g, int i, int cmdi)
{
	int	j;

	if (!list->cmd[cmdi][i] || is_in_set(list->cmd[cmdi][i], "\'\""))
		return (0);
	j = i;
	while (list->cmd[cmdi][i] && !is_in_set(list->cmd[cmdi][i], " \'\"$"))
		i++;
	expand_variables_3(g, i, j, cmdi);
	return (1);
}

void	expand_variables(t_node *list, t_global *g, int cmdi)
{
	int		j;

	j = 0;
	while (list->cmd[cmdi][j])
	{
		if (list->cmd[cmdi][j] && list->cmd[cmdi][j] == '\'' && \
		find_pair(list->cmd[cmdi], cmdi, list->cmd[cmdi][j]))
			while (list->cmd[cmdi][++j])
				if (list->cmd[cmdi][j] == '\'')
					break ;
		if (list->cmd[cmdi][j] == '$')
		{
			if (expand_variables_2(list, g, j + 1, cmdi))
				j = 0;
		}
		else
			j++;
	}
}
