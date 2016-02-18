#ifndef ERROR_UTIL_H
# define ERROR_UTIL_H

# include "struct.h"
# include <libft.h>
# include <ft_printf.h>
# include "utils.h"

# define COM_ERR_QUOTE	"Quote not valid"
# define COM_LENGTH "Section is too long"
# define INVALID_LINE	"Invalid line"

t_error		*get_error(char *description);
void		*print_error(void *data);
int			ret_error(char *description);
int			set_error_ret(t_error **err, char *desc, int line);

#endif
