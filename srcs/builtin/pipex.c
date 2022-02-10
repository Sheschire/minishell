/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/02/10 16:03:37 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_pids(t_global *g)
{
	int	i;

	i = -1;
	while (++i < g->cmd_nbr)
		waitpid(g_sig.pids[i], 0, 0);
}

int	check_pid(int pid, int i, t_global *g, t_node *node)
{
	if (pid < 0)
		return (-1);
	else if (pid > 0)
	{
		if (g->_pipes[i][1])
			close(g->_pipes[i][1]);
		if (g->_pipes[i - 1][0])
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

void	pipex(t_global *g)
{
	int		i;
	int		pid;
	t_node	*tmp;

	i = 0;
	pid = 0;
	ft_list_cleaner(g->list);
	g->cmd_nbr = count_cmd(g->list);
	tmp = (*g->list);
	while (i < g->cmd_nbr - 1)
	{
		if (tmp->token_type == CMD && !tmp->_error)
		{
			if (pipe(g->_pipes[i]) == -1)
				ft_error_pipe(g);
			tmp->is_child = 1;
			pid = fork();
			g_sig.pids[i] = pid;
			i = check_pid(pid, i, g, tmp);
		}
		tmp = tmp->n;
	}
	exec_in_parent(g, tmp, i, g->_pipes);
	wait_pids(g);
	ft_close_pipe(g, INT_MAX);
	wait_pids(g);
	dup_cp_std(g);
}
