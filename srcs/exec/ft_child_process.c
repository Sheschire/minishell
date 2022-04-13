/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:02:01 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/13 17:52:44 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_child(t_global *g)
{
	free_minishell(g);
	ft_close_pipe(g, INT_MAX);
	exit(1);
}

void	_free_node_error(t_global *g, int i, int _pipes[1024][2])
{
	if (i != 0)
	{
		close(_pipes[i - 1][0]);
		close(_pipes[i - 1][1]);
	}
	close(_pipes[i][1]);
	close(_pipes[i][0]);
	close(g->cp_stdin);
	close(g->cp_stdout);
	free_minishell(g);
	exit(1);
}

void	child_begin(t_global *g, t_node *node, int i, int _pipes[1024][2])
{
	int	file;

	file = 0;
	if (g->cmd_nbr > 1)
		node->is_child = 1;
	if (node->filein)
	{
		file = open(node->filein, O_RDONLY, 0777);
		dup2(file, STDIN_FILENO);
		close(file);
	}
	else if (node->here_doc == 1)
		ft_here_doc(file, node);
	dup_exit_node(node, i, _pipes);
	find_cmd_path(node->cmd, g, node);
}

void	child_process(t_global *g, t_node *node, int i, int _pipes[1024][2])
{
	if (node->_error)
		_free_node_error(g, i, _pipes);
	if (node->is_child == 1)
		close(2);
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
