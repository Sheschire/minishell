/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:46:50 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/04 06:08:17 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
	{
		if (array[i])
			free(array[i]);
	}
	if (array)
		free(array);
}

void	free_cmd(t_node *node)
{
	free_array(node->cmd);
	if (node->filein)
		free(node->filein);
	if (node->fileout)
		free(node->fileout);
	if (node->limiter)
		free(node->limiter);
}

void	free_list(t_node **list)
{
	t_node	*to_free;
	t_node	*save;
	
	save = NULL;
	if (!list)
		return ;
	to_free = *list;
	while (to_free)
	{
		if (to_free->n)
			save = to_free->n;
		else
			save = NULL;
		if (to_free->s)
			free(to_free->s);
		if (to_free->cmd)
			free_cmd(to_free);
		if (to_free)
			free(to_free);
		to_free = save;
	}
}

void	ft_delnode(t_node *node)
{
	int		i;

	i = -1;
	if (node->n)
		node->n = NULL;
	if (node->s)
		free(node->s);
	if (node->cmd)
	{
		while (node->cmd[++i])
			free(node->cmd[i]);
		free(node->cmd);
	}
	if (node->fileout)
		free(node->fileout);
	if (node->filein)
		free(node->filein);
	if (node->limiter)
		free(node->limiter);
	free(node);
	node = 0;
}

void	free_exec(t_global *g)
{
	int	i;

	i = -1;
	while (g_sig.pids[++i])
		g_sig.pids[i] = 0;
}

void	free_minishell(t_global *g)
{
	free_exec(g);
	free_array(g->env);
	free_array(g->path);
	ft_close_pipe(g, INT_MAX);
	if (g->list)
		free_list(g->list);
}
