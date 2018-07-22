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

void	convert_map(t_win *win, t_list *lst)
{
	t_list	*cur;
	char	*str;
	size_t	i;
	int		y;
	int		x;

	if (!win || !(cur = lst) || !(y = -1))
		return ;
	if ((win->map = (t_px **)malloc(sizeof(t_px *) * win->map_rows)))
	{
		while (cur && cur->content && (str = (char *)cur->content))
		{
			x = -1;
			i = -1;
			win->map[++y] = (t_px *)malloc(sizeof(t_px) * win->map_cols);
			while (++i < cur->content_size)
			{
				win->map[y][++x].y = y;
				win->map[y][x].x = x;
				win->map[y][x].z = i_atoi(str, &i, cur->content_size);
				win->map[y][x].col = parse_color(str + i, &i, cur->content_size); 
				//printf("prsPX: y = %f, x = %f, z = %f, col=%d\n", win->map[y][x].y, win->map[y][x].x, win->map[y][x].z, win->map[y][x].color);
			}
			cur = cur->next;
		}
	}
}

void	set_map_size(t_win *win, t_list *lst)
{
	t_list	*cur;

	if (!(cur = lst))
		return ;
	while (cur)
	{
		if (win->map_cols == 0)
			win->map_cols = cnt_words((char *)cur->content, cur->content_size, ' ');
		else
			if (win->map_cols != cnt_words((char *)cur->content, cur->content_size, ' '))
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
		&& (lst_append(&lst, buf, ft_strlen(buf))) && (++win->map_rows))
		free(buf);
	set_map_size(win, lst);
	//printf("rows=%zu\n",win->map_rows);
	//printf("cols=%zu\n",win->map_cols);
	convert_map(win, lst);
	destroy_lst(lst);
	close(fd);
	return (win);
}