/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:54:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/05 17:35:30 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../libft/libft.h"

int	ft_pwd(int flag)
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
	ft_putstr_fd(cwd, 1);
	if (!flag)
		ft_putchar_fd('\n', 1);
	free(cwd);
	return (0);
}
