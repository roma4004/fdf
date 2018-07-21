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

void	free_map(t_win *win)
{
	int	i;
	int j;

	if (win)
	{
		i = 0;
		while (i < win->map_rows)
		{
			while (j < win->map_cols)
			{
				ft_memdel((void *)&win->map[i][j++]);
			}
		ft_memdel((void *)&win->map[i++]);
		}
		ft_memdel((void*)&win->map);
	}
}

void 	print_map(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
/*
	line->end_y = 500;
	line->end_x = 500;
	draw_line(win, line, 100, 100, DEF_COLOR);

	line->end_y = 600;
	line->end_x = 150;
	draw_line(win, line, 100, 500, DEF_COLOR);

	line->end_y = 200;
	line->end_x = 200;
	draw_line(win, line, 200, 500, DEF_COLOR);

	line->end_y = 200;
	line->end_x = 200;
	draw_line(win, line, 500, 200, DEF_COLOR);
*/
	y = 0;
	while (y < win->map_rows)
	{
		x = 0;
		while (x < win->map_cols)
			draw_px_by_map(win, y, x++);
		y++;
	}
	free(line);
}

void	draw_line_map_diag_v2(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 1;
	while (y < win->map_rows )
	{
		x = 1;
		while (x < win->map_cols)
		{
			line->end_y = 150 +  win->map[y -1][x -1 ].y  * (win->sc_y)
			                  -  win->map[y   ][x  ].z  * (win->sc_z); 
			line->end_x = 150 +  win->map[y -1][x -1 ].x  * (win->sc_x);
			draw_line(win, line, 						  
						  150 + (win->map[y ][x ].y) * (win->sc_y)
							  -  win->map[y ][x    ].z    * (win->sc_z), 
						  150 + (win->map[y ][x  ].x) * (win->sc_x), DEF_COLOR);
			x++;
		}
		y++;
	}
}
void	draw_line_map_diag_v2_1(t_win *win)
{

	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 1;
	while (y < win->map_rows)
	{
		x = 1;
		while (x < win->map_cols)
		{
			line->end_x = 150 + win->map[y][x].y * (win->sc_y) - win->map[y][x].z * (win->sc_z); 
			line->end_y = 150 + win->map[y][x].x * (win->sc_x);
			draw_line(win, line, 150 + (x - 1) * (win->sc_x), 150 + (y - 1) * (win->sc_y)- win->map[y - 1][x - 1].z * (win->sc_z), DEF_COLOR);
			x++;
		}
		y++;
	}
}
void	draw_line_map(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 0;
	while (y < win->map_rows)
	{
		x = 0;
		while (x < win->map_cols)
		{
			line->end_x = win->offset_y + win->map[y + 1][x + 1].y * (win->sc_y) - win->map[y + 1][x + 1].z * (win->sc_z); 
			line->end_y = win->offset_x + win->map[y + 1][x + 1].x * (win->sc_x);
			draw_line(win, line, win->offset_x + (x) * (win->sc_x), win->offset_y + (y) * (win->sc_y) - win->map[y][x].z * (win->sc_z), DEF_COLOR);
			x++;
		}
		y++;
	}
}

void	init_line(t_line *line)
{
	if (line != NULL)
	{
		line->start_x = 0;
		line->start_y = 0;
		line->end_x = 0;
		line->end_y = 0;
		line->len_y = 0;
		line->len_x = 0;
		line->len = 0;
		line->dy = 0;
		line->dx = 0;
		line->y = 0;
		line->x = 0;
		line->d = 0;
	}
}

void	multi_init_line(t_line *l1, t_line *l2, t_line *l3, t_line *l4)
{
	if (l1 != NULL)
		init_line(l1);
	if (l2 != NULL)
		init_line(l2);
	if (l3 != NULL)
		init_line(l3);
	if (l4 != NULL)
		init_line(l4);
}

void	set_start_if_max(t_line *line, double new_y, double new_x){	if (line->start_y < new_y)	line->start_y = new_y;
																	if (line->start_x < new_x)	line->start_x = new_x;}
void	set_end_if_max  (t_line *line, double new_y, double new_x){	if (line->end_y   < new_y)	line->end_y   = new_y;
																	if (line->end_x   < new_x)	line->end_x   = new_x;}
void	set_start_if_min(t_line *line, double new_y, double new_x){	if (line->start_y > new_y)	line->start_y = new_y;
																	if (line->start_x > new_x)	line->start_x = new_x;}
void	set_end_if_min  (t_line *line, double new_y, double new_x){	if (line->end_y   > new_y)	line->end_y   = new_y;
																	if (line->end_x   > new_x)	line->end_x   = new_x;}

void	set_start_if_max_y	(t_line *line, double new){ if (line->start_y < new)	line->start_y = new;}
void	set_start_if_max_x	(t_line *line, double new){ if (line->start_x < new)	line->start_x = new;}
void	set_end_if_max_y	(t_line *line, double new){ if (line->end_y   < new)	line->end_y   = new;}
void	set_end_if_max_x	(t_line *line, double new){ if (line->end_x   < new)	line->end_x   = new;}
void	set_start_if_min_y 	(t_line *line, double new){ if (line->start_y > new)	line->start_y = new;
														if (line->start_y == 0) 	line->start_y = new;}
void	set_start_if_min_x	(t_line *line, double new){ if (line->start_x > new)	line->start_x = new;
														if (line->start_x == 0) 	line->start_x = new;}
void	set_end_if_min_y	(t_line *line, double new){ if (line->end_y   > new)	line->end_y   = new;}
void	set_end_if_min_x	(t_line *line, double new){ if (line->end_x   > new)	line->end_x   = new;}

void	get_top_line(t_line *line, double new_y, double new_x)
{
	set_start_if_min_y(line, new_y);
	set_start_if_min_x(line, new_x);
	set_end_if_min_y(line, new_y);
	set_end_if_max_x(line, new_x);
}

void	get_bottom_line(t_line *line, double new_y, double new_x)
{
	set_start_if_max_y(line, new_y);
	set_start_if_min_x(line, new_x);	
	set_end_if_max_y(line, new_y);
	set_end_if_max_x(line, new_x);
}

void	get_left_line(t_line *line, double new_y, double new_x)
{
	set_start_if_min_y(line, new_y);
	set_start_if_min_x(line, new_x);	
	set_end_if_max_y(line, new_y);
	set_end_if_min_x(line, new_x);
}

void	get_right_line(t_line *line, double new_y, double new_x)
{
	set_start_if_min_y(line, new_y);
	set_start_if_max_x(line, new_x);	
	set_end_if_max_y(line, new_y);
	set_end_if_max_x(line, new_x);
}

void	print_map_frame(t_win *win)
{	//обойти все точки выбрать из них левую верхнюю, правую верхнюю, нижнюю левую, правую левую
	t_line	*line;
	size_t	y;
	size_t	x;
	size_t	tmp_y;
	size_t	tmp_x;
print_map(win);
	t_line *frame_top_line;
	t_line *frame_left_line;
	t_line *frame_right_line;
	t_line *frame_bottom_line;
	line = (t_line *)malloc(sizeof(t_line));
	frame_top_line = (t_line *)malloc(sizeof(t_line));
	frame_left_line = (t_line *)malloc(sizeof(t_line));
	frame_right_line = (t_line *)malloc(sizeof(t_line));
	frame_bottom_line = (t_line *)malloc(sizeof(t_line));
	init_line(line);
	multi_init_line(frame_top_line, frame_left_line, frame_right_line, frame_bottom_line);

	y = 0;
	while (y < win->map_rows)
	{
		x = 0;
		while (x < win->map_cols)
		{
			tmp_y = win->offset_y + win->map[y][x].y * (win->sc_y) - win->map[y][x].z * (win->sc_z); 
			tmp_x = win->offset_x + win->map[y][x].x * (win->sc_x);			
			get_top_line(frame_top_line, tmp_y, tmp_x);
			get_left_line(frame_left_line, tmp_y, tmp_x);
			get_right_line(frame_right_line, tmp_y, tmp_x);
			get_bottom_line(frame_bottom_line, tmp_y, tmp_x);
			x++;
		}
		y++;
	}
	draw_line(win, frame_top_line, frame_top_line->start_y, frame_top_line->start_x, DEF_COLOR);
	draw_line(win, frame_left_line, frame_left_line->start_y, frame_left_line->start_x, DEF_COLOR);
	draw_line(win, frame_right_line, frame_right_line->start_y, frame_right_line->start_x, DEF_COLOR);
	draw_line(win, frame_bottom_line, frame_bottom_line->start_y, frame_bottom_line->start_x, DEF_COLOR);
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
			win->offset_x = WIN_OFFSET_X;
			win->offset_y = WIN_OFFSET_Y;
			win->sc_x = WIN_SCALE;
			win->sc_y = WIN_SCALE;
			win->sc_z = WIN_SCALE;
			win->mlx_ptr = mlx_init();
			win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->height, WIN_NAME);
			//print_map(parse_map(argv[1], win));			
			//draw_line_map(parse_map(argv[1], win));
			//draw_line_map_diag_v2(parse_map(argv[1], win));
			parse_map(argv[1], win);
			draw_line_map_fdf(win);
			
			//draw_line_map_vertical(win, 150, 150, 0);
			//draw_line_map_slash(win, 150, 150, 0);					
			//draw_line_map_horizontal(win, 150, 150, 0);
			//draw_line_map_backslash(win, 150, 150, 0);
			
			
			//при выводе 4 эффектов, добавлять погрешность
			//по нажатию на кнопку накручивать число которое прибвалять в качестве смещения, что бы эти 4 эффекта разъезжались

			//print_map_frame(parse_map(argv[1], win));
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
