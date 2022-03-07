/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:22:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/07 15:28:55 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char **builtcmd)
{
	int	size;

	size = ft_strlen(builtcmd[0]);
	if (!ft_strncmp(builtcmd[0], "cd", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "pwd", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "exit", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "env", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "export", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "echo", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "unset", size))
		return (1);
	else
		return (0);
}

int	is_builtin_exec(char **builtcmd, t_global *g, int i)
{
	if (i != INT_MAX && is_builtin(builtcmd))
		ft_close_pipe(g, i);
	if (!ft_strallcmp(builtcmd[0], "cd", 0))
		return (ft_cd(builtcmd, g));
	else if (!ft_strallcmp(builtcmd[0], "pwd", 0))
		return (ft_pwd());
	else if (!ft_strallcmp(builtcmd[0], "exit", 0))
		return (ft_exit(builtcmd, g));
	else if (!ft_strallcmp(builtcmd[0], "env", 0))
		return (ft_env(g));
	else if (!ft_strallcmp(builtcmd[0], "export", 0))
		return (ft_export(builtcmd, g));
	else if (!ft_strallcmp(builtcmd[0], "echo", 0))
		return (ft_echo(builtcmd));
	else if (!ft_strallcmp(builtcmd[0], "unset", 0))
		return (ft_unset(builtcmd, g));
	else
		return (0);
}

char	*get_in_env(char *str, t_global *g)
{
	int		i;
	char	*var;

	i = -1;
	while (g->env[++i])
	{
		if (!ft_strallcmp(g->env[i], str, 1))
		{
			var = g->env[i];
			while (*var != '=')
				var++;
			if (*var == '=')
				var++;
			return (var);
		}
	}
	return (NULL);
}
