/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:41:14 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/22 13:41:36 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token_err)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	ft_putstr_fd(token_err, 2);
	ft_putstr_fd("'\n", 2);
	return ;
}
