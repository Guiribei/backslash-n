/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:34:20 by guribeir          #+#    #+#             */
/*   Updated: 2022/05/11 23:46:32 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char *keep, char *buf)
{
	char	*aux;

	aux = ft_strjoin(keep, buf);
	free(keep);
	return (aux);
}

static char	*ft_pull_keep(char *keep)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	str = malloc((ft_strlen(keep) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (keep[i])
		str[j++] = keep[i++];
	str[j] = '\0';
	free(keep);
	return (str);
}

static char	*ft_get_str(char *keep)
{
	char	*str;
	int		i;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] && keep[i] != '\n')
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		str[i] = keep[i];
		i++;
	}
	if (keep[i] && keep[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_read_line(int fd, char *keep)
{
	char	*buf;
	int		count;

	if (!keep)
	{
		keep = malloc(1);
		keep[0] = '\0';
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	count = 1;
	while (!ft_strchr(keep, '\n') && count != 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[count] = '\0';
		keep = ft_free(keep, buf);
	}
	free(buf);
	return (keep);
}

char	*get_next_line(int fd)
{
	static char	*keep[1024];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	keep[fd] = ft_read_line(fd, keep[fd]);
	if (!keep[fd])
		return (NULL);
	str = ft_get_str(keep[fd]);
	keep[fd] = ft_pull_keep(keep[fd]);
	return (str);
}
