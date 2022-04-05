/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:22:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/05 17:35:58 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

void	ft_exit_num_arg(char **cmd, t_global *g)
{
	ft_putstr_fd("exit\n exit: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_minishell(g);
	exit(255);
}

int	is_builtin(char **builtcmd)
{
	if (!builtcmd)
		return (0);
	if (!ft_strncmp(builtcmd[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "env", 4))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "export", 7))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "unset", 6))
		return (1);
	else
		return (0);
}

int	is_builtin_exec(char **builtcmd, t_global *g, int i, t_node *node)
{
	if (i != INT_MAX && is_builtin(builtcmd))
		ft_close_pipe(g, i);
	if (!ft_strallcmp(builtcmd[0], "cd", 0))
		return (ft_cd(builtcmd, g));
	else if (!ft_strallcmp(builtcmd[0], "pwd", 0))
		return (ft_pwd(0));
	else if (!ft_strallcmp(builtcmd[0], "exit", 0))
		return (ft_exit(builtcmd, g, node));
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
