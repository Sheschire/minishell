/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:38 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/29 10:47:14 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*
// It shall return 0 in case of success.
// If it fails it shall return -1 and set errno in consequences.
*/

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
	{
		printf("no such file or directory : %s\n", path);
		return (-1);
	}
	return (0);
}

/*int	ft_pwd()
{
	char	*cwd;
	int		buffer_size;

	buffer_size = 1000;
	cwd = ft_calloc(1, buffer_size);
	if (!cwd)
		return (0);
	cwd = getcwd(cwd, buffer_size);
	while (!cwd)
	{
		buffer_size += 1000;
		free(cwd);
		cwd = ft_calloc(1, buffer_size);
		if (!cwd)
			return (0);
		cwd = getcwd(cwd, buffer_size);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (1);
}*/

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Not enough args to test\n");
        return (0);
    }
    else
    {
        if (!ft_strncmp(av[1], "cd", ft_strlen(av[1])))
		{
            ft_cd(av[2]);
			ft_pwd();
		}
        else
            printf("ERROR IN AV[1]\n");
    }
    return (1);
}