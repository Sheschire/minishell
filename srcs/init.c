/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:24:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/07 13:48:29 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_cp_std(t_global *g)
{
	dup2(g->cp_stdin, STDIN_FILENO);
	close(g->cp_stdin);
	dup2(g->cp_stdout, STDOUT_FILENO);
	close(g->cp_stdout);
}

char	**get_path(char **env)
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

void	init_global(t_global *g, char **envp)
{
	if (!envp)
	{
		write(2, "No environment detected\n", 24);
		write(2, "Minishell needs an environment to run properly.\n", 48);
		exit(1);
	}
	g->path = get_path(envp);
	g->env = ft_get_all_env(envp);
	g->list = NULL;
	g->cmd_nbr = 0;
	g->status = 0;
	g_sig.exit_status = 0;
}

void	init_cmd_nodes(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->cmd = NULL;
		tmp = tmp->n;
	}
}
