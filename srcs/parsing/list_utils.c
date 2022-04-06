/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:15:17 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/06 14:32:16 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newnode_cmd_add_back(char **cmd, t_node **list)
{
	t_node	*new;

	new = newnode(NULL, CMD);
	new->cmd = cmd;
	add_back(list, new);
}

void	newnode_add_back(char *s, int token_type, t_node **list)
{
	t_node	*tmp;

	tmp = newnode(s, token_type);
	add_back(list, tmp);
}

t_node	*newnode(char *s, int token_type)
{
	t_node	*new;

	new = (t_node *)ft_calloc(1, sizeof(t_node));
	if (new == NULL)
		return (0);
	new->s = s;
	new->token_type = token_type;
	new->cmd = NULL;
	new->here_str = NULL;
	new->filein = NULL;
	new->fileout = NULL;
	new->limiter = NULL;
	new->n = NULL;
	new->here_doc_quotes_removed = 0;
	return (new);
}

void	add_back(t_node **s, t_node *new)
{
	t_node	*last;

	if (s == NULL)
		return ;
	last = *s;
	if (*s == NULL)
		*s = new;
	else
	{
		while (last->n)
			last = last->n;
		last->n = new;
		new->n = NULL;
	}
}
