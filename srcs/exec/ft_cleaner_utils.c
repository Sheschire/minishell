/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:09:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/20 18:13:04 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_flux_append(t_node *node, char *hook, t_global *g)
{
	node->filein = NULL;
	node->here_doc = 1;
	if (node->limiter)
		ft_useless_here_doc(node->limiter, g);
	node->limiter = hook;
}

int	no_such_file(char *hook, t_node *node)
{
	node->_error = 1;
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(hook, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	end_of_filein_check(t_node *node, int ret, char *hook)
{
	node->limiter = NULL;
	node->filein = hook;
	close(ret);
}
