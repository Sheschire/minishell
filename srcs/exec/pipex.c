/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/08 19:20:29 by barodrig         ###   ########.fr       */
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
	printf("I = %i\n", i);
	if (!node->is_child && !is_builtin(node->cmd))
	{
		printf("PROUTS\n");
		tmp_status = waitpid(g_sig.pids[i], &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			tmp_status = waitpid(g_sig.pids[i], &status, WUNTRACED);
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

void	pipex(t_global *g, t_node *node)
{
	int	i;
	int	pid;

	i = 0;
	ft_list_cleaner(node);
	g->cmd_nbr = count_cmd(node);
	pid = 0;
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
	g->child_exist = 0;
	exec_in_parent(g, node, i, g->_pipes);
	ft_close_pipe(g, INT_MAX);
	dup_cp_std(g);
}
