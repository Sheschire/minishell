/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:24:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/06 14:30:16 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(void)
{
	char	**path;
	char	*path_string;

	path_string = getenv("PATH");
	path = ft_split(path_string, ':');
	return (path);
}

char	**ft_get_all_env(char **envp)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		new_env[i] = (char *)ft_calloc(ft_strlen(envp[i]) + 1,
				sizeof(char));
		j = -1;
		while (envp[i][++j])
			new_env[i][j] = envp[i][j];
		new_env[i][j] = '\0';
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_set_shlvl(t_global *g, char **env)
{
	char	*var;
	char	*shlvl;
	char	*var_env;
	int		value;

	var = parse_env("SHLVL", env);
	value = ft_atoi(var) + 1;
	var = ft_itoa(value);
	shlvl = ft_strdup("SHLVL=");
	var_env = ft_strjoin(shlvl, var);
	ft_export_variable(var_env, g);
	free(var);
	free(var_env);
}

void	init_global(t_global *g, char **envp)
{
	g->path = get_path();
	g->env = ft_get_all_env(envp);
	ft_set_shlvl(g, g->env);
	g->list = NULL;
	g->cmd_nbr = 0;
	g->status = 0;
	g->child_exist = 0;
	g_sig.exit_status = 0;
	g->syntax_err = 0;
	g->cp_stdin = dup(STDIN_FILENO);
	g->cp_stdout = dup(STDOUT_FILENO);
}

void	init_cmd_nodes(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->cmd = NULL;
		tmp->here_str = NULL;
		tmp->here_doc_quotes_removed = 0;
		tmp = tmp->n;
	}
}
