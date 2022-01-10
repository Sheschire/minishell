/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/01/10 15:17:01 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_exit_node(t_node *node, int i, int _pipes[512][2])
{
	int	file;

	file = 0;
	if (node->after == R_FLUX_CREATE && node->fileout)
	{
		file = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(file, STDOUT_FILENO);
		close(file);
		close(_pipes[i][0]);
	}
	else if (node->after == R_FLUX_APPEND && node->fileout)
	{
		file = open(node->fileout, O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(file, STDOUT_FILENO);
		close(file);
		close(_pipes[i][0]);
	}
	else if (node->is_child == 1)
	{
		dup2(_pipes[i][1], STDOUT_FILENO);
		close(_pipes[i][1]);
		close(_pipes[i][0]);
	}
	else
	{
		close(_pipes[i][0]);
		close(_pipes[i][1]);
	}
}

void	dup_entry_node(t_node *node, int i, int _pipes[512][2])
{
	int	file;

	file = 0;
	if (node->filein)
	{
		close(_pipes[i - 1][0]);
		file = open(node->filein, O_RDONLY, 0777);
		dup2(file, STDIN_FILENO);
		close(file);
	}
	else if (node->here_doc == 1)
	{
		close(_pipes[i - 1][0]);
		ft_here_doc(node->limiter);
	}
	else
	{
		dup2(_pipes[i - 1][0], STDIN_FILENO);
		close(_pipes[i - 1][0]);
	}
}

void	parent_process(t_global *g, t_node *node, int i, int _pipes[512][2])
{
	int	file;
	
	node->is_child = 0;
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
	{
		close(_pipes[i][1]);
		close(_pipes[i][0]);
	}
	find_cmd_path(node->cmd, g, node);
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
	else if (i == g->cmd_nbr - 1)
		parent_process(g, node, i, _pipes);
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
				i++;
			else
				child_process(g, node, i, g->_pipes);
		}
		node = node->n;
	}
	i = -1;
	while (++i < g->cmd_nbr - 1)
		waitpid(g->pids[i], 0, 0);
}	
