/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:56:57 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/07 15:35:00 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_unset(char **cmd, t_global *g)
{
	int	i;

	g_sig.exit_status = 0;
	i = -1;
	while (g->env[++i])
	{
		if (!ft_strallcmp(g->env[i], cmd[1], 1))
		{
			ft_remove_from_env(g, i);
		}
	}
	return (0);
}