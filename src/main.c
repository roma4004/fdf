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

void	draw_line_map_diag_v2(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = (t_line *)malloc(sizeof(t_line))) )
		return ;
		y = -1;
	while (++y < win->map_rows-1)
	{
		x = -1;
		while (++x < win->map_cols-1)
		{
			line->end_y = 150 +  win->map[y +1][x +1 ].y * (win->sc_y)
			                -  win->map[y   ][x    ].z * (win->sc_z); 
			line->end_x = 150 +  win->map[y +1][x +1 ].x * (win->sc_x);
			draw_line(win, line, 150 + (win->map[y][x].y) * (win->sc_y)
							-  win->map[y][x].z  * (win->sc_z), 
						150 + (win->map[y][x].x) * (win->sc_x), DEF_COLOR);
	
		}		
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

void	draw_map(t_win *win)
{
	if (win->fdf_on)
		draw_map_fdf(win, win->offset_y, win->offset_x, win->con_on);
	if (win->ver_on)	
		draw_map_vertical(win, win->offset_y, win->offset_x, win->con_on);
	if (win->sla_on)	
		draw_map_slash(win, win->offset_y, win->offset_x, win->con_on);					
	if (win->hor_on)
		draw_map_horizontal(win, win->offset_y, win->offset_x, win->con_on);
	if (win->bsl_on)
		draw_map_backslash(win, win->offset_y, win->offset_x, win->con_on);
}

int		main(int argc, char **argv)
{
	t_win	*win;

	if (argc == 2) //add parsing multi map
	{
		if((win = (t_win *)malloc(sizeof(t_win))))
		{
			init_win(win);			
			//print_map(parse_map(argv[1], win));			
			//draw_line_map(parse_map(argv[1], win));
			//draw_line_map_diag_v2(parse_map(argv[1], win));			
			parse_map(argv[1], win);
			draw_line_map_diag_v2(win);
			//draw_map(win);

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
			mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);

			//mlx_key_hook(win->win_ptr, deal_key, (win));
			mlx_mouse_hook(win->win_ptr, deal_mouse, win);
			//mlx_clear_window(map->mlx, map->win);
			mlx_loop(win->mlx_ptr);


		}
	}
	//system("leaks ./fdf");
	return (0);
}
