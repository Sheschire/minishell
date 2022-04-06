/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:46 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/06 16:44:10 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_create_redirin(t_node *node, t_global *g, char *hook, int ret)
{
	t_node	*tmp;

	node->here_doc = 0;
	tmp = node;
	if (tmp->token_type == 8 || tmp->token_type == 10)
	{
		hook = tmp->n->s;
		if (tmp->token_type == L_FLUX_CREATE)
		{
			node->here_doc = 0;
			ret = open(tmp->n->s, O_RDONLY);
			if (ret == -1)
				no_such_file(hook, node);
			if (node->limiter)
				ft_useless_here_doc(node->limiter, node);
			end_of_filein_check(node, ret, hook);
		}
		else if (tmp->token_type == L_FLUX_APPEND)
			handling_append(node, tmp, hook, g);
	}
	return (print_no_such_file(node));
}

void	count_create_redirout(t_node *node, char *hook)
{
	hook = node->n->n->s;
	if (node->token_type == R_FLUX_CREATE)
	{
		open(hook, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		node->after = R_FLUX_CREATE;
	}
	else
	{
		open(hook, O_WRONLY | O_CREAT | O_APPEND, 0755);
		node->after = R_FLUX_APPEND;
	}
	node->fileout = hook;
	return ;
}

int	check_redir_list(t_node *tmp, t_global *g)
{
	char	*hook;
	int		ret;
	t_node	*node;

	hook = NULL;
	ret = 0;
	node = tmp;
	while (tmp && tmp->token_type != TOKEN_PIPE)
	{
		if (tmp->token_type == 8 || tmp->token_type == 10)
			if (count_create_redirin(node, g, hook, ret))
				return (0);
		if (tmp->token_type == 7 || tmp->token_type == 9)
			count_create_redirout(node, hook);
		if (tmp->n && tmp->n->token_type != TOKEN_PIPE)
			tmp = tmp->n;
		else
			return (1);
	}
	return (1);
}

int	ft_list_cleaner(t_node *node, t_global *g)
{
	t_node	*tmp;
	int		ret;

	ret = 0;
	tmp = node;
	while (tmp)
	{
		if (tmp->token_type == CMD)
		{
			if (tmp->cmd[0] == NULL)
				return (0);
			ret = check_redir_list(tmp, g);
			if (tmp->signal_here_doc)
				return (0);
		}
		if (tmp->n)
			tmp = tmp->n;
		else
			break ;
	}
	if (ret == 0)
		return (0);
	return (1);
}
