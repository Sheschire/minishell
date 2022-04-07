/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:46 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/07 16:16:27 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_create_redirin(t_node *node, t_node *tmp, t_global *g, char *hook)
{
	int	ret;

	ret = 0;
	node->here_doc = 0;
	if (tmp->token_type == 8 || tmp->token_type == 10)
	{
		hook = tmp->n->s;
		if (tmp->token_type == L_FLUX_CREATE)
		{
			node->here_doc = 0;
			ret = open(hook, O_RDONLY);
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

void	count_create_redirout(t_node *node, t_node *tmp)
{
	char	*hook;

	hook = tmp->n->s;
	if (tmp->token_type == R_FLUX_CREATE)
	{
		open(hook, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		node->after = R_FLUX_CREATE;
	}
	else if (tmp->token_type == R_FLUX_APPEND)
	{
		open(hook, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
			if (count_create_redirin(node, tmp, g, hook))
				return (0);
		if (tmp->token_type == 7 || tmp->token_type == 9)
			count_create_redirout(node, tmp);
		if (tmp->n && tmp->n->token_type != TOKEN_PIPE)
			tmp = tmp->n;
		else
			return (1);
	}
	return (1);
}

int	is_a_redir(t_node *node, int type, int ret)
{
	if (type == 7 || type == 8 || type == 9 || type == 10)
	{
		if (type == 7 || type == 9)
		{
			if (type == 7)
				ret = open(node->n->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (type == 9)
				ret = open(node->n->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (ret != -1)
				close(ret);
		}
		if (type == 8 || type == 10)
		{
			if (type == 8)
			{
				ret = open(node->n->s, O_RDONLY);
				if (ret == -1)
					no_such_file(node->n->s, node->n);
			}
			else if (type == 10)
				ft_useless_here_doc(node->n->s, node->n);
		}
		return (print_no_such_file(node->n));
	}
	return (1);
}

int	ft_list_cleaner(t_node *node, t_global *g, int ret)
{
	t_node	*tmp;

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
			while (tmp->token_type != TOKEN_PIPE && tmp->n)
				tmp = tmp->n;
		}
		ret = is_a_redir(tmp, tmp->token_type, 0);
		if (tmp->n)
			tmp = tmp->n;
		else
			break ;
	}
	if (ret == 0)
		return (0);
	return (1);
}
