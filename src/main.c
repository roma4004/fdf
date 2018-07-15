/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/15 23:21:39 by dromanic         ###   ########.fr       */
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
	|| ch == 'F' || ch == 'f')
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

	if (!win || !(cur = lst) || (y = -1))
		return ;
	if ((win->map = (t_px **)malloc(sizeof(t_px *) * win->map_rows)))
	{
		while (cur && cur->content && (str = (char *)cur->content))
		{
			x = 0;
			i = -1;
			win->map[++y] = (t_px *)malloc(sizeof(t_px) * win->map_cols);
			while (++i < cur->content_size)
			{
				win->map[y][x].y = y;
				win->map[y][x].x = x;
				win->map[y][x].z = i_atoi(str, &i, cur->content_size);
				win->map[y][x++].color = parse_color_to(str + i, &i, cur->content_size); //printf(" prsPX: y = %f, x = %f, z = %f, col=%d\n", win->map[y][x].y, win->map[y][x].x, win->map[y][x].z, win->map[y][x].color);
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
	printf("rows=%zu\n",win->map_rows);
	printf("cols=%zu\n",win->map_cols);
	convert_map(win, lst);//need refactor convert_map   char *** to char **
	close(fd);
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
	size_t	col;
	size_t	row;

	printf("rows=%zu, cols=%zu\n", win->map_rows, win->map_cols);
//	printf("x=%f, y=%f, z=%f", win->map[10][10].x, win->map[10][10].y, win->map[10][10].z);
	row = -1;
	while (win->map[++row] )
	{
		//ft_putnbr( win->map_rows);

	printf("cur rows=%zu\n", row);
		col = 0;

		while (col < win->map_cols)
		{
	printf("cur cols=%zu\n", col);
	//printf("%f\n",win->map[col][row].z);
			mlx_pixel_put(win->mlx_ptr, win->win_ptr,
				   	150 + (int)win->map[col][row].x * win->scale_x,
				   	500 + (int)win->map[col][row].y * win->scale_y 
					    -((int)win->map[col][row].z * win->scale_z),
				   	DEF_COLOR);
				   	//win->offset_x + (col * win->scale_x),
				   	//win->offset_y + (row * win->scale_y)
				  	//- (win->map[row][col].z) * win->scale_z, 
					// win->map[row][col].color);
			col++;
		}
		printf("\n");
	}
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
		
			//printf("%p\n", win_ptr);
			//printf("%d\n", ln_in_file(argv[1]));
			parse_map(argv[1], win);
			//	print_map(win);
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
