/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:38 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/05 18:09:20 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char **cmd)
{
	if (access(cmd[1], R_OK) == 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putchar_fd('\n', 2);
		g_sig.exit_status = 1;
	}
	return (1);
}

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

int	change_pwd_env(char *var, t_global *g)
{
	char	*var_export;
	char	*copy_pwd;
	char	*oldpwd;

	printf("COUCOU\n");
	oldpwd = ft_strdup("OLDPWD=");
	copy_pwd = ft_strdup(parse_env("PWD", g->env));
	oldpwd = ft_strjoin(oldpwd, copy_pwd);
	ft_export_variable(oldpwd, g);
	free(oldpwd);
	var_export = ft_strdup("PWD=");
	var_export = ft_strjoin(var_export, var);
	ft_export_variable(var_export, g);
	free(var_export);
	return (0);
}

int	ft_cd(char **cmd, t_global *g)
{
	char	*var;

	var = NULL;
	g_sig.exit_status = 0;
	if (ft_check_args_cd(cmd))
		return (1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "--") || !ft_strcmp(cmd[1], "~"))
	{
		var = get_in_env("HOME", g);
		if (!var)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_sig.exit_status = 1;
			return (1);
		}
		else
		{
			if (chdir(var) == 0)
				return (change_pwd_env(var, g));
			return (-1);
		}
	}
	else if (chdir(cmd[1]) == 0)
		return (change_pwd_env(cmd[1], g));
	else
		return (cd_cant_find(cmd));
}
