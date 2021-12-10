/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:53:35 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/10 14:02:19 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void    action(int signum, siginfo_t *info, void *context)
// {
// 	(void)context;
// 	if (signum == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		// QUIT RUNNING PROCESS AND PROMPT A NEW LINE
// 		return ;
// 	}
// 	if (signum == SIGQUIT)
// 		printf("signal is %d\n", signum);
// }

// void    handle_signals(void)
// {
// 	struct sigaction    sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = action;
// 	if (sigaction(SIGINT, &sa, NULL) < 0)
// 		printf("BUG\n");
// 	if (sigaction(SIGQUIT, &sa, NULL) < 0)
// 		printf("BUG\n");
// }