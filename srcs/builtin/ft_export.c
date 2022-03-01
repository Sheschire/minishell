/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 05:27:06 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/01 15:59:55 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_lenght(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**create_sort_env(char **env)
{
	char	**sort_env;
	char	*str;
	int		i;
	int		j;

	str = NULL;
	i = -1;
	j = env_lenght(env);
	sort_env = (char **)ft_calloc(j + 1, sizeof(char *));
	while (env[++i])
		sort_env[i] = ft_strdup(env[i]);
	sort_env[i] = NULL;
	i = -1;
	while (sort_env[++i])
	{
		j = i + 1;
		while (sort_env[j])
		{
			if (ft_strcmp(sort_env[i], sort_env[j]) > 0)
			{
				str = sort_env[i];
				sort_env[i] = sort_env[j];
				sort_env[j] = str;
			}
			j++;
		}
	}
	return (sort_env);
}

void	ft_declare_env(t_global *g)
{
	int		i;
	char	**sort_env;

	sort_env = create_sort_env(g->env);
	i = 0;
	while (sort_env[i])
	{
		printf("declare -x ");
		printf("%s\n", sort_env[i]);
		i++;
	}
	free_array(sort_env);
}

int	ft_check_variable(t_global *g, char **cmd)
{
	int	i;
	
	i = 0
	if (!cmd || !cmd[0] || cmd[0] == '=')
		return (0);
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i])
		i++;
	}
}

void	ft_export(char **cmd, t_global *g)
{
	int	i;

	g_sig.exit_status = 0;
	i = 0;
	if (!cmd[1])
	{
		ft_declare_env(g);
		return ;
	}
	else
	{
		while (cmd[++i])
		{
			if (!ft_check_variable(g, cmd))
			{
				ft_putstr_fd("shell\n export: '", 2);
				ft_putstr_fd(cmd[++i], 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
			}
		}
		//ft_export_variable(g, cmd);
	}
	return ;
}
