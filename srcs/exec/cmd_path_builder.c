/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:41:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/03 16:03:55 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcat(char *src, char *dest)
{
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
	return ;
}

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
	if (pathname == NULL || !ft_strcmp(cmd[0], "..") || !ft_strcmp(cmd[0], "."))
		_error_cmd(cmd, pathname, g, node);
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
	if (pathname == NULL || !ft_strcmp(cmd[0], "..") || !ft_strcmp(cmd[0], "."))
		_error_cmd(cmd, pathname, g, node);
	cmd[0] = pathname;
	signal(SIGQUIT, SIG_DFL);
	execve(pathname, cmd, g->env);
}
