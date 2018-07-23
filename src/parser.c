/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/17 15:22:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		convert_map(t_win *win, t_list *lst)
{
	t_list	*cur;
	char	*str;
	size_t	i;
	int		y;
	int		x;

	if (!win || !(cur = lst) || !(y = -1))
		return (0);
	if ((win->map = (t_px **)malloc(sizeof(t_px *) * win->map_rows)))
		while (cur && cur->content && (str = (char *)cur->content))
		{
			if (!(win->map[++y] = (t_px *)malloc(sizeof(t_px) * win->map_cols))
				|| !(x = - 1) || !(i = - 1))
			{
				free_map(win);
				return (0);
			}
			while (++i < cur->content_size)
			{
				set_map_vec(win, y, ++x, ft_i_atoi(str, &i, cur->content_size));
				win->map[y][x].color = get_col(str + i, &i, cur->content_size);
			}
			cur = cur->next;
		}
	return (1);
}

void	set_map_size(t_win *win, t_list *lst)
{
	t_list	*cur;

	if (!(cur = lst))
		return ;
	while (cur)
	{
		if (win->map_cols == 0)
			win->map_cols = ft_cnt_words((char *)cur->content, cur->content_size, ' ');
		else
			if (win->map_cols != ft_cnt_words((char *)cur->content, cur->content_size, ' '))
			   return ; //win->err_status = 1; set status map invalitd	
		cur = cur->next;
	}
}

t_win	*parse_map(char *file_name, t_win *win)
{
	int		fd;
	t_list	*lst;
	char	*buf;

	win->map_cols = 0;
	win->map_rows = 0;
	lst = NULL;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &buf) 
		&& (ft_lst_append(&lst, buf, ft_strlen(buf))) && (++win->map_rows))
		free(buf);
	set_map_size(win, lst);
	if (convert_map(win, lst))
	{	//set error status
		return (NULL);
	}
	ft_destroy_lst(lst);
	close(fd);
	return (win);
}