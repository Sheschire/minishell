/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:10 by barodrig          #+#    #+#             */
/*   Updated: 2022/02/02 14:33:05 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_pipe(t_global *g)
{
	char	*error;

	error = NULL;
	ft_to_break_free(g->path);
	error = strerror(errno);
	write(2, "Error: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
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
	g_sig.exit_status = 127;
	exit(EXIT_FAILURE);
}

void	_error(int i, char **to_free)
{
	if (i == 0)
	{
		write(2, "Error: Command not found.\n", 26);
		ft_to_break_free(to_free);
		g_sig.exit_status = 127;
		exit(EXIT_FAILURE);
	}
	else if (i == 1)
	{
		write(2, "Error: Malloc alocation error.\n", 31);
		ft_to_break_free(to_free);
		g_sig.exit_status = 11;
		exit(EXIT_FAILURE);
	}
	return ;
}
