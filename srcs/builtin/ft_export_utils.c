/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:24:55 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/08 14:24:58 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_equal(char *var)
{
	int	i;
	int	equal;

	equal = 0;
	i = -1;
	while (var[++i])
	{
		if (var[i] == '=')
			equal = 1;
	}
	return (equal);
}

int	env_lenght(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	loop_env(char **env, char *str, int i)
{
	int	j;
	int	k;
	int	equal;

	j = 0;
	k = 0;
	equal = 0;
	while (env[i][j])
	{
		if (env[i][j] == '=' && !equal)
		{
			str[k++] = env[i][j++];
			str[k++] = '\"';
			equal = 1;
		}
		if (env[i][j])
			str[k++] = env[i][j++];
		if (!env[i][j])
		{
			str[k++] = '\"';
			str[k] = '\0';
		}
	}
}

char	**ft_requote_env(char **env)
{
	int		i;
	char	*str;

	i = -1;
	while (env[++i])
	{
		str = (char *)ft_calloc(ft_strlen(env[i]) + 3, sizeof(char));
		loop_env(env, str, i);
		free(env[i]);
		env[i] = ft_strdup(str);
		free(str);
	}
	return (env);
}
