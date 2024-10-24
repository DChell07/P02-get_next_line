/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:21:09 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/24 17:00:51 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clean_line(char *box)
{
	int		i;
	char	*new;

	i = 0;
	while (box[i] != '\n' && box[i] != '\0')
	{
		i++;
	}
	new = ft_substr(box, 0, i + 1);
	return (new);
}

static char	*read_file(int fd, char *buf, char *box, char *temp)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(box);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (box == NULL)
			box = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(box, buf);
			free(box);
			box = temp;
		}
		if (ft_strchr(box, '\n') != NULL)
			return (box);
	}
	return (box);
}

static char	*rest_of_line(char *box, char *temp)
{
	if (ft_strchr(box, '\n') != NULL)
	{
		temp = ft_strdup(ft_strchr(box, '\n') + 1);
		free(box);
		box = temp;
	}
	else
	{
		free(box);
		box = NULL;
	}
	return (box);
}

char	*get_next_line(int fd)
{
	static char	*box[1024];
	char		*new;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];

	new = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(box[fd]);
		box[fd] = NULL;
		return (NULL);
	}
	box[fd] = read_file(fd, buf, box[fd], temp);
	if (box[fd] != NULL)
	{
		new = clean_line(box[fd]);
		box[fd] = rest_of_line(box[fd], temp);
		if (new[0] == '\0' || new == NULL)
		{
			free (new);
			return (NULL);
		}
	}
	return (new);
}
