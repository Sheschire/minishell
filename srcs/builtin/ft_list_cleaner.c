/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:46 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/13 16:32:29 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_del_two_nodes(t_node *node_a, t_node *node_b)
{
	ft_delnode(node_a);
	ft_delnode(node_b);
	return ;
}

void	ft_clean_flux_append(t_node *node)
{
	t_node	*tmp;
	t_node	*tmp_tmp;

	tmp = node;
	tmp_tmp = node;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		tmp = tmp->n;
		if (tmp->n->token_type == TOKEN_FILE)
		{
			if ((tmp->n->n && tmp->n->n->token_type == L_FLUX_APPEND))
			{
				ft_useless_here_doc(tmp->n->n->n->limiter);
				*tmp_tmp = *(tmp->n->n->n->n);
				ft_del_two_nodes(tmp->n->n->n, tmp->n->n);
				tmp->n->n = tmp_tmp;
			}
		}
		if (tmp->n && tmp->n->token_type == L_FLUX_APPEND)
		{
			ft_useless_here_doc(node->n->n->limiter);
			ft_del_two_nodes(node->n->n, node->n);
			node->n = tmp->n;
		}
	}
}

void	ft_clean_flux_create(t_node	*node)
{
	t_node	*tmp;
	t_node	*begin;

	begin = node;
	tmp = node;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		if (tmp->n && tmp->n->token_type == R_FLUX_CREATE)
		{	
			open(node->n->n->s, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			tmp = tmp->n->n->n;
			node->n = tmp;
			ft_del_two_nodes(begin->n->n, begin->n);
			begin = node;
		}
		if (tmp->n)
			tmp = tmp->n;
	}
	printf("NODE->N->N->TOKEN_TYPE = %i\n", node->n->n->token_type);
	return ;
}

void	ft_list_cleaner(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp->n)
	{
	//	if (tmp->token_type == CMD && tmp->n->token_type == L_FLUX_APPEND)
	//		ft_clean_flux_append(tmp);
		if (tmp->token_type == CMD && tmp->n->token_type == R_FLUX_CREATE)
			ft_clean_flux_create(tmp);
		if (!tmp->n)
			return ;
		tmp = tmp->n;
		while (tmp->n && tmp->token_type != CMD)
			tmp = tmp->n;
	}
	return ;
}
