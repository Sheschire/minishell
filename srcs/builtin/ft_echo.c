/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:38:29 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/20 12:11:09 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_n(char **builtcmd, int i)
{
	while (builtcmd[++i])
	{
		ft_putstr_fd(builtcmd[i], 1);
		ft_putchar_fd(' ', 1);
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	int	i;

	g_sig.exit_status = 0;
	i = 1;
	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (!ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])))
		return (ft_echo_n(cmd, i));
	else
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
