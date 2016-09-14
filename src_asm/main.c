/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "lexer.h"
#include "parser.h"
#include "free_files.h"

int			main(int argc, char **argv)
{
	int		ret;
	t_file	*file;

	if (argc < 2)
	{
		if (argc > 0)
			ft_printf("%s <sourcefile.s>\n", argv[0]);
		return (1);
	}
	if (!(file = read_file(argv[argc - 1])))
		return (1);
	if (!(parse_file(file)))
	{
		ft_printf("Error in file\n");
		return (1);
	}
	ret = process_file(file);
	free_files(file);
	return (!ret);
}
