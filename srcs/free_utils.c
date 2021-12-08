/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:46:50 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/08 13:00:15 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

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
		// if (to_free->s)                  NEED TO FIND A SOLUTION TO CHECK IF FREE IS NEEDED
		// 	free(to_free->s);
		//if (to_free->token_type == CMD)
			//free_array(to_free->cmd);
		free(to_free);
		to_free = save;
	}
	*list = NULL;
}