/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/19 12:05:13 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Need to free the child better, need to put the result in a file.

#include "../../includes/minishell.h"

int	ft_check_expand_need(char *limiter, char *line, t_global *g)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (limiter[++i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
			return (0);
	}
	tmp = heredoc_expand(line, g);
	if (tmp != NULL)
	{
		free(line);
		line = tmp;
	}
	return (1);
}

void	ft_useless_here_doc(char *limiter, t_global *g)
{
	char	*line;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		while (get_next_line(0, &line, limiter, g))
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(0);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	do_here_doc_thing(char *line, char *limit, int _pipe[2], t_global *g)
{
	int	i;

	i = 0;
	while (get_next_line(0, &line, limit, g))
	{
		if (!ft_strncmp(line, limit, ft_strlen(limit)))
		{
			dup2(_pipe[1], STDOUT_FILENO);
			close(_pipe[1]);
			free(line);
			free_minishell(g);
			exit(0);
		}
		ft_putstr_fd(line, _pipe[1]);
		ft_putstr_fd("\n", _pipe[1]);
		free(line);
		i++;
	}
}

void	ft_here_doc(char *limiter, t_global *g)
{
	char	*line;
	int		_pipe_here[2];
	int		pid;
	int		fd;

	if (pipe(_pipe_here) == -1)
		ft_error_pipe(g);
	pid = fork();
	if (pid == 0)
		do_here_doc_thing(line, limiter, _pipe_here, g);
	else
	{
		waitpid(pid, NULL, 0);
		dup2(_pipe_here[0], STDIN_FILENO);
		close(_pipe_here[0]);
		close(_pipe_here[1]);
	}
}
