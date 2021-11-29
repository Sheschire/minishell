/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:21 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/29 16:09:10 by tlemesle         ###   ########.fr       */
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
	if (c == '/')
		return (TOKEN_SLASH);
	return (0);
}
char	*create_option_node(char *line, t_node **list)
{
	int		i;
	t_node	*tmp;

	i = 1;
	if (!find_token_type(line[i]))
	{
		tmp = newnode("-", TOKEN_LITERAL);
		add_back(list, tmp);
		line++;
		return (line);
	}
	while (find_token_type(line[i]) == 1)
		i++;
	tmp = newnode(ft_substr(line, 0, i), TOKEN_OPTION);
	add_back(list, tmp);
	line += i;
	return (line);
}

void	lexer_parser(char *line, t_node **list)
{
	t_node	*tmp;
	int		current_token_type;
	int		i;
	
	while (*line) 
	{
		i = 0;
		if (find_token_type(*line))
		{
			current_token_type = find_token_type(*line);
			if (current_token_type == TOKEN_OPTION)
				line = create_option_node(line, list);
			while (find_token_type(line[i]) == current_token_type)
				i++;
			if (*line)
			{
				tmp = newnode(ft_substr(line, 0, i), current_token_type);
				add_back(list, tmp);
				line += i;
			}
		}
		if (find_token_type(*line) == 0)
			line++;
	}
}

void	syntax_parser(t_node **node)
{
	while (*node)
	{
		if ((*node)->n && ((*node)->n->token_type == TOKEN_OPTION || (*node)->n->token_type == TOKEN_PIPE))
			(*node)->token_type = TOKEN_COMMAND;
		*node = (*node)->n;
	}
	print_list(node);
}

void	input_parser(char *line)
{
	t_node	*list;

	lexer_parser(line, &list);
}
