/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:10 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/09 15:00:44 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	_error_pipe(t_global *g)
{
	char	*error;

	error = NULL;
	ft_to_break_free(g->path);
	error = strerror(errno);
	write(2, "Error: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(1);
}

void	ft_to_break_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

void	_error_cmd(char **cmd, char *pathname, t_global *g)
{
	write(2, "Error: Command not found.\n", 26);
	if (pathname)
		free(pathname);
	if (cmd)
		ft_to_break_free(cmd);
	if (g->path)
		ft_to_break_free(g->path);
	exit(127);
}

void	_error_next(int i, char **to_free)
{
	if (i == 3)
	{
		write(2, "Error: Pipe creation error.\n", 28);
		ft_to_break_free(to_free);
		exit(1);
	}
	else if (i == 4)
	{
		write(2, "Error: Malloc alocation error.\n", 31);
		ft_to_break_free(to_free);
		exit(11);
	}
	else
		return ;
}

void	_error(int i, char **to_free)
{
	if (i == 0)
	{
		write(2, "Error: You need 4 arguments to make this program run.\n", 54);
		ft_to_break_free(to_free);
		exit(1);
	}
	else if (i == 2)
	{
		write(2, "Error: Command not found.\n", 26);
		ft_to_break_free(to_free);
		exit(127);
	}
	else
		_error_next(i, to_free);
	return ;
}
