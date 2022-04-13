/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:46:50 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/13 14:02:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int		i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
	{
		if (array[i])
			free(array[i]);
	}
	if (array)
		free(array);
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
		free(to_free->s);
		to_free->s = NULL;
		if (to_free->cmd)
			free_array(to_free->cmd);
		if (to_free->here_str)
			free(to_free->here_str);
		if (to_free)
			free(to_free);
		to_free = save;
	}
	*list = NULL;
}

void	free_exec(void)
{
	int	i;

	i = -1;
	while (g_sig.pids[++i])
		g_sig.pids[i] = 0;
}

void	free_builtins(t_global *g)
{
	free_exec();
	free_array(g->env);
	free_array(g->path);
	if (g->list)
		free_list(&g->list);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
	close(g->cp_stdin);
	close(g->cp_stdout);
	exit(0);
}

void	free_minishell(t_global *g)
{
	free_exec();
	free_array(g->env);
	free_array(g->path);
	if (g->list)
		free_list(&g->list);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
	close(g->cp_stdin);
	close(g->cp_stdout);
}
