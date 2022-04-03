/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:59:25 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/03 12:26:06 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process_fd(t_node *node, int i, int _pipes[512][2])
{
	int	file;

	file = 0;
	if (i != 0)
		dup_entry_node(node, i, _pipes);
	else
	{
		if (node->filein)
		{
			file = open(node->filein, O_RDONLY, 0777);
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (node->here_doc == 1)
			ft_here_doc(file, node);
	}
	dup_exit_node_parent(node, i, _pipes);
	if (node->after != R_FLUX_CREATE && node->after != R_FLUX_APPEND)
		close(_pipes[i][1]);
	close(_pipes[i][0]);
}

void	prepare_for_built(t_node *node, int i, int _pipes [512][2], t_global *g)
{
	parent_process_fd(node, i, _pipes);
	is_builtin_exec(node->cmd, g, i);
}

void	exec_in_parent(t_global *g, t_node *node, int i, int _pipes[512][2])
{
	int	pid;

	pid = 0;
	while (i < g->cmd_nbr)
	{
		if (node->token_type == CMD && !node->_error)
		{
			if (pipe(g->_pipes[i]) == -1)
				ft_error_pipe(g);
			node->is_child = 0;
			if (!is_builtin(node->cmd))
			{
				pid = fork();
				g_sig.pids[i] = pid;
				i = check_pid(pid, i, g, node);
			}
			else
				prepare_for_built(node, i, _pipes, g);
			if (!pid)
				i++;
		}
		if (node->n != NULL)
			node = node->n;
	}
	wait_pids(g, node);
}
