/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/08 12:35:21 by tlemesle         ###   ########.fr       */
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
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(g_sig.exit_status));
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

char	*expand(t_global *g, int i, int j, int cmdi)
{
	char	*tmp;
	char	*var;
	char	*dup;

	if (g->list->cmd[cmdi][j] == '?')
	{
		tmp = ft_substr(g->list->cmd[cmdi], j, 1);
		var = parse_env(tmp, g->env);
	}
	else
	{
		tmp = ft_substr(g->list->cmd[cmdi], j, i - j);
		var = ft_strdup(parse_env(tmp, g->env));
	}
	if (g->double_quotes == 0)
		var = split_var(var, g);
	if (ft_strcmp(var, ""))
	{
		dup = recreate_string(tmp, var, g->list->cmd[cmdi], j - 1);
		free(g->list->cmd[cmdi]);
		g->list->cmd[cmdi] = dup;
	}
	else
		recreate_string_with_empty(g, tmp, j, cmdi);
	return (recreate_cmd_varsplit(g), free(tmp), var);
}

int	run_to_limiters(t_node *list, t_global *g, int i, int cmdi)
{
	int		j;
	char	*var;

	if (!list->cmd[cmdi][i])
		return (0);
	j = i;
	while (list->cmd[cmdi][i] && \
	!is_in_set(list->cmd[cmdi][i], g->expand_limiters))
		i++;
	var = expand(g, i, j, cmdi);
	j = (int)ft_strlen(var);
	free(var);
	return (j - 1);
}

void	expand_variables(t_node *list, t_global *g, int cmdi)
{
	int		j;

	j = 0;
	g->expand_limiters = ft_strdup(" \'\"$=+-*^%#@!~.,:{}[]?/");
	g->double_quotes = 0;
	while (list->cmd[cmdi][j])
	{
		if (list->cmd[cmdi][j] == '\"' && \
		find_pair(list->cmd[cmdi], j, list->cmd[cmdi][j]))
			extend_limiters_list(g, 0);
		if (list->cmd[cmdi][j] && list->cmd[cmdi][j] == '\'' && \
		find_pair(list->cmd[cmdi], j, list->cmd[cmdi][j]))
			while (list->cmd[cmdi][++j])
				if (list->cmd[cmdi][j] == '\'')
					break ;
		if (list->cmd[cmdi][j] == '$')
		{
			if (is_in_set(list->cmd[cmdi][j + 1], g->expand_limiters))
				j++;
			else
				j += run_to_limiters(list, g, j + 1, cmdi);
		}
		j++;
	}
	free(g->expand_limiters);
}
