/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/04/28 16:45:56 by dromanic         ###   ########.fr       */
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
		if (str != NULL)
		{
			free(str);
			str = NULL;
		}
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

int		parse_color(char *hex)
{
	if (hex == NULL || ft_strlen(hex) > 8 || hex[0] != '0' || hex[1] != 'x')
	{
		printf("%zu\n", ft_strlen(hex) );
		return (0xffffff); //default color will be macros
	}
	return (ch2int(hex[2]) * 1048576
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
		{
			if (arr[i] != NULL)
				free(arr[i]);
			arr[i++] = NULL;
		}
		if (arr != NULL)
			free(arr);
		arr = NULL;
	}
}

t_px	*parse_px(char *z_dt, int y, int x)
{
	t_px *px;
	char **temp;

	if ((px = (t_px *)malloc(sizeof(t_px))))
	{
		px->x = x;
		px->y = y;
		if((temp = ft_strsplit(z_dt, ',')))
		{
			px->z = ft_atoi(temp[0]);
			px->color = parse_color(temp[1]);
		}
		free_arr(temp);
	}
	return (px);
}

void	convert_map_and_free(t_win *win, char ***map)
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
			win->map[y] = parse_px(map[y][x], y, x);
			if (map != NULL)
			{
				free(map[y]);
				map[y] = NULL;
			}
			x++;
		}
		if (map != NULL)
			free(map);
			map = NULL;
		y++;
	}
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
		fd = open(file_name, O_RDONLY);
		i = 0;
		while (get_next_line(fd, &buf))
		{
			temp[i++] = ft_strsplit(buf, ' ');
			if (buf != NULL)
				free(buf);
		}
		convert_map_and_free(win, temp);
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
//---->>>		//printf("%f",win->map[y][x].z);

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
			win->width = 1024;   //will be macros
			win->height = 768;
			win->offset_x = 50;
			win->offset_y = 50;
			win->scale_x = 20;
			win->scale_y = 20;
			win->scale_z = 20;
			win->mlx_ptr = mlx_init();
			win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->height, "I Am minilibX"); //name will be macros
		}
		if((win->map = (t_px **)malloc(sizeof(t_px *) * win->len)))
		{
			win->len = ln_in_file(argv[1]);
			win->map[win->len] = 0;
			printf("%d", parse_color("0x012def"));
		
			//printf("%p\n", win_ptr);
			//printf("%d\n", ln_in_file(argv[1]));
		//	print_map(parse_map(argv[1], win));
		}
	//	mlx_pixel_put(mlx_ptr, win_ptr, 5, 5, 0x009100FF);
	//	mlx_string_put(mlx_ptr, win_ptr, 5, 5, 0x009100FF, "str");
//		mlx_loop(win->mlx_ptr);
	}
	return (0);
}
