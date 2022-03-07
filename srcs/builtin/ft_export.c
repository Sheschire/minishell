/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:03:01 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/07 15:15:51 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_variable(t_global *g, char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd[0] || cmd[0] == '='
		|| ((cmd[0] < 'A' || cmd[0] > 'Z')
			&& (cmd[0] < 'a' || cmd[0] > 'z') && cmd[0] != '_'))
		return (0);
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (((cmd[i] < 'A' || cmd[i] > 'Z')
				&& (cmd[i] < 'a' && cmd[i] > 'z') && cmd[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

char	**create_new_env(char *var, int count, t_global *g)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[i] = var;
	while (++i < count)
		new_env[i] = ft_strdup(g->env[i - 1]);
	new_env[i] = NULL;
	return (new_env);
}

void	ft_put_in_env(char *var, t_global *g, int index)
{
	int		count;
	char	*dequoted_var;
	char	**new_env;

	count = env_lenght(g->env);
	dequoted_var = (char *)ft_calloc(dup_size(var) + 1, sizeof(char));
	if (index == -1)
	{
		dup_without_quotes(dequoted_var, var);
		new_env = create_new_env(dequoted_var, count + 1, g);
		free_array(g->env);
		g->env = new_env;
	}
	else
	{
		free(g->env[index]);
		dup_without_quotes(dequoted_var, var);
		g->env[index] = dequoted_var;
	}
}

void	ft_export_variable(char *var, t_global *g)
{
	int		i;
	char	**var_split;

	i = -1;
	var_split = ft_split(var, '=');
	if (var_split[0])
	{
		while (g->env[++i])
		{
			if (!ft_strallcmp(g->env[i], var_split[0], 1))
			{
				if (!var_split[1])
				{
					free_array(var_split);
					return ;
				}
				ft_put_in_env(var, g, i);
				return ;
			}
		}
		free_array(var_split);
		ft_put_in_env(var, g, -1);
	}
}

int	ft_export(char **cmd, t_global *g)
{
	int	i;

	g_sig.exit_status = 0;
	i = 0;
	if (!cmd[1])
	{
		ft_declare_env(g);
		return (0);
	}
	while (cmd[++i])
	{
		if (!ft_check_variable(g, cmd[i]))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_sig.exit_status = 1;
		}
		else
			ft_export_variable(cmd[i], g);
	}
	return (0);
}
