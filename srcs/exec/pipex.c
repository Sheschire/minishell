/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/09 14:15:24 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_pids(t_global *g, t_node *node)
{
	int	i;
	int	status;
	int	tmp_status;

	i = -1;
	while (++i < g->cmd_nbr - 1)
		waitpid(g_sig.pids[i], 0, WUNTRACED);
	if (!node->is_child && !is_builtin(node->cmd))
	{
		tmp_status = waitpid(g_sig.pids[i], &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			WTERMSIG(status);
			tmp_status = waitpid(g_sig.pids[i], &status, WUNTRACED);
			g_sig.exit_status = (status + 128);
			return ;
		}
		if (!WIFEXITED(status) && !WIFSIGNALED(status))
			tmp_status = waitpid(g_sig.pids[i], &status, WUNTRACED);
		g_sig.exit_status = (status / 256);
	}
}

int	check_pid(int pid, int i, t_global *g, t_node *node)
{
	g_sig.pids[i] = pid;
	if (pid < 0)
		return (-1);
	else if (pid > 0)
	{
		if (g->_pipes[i][1])
			close(g->_pipes[i][1]);
		if (i > 0)
			close(g->_pipes[i - 1][0]);
		i++;
		return (i);
	}
	else
	{
		if (!is_builtin(node->cmd))
			child_process(g, node, i, g->_pipes);
		else
		{
			is_builtin_exec(node->cmd, g, i);
			exit(g_sig.exit_status);
		}
		return (-1);
	}
}

void	pipex(t_global *g, t_node *node, int i)
{
	int	pid;

	g->cmd_nbr = count_cmd(node);
	pid = 0;
	while (i < g->cmd_nbr - 1)
	{
		ft_list_cleaner(node, g);
		while (node->token_type != TOKEN_PIPE)
		{
			if (node->token_type == CMD && node->_error == 0)
			{
				if (pipe(g->_pipes[i]) == -1)
					ft_error_pipe(g);
				node->is_child = 1;
				pid = fork();
				i = check_pid(pid, i, g, node);
			}
			node = node->n;
		}
		node = node->n;
	}
	exec_in_parent(g, node, i, g->_pipes);
	ft_close_pipe(g, INT_MAX);
	dup_cp_std(g);
}
