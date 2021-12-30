/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:09:42 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/30 12:32:17 by barodrig         ###   ########.fr       */
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

void	define_after_next(t_node *tmp)
{
	if (tmp->n && tmp->n->token_type == R_FLUX_APPEND)
	{
		tmp->after = R_FLUX_APPEND;
		tmp->fileout = (tmp->n->n)->s;
	}
	else if (tmp->n && tmp->n->token_type == L_FLUX_APPEND)
	{
		tmp->after = L_FLUX_APPEND;
		tmp->limiter = (tmp->n->n)->s;
	}
	else
		tmp->after = 0;
}

void	define_after(t_node *tmp)
{
	if (tmp->n && tmp->n->token_type == R_FLUX_CREATE)
	{
		tmp->after = R_FLUX_CREATE;
		tmp->fileout = (tmp->n->n)->s;
	}
	else if (tmp->n && tmp->n->token_type == L_FLUX_CREATE)
	{
		tmp->after = L_FLUX_CREATE;
		tmp->filein = (tmp->n->n)->s;
	}
	else if (tmp->n && tmp->n->token_type == TOKEN_PIPE)
		tmp->after = TOKEN_PIPE;
	else
		define_after_next(tmp);
	return ;
}

void	define_position(t_node *node)
{
	t_node	*tmp;
	t_node	*begin;
	int		i;

	tmp = node;
	begin = node;
	i = 0;
	while (tmp)
	{
		if (tmp->token_type == CMD)
		{
			if (i != 0)
				tmp->before = TOKEN_PIPE;
			define_after(tmp);
			i++;
		}
		if (!tmp->n)
			break ;
		tmp = tmp->n;
	}
}
