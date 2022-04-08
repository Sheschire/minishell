/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:59:25 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/08 12:20:17 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process_fd(t_node *node, int i, int _pipes[1024][2])
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

void	prepare_for_built(t_node *node, int i, int _pipes[1024][2], t_global *g)
{
	parent_process_fd(node, i, _pipes);
	g_sig.exit_status = is_builtin_exec(node->cmd, g, i, node);
}

void	init_parent(t_node *node)
{
	g_sig.exit_status = 0;
	node->is_child = 0;
}

int	launch_cmd(t_node *node, t_global *g, int *i, int _pipes[1024][2])
{
	int	pid;

	pid = 0;
	if (node->token_type == CMD)
	{
		if (pipe(g->_pipes[*i]) == -1)
			ft_error_pipe(g);
		init_parent(node);
		if (!is_builtin(node->cmd))
		{
			pid = fork();
			g_sig.pids[*i] = pid;
			*i = check_pid(pid, *i, g, node);
		}
		else
			prepare_for_built(node, *i, _pipes, g);
		if (!pid)
			*i += 1;
		return (1);
	}
	return (0);
}

void	exec_in_parent(t_global *g, t_node *node, int i, int _pipes[1024][2])
{
	while (i < g->cmd_nbr)
	{
		if (launch_cmd(node, g, &i, _pipes))
			break ;
		if (node->token_type == CMD && node->_error)
			i++;
		if (node->n)
			node = node->n;
	}
}
