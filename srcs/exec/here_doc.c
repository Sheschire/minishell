/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/09 14:40:15 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_here_doc_fd(int option)
{
	char	*path;
	int		fd;

	path = NULL;
	if (access("/tmp", F_OK) == 0)
		path = ft_strdup("/tmp/.heredoc");
	else
		path = ft_strdup(".heredoc");
	if (option == 0)
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (option == 1)
		fd = open(path, O_CREAT | O_RDONLY, 0644);
	free(path);
	return (fd);
}

int	ft_here_doc_w_expand(char *limiter, t_global *g, char *line, int fd)
{
	while (1)
	{
		line = readline (" > ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (ft_strchr(line, '$'))
			heredoc_expand(line, g);
		if (line)
			ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		close(fd);
	}
	return (fd);
}

int	ft_exec_here_doc(char *limiter, t_global *g, char *line, int fd)
{
	while (1)
	{
		line = readline (" > ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (line)
			ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		close(fd);
	}
	return (fd);
}

int	ft_here_doc(char *limiter, t_global *g)
{
	char	*line;
	int		fd;

	fd = (make_here_doc_fd(0));
	if (fd < 0)
		return (perror(line), fd);
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '\"'))
		return (ft_here_doc_w_expand(limiter, g, line, fd));
	else
		return (ft_exec_here_doc(limiter, g, line, fd));
}
