/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:15:17 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/01 14:39:54 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_node **node)
{
	int	pos;

	pos = 0;
	while (*node)
	{
		printf("---------------\n");
		printf("POS = %d\n", pos);
		printf("➜ %s\n", (*node)->s);
		if ((*node)->token_type == 1)
			printf("➜ LITERAL\n");
		if ((*node)->token_type == 2)
			printf("➜ PIPE\n");
		if ((*node)->token_type == 3)
			printf("➜ FLUX\n");
		if ((*node)->token_type == 4)
			printf("➜ OPTION\n");
		if ((*node)->token_type == 5)
			printf("➜ COMMAND\n");
		if ((*node)->token_type == 6)
			printf("➜ SLASH\n");
		if ((*node)->token_type == 7)
			printf("➜ R_FLUX_CREATE\n");
		if ((*node)->token_type == 8)
			printf("➜ L_FLUX_CREATE\n");
		if ((*node)->token_type == 9)
			printf("➜ R_FLUX_APPEND\n");
		if ((*node)->token_type == 10)
			printf("➜ L_FLUX_APPEND\n");
		if ((*node)->token_type == 11)
			printf("➜ SINGLE_QUOTE_NODE\n");
		if ((*node)->token_type == 12)
			printf("➜ DOUBLE_QUOTE_NODE\n");
		printf("---------------\n");
		*node = (*node)->n;
		pos++;
	}
}

void	newnode_add_back(char *s, int token_type, t_node **list)
{
	t_node *tmp;

	tmp = newnode(s, token_type);
	add_back(list, tmp);
}

t_node	*newnode(char *s, int token_type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		return (0);
	new->s = s;
	new->token_type = token_type;
	new->n = NULL;
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

void	add_front(t_node **s, t_node *new)
{
	if (new && s)
	{
		new->n = *s;
		*s = new;
	}
}

t_node	*getlast(t_node *s)
{
	if (s == NULL)
		return (0);
	while (s->n)
		s = s->n;
	return (s);
}

void	free_list(t_node **s)
{
	t_node	*tmp;
	t_node	*copy;

	if (!s)
		return ;
	copy = *s;
	while (copy)
	{
		tmp = copy->n;
		free(copy);
		copy = tmp;
	}
	*s = NULL;
}
