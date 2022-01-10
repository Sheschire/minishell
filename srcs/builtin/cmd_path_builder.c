/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:41:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/01/10 15:48:22 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/**
**	As its name says "testpath_builder" will
**	create a path to try to access our command.
**/

char	*testpath_builder(t_global *g, char *cmd, int i)
{
	char	*pathname;

	if (cmd == NULL)
	{
		if (cmd)
			free(cmd);
		_error(2, g->path);
	}
	pathname = (char *)calloc(sizeof(char),
			(ft_strlen(g->path[i]) + ft_strlen(cmd) + 2));
	ft_strcat(g->path[i], pathname);
	ft_strcat("/", pathname);
	ft_strcat(cmd, pathname);
	return (pathname);
}

/**
**	"find_cmd_path" will call "testpath_builder"
**	and try to access() the test path given by it.
**	In case of failure it will try another test path.
**	In case of success it will execve() the cmd path
**	and its flags if there are some.
**	If there are no path to the cmd, it will launch _error_cmd()
**	to free everything and exit the process.
**/

void	find_cmd_path(char **builtcmd, t_global *g, t_node *node)
{
	char	*pathname;
	int		i;

	i = -1;
	pathname = NULL;
	if (access(builtcmd[0], F_OK) == 0)
		pathname = builtcmd[0];
	while (g->path && g->path[++i] && pathname == NULL)
	{
		pathname = testpath_builder(g, builtcmd[0], i);
		if (access(pathname, F_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
	}
	if (pathname == NULL)
		_error_cmd(builtcmd, pathname, g);
	free(builtcmd[0]);
	builtcmd[0] = pathname;
	execve(pathname, builtcmd, g->env);
	ft_to_break_free(g->path);
	ft_to_break_free(builtcmd);
	exit(0);
	return ;
}
