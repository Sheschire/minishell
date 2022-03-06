/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:54:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/06 14:14:22 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_pwd(void)
{
	char	*cwd;
	int		buffer_size;

	buffer_size = 1024;
	cwd = ft_calloc(1, buffer_size);
	if (!cwd)
		return (1);
	cwd = getcwd(cwd, buffer_size);
	while (!cwd)
	{
		buffer_size += 1024;
		free(cwd);
		cwd = ft_calloc(1, buffer_size);
		if (!cwd)
			return (1);
		cwd = getcwd(cwd, buffer_size);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
