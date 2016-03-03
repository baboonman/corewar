#include "dump_memory.h"

static void		dump_addr(uint32_t addr)
{
	char	*str;

	str = get_hexa_32(addr);
	ft_printf("0x%s :", str + 4);
	free(str);
}

void			dump_memory(t_vm *vm)
{
	char		hex[3];
	uint32_t	i;

	i = 0;
	hex[0] = ' ';
	while (i < MEM_SIZE)
	{
		if (i != 0 && !(i % 64))
			ft_printf(" \n");
		if (!(i % 64))
			dump_addr(i);
		get_hexa_8(*((uint8_t *)vm->mem_space + i), hex + 1);
		write(1, hex, 3);
		++i;
	}
	ft_printf(" \n");
}
