/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:46:11 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/11 16:18:50 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	oldpwd_cd(t_global *g)
{
	char	*var;

	var = parse_env("OLDPWD", g->env);
	if (!var)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return ((g_sig.exit_status = 1), 1);
	}
	else
	{
		if (chdir(var) == 0)
		{
			change_pwd_env(g);
			ft_pwd(0, g);
			return ((g_sig.exit_status = 0), 0);
		}
		else
			return ((g_sig.exit_status = 1), 1);
	}
}

int	change_pwd_env(t_global *g)
{
	char	*cmd;
	char	*var_export;
	char	*copy_pwd;
	char	*oldpwd;

	cmd = ft_calloc(1, 1024);
	oldpwd = ft_strdup("OLDPWD=");
	copy_pwd = ft_strdup(parse_env("PWD", g->env));
	oldpwd = ft_strjoin(oldpwd, copy_pwd);
	ft_export_variable(oldpwd, g);
	free(oldpwd);
	free(copy_pwd);
	var_export = ft_strdup("PWD=");
	var_export = ft_strjoin(var_export, getcwd(cmd, 1024));
	ft_export_variable(var_export, g);
	free(cmd);
	free(var_export);
	return (0);
}
