/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/11/11 19:48:42 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	convert_map(t_win *win, t_list *lst)
{
	t_list	*cur;
	char	*str;
	size_t	i;
	int		y;
	int		x;

	if (!win || !(cur = lst))
		return (1);
	y = -1;
	if ((win->map = (t_px **)malloc(sizeof(t_px *) * win->param->rows)))
		while (cur && (str = (char *)cur->content))
		{
			if ((x = -1) &&
			!(win->map[++y] = (t_px *)malloc(sizeof(t_px) * win->param->cols)))
				return (1);
			i = -1;
			while (++i < cur->content_size)
			{
				set_vec(win, ++x, y, ft_i_atoi(str, &i, cur->content_size));
				win->map[y][x].color = get_col(win, str + i, &i,
						cur->content_size);
			}
			cur = cur->next;
		}
	return (0);
}

static int	is_valid_row(t_win *win, void *cont, size_t max_i)
{
	size_t	i;
	char	*str;

	if (!win || !(str = (char *)cont))
		return (0);
	i = -1;
	while (str && i < max_i)
		if ((!(str[++i] >= '0' && str[i] <= '9')
		|| !(str[i] == ' ')
		|| !(str[i] >= 'A' && str[i] <= 'F')))
			win->flags->error_code = MAP_INVALID;
	if (win->flags->error_code)
		return (0);
	return (1);
}

static int	get_map_param(t_win *win, t_list *lst)
{
	t_list *cur;
	size_t width;

	if (!(cur = lst) || !win)
		return (1);
	while (cur)
	{
		if (!is_valid_row(win, cur->content, cur->content_size))
			break ;
		width = ft_cnt_words((char *)cur->content, cur->content_size, ' ');
		if (win->param->cols == 0)
			win->param->cols = width;
		else if (win->param->cols != width && !WIDTH_ERR_SKIP)
			win->flags->error_code = WIDTH_ERR;
		cur = cur->next;
	}
	if (win->param->cols == 0 && !WIDTH_ERR_SKIP)
	{
		win->flags->error_code = WIDTH_ERR;
		return (1);
	}
	win->param->centr_y = win->param->rows / 2;
	win->param->centr_x = win->param->cols / 2;
	return (0);
}
//
//
//static int		print_map(t_win *win, size_t **map_val)
//{
//	int	y;
//	int	x;
//
//	if (!win)
//		return (1);
//	y = 0;
//	while (y < win->param->height)
//	{
//		x = 0;
//		while (x < win->param->width)
//		{
//			ft_putnbr(map_val[y][x]);
//			ft_putchar(' ');
//			x++;
//		}
//		ft_putchar('\n');
//		y++;
//	}
//	return (0);
//}
//
//t_list	**ft_lstappend2(t_list **lst, void *data, size_t data_size)
//{
//	t_list *cur;
//
//	if (!lst)
//		return (NULL);
//	if (!(*lst))
//		*lst =
//				ft_lstnew(data, data_size);
//	else
//	{
//		cur = *lst;
//		while (cur->next)
//			cur = cur->next;
//		cur->next =
//				ft_lstnew(data, data_size);
//	}
//	return (lst);
//}

#include <stdio.h>
t_win		*parse_map(char *file_name, t_win *win)
{
	int		fd;
	t_list	*lst;
	char	*buf;

	if (!win || !file_name)
		return (NULL);
	lst = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1 || errno == ITS_A_DIRECTORY)
	{
		win->flags->error_code = READ_ERR;
		return (NULL);
	}
	while (get_next_line(fd, &buf) > 0
	&& (ft_lstappend(&lst, buf, ft_strlen(buf)))
	&& (++win->param->rows))
		ft_memdel((void *)&buf);
	close(fd);

//	t_list *cur;
//	int i;
//
//	i = 0;
//	cur = lst;
//	while (cur)
//	{
//		printf("\n%d\n", i++);
//		if (cur->content)
//			printf("%s", (char *)cur->content);
//		cur = cur->next;
//	}


	if (lst == NULL && !(errno) && !WIDTH_ERR_SKIP)
		win->flags->error_code = WIDTH_ERR;
	if (get_map_param(win, lst) || win->flags->error_code
	|| convert_map(win, lst) || ft_destroy_lst(lst))
		return (NULL);
	return (win);
}
