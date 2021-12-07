/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:46:50 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/07 14:17:26 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_node **list)
{
	t_node	*to_free;
	t_node	*save;
	
	if (!list)
		return ;
	to_free = *list;
	while (to_free)
	{
		save = to_free->n;
		free(to_free);
		to_free = save;
	}
	*list = NULL;
}

char	**free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}