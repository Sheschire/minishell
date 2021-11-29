/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:54:27 by barodrig          #+#    #+#             */
/*   Updated: 2021/11/29 10:25:21 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*char	*ft_search_in_env(char **env, "PWD")
{
	int	i;
}*/

int	ft_pwd()
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
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Not enough args to test\n");
        return (0);
    }
    else
    {
        if (!ft_strncmp(av[1], "pwd", ft_strlen(av[1])))
            ft_pwd();
        else
            printf("ERROR IN AV[1]\n");
    }
    return (1);
}