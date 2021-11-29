/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:21 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/29 10:51:55 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_token_type(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (TOKEN_LITERAL);
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '>' || c == '<')
		return (TOKEN_FLUX);
	if (c == '-')
		return (TOKEN_OPTION);
	return (0);
}

void	lexer_parser(char *line, t_node **list)
{
	t_node	*tmp;
	int		current_token_type;
	int		i;
	int		j;
	char	**tab;
	
	while (*line)
	{
		i = 0;
		if (find_token_type(*line))
		{
			current_token_type = find_token_type(*line);
			while (find_token_type(line[i]) == current_token_type)
				i++;
			tmp = newnode(ft_substr(line, 0, i), current_token_type);
			add_back(list, tmp);
			line += i;
		}
		if (find_token_type(*line) == 0)
			line++;
	}
	print_list(list);
}

void	input_parser(char *line)
{
	t_node	*list;
	
	lexer_parser(line, &list);
}
