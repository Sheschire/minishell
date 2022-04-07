/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:54:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/07 11:52:10 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cwd(char *cwd)
{
	free(cwd);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	ft_pwd(int flag)
{
	char	*cwd;
	int		buffer_size;

	buffer_size = 1024;
	cwd = ft_calloc(1, buffer_size);
	if (!cwd)
		return (1);
	if (getcwd(cwd, buffer_size) == NULL)
		return (free(cwd), 1);
	cwd = getcwd(cwd, buffer_size);
	while (errno == ERANGE && buffer_size < 15360)
	{
		buffer_size += 1024;
		free(cwd);
		cwd = ft_calloc(1, buffer_size);
		cwd = getcwd(cwd, buffer_size);
	}
	if (errno == ENOENT || errno == EACCES)
		return (error_cwd(cwd));
	ft_putstr_fd(cwd, 1);
	if (!flag)
		ft_putchar_fd('\n', 1);
	return ((free(cwd)), 0);
}
