/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:50:48 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/13 15:15:29 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_error_pipe(t_global *g, t_node *node, int i)
{
	(void)node;
	if (g->_pipes[i - 1][0])
		close(g->_pipes[i - 1][1]);
	if (g->_pipes[i - 1][1])
		close(g->_pipes[i - 1][0]);
	g_sig.exit_status = 1;
}
