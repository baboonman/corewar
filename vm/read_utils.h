#ifndef READ_UTILS_H
# define READ_UTILS_H

# include <unistd.h>
# include "corewar_define.h"

int			read_part_file(int fd, size_t size, void *dst);

#endif
