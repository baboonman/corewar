#include "reader.h"
#include "parser.h"

static void	free_file(t_file *file)
{
	while (file->nb_lines + 1 > 0)
		free(file->lines[file->nb_lines--]);
	free(file->lines);
	free(file);
}

int main()
{
	t_file	*file;

	if (!(file = read_file("test.s")))
		return (1);
	if (!(parse_file(file)))
		return (1);
	free_file(file);
	return (0);
}
