/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/10 15:27:36 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_global	g;

	(void)ac;
	(void)av;
	init_global(&g, env);
	while (1)
	{
		//handle_signals();
		line = readline("\033[1;33m➜  Shell  ✗ \033[0m");
		if (ft_strlen(line))
		{
			add_history((const char *)line);
			input_parser(line, &g);
			pipex(&g, (*g.list));
		}
		free(line);
	}
	return (0);
}
