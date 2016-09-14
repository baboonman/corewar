/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <vwatrelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 15:30:57 by vwatrelo          #+#    #+#             */
/*   Updated: 2014/02/13 15:30:58 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static int	helper(t_list **cur, t_list **list, t_list *elem)
{
	*cur = *list;
	if (*cur == elem)
	{
		*list = (*cur)->next;
		free(*cur);
		*cur = NULL;
		return (0);
	}
	return (1);
}

void		ft_lstdelone(t_list **list, t_list *elem)
{
	t_list	*last;
	t_list	*cur;

	if (elem == NULL)
		return ;
	if (helper(&cur, list, elem))
	{
		last = cur;
		cur = cur->next;
	}
	while (cur != NULL)
	{
		if (cur == elem)
		{
			last->next = cur->next;
			free(cur);
			return ;
		}
		last = cur;
		cur = cur->next;
	}
}
