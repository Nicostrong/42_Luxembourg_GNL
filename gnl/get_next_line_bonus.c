/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:43:54 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/06/17 11:27:37 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 * <cat>str</cat>
 *
 * <summary>
 *	size_t	ft_find_newline(char *str)
 * </summary>
 *
 * <description>
 *	ft_find_newline shearch the first occurence of '\n' on the string str.
 * </description>
 *
 * <param type="char *" name="str">string to parse</param>
 *
 * <return>
 *	the index position more one of '\n' in str.
 *  or
 *  len of str if '\n' not in str.
 * </return>
 *
 */

static size_t	ft_find_newline(char *str)
{
	char	*ptr;
	size_t	index;

	ptr = str;
	index = 0;
	while (ptr[index] != 0 && ptr[index] != '\n')
		index++;
	if (ptr[index] == '\n')
		index++;
	return (index);
}

/*
 * ft_substr retourne la string apres le '\n'
 */

static char	*ft_substr(char *str)
{
	char	*substr;
	size_t	i_start;
	size_t	i_new;

	i_new = 0;
	if (*str == 0)
		return (free(str), NULL);
	i_start = ft_find_newline(str);
	substr = (char *)malloc((ft_strlen(str) - i_start + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (*(str + i_start))
		*(substr + i_new++) = *(str + i_start++);
	*(substr + i_new) = 0;
	if (!substr)
		return (free(substr), free(str), NULL);
	free(str);
	return (substr);
}

/*
 * <cat>memory</cat>
 *
 * <summary>
 *	char	*ft_free(char *s1, char *s2)
 * </summary>
 *
 * <description>
 *	ft_free free the pointer s1 and s2 and return the value NULL
 * </description>
 *
 * <param type="char *" name="s1">pointer 1</param>
 * <param type="char *" name="s2">pointer 2</param>
 *
 * <return>
 *	NULL
 * </return>
 *
 */

static char	*ft_free(char *s1, char *s2)
{
	return (free(s1), free(s2), NULL);
}

/*
 * <cat>str</cat>
 *
 * <summary>
 *	char	*ft_get_line(char *str)
 * </summary>
 *
 * <description>
 *	ft_get_line create a new line from the string buff, from the start to the
 *	first '\n' char.
 * </description>
 *
 * <param type="char *" name="str">string multiline</param>
 *
 * <return>
 *	a pointer containing just the first line.
 * </return>
 *
 */

static char	*ft_get_line(char *str)
{
	size_t	index;
	char	*line;

	if (!str || *str == 0)
		return (NULL);
	index = ft_find_newline(str);
	line = (char *)malloc((index + 1) * sizeof(char));
	if (!line)
		return (NULL);
	index = 0;
	while (*(str + index) && *(str + index) != '\n')
	{
		*(line + index) = *(str + index);
		index++;
	}
	if (*(str + index) == '\n')
	{
		*(line + index) = '\n';
		index++;
	}
	*(line + index) = 0;
	return (line);
}

/*
 * <cat>print</cat>
 *
 * <summary>
 * 	char	*get_next_line(int fd)
 * </summary>
 *
 * <description>
 * 	get_next_line Return a pointer to a string read in a file descriptor.
 * </description>
 *
 * <param type="int" name="fd">file descriptor</param>
 *
 * <return>
 * 	a pointer to a ligne reading on the file descriptor.
 * 	or
 * 	NULL if EOF or ERROR.
 * </return>
 *
 */

char	*get_next_line(int fd)
{
	int			byte_read;
	char		*line;
	static char	*buff[MAX_FD];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147183647)
		return (NULL);
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	byte_read = 1;
	while (!(ft_strchr(buff[fd], '\n')) && byte_read > 0)
	{
		byte_read = read(fd, line, BUFFER_SIZE);
		if (byte_read <= 0 && buff[fd] == NULL)
		{
			*(buff + fd) = ft_free(*(buff + fd), line);
			return (NULL);
		}
		*(line + byte_read) = 0;
		buff[fd] = ft_strjoin(*(buff + fd), line);
	}
	free(line);
	line = ft_get_line(buff[fd]);
	buff[fd] = ft_substr(buff[fd]);
	return (line);
}