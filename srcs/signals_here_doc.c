/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:44:08 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/29 10:47:15 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event_heredoc(void)
{
	return (0);
}

void	here_doc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = here_doc_action;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		ft_putstr_fd("Signal error\n", 2);
	signal(SIGQUIT, SIG_IGN);
}

void	here_doc_action(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		g_sig.exit_status = 130;
		ft_putendl_fd("", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
	}
}
