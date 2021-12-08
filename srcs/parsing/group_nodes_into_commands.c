/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_nodes_into_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:37:33 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/08 13:06:11 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd_size(t_node *list)
{
	t_node	*tmp;
	int		size;

	tmp = list;
	size = 0;
	while (tmp && !is_redir(tmp) && tmp->token_type != TOKEN_PIPE)
	{
		size++;
		tmp = tmp->n;
	}
	return (size);
}

void	fill_cmd_array(char **cmd, t_node *list)
{
	t_node	*tmp;
	int		i;
	
	tmp = list;
	i = 0;
	while (tmp && !is_redir(tmp) && tmp->token_type != TOKEN_PIPE)
	{
		cmd[i] = ft_strdup(tmp->s);
		i++;
		tmp = tmp->n;
	}
}

void	create_cmd_node(t_node **list, t_node **new_list)
{
	t_node	*tmp;
	int		size;
	char	**cmd;
	
	tmp = *list;
	size = 0;
	cmd = NULL;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_COMMAND)
		{
			size = get_cmd_size(tmp);
			cmd = (char **)malloc(sizeof(char *) * size + 1);
			cmd[size] = NULL;
			if (cmd == NULL)
				return ;
			fill_cmd_array(cmd, tmp);
			newnode_cmd_add_back(cmd, new_list);
		}
		if (is_redir(tmp) || tmp->token_type == TOKEN_PIPE || tmp->token_type == TOKEN_FILE || tmp->token_type == HERE_DOC)
			newnode_add_back(tmp->s, tmp->token_type, new_list);
		tmp = tmp->n;
	}
}

void	group_nodes_into_commands(t_node **list)
{
	t_node	*new_list;

	new_list = 0;
	create_cmd_node(list, &new_list);
	free_list(list);
	*list = new_list;
	new_list = NULL;
}