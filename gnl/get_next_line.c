/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:59:10 by mquero            #+#    #+#             */
/*   Updated: 2025/02/22 16:10:06 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_when_nl(char *temp, t_myitems *mystruct, int hold)
{
	if (mystruct->i == 0)
		temp = ft_strjoin_free(temp, mystruct->buffer, mystruct->j + 1);
	else
		temp = ft_strjoin_free(temp, mystruct->buffer + hold, mystruct->j - hold
				+ 1);
	mystruct->j = mystruct->j + 1;
	mystruct->i = 1;
	return (temp);
}

char	*check_when_no_nl(char *temp, t_myitems *mystruct, int hold)
{
	if (mystruct->i == 1)
	{
		temp = ft_strjoin_free(temp, mystruct->buffer + hold, mystruct->j - hold);
		mystruct->i = 0;
	}
	else
	{
		temp = ft_strjoin_free(temp, mystruct->buffer, mystruct->j);
		mystruct->i = 0;
	}
	return (temp);
}

char	*read_line(int fd, char *temp, t_myitems *mystruct)
{
	int	hold;

	hold = mystruct->j;
	while (mystruct->k > 0)
	{
		if (mystruct->j == mystruct->k && mystruct->i == 0)
		{
			mystruct->j = 0;
			mystruct->k = read(fd, mystruct->buffer, BUFFER_SIZE);
			if (hold > 0 && mystruct->k == 0 && mystruct->i != 1
				&& temp[0] != '\0')
				return (temp);
		}
		while (mystruct->j < mystruct->k)
		{
			if (mystruct->buffer[mystruct->j] == '\n')
				return (check_when_nl(temp, mystruct, hold));
			mystruct->j++;
		}
		if (mystruct->j == mystruct->k && mystruct->k > 0)
			temp = check_when_no_nl(temp, mystruct, hold);
	}
	free(temp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char				*temp;
	char				*line;
	static t_myitems	mystruct = {0, 1, 1, ""};

	if (mystruct.k == 0)
	{
		mystruct.k = 1;
		mystruct.j = 1;
		mystruct.i = 0;
	}
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (temp == NULL)
		return (NULL);
	line = read_line(fd, temp, &mystruct);
	if (line != NULL)
		return (line);
	return (NULL);
}
