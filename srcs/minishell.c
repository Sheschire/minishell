/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/24 16:00:18 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **env)
{
	char	**path;
	char	*path_string;
	int		i;

	path_string = 0;
	path = 0;
	i = -1;
	while (env[++i])
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
			path_string = ft_strdup(env[i]);
	path = ft_split(path_string, ':');
	return (path);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	**path;
	char	*line;

	path = NULL;
	if (!*env)
		return (0); // TO DO : generate env manually and continue program
	path = get_path(env);
  	return 0;
}