/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/09 11:46:25 by barodrig         ###   ########.fr       */
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
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(0);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	do_the_here_doc_thing(char *line, char *limiter, int _pipe_here[2])
{
	while (get_next_line(0, &line))
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			dup2(_pipe_here[1], STDOUT_FILENO);
			close(_pipe_here[1]);
			exit (0);
		}
		ft_putstr_fd(line, _pipe_here[1]);
		ft_putstr_fd("\n", _pipe_here[1]);
	}
}

/*void	make_here_doc_fd(int fd, int option)
{
	if (option == 0)
	{
		fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0777)
	}
	else if (option == 0)
}

void	ft_here_doc_w_expand(char *limiter)
{
	return ;
}*/

void	ft_here_doc(char *limiter)
{
	char	*line;
	int		_pipe_here[2];
	int		pid;
	int		fd;

	if (pipe(_pipe_here) == -1)
		write(2, "CA MARCHE PAS FRERE\n", 20);
	pid = fork();
	if (pid == 0)
	{
		do_the_here_doc_thing(line, limiter, _pipe_here);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(_pipe_here[0], STDIN_FILENO);
		close(_pipe_here[0]);
		close(_pipe_here[1]);
	}
}
