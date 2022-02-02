/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:53:35 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/02 15:17:42 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	kill_pids()
{
	int	i;

	i = -1;
	while (g_sig.pids[++i])
		kill(g_sig.pids[i], SIGTERM);
	return (i);
}

void    action(int signum, siginfo_t *info, void *context)
{
	int	kill_ret;
	(void)context;

	if (signum == SIGINT)
	{
		kill_ret = kill_pids();
		write(1, "\n", 1);
		//TO DO : INSERT FREE FUNCTION
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
			write(2, "Quitter (core dumped)", ft_strlen("Quitter (core dumped)"));
			write(1, "\n", 1);
		}
		else
			ft_putstr_fd("\b\b  \b\b", 1);
	}
	else // TO DO : HANDLE OTHER CONTROLS
	{
		
	}
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