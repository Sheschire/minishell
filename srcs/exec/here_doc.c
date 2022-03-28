/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/28 16:42:14 by barodrig         ###   ########.fr       */
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

void	here_doc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = here_doc_action;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		ft_putstr_fd("Signal error\n", 2);
	signal(SIGQUIT, SIG_IGN);
}

int	event_heredoc(void)
{
	return (0);
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
				ft_check_expand_need(node->limiter, node->here_str, g);
				break ;
			}
			node->here_str = ft_strjoin(node->here_str, line);
			node->here_str = ft_strjoin(node->here_str, "\n");
		}
		else
			break ;
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
	if (!node->here_str)
		write(1, "\n", 1);
	signal(SIGQUIT, SIG_DFL);
}
