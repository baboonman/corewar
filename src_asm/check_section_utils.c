/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_section_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:48:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_section.h"

static void					*ft_realloc(void *p, size_t size)
{
	void	*tmp_p;

	tmp_p = NULL;
	tmp_p = safe_malloc(sizeof(char) * size);
	ft_bzero(tmp_p, size);
	if (p)
	{
		ft_strcpy(tmp_p, p);
		free(p);
	}
	return (tmp_p);
}

static char					*manage_end(char *res, char *tmp_line, size_t size,
		char *end)
{
	if (ft_strchr(end + 1, '"'))
	{
		free(res);
		return (NULL);
	}
	size += end - tmp_line;
	if (!(res = ft_realloc(res, sizeof(char) * (size + 1))))
		return (NULL);
	return (ft_strncat(res, tmp_line, end - tmp_line));
}

char						*get_str(size_t *line, t_file *file, char *start)
{
	char		*res;
	char		*end;
	size_t		size;
	char		*tmp_line;

	res = ft_realloc(NULL, sizeof(char));
	size = 1;
	tmp_line = NULL;
	while (*line < file->nb_lines)
	{
		if (!tmp_line)
			tmp_line = start;
		else
			tmp_line = file->lines[*line];
		if ((end = ft_strchr(tmp_line, '"')))
			return (manage_end(res, tmp_line, size, end));
		size += ft_strlen(tmp_line) + 1;
		if (!(res = ft_realloc(res, sizeof(char) * (size + 1))))
			return (NULL);
		ft_strcat(res, tmp_line);
		res[size - 2] = '\n';
		*line += 1;
	}
	free(res);
	return (NULL);
}
