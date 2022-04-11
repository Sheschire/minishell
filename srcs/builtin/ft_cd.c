/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:38 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/11 16:33:52 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_cant_find(char **cmd)
{
	if (access(cmd[1], F_OK) == 0)
		return (check_dir(cmd));
	else
	{
		ft_putstr_fd("cd: no such file or directory : ", 2);
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

	var = NULL;
	if (ft_check_args_cd(cmd))
		return (1);
	if (!cmd[1] || (cmd[1] && (!ft_strcmp(cmd[1], "--")
				|| !ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "-"))))
	{
		if (cmd[1] && !ft_strcmp(cmd[1], "-"))
			return (oldpwd_cd(g));
		var = get_in_env("HOME", g);
		if (!var)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ((g_sig.exit_status = 1), 1);
		}
		else
			if (chdir(var) == 0)
				return (change_pwd_env(g));
		return (0);
	}
	else if (cmd[1] && chdir(cmd[1]) == 0)
		return (change_pwd_env(g));
	else
		return (cd_cant_find(cmd));
}
