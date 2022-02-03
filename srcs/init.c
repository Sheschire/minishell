/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:24:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/03 03:33:09 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **env)
{
	char	**path;
	char	*path_string;

	path_string = getenv("PATH");
	path = ft_split(path_string, ':');
	return (path);
}

void	init_global(t_global *g, char **env)
{
	// if (!*env)
	// 	return (0); // TO DO : generate env manually and continue program
	g->path = get_path(env);
	g->env = env;
	g->list = NULL;
	g->cmd_nbr = 0;
	g->status = 0;
	g_sig.exit_status = 0;
}

void	init_cmd_nodes(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->cmd = NULL;
		tmp = tmp->n;
	}
}