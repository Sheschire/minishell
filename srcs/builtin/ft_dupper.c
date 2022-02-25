/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:39:46 by barodrig          #+#    #+#             */
/*   Updated: 2022/02/24 15:31:35 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_exit_node_parent(t_node *node, int i, int _pipes[512][2])
{
	int	file;

	file = 0;
	if (!is_builtin(node->cmd))
	{
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
	}
}

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
	else if (i > 0)
	{
		dup2(_pipes[i - 1][0], STDIN_FILENO);
		close(_pipes[i - 1][0]);
	}
}
