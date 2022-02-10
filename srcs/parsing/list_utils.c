/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:15:17 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/10 15:23:26 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_node **list)
{
	t_node	*tmp;
	int		i;
	int		pos;
	
	tmp = *list;
	pos = 0;
	while (tmp)
	{
		i = -1;
		printf("---------------\n");
		printf("POS = %d\n", pos);
		if (tmp->token_type == CMD)
			while (tmp->cmd[++i])
				printf("➜ cmd[%d] = %s\n", i, tmp->cmd[i]);
		if (tmp->s)
			printf("➜ %s\n", tmp->s);
		if (tmp->token_type == 1)
			printf("➜ LITERAL\n");
		if (tmp->token_type == 2)
			printf("➜ PIPE\n");
		if (tmp->token_type == 3)
			printf("➜ FLUX\n");
		if (tmp->token_type == 4)
			printf("➜ OPTION\n");
		if (tmp->token_type == 5)
			printf("➜ COMMAND\n");
		if (tmp->token_type == 6)
			printf("➜ FILE\n");
		if (tmp->token_type == 7)
			printf("➜ R_FLUX_CREATE\n");
		if (tmp->token_type == 8)
			printf("➜ L_FLUX_CREATE\n");
		if (tmp->token_type == 9)
			printf("➜ R_FLUX_APPEND\n");
		if (tmp->token_type == 10)
			printf("➜ L_FLUX_APPEND\n");
		if (tmp->token_type == 11)
			printf("➜ SINGLE_QUOTE_NODE\n");
		if (tmp->token_type == 12)
			printf("➜ DOUBLE_QUOTE_NODE\n");
		if (tmp->token_type == 13)
			printf("➜ ARG\n");
		if (tmp->token_type == 14)
			printf("➜ HERE_DOC\n");
		if (tmp->token_type == 100)
			printf("➜ CMD\n");
		printf("---------------\n");
		pos++;
		tmp = tmp->n;
	}
}

void	newnode_cmd_add_back(char **cmd, t_node **list)
{
	t_node	*new;

	new = newnode(NULL, CMD);
	new->cmd = cmd;
	add_back(list, new);
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

	new = (t_node *)ft_calloc(1, sizeof(t_node));
	if (new == NULL)
		return (0);
	new->s = s;
	new->token_type = token_type;
	new->cmd = NULL;
	new->filein = NULL;
	new->fileout = NULL;
	new->limiter = NULL;
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
