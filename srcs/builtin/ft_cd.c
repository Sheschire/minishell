/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:38 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/01 13:56:12 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*
// It shall return 0 in case of success.
// If it fails it shall return -1 and set errno in consequences.
*/

int	ft_cd(char **builtcmd)
{
	if (chdir(builtcmd[0]) == -1)
	{
		write(2, "no such file or directory : %s\n", ft_strlen(builtcmd[0]));
		return (-1);
	}
	return (0);
}
