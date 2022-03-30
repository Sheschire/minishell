/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:38 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/30 10:54:43 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home_not_set(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	g_sig.exit_status = 1;
	return (1);
}

int	cd_cant_find(char **cmd)
{
	if (access(cmd[1], F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: no such file or directory : ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putchar_fd('\n', 2);
	}
	g_sig.exit_status = 1;
	return (1);
}

int	ft_check_args_cd(char **builtcmd)
{
	char	*var;

	var = NULL;
	if (*builtcmd && builtcmd[1] && builtcmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_sig.exit_status = 1;
		return (1);
	}
	return (0);
}

int	ft_cd(char **cmd, t_global *g)
{
	char	*var;

	g_sig.exit_status = 0;
	if (ft_check_args_cd(cmd))
		return (1);
	if (!cmd[1] || !ft_strallcmp(cmd[1], "--", 0)
		|| !ft_strallcmp(cmd[1], "~", 0))
	{
		var = get_in_env("HOME", g);
		if (!var)
			return (cd_home_not_set());
		else
			return (chdir(var));
	}
	else if (chdir(cmd[1]) == 0)
		return (0);
	else
		return (cd_cant_find(cmd));
}
