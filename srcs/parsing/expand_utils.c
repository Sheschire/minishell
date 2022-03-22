/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:13:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/22 13:16:55 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_expand(char *dup, char *to_replace, int j)
{
	int	i;

	i = 0;
	while (to_replace[i])
		dup[j++] = to_replace[i++];
	return (j);
}

void	recreate_string_with_empty(t_node *node, char *tmp, int j)
{
	char	*sub1;
	char	*sub2;
	char	*join;

	sub1 = ft_substr(node->s, 0, j - 1);
	if ((j + ft_strlen(tmp)) == ft_strlen(node->s))
		sub2 = ft_strdup("");
	else
		sub2 = ft_substr(node->s, j + ft_strlen(tmp), \
		ft_strlen(node->s) - ft_strlen(tmp));
	join = ft_strjoin(sub1, sub2);
	free(node->s);
	node->s = ft_strdup(join);
	if (!ft_strcmp(node->s, ""))
		printf("\n");
	free(join);
	free(sub2);
}

char	*recreate_string(char *tmp, char *var, t_node *node, int start)
{
	char	*dup;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(node->s) + ft_strlen(var) - ft_strlen(tmp);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (node->s[i])
	{
		while (i < start)
			dup[j++] = node->s[i++];
		j = replace_expand(dup, var, j);
		i += ft_strlen(tmp) + 1;
		if (node->s[i])
			while (node->s[i])
				dup[j++] = node->s[i++];
	}
	dup[j] = '\0';
	return (dup);
}
