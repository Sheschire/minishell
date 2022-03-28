/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:09:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/28 16:49:29 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_append(t_node *node, t_node *tmp, char *hook, t_global *g)
{
	node->filein = NULL;
	node->here_doc = 1;
	if (node->limiter)
		ft_useless_here_doc(node->limiter);
	node->limiter = hook;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		if (tmp->n->token_type == 8 || tmp->n->token_type == 10)
			break ;
		if (!tmp->n->n || tmp->n->n->token_type == TOKEN_PIPE)
			ft_here_doc_before(node, g);
		tmp = tmp->n;
	}
}

int		print_no_such_file(t_node *node)
{
	if (node->signal_here_doc)
	{
		g_sig.exit_status = node->signal_here_doc;
		return (1);
	}
	else if (node->_error)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(node->no_file, 2);
		ft_putstr_fd("\n", 2);
		free(node->no_file);
		return (1);
	}
	return (0);
}

void	no_such_file(char *hook, t_node *node)
{
	node->_error = 1;
	node->no_file = ft_strdup(hook);
}

void	end_of_filein_check(t_node *node, int ret, char *hook)
{
	node->limiter = NULL;
	if (!node->_error)
	{
		node->filein = hook;
		close(ret);
	}
}
