/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/27 13:55:16 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Need to free the child better, need to put the result in a file.

#include "minishell.h"

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

void	ft_useless_here_doc(char *limiter)
{
	char	*line;
	
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline(">>");
		if (!line)
			break;
		if (!ft_strcmp(line, limiter))
			break ;
	}
	signal(SIGQUIT, SIG_DFL);
}

void	ft_here_doc(int	file, t_node *node)
{
	file = open("./.here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
	write(file, node->here_str, ft_strlen(node->here_str));
	close(file);
	file = open("./.here_doc", O_RDONLY, 0777);
	dup2(file, STDIN_FILENO);
	close(file);
}

void	waitpid_here_doc(int pid, t_node *node)
{
	int	status;
	
	waitpid(pid, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		g_sig.exit_status = WTERMSIG(status) + 128;
		node->signal_here_doc = g_sig.exit_status;
		return ;
	}
	else
		g_sig.exit_status = (status / 256);
}

void	ft_here_doc_before(t_node *node, t_global *g)
{
	char	*line;
	int		pid;

	line = NULL;
	pid = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	while (1 && pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		line = readline(">>");
		if (!line)
			break;
		if (!ft_strcmp(line, node->limiter))
		{
			ft_check_expand_need(node->limiter, node->here_str, g);
			break ;
		}
		node->here_str = ft_strjoin(node->here_str, line);
		node->here_str = ft_strjoin(node->here_str, "\n");
	}
	if (pid > 0)
		waitpid_here_doc(pid, node);
	signal(SIGQUIT, SIG_DFL);
}
