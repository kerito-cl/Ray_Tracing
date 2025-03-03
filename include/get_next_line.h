/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:48 by mquero            #+#    #+#             */
/*   Updated: 2025/02/22 16:10:25 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_myitems
{
	int		i;
	int		j;
	int		k;
	char	buffer[BUFFER_SIZE];
}			t_myitems;

char		*get_next_line(int fd);
char		*ft_strdup(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strjoin_free(char *s1, char const *s2, int n);

#endif
