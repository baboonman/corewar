#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <unistd.h>

# include <ft_printf.h>
# include "lexer.h"
# include "struct.h"
# include "op.h"
# include "swap_bytes.h"
# include "safe_malloc.h"
# include "check_param_type.h"

typedef struct			s_label_param
{
	size_t				offset;
	size_t				size;
	size_t				pc;
	char				*name;
}						t_label_param;

typedef struct			s_label_offset
{
	char				*name;
	size_t				offset;
}						t_label_offset;

typedef struct			s_bin_data
{
	char				*bin_file;
	t_header			*header;
	int					size;
	t_label_param		**pl;
	size_t				pl_size;
	t_label_offset		**lo;
	size_t				lo_size;
}						t_bin_data;

int						process_file(t_file *file);

/*
** parser_utils.c
*/
int64_t					ft_pow(int64_t x, int n);
int						check_overflow(int64_t v, int nb_bytes, int cur_line,
									void **error);
size_t					ft_memcat(void *dest, void *src, size_t i, size_t n);

/*
** parser_token.c
*/
int						process_token(t_bin_data *data, t_list *op_tokens);

/*
** parser_label.c
*/
int						add_label(t_bin_data *data, t_token_op *token);
int						process_label(t_bin_data *data);
int						add_label_param(t_bin_data *data, int off, int size,
									char *label_name);

#endif
