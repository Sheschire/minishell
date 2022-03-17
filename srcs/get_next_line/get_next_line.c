/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:40:06 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/17 10:35:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_tmp(char *tmp)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!tmp)
		return (0);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (0);
	}
	rtn = malloc(sizeof(char) * ((ft_strlen(tmp) - i) + 1));
	if (!(rtn))
		return (0);
	i++;
	while (tmp[i])
		rtn[j++] = tmp[i++];
	rtn[j] = '\0';
	free(tmp);
	return (rtn);
}

char	*ft_get_line(char *tmp, t_global *g, char *limit)
{
	int		i;
	char	*line;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = '\0';
	if (ft_check_expand_need(limit))
	{
		line = heredoc_expand(line, g);
	}
	return (line);
}

int	get_next_line(int fd, char **line, char *limit, t_global *g)
{
	char			*buf;
	static char		*tmp;
	int				ret;

	ret = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	write(1, " > ", 3);
	while (ret != 0 && !ft_return(tmp))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (-1);
		}
		buf[ret] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	free(buf);
	*line = ft_get_line(tmp, g, limit);
	tmp = ft_get_tmp(tmp);
	if (ret == 0)
		return (0);
	return (1);
}
