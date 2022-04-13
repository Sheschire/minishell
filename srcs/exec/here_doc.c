/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:47:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/13 11:48:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Need to free the child better, need to put the result in a file.

#include "minishell.h"

int	ft_check_expand_need(t_node *node, t_global *g)
{
	if (node->here_doc_quotes_removed == 1)
		return (0);
	g->expand_limiters = ft_strdup(" \'\"$=+-*^%#@!~.,:{}[]/?\n");
	heredoc_expand(node, g, 0);
	return (1);
}

void	ft_useless_here_doc(char *limiter, t_node *node)
{
	char	*line;

	line = NULL;
	g_sig.exit_status = 0;
	here_doc_signals();
	rl_event_hook = event_heredoc;
	signal(SIGQUIT, SIG_IGN);
	while (1 && g_sig.exit_status != 130)
	{
		line = readline(" > ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (line && g_sig.exit_status != 130)
			free(line);
	}
	if (g_sig.exit_status == 130)
		node->signal_here_doc = 130;
	free(line);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	ft_here_doc(int file, t_node *node)
{
	file = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
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
				break ;
			node->here_str = ft_strjoin(node->here_str, line);
			node->here_str = ft_strjoin(node->here_str, "\n");
			if (node->here_str)
				ft_check_expand_need(node, g);
		}
		else
		{
			write(1, "\n", 1);
			break ;
		}
		if (line && g_sig.exit_status != 130)
			free(line);
	}
	free(line);
}

void	ft_here_doc_before(t_node *node, t_global *g)
{
	char	*line;

	line = NULL;
	g_sig.exit_status = 0;
	here_doc_signals();
	rl_event_hook = event_heredoc;
	if (ft_strchr(node->limiter, '\'') || ft_strchr(node->limiter, '\"'))
		dequote_heredoc(node, g);
	here_loop(line, node, g);
	if (node->limiter && node->here_doc_quotes_removed)
		free(node->limiter);
	if (g_sig.exit_status == 130)
		node->signal_here_doc = 130;
	signal(SIGQUIT, SIG_DFL);
}
