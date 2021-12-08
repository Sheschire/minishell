/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:36:55 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/08 13:00:00 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_global	g;

	(void)ac;
	(void)av;
	init_global(&g, env);
	while (1)
	{
		line = readline("\033[1;33m➜  Shell  ✗ \033[0m");
		if (ft_strlen(line))
		{
			add_history((const char *)line);
			input_parser(line, &g);
			// g->list [OK] -> Here call execution
		}
	}
  	return (0);
}