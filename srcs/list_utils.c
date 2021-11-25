/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:15:17 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/25 12:47:35 by tlemesle         ###   ########.fr       */
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
		printf("STRING = %s\n", node->s);
		printf("TOKEN_TYPE = %d\n", *node->token_type);
		printf("---------------\n");
		*node = *node->n;
		pos++;
	}
}

t_node	*newnode(char *s, int token_type)
{
	t_list	*new;

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
