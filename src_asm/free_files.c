/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:48:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_files.h"

static void	free_section_list(t_list *token)
{
	t_token_section	*section;
	t_list			*tmp;

	while (token)
	{
		section = token->content;
		tmp = token->next;
		free(section->value);
		free(section);
		free(token);
		token = tmp;
	}
}

static void	free_op_list(t_list *token)
{
	t_token_op		*op;
	t_list			*tmp;
	int				i;

	while (token)
	{
		op = token->content;
		tmp = token->next;
		if (op->label)
			free(op->label);
		i = 0;
		while (i < 3)
		{
			if (op->param_lab[i])
				free(op->param_lab[i]);
			i++;
		}
		free(op);
		free(token);
		token = tmp;
	}
}

void		free_files(t_file *file)
{
	while (file->nb_lines + 1 > 0)
		free(file->lines[file->nb_lines--]);
	free(file->lines);
	free_section_list(file->list_sections);
	free_op_list(file->list_op);
	if (file->file_name)
		free(file->file_name);
	if (file->cor_name)
		free(file->cor_name);
	free(file);
}
