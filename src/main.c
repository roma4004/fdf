/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/06/05 11:39:18 by dromanic         ###   ########.fr       */
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

void	parse_color_to(char *hex, t_px *px)
{
	if (!hex || !px || ft_strlen(hex) > 8 || hex[0] != '0' || hex[1] != 'x')
		return ;
	px->color = (ch2int(hex[2]) * 1048576
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

	if (arr == NULL || *arr == NULL)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int		init_px(t_px *px)
{
	if (px == NULL)
		return (1);
	px->x = 0;
	px->y = 0;
	px->z = 0;
	px->color = DEF_COLOR;
	return (0);
}

t_px	*parse_px(char *z_dt, int y, int x)
{
	t_px *px;
	char **temp;
//z_dt = NULL;
//temp = NULL;
	printf("input parsePX, z=%s y=%d x=%d", z_dt, y, x);
	if ((px = (t_px *)malloc(sizeof(t_px))))
	{
		init_px(px);
		px->x = x;
		px->y = y;
		//printf("prsPX: x = %f, y = %f", px->x, px->y);

		if((temp = ft_strsplit(z_dt, ',')))
		{
			px->z = ft_atoi(temp[0]);
			if (arr_len(temp) > 1)
				parse_color_to(temp[1], px);
			//printf("prsPX: z = %f, color = %0x", px->z, px->color);
		//	printf("prsPX: z = %f, color = %0x", px->z, px->color);
		}
		free_arr(temp);
	}
	return (px);
}

void	convert_map(t_win *win, char ***map)
{
	int		y;
	int		x;

	if (win == NULL || map == NULL)
		return ;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			//segfaul in this func or in parse_px
			//need test this part
			win->map[y][x] = parse_px(map[y][x], y, x);
		
			x++;
		}
		y++;
	}
}

t_win	*parse_map_to(char *file_name, t_win *win)
{
	int		i;

	int		j;
	int		fd;
	char	***temp;
	char	*buf;

	if ((temp = (char ***)malloc(sizeof(char **) * (win->len + 1))))
	{
		temp[win->len] = NULL;
		fd = open(file_name, O_RDONLY);
		i = -1;
		while (get_next_line(fd, &buf))
		{
			temp[++i] = ft_strsplit(buf, ' ');
			j = -1;
			while (temp[i] && temp[i][++j])
				printf("%s \t", temp[i][j]);
			printf("\n");
			ft_memdel((void *)&buf);
		}
		convert_map(win, temp);
		free_arr(temp);
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
	int	y;
	int	x;

	y = -1;
	while (win->map[++y])
	{
		x = 0;
		printf("%f\n",win->map[y][x]->z);

		//while (win->map[y][x].z != -1)
		//{
		//	mlx_pixel_put(win->mlx_ptr, win->win_ptr,
		//			win->offset_x + (x * win->scale_x), 
		//			win->offset_y + (y * win->scale_y)
		//		  	- (win->map[y][x].z) * win->scale_z, 0x009100FF); //win->map[y][x].color);
	//		x++;
	//	}	//printf("%d ", ft_atoi(map[y][x++]));
		printf("\n");
	}
}

/*int		exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}*/

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
		if((win->map = (t_px ***)malloc(sizeof(t_px **) * win->len + 1)))
		{
			win->map[win->len] = NULL;
			//printf("%p\n", win_ptr);
			//printf("%d\n", ln_in_file(argv[1]));
			//print_map(parse_map(argv[1], win));
			parse_map_to(argv[1], win);
		}
	//	mlx_pixel_put(mlx_ptr, win_ptr, 5, 5, 0x009100FF);
	//	mlx_string_put(mlx_ptr, win_ptr, 5, 5, 0x009100FF, "str");
	//	mlx_loop(win->mlx_ptr);
	}
	//system("leaks ./fdf");
	return (0);
}
