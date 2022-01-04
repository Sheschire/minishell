/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/01/04 14:22:42 by barodrig         ###   ########.fr       */
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
	int		pid;

	pid = fork();
	if (pipe(g->_pipe_heredoc) == -1)
		write(2, "NOT WORKING PIPE\n", 17);
	if (pid == 0)
	{
		while (get_next_line(0, &line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(1);
			write(STDIN_FILENO, line, ft_strlen(line));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(g->_pipe_heredoc[1]);
		dup2(g->_pipe_heredoc[0], STDIN_FILENO);
		close(g->_pipe_heredoc[0]);
		ft_bzero_pipe(g);
	}
}
