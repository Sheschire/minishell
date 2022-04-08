/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_declare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:04:14 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/08 14:23:33 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_sort_env(char **sort_env, char **env)
{
	char	*str;
	int		i;
	int		j;

	str = NULL;
	i = -1;
	while (env[++i])
		sort_env[i] = ft_strdup(env[i]);
	sort_env[i] = NULL;
	i = -1;
	while (sort_env[++i])
	{
		j = i;
		while (sort_env[++j])
		{
			if (ft_strcmp(sort_env[i], sort_env[j]) > 0)
			{
				str = sort_env[i];
				sort_env[i] = sort_env[j];
				sort_env[j] = str;
			}
		}
	}
	return (ft_requote_env(sort_env));
}

void	ft_declare_env(t_global *g)
{
	int		i;
	char	**sort_env;
	size_t	env_size;

	env_size = env_lenght(g->env);
	sort_env = (char **)ft_calloc(env_size + 1, sizeof(char *));
	if (!sort_env)
		return ;
	sort_env = create_sort_env(sort_env, g->env);
	i = 0;
	while (sort_env[i])
	{
		printf("declare -x ");
		printf("%s\n", sort_env[i]);
		i++;
	}
	free_array(sort_env);
}
