/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 05:27:06 by barodrig          #+#    #+#             */
/*   Updated: 2022/02/07 06:05:41 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_declare_env(t_global *g)
{
	int	i;

	i = -1;
	while (g->env[++i])
	{
		printf("declare -x ");
		printf("%s\n", g->env[i]);
	}
}

void	ft_export(char **cmd, t_global *g)
{
	g_sig.exit_status = 0;
	
	if (!cmd[1])
	{
		ft_declare_env(g);
		return ;
	}
}