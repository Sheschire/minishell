/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:54:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/11 16:24:35 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cwd(char *cwd, t_global *g)
{
	free(cwd);
	cwd = parse_env("PWD", g->env);
	if (!cwd)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	else
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
}

int	ft_pwd(int flag, t_global *g)
{
	char	*cwd;
	int		buffer_size;

	buffer_size = 1024;
	cwd = ft_calloc(1, buffer_size);
	if (!cwd)
		return (1);
	if (getcwd(cwd, buffer_size) == NULL)
		return (error_cwd(cwd, g));
	cwd = getcwd(cwd, buffer_size);
	while (errno == ERANGE && buffer_size < 15360)
	{
		buffer_size += 1024;
		free(cwd);
		cwd = ft_calloc(1, buffer_size);
		cwd = getcwd(cwd, buffer_size);
	}
	if (errno == ENOENT || errno == EACCES)
		return (error_cwd(cwd, g));
	ft_putstr_fd(cwd, 1);
	if (!flag)
		ft_putchar_fd('\n', 1);
	return ((free(cwd)), 0);
}
