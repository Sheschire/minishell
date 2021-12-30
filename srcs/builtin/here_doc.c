/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/30 14:14:07 by barodrig         ###   ########.fr       */
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

// DON"T FORGET TO REMOVE VVVVV WRITE(2,...)

void	ft_here_doc(int i, int _pipes[512][2], char *limiter)
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
			write(_pipes[i][1], line, ft_strlen(line));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(_pipes[i][1]);
		dup2(_pipes[i][0], STDIN_FILENO);
		close(_pipes[i][0]);
	}
}
