/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:53:35 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/18 11:37:28 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    action(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	else
		exit(0);
}

void    handle_signals(void)
{
	struct sigaction    sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = action;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		printf("BUG\n");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		printf("BUG\n");
}