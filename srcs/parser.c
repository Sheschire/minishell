/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:21 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/29 10:46:33 by tlemesle         ###   ########.fr       */
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
	
	i = 0;
	while (*line)
	{
		if (find_token_type(*line))
		{
			current_token_type = find_token_type(*line);
			//while (current_token_type == fi)	
		}
		line++;
	}
	print_list(list);
}

void	input_parser(char *line)
{
	t_node	*list;
	
	lexer_parser(line, &list);
}


// tab = ft_split(line, ' ');
// 	while (tab[++i])
// 	{
// 		h = 0;
// 		j = -1;
// 		current_token_type = find_token_type(tab[i][0]);
// 		while (tab[i][++j])
// 		{
// 			if (current_token_type != find_token_type(tab[i][j]))
// 			{
// 				tmp = newnode(ft_substr(tab[i], h, j), current_token_type);
// 				add_back(list, tmp);
// 				h += j;
// 				current_token_type = find_token_type(tab[i][j]);
// 			}
// 		}
// 	}