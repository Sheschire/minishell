/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:53:35 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/20 12:03:07 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	kill_pids(void)
{
	int	i;

	i = -1;
	while (g_sig.pids[++i])
		kill(g_sig.pids[i], SIGTERM);
	return (i);
}

void	action(int signum, siginfo_t *info, void *context)
{
	int	kill_ret;

	/* 
	//	WHY KEEP THEM IF THEY ARE NOT USEFUL ?
	*/
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		kill_ret = kill_pids();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (!kill_ret)
			rl_redisplay();
		return ;
	}
	else if (signum == SIGQUIT)
	{
		kill_ret = kill_pids();
		if (kill_ret)
		{
			ft_putstr_fd("Quitter (core dumped)", 2);
			write(1, "\n", 1);
		}
		else
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void    handle_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = action;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		printf("BUG\n");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		printf("BUG\n");
}
