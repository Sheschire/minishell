/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/03 16:18:55 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_pids(t_global *g, t_node *node)
{
	int	i;
	int	status;

	i = -1;
	if (g->cmd_nbr == 1 && is_builtin(node->cmd))
		return ;
	while (++i < g->cmd_nbr && g_sig.pids[i])
		waitpid(g_sig.pids[i], &status, WUNTRACED);
	if (status && !is_builtin(node->cmd) && !node->_error)
	{
		waitpid(g_sig.pids[i], &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			g_sig.exit_status = WTERMSIG(status) + 128;
			return ;
		}
		if (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(g_sig.pids[i], &status, WUNTRACED);
		g_sig.exit_status = (status / 256);
	}
}

int	check_pid(int pid, int i, t_global *g, t_node *node)
{
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
		if (!is_builtin(node->cmd) || node->is_child == 1)
			child_process(g, node, i, g->_pipes);
		else
		{
			is_builtin_exec(node->cmd, g, i, node);
			exit(g_sig.exit_status);
		}
		return (-1);
	}
}

void	end_pipex(t_global *g)
{
	ft_close_pipe(g, INT_MAX);
	dup_cp_std(g);
	free_exec();
	free_list(&g->list);
	signal(SIGQUIT, SIG_DFL);
}

void	pipex(t_global *g, t_node *node)
{
	int	i;
	int	pid;

	i = 0;
	g->cmd_nbr = count_cmd(node);
	pid = 0;
	signal(SIGQUIT, ft_sigquit_off);
	while (i < g->cmd_nbr - 1)
	{
		if (node->token_type == CMD && !node->_error)
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
	g->child_exist = 0;
	exec_in_parent(g, node, i, g->_pipes);
	end_pipex(g);
}
