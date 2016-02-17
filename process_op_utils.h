#ifndef PROCESS_OP_UTILS_H
# define PROCESS_OP_UTILS_H

# include <libft.h>
# include "define_error.h"
# include "op.h"
# include "struct.h"

char		*remove_space(char *str);
int			get_reg(char *str);
int			get_label(char *str, char **label);
int64_t		get_dir(char *str, int *match, char **label);
int64_t		get_ind(char *str, int *match, char **label);

#endif
