/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:38:29 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/11 16:22:50 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_echo_flag(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		if (cmd[i][j++] == '-' && cmd[i][j] && cmd[i][j] == 'n')
		{
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] && cmd[i][j] != 'n')
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int	print_echo(char **cmd, int i, t_global *g)
{
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "~"))
			ft_pwd(1, g);
		else
			ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	return (0);
}

int	ft_echo(char **cmd, t_global *g)
{
	int	i;
	int	flag;

	g_sig.exit_status = 0;
	i = 1;
	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = ft_check_echo_flag(cmd);
	if (i > 1)
		flag = 0;
	else
		flag = 1;
	print_echo(cmd, i, g);
	if (flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
