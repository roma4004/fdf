/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/11 18:13:51 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include "main.h"

int		ln_in_file(char *file_name)
{
	int		fd;
	int		cnt;
	int		status;
	char	*str;

	fd = open(file_name, O_RDONLY);
	cnt = 0;
	str = NULL;
	while ((status = get_next_line(fd, &str)))
	{
		cnt++;
		ft_memdel((void *)&str);
	}
	close(fd);
	return (cnt);
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

void	parse_color_to(char *hex, t_win *win, int y, int x)
{
	printf("parse_col hex: %s\n", hex);
	if (!hex || !win || ft_strlen(hex) > 8 || hex[0] != '0' || hex[1] != 'x')
		return ;
	win->map[y][x].color = (ch2int(hex[2]) * 1048576
					+ ch2int(hex[3]) * 65536
					+ ch2int(hex[4]) * 4096
					+ ch2int(hex[5]) * 256
					+ ch2int(hex[6]) * 16
					+ ch2int(hex[7]) * 1);
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

int		arr_len(char **arr)
{
	int	len;

	if (arr == NULL)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	//printf("\nsizeof array:%d\n", len);
	return (len);
}

int		init_px(t_px *px)
{
	if (px == NULL)
		return (0);
	px->x = 0;
	px->y = 0;
	px->z = 0;
	px->color = DEF_COLOR;
	return (1);
}

void	convert_map(t_win *win, char ***map, int y, int x)
{
	char **temp;//need refactor this func
	
	if (win == NULL || map == NULL)
		return ;
	while (map[y])
	{
		win->map[y] = (t_px *)malloc(sizeof(t_px) * (win->map_cols + 1));
		win->map[win->map_cols] = NULL;
		x = 0;
		while (map[y][x])
		{//parse_px(win, map, y, x); 
			if((temp = ft_strsplit(map[y][x], ',')) && init_px(&win->map[y][x]))
			{
				win->map[y][x].y = y;
				win->map[y][x].x = x;
				//win->map[y][x].z = ft_atoi(temp[0]);
				//if (arr_len(temp) > 1)
				//	parse_color_to(temp[1], win, y, x);
				free_arr(temp);
			}		//printf(" prsPX: x = %f, y = %f, z = %f, col=%d\n", px->x, px->y, px->z, px->color);
		printf(" prsPX: y = %f, x = %f, z = %f, col=%d\n", win->map[y][x].y, win->map[y][x].x, win->map[y][x].z, win->map[y][x].color);
			x++;
		}
		y++;
	}
}

int		set_map_size(t_win *win, char ***temp)
{
	int		i;
	int		j;
	int		first;

	i = 0;
	first = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
			j++;
		if (first == 0)
			first = j;
		if (j != first)
			return (1);
		i++;
	}
	win->map_cols = i;
   	win->map_rows = j;
	//check tmp map width
	//check allowed symbol
	//need add validate on start func
	return (0);
}

t_win	*parse_map(char *file_name, t_win *win)
{
	int		i;
	int		fd;
	char	***temp;
	char	*buf;

	if ((temp = (char ***)malloc(sizeof(char **) * (win->len + 1))))
	{
		temp[win->len] = NULL;
		win->map_cols = 0;
		fd = open(file_name, O_RDONLY);
		i = -1;
		printf("len %d \n", win->len);
		while (get_next_line(fd, &buf) && (temp[++i] = ft_strsplit(buf, ' ')))
			ft_memdel((void *)&buf);
		if (set_map_size(win, temp) == 1)
			printf("map_invalid");
		//printf("val width  %d \t", win->map_cols);
		//printf("val height %d \t", win->map_rows);
		convert_map(win, temp, 0, 0);
		//free_arr***
		//free_arr(temp);
		close(fd);
	}
	return (win);
}


//  учесть возможность могих вайстпейсов между координатами
//void	draw_line_h(int start_x, int statr_y, int end_x, int end_y)
//{
//}
//void	draw_px(t_map *map_data)
//{
//}

void 	print_map(t_win *win)
{
	int	col;
	int	row;

	printf("rows=%d, cols=%d\n", win->map_rows, win->map_cols);
//	printf("x=%f, y=%f, z=%f", win->map[10][10].x, win->map[10][10].y, win->map[10][10].z);
	row = -1;
	while (win->map[++row] )
	{
		//ft_putnbr( win->map_rows);

	printf("cur rows=%d\n", row);
		col = 0;

		while ((void *)win->map[row][col] != NULL)
		{
	printf("cur cols=%d\n", col);
	//printf("%f\n",win->map[col][row].z);
			mlx_pixel_put(win->mlx_ptr, win->win_ptr,
				   	150 + (int)win->map[col][row].x * win->scale_x,
				   	500 + (int)win->map[col][row].y * win->scale_y 
					    -((int)win->map[col][row].z * win->scale_z),
				   	0x009100FF);
				   	//win->offset_x + (col * win->scale_x),
				   	//win->offset_y + (row * win->scale_y)
				  	//- (win->map[row][col].z) * win->scale_z, 
					// win->map[row][col].color);
			col++;
		}
		printf("\n");
	}
}

int		exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_win	*win;

	if (argc == 2)
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
			win->len = ln_in_file(argv[1]);
		}
		if((win->map = (t_px **)malloc(sizeof(t_px *) * (win->len + 1))))
		{
			win->map[win->len] = NULL;
			//printf("%p\n", win_ptr);
			//printf("%d\n", ln_in_file(argv[1]));
			parse_map(argv[1], win);
			print_map(win);
		}
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, 5, 5, 0x009100FF);
		mlx_string_put(win->mlx_ptr, win->win_ptr, 5, 5, 0x009100FF, "str");
  //int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
		mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
		mlx_loop(win->mlx_ptr);
	}
	//system("leaks ./fdf");
	return (0);
}
