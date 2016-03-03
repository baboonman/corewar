#include "mem_utils.h"

int			read_n_bytes(int size, void *mem, size_t off)
{
	int			val;
	char		*data;
	int			p_size;

	data = (char *)(&val);
	off = off % MEM_SIZE;
	p_size = size;
	while (size)
	{
		size--;
		data[size] = *((char *)(mem + off));
		off = (off + 1) % MEM_SIZE;
	}
	return (val);
}

void		write_n_bytes(int size, void *mem, size_t off, int val)
{
	char		*data;
	int			i;

	data = (char *)(&val);
	off = off % MEM_SIZE;
	i = 0;
	while (i < size)
	{
		*((char *)(mem + off)) = data[3 - i];
		off = (off + 1) % MEM_SIZE;
		i++;
	}
}
