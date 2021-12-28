/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/28 16:50:44 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_exit_node(t_global *g, t_node *node, int _pipe[2])
{
	int	file;

	file = 0;
	if (node->after == R_FLUX_CREATE && node->fileout)
	{
		file = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(file, STDOUT_FILENO);
	}
	else if (node->after == R_FLUX_APPEND && node->fileout)
	{
		file = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(file, STDOUT_FILENO);
	}
	else
		dup2(_pipe[0], STDIN_FILENO);
}

void	dup_entry_node(t_global *g, t_node *node, int _pipe[2])
{
	int	file;

	file = 0;
	if (node->filein)
	{
		file = open(node->filein, O_RDONLY, 0777);
		dup2(file, STDIN_FILENO);
	}
	else if (node->here_doc == 1)
		ft_here_doc(node->limiter);
/*	if (node->after == R_FLUX_CREATE && node->fileout)
	{
		file = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(file, STDOUT_FILENO);
	}
	else if (node->after == R_FLUX_APPEND && node->fileout)
	{
		fileout = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fileout, STDOUT_FILENO);
	}
*/
}

void	child_process(t_global *g, t_node *node)
{
	pid_t	pid;
	int		_pipe[2];

	if (pipe(_pipe) == -1)
		ft_error_pipe(g);
	pid = fork();
	if (pid == -1)
		ft_error_pipe(g);
	if (pid == 0)
	{
		close(_pipe[0]);
		dup_entry_node(g, node, _pipe);
		find_cmd_path(node->cmd, g);
	}
	else
	{
		close(_pipe[1]);
		dup_exit_node(g, node, _pipe);
		waitpid(pid, NULL, 0);
	}
}

void	parent_process(t_global *g, t_node *node)
{
	int	fileout;

	fileout = 0;
	while (node->n && node->token_type != CMD)
		node = node->n;
	if (node->after == R_FLUX_CREATE && node->fileout)
	{
		fileout = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fileout, STDOUT_FILENO);
	}
	else if (node->after == R_FLUX_APPEND && node->fileout)
	{
		fileout = open(node->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fileout, STDOUT_FILENO);
	}
	find_cmd_path(node->cmd, g);
}

void	pipex(t_global *g, t_node *node)
{
	int	i;
	int	cmd_nbr;

	i = -1;
	cmd_nbr = count_cmd(node);
	printf("CMD NBR = %i\n", cmd_nbr);
	ft_list_cleaner(node);
	//print_list(&node);
	while (++i < cmd_nbr - 1)
	{
		child_process(g, node);
		while (node->n)
		{
			node = node->n;
			if (node->token_type == CMD)
				break ;
		}
	}
	parent_process(g, node);
	
	return ;
}
