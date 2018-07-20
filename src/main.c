/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/18 19:48:41 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	if (result > 9223372036854775807U && sign == 1)
		return (-1);
	if (result > 9223372036854775808U && sign == -1)
		return (0);
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

void	draw_line(t_win *win, t_line *line, double y, double x)
{
	line->dy = (line->end_y - y >= 0 ? 1 : -1);
	line->dx = (line->end_x - x >= 0 ? 1 : -1);
	line->len_y = ft_abs(line->end_y - y);
	line->len_x = ft_abs(line->end_x - x);
	line->len = ft_max(line->len_y, line->len_x);
	if (line->len++ == 0)
		draw_px_by_coord(win, y, x);
	line->d = ((line->len_y <= line->len_x) ? -line->len_x : -line->len_y);		
	while (line->len--)
	{
		draw_px_by_coord(win, x, y);
		line->d += 2 * ((line->len_y <= line->len_x) ? line->len_y : line->len_x);
		if (line->len_y <= line->len_x)
			x += line->dx;			
		else
			y += line->dy;
		if (line->d > 0)
		{
			line->d -= 2 * ((line->len_y <= line->len_x) ? line->len_x : line->len_y);
			if (line->len_y <= line->len_x)
				y += line->dy;
			else
				x += line->dx;
		}
	}
}

void 	print_map(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));

	line->end_y = 500;
	line->end_x = 500;
	draw_line(win, line, 100, 100);

	line->end_y = 600;
	line->end_x = 150;
	draw_line(win, line, 100, 500);

	y = 0;
	while (y < win->map_rows)
	{
		x = 0;
		while (x < win->map_cols)
			draw_px_by_map(win, y, x++);
		y++;
	}
}

void	draw_line_map()
{
	
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
