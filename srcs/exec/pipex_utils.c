/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:09:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/06 14:12:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_are_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	count_cmd(t_node *node)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = node;
	if (!tmp->n)
		return (1);
	while (tmp->n)
	{
		if (tmp->token_type == CMD)
			i++;
		if (tmp->n)
			tmp = tmp->n;
	}
	if (tmp->token_type == CMD)
		i++;
	return (i);
}

void	ft_close_pipe(t_global *g, int i)
{
	if (i == INT_MAX)
		i = 0;
	else
	{
		close(g->_pipes[i][0]);
		close(g->_pipes[i][1]);
		return ;
	}
	while (i < g->cmd_nbr)
	{
		if (g->_pipes[i][1])
			close(g->_pipes[i][1]);
		if (g->_pipes[i][0])
			close(g->_pipes[i][0]);
		i++;
	}
}
