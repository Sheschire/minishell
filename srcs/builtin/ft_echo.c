/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:38:29 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/06 11:05:37 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo_n(char **builtcmd, int i)
{
	while (builtcmd[++i])
	{
		ft_putstr_fd(builtcmd[i], 1);
		ft_putchar_fd(' ', 1);
	}
	return ;
}

void	ft_echo(char **builtcmd)
{
	int	i;

	g_sig.exit_status = 0;
	i = 1;
	if (!builtcmd[1])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	if (!ft_strncmp("-n", builtcmd[1], ft_strlen(builtcmd[1])))
	{
		ft_echo_n(builtcmd, i);
		return ;
	}
	else
	{
		while (builtcmd[i++])
		{
			ft_putstr_fd(builtcmd[i], 1);
			ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
	}
}
