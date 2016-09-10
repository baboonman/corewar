#ifndef INS_TOOLS_H
# define INS_TOOLS_H

# include "corewar_struct.h"
# include "process_struct.h"
# include <libft.h>
# include "struct_op.h"

void	add_ins_line(t_ncurses *ncurses, char *line);
char	*get_proc_player_str(t_process *proc);
char	*get_reg_str(t_process *proc, int reg);
char	*get_itoa_space(int val);
char	*get_param_str(t_process *proc);

#endif
