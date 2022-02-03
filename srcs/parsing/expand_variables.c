/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/03 14:22:08 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_env(char *var, char **env)
{
	char	*var_value;

	var_value = getenv(var);
	if (var_value != NULL)
		return (var_value);
	return ("");
}

char	*expand_variable(char *s, t_global *g)
{
	int		i;
	char	*tmp;
	char	*var;

	i = 0;
	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' ')
 		i++;
	tmp = ft_substr(s, 0, i);
	var = ft_strdup(parse_env(tmp, g->env));
	free(tmp);
	return (var);
}

void	big_join(char *s1, char *s2, int i)
{
	char	*sub;

	sub = ft_substr(s1, 0, i);
	free(s1);
	s1 = ft_strjoin(sub, s2);
	printf("s1 = %s\n", s1);
	free(s2);
}

int	find_pair(char *s, int i, char c)
{
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

int	dup_size(char *s)
{
	int		i;
	char	actual_quote;
	int		pair_to_remove;
	
	i = -1;
	actual_quote = 0;
	pair_to_remove = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			actual_quote = s[i];
			if (find_pair(s, i, actual_quote))
				pair_to_remove++;
			i++;
			while (s[i] && s[i] != actual_quote)
				i++;
			if (!s[i])
				return (i);
		}
	}
	return (i - (pair_to_remove * 2));
}

void	dup_without_quotes(t_node *tmp, char *s, t_global *g)
{
	int		i;
	int		j;
	char	*dup;
	char	actual_quote;
	
	i = -1;
	j = 0;
	tmp->d_quotes = 0;
	//dup = (char *)malloc(sizeof(char) * (dup_size(s) + 1));
	// if (!dup)
	// 	ft_exit(ft_split("exit 0", ' '));
	// while (s[++i])
	// {
	// 	if ((s[i] == '\'' || s[i] == '\"') && find_pair(s, i, s[i]))
	// 	{
	// 		printf("yoooooo\n");
	// 		// actual_quote = s[i];
	// 		// while (s[++i] != actual_quote)
	// 		// {
	// 		// 	dup[j] = s[i];
	// 		// 	j++;
	// 		// }
	// 		// i++;
	// 	}
	// 	dup[j] = s[i];
	// 	j++;
	// }
	// dup[j] = '\0';
	// printf("DUP = %s\n", dup);
}

void	quote_parser(t_node **list, t_global *g)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!strcmp(tmp->s, "$?"))
		{
			free(tmp->s);
			tmp->s = ft_itoa(g_sig.exit_status);
		}
		dup_without_quotes(tmp, tmp->s, g);
		tmp = tmp->n;
	}
}