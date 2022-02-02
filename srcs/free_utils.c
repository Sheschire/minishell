/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:46:50 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/02 14:03:35 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_list(t_node **list)
{
	t_node	*to_free;
	t_node	*save;
	
	if (!list)
		return ;
	to_free = *list;
	while (to_free)
	{
		save = to_free->n;
		// if (to_free->s)                  NEED TO FIND A SOLUTION TO CHECK IF FREE IS NEEDED
		// 	free(to_free->s);
		//if (to_free->token_type == CMD)
			//free_array(to_free->cmd);
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