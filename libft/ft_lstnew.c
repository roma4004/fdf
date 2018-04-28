/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:07:21 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/29 19:42:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_list;

	new_list = NULL;
	if ((new_list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		new_list->content = NULL;
		new_list->content_size = 0;
	}
	else
	{
		if ((new_list->content = malloc(content_size)))
		{
			ft_memcpy(new_list->content, content, content_size);
			new_list->content_size = content_size;
		}
		else
		{
			free(new_list);
			return (NULL);
		}
	}
	new_list->next = NULL;
	return (new_list);
}
