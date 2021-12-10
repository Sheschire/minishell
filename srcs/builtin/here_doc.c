/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/10 11:48:59 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_useless_here_doc(char *limiter)
{
	char	*line;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		while (get_next_line(0, &line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(1);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_here_doc(char *limiter)
{
	char	*line;
	int		_pipe_here[2];
	int		pid;

	if (pipe(_pipe_here[2]) == -1)
		ft_error_pipe();
	pid = fork();
	if (pid == 0)
	{
		while (get_next_line(0, &line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(1);
			write(_pipe_here[1], line, ft_strlen(line));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(_pipe_here[1]);
		dup2(_pipe_here[0], STDIN_FILENO);
	}
}
