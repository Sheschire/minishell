/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganise_commandline.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:38:48 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/07 13:40:18 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir_or_file(t_node *tmp)
{
	int	type;

	type = tmp->token_type;
	if ((tmp->token_type < R_FLUX_CREATE || tmp->token_type > L_FLUX_APPEND) && tmp->token_type != TOKEN_FILE)
		return (0);
	else if ((tmp->token_type >= R_FLUX_CREATE && tmp->token_type <= L_FLUX_APPEND) || tmp->token_type == TOKEN_FILE)
		return (1);
	return (0);
}

char	**build_flux_array(t_node **list)
{
	t_node	*tmp;
	int		i;
	char	**array;
	
	tmp = *list;
	i = found_token_flux(list);
	array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp)
	{
		if (tmp && tmp->token_type >= R_FLUX_CREATE && tmp->token_type <= L_FLUX_APPEND)
		{
			array[i] = ft_strdup(tmp->s);
			array[++i] = ft_strdup(tmp->n->s);
			i++;
		}
		tmp = tmp->n;
	}
	return (array);
}

void	push_array_into_list(t_node **new_list, char **flux_array, int size, t_node *tmp)
{
	static int	i = 0;

	while (i < size)
	{
		newnode_add_back(flux_array[i], TOKEN_FLUX, new_list);
		newnode_add_back(flux_array[++i], TOKEN_FILE, new_list);
		i++;
	}
	if (!tmp)
		i = 0;
}

void	re_create_list(t_node **list, char **flux_array, t_node **new_list)
{
	t_node	*tmp;
	int		i;

	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (!is_redir_or_file(tmp))
			newnode_add_back(tmp->s, tmp->token_type, new_list);
		else
			i++;
		if (tmp->n && tmp->n->token_type == TOKEN_PIPE)
			push_array_into_list(new_list, flux_array, i, tmp);
		tmp = tmp->n;
	}
	push_array_into_list(new_list, flux_array, i, tmp);
	print_list(new_list);
}

void	reorganize_commandline(t_node **list)
{
	char	**flux_array;
	t_node	*new_list;

	new_list = 0;
	flux_array = build_flux_array(list);
	re_create_list(list, flux_array, &new_list);
}