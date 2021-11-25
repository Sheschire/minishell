/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/25 14:09:13 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **env)
{
	char	**path;
	char	*path_string;

	path_string = getenv("PATH");
	path = ft_split(path_string, ':');
	return (path);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char		**path;
	char	*line;

	path = NULL;
	if (!*env)
		return (0); // TO DO : generate env manually and continue program
	path = get_path(env);
	while (1)
	{
		line = readline("\033[1;33m➜  Shell  ✗ \033[0m");
		if (ft_strlen(line))
		{
			add_history((const char *)line);
			input_parser(line);
		}
	}
  	return 0;
}