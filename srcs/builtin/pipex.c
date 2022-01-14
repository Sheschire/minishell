/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/01/14 11:47:16 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process_fd(t_node *node, int i, int _pipes[512][2])
{
	int	file;
	
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
			ft_here_doc(node->limiter);
	}
	dup_exit_node(node, i, _pipes);
	if (node->after != R_FLUX_CREATE && node->after != R_FLUX_APPEND)
		close(_pipes[i][1]);
	close(_pipes[i][0]);
}

void	child_begin(t_global *g, t_node *node, int i, int _pipes[512][2])
{
	int	file;

	file = 0;
	if (node->filein)
	{
		file = open(node->filein, O_RDONLY, 0777);
		dup2(file, STDIN_FILENO);
		close(file);
	}
	else if (node->here_doc == 1)
		ft_here_doc(node->limiter);
	dup_exit_node(node, i, _pipes);
	find_cmd_path(node->cmd, g, node);
}

void	child_process(t_global *g, t_node *node, int i, int _pipes[512][2])
{
//	if (node->_error == 1)
//		return ;
	node->is_child = 1;
	if (i == 0 && i != g->cmd_nbr - 1)
		child_begin(g, node, i, _pipes);
	else
	{
		dup_entry_node(node, i, _pipes);
		dup_exit_node(node, i, _pipes);
		if ((node->after == R_FLUX_CREATE && node->fileout)
			|| (node->after == R_FLUX_APPEND && node->fileout))
			close(_pipes[i][1]);
		find_cmd_path(node->cmd, g, node);
	}
}

void	exec_in_parent(t_global *g, t_node *node, int i, int _pipes[512][2])
{
	int	pid;

	if (i != 0)
		close(g->_pipes[i - 1][1]);
	while (i < g->cmd_nbr)
	{
		if (node->token_type == CMD)
		{
			if (pipe(g->_pipes[i]) == -1)
				ft_error_pipe(g);
			node->is_child = 0;
			parent_process_fd(node, i, _pipes);
			if (!is_builtin(node->cmd))
			{
				pid = fork();
				if (!pid)
					create_cmd_parent(node->cmd, g, node);
			}
			close(g->_pipes[i][1]);
			close(g->_pipes[i][0]);
			i++;
			sleep(1);
		}
		if (node->n)
			node = node->n;
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
	while (i < g->cmd_nbr)
	{
		if (node->token_type == CMD && node->_error == 0)
		{
			if (pipe(g->_pipes[i]) == -1)
				ft_error_pipe(g);
			pid = fork();
			g->pids[i] = pid;
			if (pid < 0)
				return ;
			else if (pid > 0)
			{
				close(g->_pipes[i][1]);
				i++;
			}
			else if (pid == 0)
				child_process(g, node, i, g->_pipes);
		}
		node = node->n;
	}
	exec_in_parent(g, node, i, g->_pipes);
	wait_children(g);
}
