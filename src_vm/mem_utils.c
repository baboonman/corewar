#include "mem_utils.h"

static int16_t		read_2_bytes(void *mem, size_t off)
{
	int16_t		val;
	char		*data;
	int			size;

	size = 2;
	data = (char *)(&val);
	while (size)
	{
		size--;
		data[size] = *((char *)(mem + off));
		off = (off + 1) % MEM_SIZE;
	}
	return (val);
}

static int32_t		read_4_bytes(void *mem, size_t off)
{
	int32_t		val;
	char		*data;
	int			size;

	size = 4;
	data = (char *)(&val);
	while (size)
	{
		size--;
		data[size] = *((char *)(mem + off));
		off = (off + 1) % MEM_SIZE;
	}
	return (val);
}

int			read_n_bytes(int size, void *mem, size_t off)
{
	int			val;

	val = 0;
	off = off % MEM_SIZE;
	if (size == 1)
		return (*((int8_t*)(mem + off)));
	if (size == 2)
		val = read_2_bytes(mem, off);
	else if (size == 4)
		val = read_4_bytes(mem, off);
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
