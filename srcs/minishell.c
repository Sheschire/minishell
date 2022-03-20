/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/20 12:48:33 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

t_signal	g_sig;

int	arg_error(int ac, char **av)
{
	if (ac > 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (127);
	}
	return (0);
}

void	launch_parsing(char *line, t_global *g)
{
	add_history((const char *)line);
	input_parser(line, g);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_global	g;

	arg_error(ac, av);
	init_global(&g, env);
	line = NULL;
	while (1)
	{
		handle_signals();
		line = readline("\033[1;33m➜  Shell  ✗ \033[0m");
		if (line)
		{
			if (*line)
			{
				launch_parsing(line, &g);
				if (!g.syntax_err)
					pipex(&g, g.list);
				g.syntax_err = 0;
			}
		}
		else
			ft_exit_signal(&g);
		free(line);
	}
	return (0);
}
