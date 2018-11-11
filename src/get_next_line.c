/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:59:40 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/11 20:14:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	line_len(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str != '\n' && *str != '\0' && ++str)
		len++;
	return (len);
}

static int	data_mod(t_list **lst, size_t fd, char *buf, size_t size)
{
	t_list	*cur;
	char	*tmp;

	if (!lst || (cur = *lst) < 0 || !buf || size < 1)
		return (0);
	while (cur)
	{
		if (cur->content_size == fd && cur->content)
		{
			if ((tmp = cur->content) && (cur->content = ft_strjoin(tmp, buf)))
				free(tmp);
			else
				cur->content = ft_strdup(buf);
			return (1);
		}
		cur = cur->next;
	}
	if (!(*lst))
		*lst = ft_lstnew(buf, size);
	else
		ft_lstadd(lst, ft_lstnew(buf, size));
	(*lst)->content_size = fd;
	return (1);
}

static int	get_line(t_list *lst, char **line, size_t fd)
{
	t_list	*cur;
	size_t	len;

	cur = lst;
	while (cur)
	{
		if (cur->content_size == fd && cur->content
		&& (len = line_len(cur->content)))
		{
			if ((*line = ft_strnew(len)))
				ft_strncpy(*line, cur->content, len);
			if (!ft_strchr(cur->content, '\n'))
				ft_memdel(&cur->content);
			else
				ft_strcpy(cur->content, cur->content + len + 1);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	t_list			*cur;
	ssize_t			len;
	char			buf[BUFF_SIZE];

	if (fd < 0 || BUFF_SIZE < 1 || fd > MAX_FD)
		return (-1);
	cur = lst;
	while (cur)
	{
		if ((int)cur->content_size == fd && cur->content
		&& ft_strchr(cur->content, '\n'))
		{
			get_line(lst, line, (size_t)fd);
			return (1);
		}
		cur = cur->next;
	}
	while ((len = read(fd, buf, BUFF_SIZE)) > 0
	&& data_mod(&lst, (size_t)fd, buf, (size_t)len) )
	{
		buf[len] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			ft_bzero(buf, BUFF_SIZE);
			break ;
		}
	}
	if (len == -1)
		return (-1);
	return (get_line(lst, line, (size_t)fd));
}
