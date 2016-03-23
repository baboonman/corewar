#include "check_ext.h"

int		is_cor(char *filename)
{
	char	*ext;

	if (!(ext = ft_strrchr(filename, '.')))
		return (FALSE);
	return (!ft_strcmp(ext, ".cor"));
}

int		check_ext(t_param *param)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (param->file_players[i]
				&& !is_cor(param->file_players[i]))
		{
			ft_printf("Champ file must be .cor\n");
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}
