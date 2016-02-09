#include "parser.h"

int				process_section(char *bin_file, t_list* list_sections)
{
	t_header	*header;

	header = (t_header*)malloc(sizeof(t_header));
	if (!header)
		return (ret_error("malloc failed"));

	header->magic = swap_uint32(COREWAR_EXEC_MAGIC);
	header->
	while (list_section)
	{

	}

}

int				process_file(t_file* file)
{
	int			fd;
	int			size;
	char		*bin_file;

	bin_file = (char*)malloc(CHAMP_MAX_SIZE + sizeof(t_header) + 1);
	if (!bin_file)
		return (ret_error("malloc failed"));
	
	process_section(bin_file, file->list_sections);

	if ((fd = open("test.cor", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		return (ret_error("Unable to open file"));
	write(fd, "nothin' yet.. come back later\n", 30);
	if ((close(fd)) < 0)
		return (ret_error("Unable to close file"));
	return (TRUE);
}
