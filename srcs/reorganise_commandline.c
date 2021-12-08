/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganise_commandline.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:38:48 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/08 12:48:22 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reparse_flux(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		find_flux_direction(tmp);
		tmp = tmp->n;
	}
}

char	**build_flux_array(t_node **list)
{
	t_node	*tmp;
	int		i;
	char	**array;
	
	tmp = *list;
	i = found_token_flux(list);
	array = (char **)malloc(sizeof(char *) * i + 1);
	if (array == NULL)
		return (NULL);
	array[i] = NULL;
	i = 0;
	while (tmp)
	{
		if (is_redir(tmp))
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
		newnode_add_back(ft_strdup(flux_array[i]), TOKEN_FLUX, new_list);
		newnode_add_back(ft_strdup(flux_array[++i]), TOKEN_FILE, new_list);
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
		if (!is_redir(tmp) && tmp->token_type != TOKEN_FILE && tmp->token_type != HERE_DOC)
			newnode_add_back(ft_strdup(tmp->s), tmp->token_type, new_list);
		else
			i++;
		if (tmp->n && tmp->n->token_type == TOKEN_PIPE)
			push_array_into_list(new_list, flux_array, i, tmp);
		tmp = tmp->n;
	}
	push_array_into_list(new_list, flux_array, i, tmp);
}

void	reorganize_commandline(t_node **list)
{
	t_node	*new_list;
	char	**flux_array;

	new_list = 0;
	flux_array = build_flux_array(list);
	re_create_list(list, flux_array, &new_list);
	reparse_flux(&new_list);
	free_list(list);
	free_array(flux_array);
	*list = new_list;
	new_list = NULL;
}