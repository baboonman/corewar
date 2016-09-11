#include "input.h"
#include "display_utils.h"

void			init_input(t_input *param)
{
	param->tps = 50;
	param->pause = -1;
}

void			get_input(t_input *param)
{
	int			c;

	c = getch();
	if (c == 67)
	{
		if (param->tps < 1000)
			param->tps += 50;
	}
	else if (c == 68)
	{
		if (param->tps > 50)
			param->tps -= 50;
	}
	else if (c == 65)
		param->tps = 1001;
	else if (c == 66)
		param->tps = 1;
	else if (c == 32)
		param->pause *= -1;
}
