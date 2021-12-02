/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/02 15:41:27 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*path_finder(char **envp)
{
	int		i;
	int		j;
	char	*path;
	char	*str;

	str = "PATH=";
	path = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == str[j])
			j++;
		if (!str[j])
		{
			path = envp[i];
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	char	*path;
	char	**paths;

	path = path_finder(envp);
	if (*path)
	{
		path = path + 5;
		paths = ft_split(path, ':');
		return (paths);
	}
	else
		return (NULL);
}

void	define_pipe_position(t_global *g)
{
	if (g->cmd_nbr == 2)
	{
		g->pipe_before = 0;
		g->pipe_after = 1;
	}
	else
	{
		g->pipe_before = 1;
		g->pipe_after = 1;
	}
	return ;
}

void	launch_pipex(t_global *g)
{
	int	i;
	int	pid;

	g->status = 0;
	i = 0;
	pid = 1;
	while (++i < g->ac - 3 && pid != 0)
		pid = fork();
	if (pid == -1)
		_error(3, g->path);
	else if (pid > 0)
	{
		waitpid(pid, &g->status, 0);
		parent_process(g, g->av);
	}
	else
	{
		g->cmd_nbr = i;
		define_pipe_position(g);
		child_process(g, g->av);
	}
	return ;
}

void	pipex(t_global *g, t_node *node)
{
	g.path = get_path(envp);
	//1) create seconde list frome the first > Merging the command with its options.
	//ft_assign_files();
	//is_builtin();
	if (pipe(g._pipe[1]) == -1)
		_error(3, g.path);
	launch_pipex(&g);
	return (0);
}
