/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experimental_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:27:10 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 14:27:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void	set_start_if_max(t_line *l, double new_y, double new_x){	if (l->start_y < new_y)	l->start_y = new_y;
																	if (l->start_x < new_x)	l->start_x = new_x;}
void	set_end_if_max  (t_line *l, double new_y, double new_x){	if (l->end_y   < new_y)	l->end_y   = new_y;
																	if (l->end_x   < new_x)	l->end_x   = new_x;}
void	set_start_if_min(t_line *l, double new_y, double new_x){	if (l->start_y > new_y)	l->start_y = new_y;
																	if (l->start_x > new_x)	l->start_x = new_x;}
void	set_end_if_min  (t_line *l, double new_y, double new_x){	if (l->end_y   > new_y)	l->end_y   = new_y;
																	if (l->end_x   > new_x)	l->end_x   = new_x;}

void	set_start_if_max_y	(t_line *l, double new){ if (l->start_y < new)	l->start_y = new;}
void	set_start_if_max_x	(t_line *l, double new){ if (l->start_x < new)	l->start_x = new;}
void	set_end_if_max_y	(t_line *l, double new){ if (l->end_y   < new)	l->end_y   = new;}
void	set_end_if_max_x	(t_line *l, double new){ if (l->end_x   < new)	l->end_x   = new;}
void	set_start_if_min_y 	(t_line *l, double new){ if (l->start_y > new)	l->start_y = new;
														if (l->start_y == 0) 	l->start_y = new;}
void	set_start_if_min_x	(t_line *l, double new){ if (l->start_x > new)	l->start_x = new;
														if (l->start_x == 0) 	l->start_x = new;}
void	set_end_if_min_y	(t_line *l, double new){ if (l->end_y   > new)	l->end_y   = new;}
void	set_end_if_min_x	(t_line *l, double new){ if (l->end_x   > new)	l->end_x   = new;}

void	get_top_line(t_line *l, double new_y, double new_x)
{
	set_start_if_min_y(l, new_y);
	set_start_if_min_x(l, new_x);
	set_end_if_min_y(l, new_y);
	set_end_if_max_x(l, new_x);
}

void	get_bottom_line(t_line *l, double new_y, double new_x)
{
	set_start_if_max_y(l, new_y);
	set_start_if_min_x(l, new_x);	
	set_end_if_max_y(l, new_y);
	set_end_if_max_x(l, new_x);
}

void	get_left_line(t_line *l, double new_y, double new_x)
{
	set_start_if_min_y(l, new_y);
	set_start_if_min_x(l, new_x);	
	set_end_if_max_y(l, new_y);
	set_end_if_min_x(l, new_x);
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
	t_line	*l;
	size_t	y;
	size_t	x;
	size_t	tmp_y;
	size_t	tmp_x;
print_map(win);
	t_line *frame_top_line;
	t_line *frame_left_line;
	t_line *frame_right_line;
	t_line *frame_bottom_line;
	l = (t_line *)malloc(sizeof(t_line));
	frame_top_line = (t_line *)malloc(sizeof(t_line));
	frame_left_line = (t_line *)malloc(sizeof(t_line));
	frame_right_line = (t_line *)malloc(sizeof(t_line));
	frame_bottom_line = (t_line *)malloc(sizeof(t_line));
	init_line(l);
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