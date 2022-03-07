/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/07 14:19:59 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

t_signal	g_sig;

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_global	g;

	(void)ac;
	(void)av;
	if (ac >= 2)
	{
		printf("NO SUCH FILE OR DIRECTORY\n"); // REPLACE WITH RETURN ERROR
		exit (0);
	}
	init_global(&g, env);
	line = NULL;
	g.cp_stdin = dup(STDIN_FILENO);
	g.cp_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		handle_signals();
		line = readline("\033[1;33m➜  Shell  ✗ \033[0m");
		if (line)
		{
			if (*line)
			{
				add_history((const char *)line);
				input_parser(line, &g);
				pipex(&g, g.list);
				free_exec(&g);
				free_list(&g.list);
			}
		}
		else
		{
			printf("I QUIT BITCH !\n");
			ft_exit_signal(&g);
		}
		free(line);
	}
	return (0);
}
