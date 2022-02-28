/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/02/28 16:53:17 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pid(int pid, int i, t_global *g, t_node *node)
{
	if (pid < 0)
		return (-1);
	else if (pid > 0)
	{
		waitpid(pid, 0, 0);
		if (g->_pipes[i][1])
			close(g->_pipes[i][1]);
		if (i > 0)
			close(g->_pipes[i - 1][0]);
		i++;
		return (i);
	}
	else
	{
		child_process(g, node, i, g->_pipes);
		return (-1);
	}
}

void	pipex(t_global *g, t_node *node)
{
	int	i;
	int	pid;

	i = 0;
	ft_list_cleaner(node);
	g->cmd_nbr = count_cmd(node);
	pid = 0;
	g->cp_stdin = dup(STDIN_FILENO);
	g->cp_stdout = dup(STDOUT_FILENO);
	while (i < g->cmd_nbr - 1)
	{
		if (node->token_type == CMD && node->_error == 0)
		{
			if (pipe(g->_pipes[i]) == -1)
				ft_error_pipe(g);
			node->is_child = 1;
			pid = fork();
			g_sig.pids[i] = pid;
			i = check_pid(pid, i, g, node);
		}
		node = node->n;
	}
	exec_in_parent(g, node, i, g->_pipes);
	dup_cp_std(g);
	ft_close_pipe(g, INT_MAX);
}
