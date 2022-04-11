/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:41:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/11 16:04:17 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*testpath_builder(t_global *g, char *cmd, int i)
{
	char	*pathname;

	if (cmd == NULL)
	{
		if (cmd)
			free(cmd);
		_error(2, g->path);
	}
	pathname = (char *)ft_calloc(sizeof(char),
			(ft_strlen(g->path[i]) + ft_strlen(cmd) + 2));
	ft_strcat(g->path[i], pathname);
	ft_strcat("/", pathname);
	ft_strcat(cmd, pathname);
	return (pathname);
}

int	check_dir_cmd(char **cmd)
{
	DIR	*dir;

	dir = opendir(cmd[0]);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	else
		return (0);
}

void	_error_cases(char *path, char **cmd, t_global *g, t_node *node)
{
	int	need_free;

	need_free = 0;
	if (path == NULL || !ft_strcmp(cmd[0], "..") || !ft_strcmp(cmd[0], "\0"))
		_error_cmd(cmd, path, g, node);
	else if (!ft_strcmp(cmd[0], "."))
	{
		ft_putstr_fd("minishell: .: filename argument required", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		need_free = 2;
	}
	else if (access(cmd[0], X_OK) == 0)
		need_free = check_dir_cmd(cmd);
	if (need_free)
	{
		if (path && node->is_child)
			free(path);
		free_array(g->env);
		free_array(g->path);
		free_list(&g->list);
		exit(need_free);
	}
}

void	create_cmd_parent(char **cmd, t_global *g, t_node *node)
{
	char	*pathname;
	int		i;

	i = -1;
	pathname = NULL;
	if (access(cmd[0], X_OK) == 0)
		pathname = cmd[0];
	while (g->path && g->path[++i] && pathname == NULL)
	{
		pathname = testpath_builder(g, cmd[0], i);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
	}
	_error_cases(pathname, cmd, g, node);
	free(cmd[0]);
	cmd[0] = pathname;
	execve(pathname, cmd, g->env);
}

void	find_cmd_path(char **cmd, t_global *g, t_node *node)
{
	char	*pathname;
	int		i;

	i = -1;
	pathname = NULL;
	if (is_builtin(cmd))
	{
		is_builtin_exec(cmd, g, INT_MAX, node);
		free_builtins(g);
	}
	if (access(cmd[0], X_OK) == 0)
		pathname = cmd[0];
	while (g->path && g->path[++i] && pathname == NULL)
	{
		pathname = testpath_builder(g, cmd[0], i);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
	}
	_error_cases(pathname, cmd, g, node);
	cmd[0] = pathname;
	signal(SIGQUIT, SIG_DFL);
	execve(pathname, cmd, g->env);
}
