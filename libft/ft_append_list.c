/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:00:41 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/19 19:36:26 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_append_list(t_list *lst, t_list *elem)
{
	t_list *curr_node;

	curr_node = lst;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	if (curr_node && curr_node->next == NULL)
		curr_node = curr_node->next;
	curr_node = (t_list *)malloc(sizeof(t_list));
	if (curr_node)
	{
		if (elem->content)
		{
			curr_node->content = elem->content;
			curr_node->content_size = elem->content_size;
		}
		else
		{
			curr_node->content = NULL;
			curr_node->content_size = 0;
		}
		curr_node->next = NULL;
	}
}
