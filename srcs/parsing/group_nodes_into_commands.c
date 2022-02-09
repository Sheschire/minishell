/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_nodes_into_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:37:33 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/09 08:34:59 by barodrig         ###   ########.fr       */
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
			cmd = (char **)ft_calloc(size + 1, sizeof(char *));
			cmd[size] = NULL;
			if (cmd == NULL)
				return ;
			fill_cmd_array(cmd, tmp);
			newnode_cmd_add_back(cmd, new_list);
		}
		if (is_redir(tmp) || tmp->token_type == TOKEN_PIPE || tmp->token_type == TOKEN_FILE || tmp->token_type == HERE_DOC)
			newnode_add_back(ft_strdup(tmp->s), tmp->token_type, new_list);
		tmp = tmp->n;
	}
}

char	**ft_arraydup(char **tab)
{
	char	**dup;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	dup = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (0);
	i = -1;
	while (tab[++i])
		dup[i] = ft_strdup(tab[i]);
	return (dup);
}

void	copy_cmdlist_into_list(t_node **list, t_node **cmd_list)
{
	t_node *tmp;
	int	i = 0;
	tmp = *cmd_list;
	while (tmp)
	{
		if (tmp->token_type == CMD)
			newnode_cmd_add_back(ft_arraydup(tmp->cmd), list);
		else
			newnode_add_back(ft_strdup(tmp->s), tmp->token_type, list);
		tmp = tmp->n;
		i++;
	}
}

void	group_nodes_into_commands(t_node **list)
{
	t_node	*cmd_list;

	cmd_list = 0;
	create_cmd_node(list, &cmd_list);
	free_list(list);
<<<<<<< HEAD
	*list = new_list;
	//free_list(&new_list);
}
=======
	copy_cmdlist_into_list(list, &cmd_list);
	free_list(&cmd_list);
}
>>>>>>> tlemesle
