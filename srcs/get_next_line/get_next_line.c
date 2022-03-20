/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:40:06 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/20 12:10:26 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_tmp(char *tmp)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!tmp)
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
		return (free(tmp), NULL);
	rtn = malloc(sizeof(char) * ((ft_strlen(tmp) - i) + 1));
	if (!(rtn))
		return (free(tmp), NULL);
	i++;
	while (tmp[i])
		rtn[j++] = tmp[i++];
	rtn[j] = '\0';
	return (free(tmp), rtn);
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
	ft_check_expand_need(limit, line, g);
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
			return (free(buf), -1);
		buf[ret] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	free(buf);
	*line = ft_get_line(tmp, g, limit);
	tmp = ft_get_tmp(tmp);
	if (ret == 0)
		return (0);
	if (!ft_strncmp(*line, limit, ft_strlen(limit)))
		free(tmp);
	return (1);
}
