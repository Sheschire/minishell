/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/29 11:20:46 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Need to free the child better, need to put the result in a file.

#include "minishell.h"

int	ft_check_expand_need(t_node *node, t_global *g)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (node->limiter[++i])
	{
		if (node->limiter[i] == '\'' || node->limiter[i] == '\"')
			return (0);
	}
	tmp = heredoc_expand(node->here_str, g);
	if (tmp != NULL)
		node->here_str = tmp;
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
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
	}
	signal(SIGQUIT, SIG_DFL);
}

void	ft_here_doc(int file, t_node *node)
{
	file = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
	write(file, node->here_str, ft_strlen(node->here_str));
	close(file);
	file = open("/tmp/.here_doc", O_RDONLY, 0777);
	dup2(file, STDIN_FILENO);
	close(file);
}

void	here_loop(char *line, t_node *node, t_global *g)
{
	while (1 && g_sig.exit_status != 130)
	{
		line = readline(" > ");
		if (line)
		{
			if (!ft_strcmp(line, node->limiter))
			{
				if (node->here_str)
					ft_check_expand_need(node, g);
				break ;
			}
			node->here_str = ft_strjoin(node->here_str, line);
			node->here_str = ft_strjoin(node->here_str, "\n");
		}
		else
		{
			write(1, "\n", 1);
			break ;
		}
	}
}

void	ft_here_doc_before(t_node *node, t_global *g)
{
	char	*line;
	int		pid;

	line = NULL;
	pid = 0;
	g_sig.exit_status = 0;
	here_doc_signals();
	rl_event_hook = event_heredoc;
	here_loop(line, node, g);
	if (g_sig.exit_status == 130)
		node->signal_here_doc = 130;
	signal(SIGQUIT, SIG_DFL);
}
