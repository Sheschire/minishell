/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_nodes_into_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:37:33 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/10 17:19:47 by tlemesle         ###   ########.fr       */
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
	cmd[i] = NULL;
	free(list->s);
	list->s = NULL;
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
			cmd = (char **)ft_calloc(size + 1, sizeof(char *));
			if (cmd == NULL)
				return ;
			fill_cmd_array(cmd, tmp);
			newnode_cmd_add_back(cmd, new_list);
		}
		else if (is_redir(tmp) || tmp->token_type == TOKEN_PIPE || \
		tmp->token_type == TOKEN_FILE || tmp->token_type == HERE_DOC)
			newnode_add_back(ft_strdup(tmp->s), tmp->token_type, new_list);
		tmp = tmp->n;
	}
}

void	copy_cmdlist_into_list(t_node **list, t_node **cmd_list)
{
	t_node	*tmp;

	tmp = *cmd_list;
	while (tmp)
	{
		if (tmp->token_type == CMD)
			newnode_cmd_add_back(ft_arraydup(tmp->cmd), list);
		else
			newnode_add_back(ft_strdup(tmp->s), tmp->token_type, list);
		tmp = tmp->n;
	}
}

void	group_nodes_into_commands(t_node **list)
{
	t_node	*cmd_list;

	cmd_list = 0;
	create_cmd_node(list, &cmd_list);
	free_list(list);
	copy_cmdlist_into_list(list, &cmd_list);
	free_list(&cmd_list);
}
