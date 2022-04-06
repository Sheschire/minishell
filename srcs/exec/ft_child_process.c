/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:02:01 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/06 15:50:25 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		free_minishell(g);
		exit(1);
	}
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
