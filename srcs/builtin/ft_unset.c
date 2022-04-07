/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:56:57 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/07 14:36:09 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_from_env(t_global *g, int index)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = (char **)ft_calloc(env_lenght(g->env), sizeof(char *));
	if (!new_env)
		return ;
	i = -1;
	j = 0;
	while (g->env[++i])
	{
		if (i == index)
			i++;
		else
		{
			new_env[j] = ft_strdup(g->env[i]);
			j++;
		}
	}
	free_array(g->env);
	g->env = new_env;
}

void	ft_launch_unset(t_global *g, char **cmd, int i, int j)
{
	while (g->env[++i])
	{
		if (!ft_strallcmp(g->env[i], cmd[j], 1))
			ft_remove_from_env(g, i);
	}
	if (!ft_strallcmp(cmd[j], "PATH", 1))
	{
		free_array(g->path);
		g->path = (char **)ft_calloc(1, sizeof(char *));
		g->path[0] = NULL;
	}
}

int	ft_unset(char **cmd, t_global *g)
{
	int	i;
	int	j;

	g_sig.exit_status = 0;
	j = 0;
	while (cmd[++j])
	{
		i = -1;
		if (!ft_check_variable(cmd[j]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd[j], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_sig.exit_status = 1;
		}
		else
			ft_launch_unset(g, cmd, i, j);
	}
	return (0);
}
