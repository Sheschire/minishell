/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scotchy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:00:44 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/11 14:50:28 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_scotchy(t_node *list, int cmdi, int j, int increment)
{
	char	*scotchy;
	int		i;
	int		size;

	i = 0;
	if (increment == 2)
		size = (int)ft_strlen(list->cmd[cmdi]) - 1;
	else
		size = (int)ft_strlen(list->cmd[cmdi]);
	scotchy = (char *)ft_calloc(size, sizeof(char));
	j = 0;
	while (list->cmd[cmdi][j])
	{
		if (list->cmd[cmdi][j] == '$')
			j += increment;
		scotchy[i++] = list->cmd[cmdi][j++];
	}
	scotchy[i] = '\0';
	free(list->cmd[cmdi]);
	list->cmd[cmdi] = scotchy;
	return (-1);
}

int	big_scotch(t_node *list, int cmdi, int j)
{
	int		i;

	i = 0;
	if (is_in_set(list->cmd[cmdi][j + 1], "*@!"))
	{
		if (ft_strlen(list->cmd[cmdi]) == 2)
		{
			free(list->cmd[cmdi]);
			list->cmd[cmdi] = ft_strdup("");
			return (-1);
		}
		return (create_scotchy(list, cmdi, j, 2));
	}
	else if (is_in_set(list->cmd[cmdi][j + 1], "\'\"") && \
	find_pair(list->cmd[cmdi], j + 1, list->cmd[cmdi][j + 1]))
		return (create_scotchy(list, cmdi, j, 1));
	else if (list->cmd[cmdi][j + 1] == '?')
		return (j);
	return (j + 1);
}

int	create_scotchy_heredoc(t_node *list, int j, int increment)
{
	char	*scotchy;
	int		i;
	int		size;

	i = 0;
	if (increment == 2)
		size = (int)ft_strlen(list->here_str) - 1;
	else
		size = (int)ft_strlen(list->here_str);
	scotchy = (char *)ft_calloc(size, sizeof(char));
	j = 0;
	while (list->here_str[j])
	{
		if (list->here_str[j] == '$')
			j += increment;
		scotchy[i++] = list->here_str[j++];
	}
	scotchy[i] = '\0';
	free(list->here_str);
	list->here_str = scotchy;
	return (-1);
}

int	big_scotch_heredoc(t_node *list, int i)
{
	int	j;

	j = 0;
	if (is_in_set(list->here_str[i + 1], "*@!"))
		return (create_scotchy_heredoc(list, i, 2));
	return (i + 1);
}
