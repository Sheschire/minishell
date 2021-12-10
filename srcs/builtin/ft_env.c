/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:06:35 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/29 10:46:54 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_env(t_global *g)
{
	int	i;

	i = -1;
	while (g->env[++i])
		printf("%s\n", g->env[i]);
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_global g;

// 	if (ac != 2)
// 	{
// 		printf("Not the right number of arguments to launch test.\n");
// 		return (0);
// 	}
// 	g.env = envp;
// 	if (!ft_strncmp(av[1], "env", ft_strlen(av[1])))
// 			ft_env(&g);
//  	else
// 			printf("ERROR IN AV[1]\n");
// 	return (1);
// }