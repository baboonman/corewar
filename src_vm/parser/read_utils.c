#include "read_utils.h"

int			read_part_file(int fd, size_t size, void *dst)
{
	int		ret;

	while ((ret = read(fd, dst, size)) > 0)
	{
		size -= ret;
	}
	if (!size)
		return (TRUE);
	return (FALSE);
}
