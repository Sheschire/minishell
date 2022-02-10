/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/10 17:35:26 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

t_signal	g_sig;

void	dup_cp_std(t_global *g)
{
	dup2(g->cp_stdin, STDIN_FILENO);
	close(g->cp_stdin);
	dup2(g->cp_stdout, STDOUT_FILENO);
	close(g->cp_stdout);
}

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
				dup_cp_std(&g);
				free_exec(&g);
				free_list(&g.list);
			}
		}
		else
			ft_exit_signal(&g);
		free(line);
	}
	return (0);
}
