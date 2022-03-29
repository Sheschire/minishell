/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/29 19:00:58 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

t_signal	g_sig;

void	arg_error(int ac, char **av)
{
	if (ac >= 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

int	start_parsing(char *line, t_global *g)
{
	add_history((const char *)line);
	free_array(g->path);
	g->path = ft_split(parse_env("PATH", g->env), ':');
	if (!input_parser(line, g))
		return (0);
	if (!g->syntax_err)
	{
		if (!ft_list_cleaner(g->list, g))
		{
			free_list(&g->list);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_global	g;

	init_global(&g, env);
	arg_error(ac, av);
	line = NULL;
	while (1)
	{
		handle_signals();
		line = readline("\033[1;33m➜  Shell  ✗ \033[0m");
		if (line)
		{
			if (*line)
			{
				if (start_parsing(line, &g) && !g.syntax_err)
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
