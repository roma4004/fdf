/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/16 21:37:04 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include "main.h"

int		exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

int		is_hex(char ch)
{
	if (ch == 'A' || ch == 'a'
	|| ch == 'B' || ch == 'b'
	|| ch == 'C' || ch == 'c'
	|| ch == 'D' || ch == 'd'
	|| ch == 'E' || ch == 'e'
	|| ch == 'F' || ch == 'f'
	|| (ch >= '0' && ch <= '9'))
		return (1);
	return (0);
}

int		ch2int(char ch)
{
	if (ch == 'A' || ch == 'a')
		return (10);
	else if (ch == 'B' || ch == 'b')
		return (11);
	else if (ch == 'C' || ch == 'c')
		return (12);
	else if (ch == 'D' || ch == 'd')
		return (13);
	else if (ch == 'E' || ch == 'e')
		return (14);
	else if (ch == 'F' || ch == 'f')
		return (15);
	return (ch - '0');
}

int		parse_color_to(char *hex, size_t *i, size_t max_i)
{
	int		res;

	res = 0;
	if (*i >= max_i || !hex || hex[0] != ',' || hex[1] != '0' || hex[2] != 'x' 
	|| !is_hex(hex[3]) || !is_hex(hex[4])
	|| !is_hex(hex[5]) || !is_hex(hex[6])
	|| !is_hex(hex[7]) || !is_hex(hex[8]))
		return (DEF_COLOR);
  //printf("col=%c%c%c%c%c%c%c%c", hex[1], hex[2], hex[3], hex[4], hex[5], hex[5], hex[6], hex[7]);
	res = ch2int(hex[3]) * 1048576
		+ ch2int(hex[4]) * 65536
		+ ch2int(hex[5]) * 4096
		+ ch2int(hex[6]) * 256
		+ ch2int(hex[7]) * 16
		+ ch2int(hex[8]) * 1;
	*i = *i + 9;
	return (res);
}

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			ft_memdel((void *)&arr[i++]);
		ft_memdel((void*)&arr);
	}
}

void	destroy_lst(t_list *lst)
{
	t_list	*cur;
	t_list	*tmp;

	if (!(cur = lst))
		return ;
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		cur = tmp;
	}
}

int		lst_append(t_list **lst, char *buf, int size)
{
	t_list *cur;

	if (*lst == NULL)
		*lst = ft_lstnew(buf, size);
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_lstnew(buf, size);
	}
	return (1);
}

int		ft_len_of_num(const char *s, size_t i, size_t max_i)
{
	int		len;

	len = 0;
	while (s[i] && i < max_i)
		if (s[i] >= '0' && s[i++] <= '9')
			len++;
	return (len);
}

long long	i_atoi(const char *str, size_t *i, size_t max_i)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while ((str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\r' ||
			str[*i] == ' ' || str[*i] == '\v' || str[*i] == '\f') && *i < max_i)
		*i = *i + 1;
	if (str[*i] == '-')
		sign = -1;
	if (str[*i] == '-' || str[*i] == '+')
		*i = *i + 1;
	while (str[*i] >= '0' && str[*i] <= '9' && *i < max_i)
		result = result * 10 + (int)str[(*i)++] - '0';
	//if ((result > 9223372036854775807 && sign == 1)
	//	|| (ft_len_of_num(str, *i, max_i) >= 19 && sign == 1))
	//	return (-1);
	//if (result > 9223372036854775807 && sign == -1)
	//	return (0);
	return (result * sign);
}

size_t	cnt_words(char *str, size_t max_i, char ch)
{
	size_t	i;
	size_t	num;

	if (str == NULL)
		return (0);
	i = -1;
	num = 0;
	while (++i < max_i && str[i])
		if (str[i] == ch && str[i + 1] != ch)
			num++;
	if (str[0] != '\0')
		num++;
	return (num);
}

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
				win->map[y][x].color = parse_color_to(str + i, &i, cur->content_size); 
				//printf("prsPX: y = %f, x = %f, z = %f, col=%d\n", win->map[y][x].y, win->map[y][x].x, win->map[y][x].z, win->map[y][x].color);
			}
			cur = cur->next;
		}
	}
}

void	print_content_lst(t_list *lst)
{
	size_t	i;
	char	*s;
	t_list	*cur;

	if (!(cur = lst))
		return ;
	while (cur)
	{
		i = 0;
		s = (char *)cur->content;
		while (i < cur->content_size)
			printf("%c", s[i++]);
		printf("\n");
		cur = cur->next;
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
	close(fd);
	return (win);
}

double	ft_abs(double num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

double	ft_max(double first, double second)
{
	if (first > second)
		return (first);
	return (second);
}

void	draw_px_by_coord(t_win *win, double y, double x)
{
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, DEF_COLOR);
}

void	draw_px_by_map(t_win *win, size_t y, size_t x)
{
	mlx_pixel_put(win->mlx_ptr, win->win_ptr,
		   	150 + win->map[y][x].x * (win->scale_x),
		   	400 + win->map[y][x].y * (win->scale_y) 
			    -(win->map[y][x].z * win->scale_z),
				  win->map[y][x].color);
}

void	draw_line(t_win *win, t_line *line)
{
	double	y;
	double	x;

	line->len_y = ft_abs(line->end_y - line->start_y);
	line->len_x = ft_abs(line->end_x - line->start_y);
	line->len   = ft_max(line->len_y,  line->len_x);

	if (line->len == 0)
		draw_px_by_coord(win, line->start_y, line->start_x);

	if (line->len_y <= line->len_x)
	{
		y = line->start_y;
		x = line->start_x;
		line->step = line->len_y / line->len_x;
		line->len++;
		while (line->len--)
		{
			draw_px_by_coord(win, x, y);
			x++;
			y += line->step;
		}
	}
	else
	{
		y = line->start_y;
		x = line->start_x;
		line->step = line->len_x / line->len_y;
		line->len++;
		while (line->len--)
		{
			draw_px_by_coord(win, x, y);
			x += line->step;
			y++;
		}
	}
//----------------------
}

void 	print_map(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	line->start_y = 100;
	line->start_x = 100;
	line->end_y = 500;
	line->end_y = 500;
	draw_line(win, line);
	y = 0;
	while (y < win->map_rows)
	{
		x = 0;
		while (x < win->map_cols)
			draw_px_by_map(win, y, x++);
		y++;
	}
}

int		main(int argc, char **argv)
{
	t_win	*win;

	if (argc == 2) //add parsing multi map
	{
		if((win = (t_win *)malloc(sizeof(t_win))))
		{
			win->width = WIN_WIDTH;
			win->height = WIN_HEIGHT;
			win->offset_x = WIN_OFFSET;
			win->offset_y = WIN_OFFSET;
			win->scale_x = WIN_SCALE;
			win->scale_y = WIN_SCALE;
			win->scale_z = WIN_SCALE;
			win->mlx_ptr = mlx_init();
			win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->height, WIN_NAME);
			print_map(parse_map(argv[1], win));
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, 5, 5, 0x009100FF);
			mlx_string_put(win->mlx_ptr, win->win_ptr, 5, 5, 0x009100FF, "str");
 	 //int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
			mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
			mlx_loop(win->mlx_ptr);
		}
	}
	//system("leaks ./fdf");
	return (0);
}
